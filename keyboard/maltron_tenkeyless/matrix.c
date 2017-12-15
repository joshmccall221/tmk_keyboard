/*
  Copyright 2012 Jun Wako <wakojun@gmail.com>
  Copyright 2016 D. F. Hall
  Copyright 2017 D. F. Hall

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


static uint8_t DEBOUNCE_INDEX = 0;
static double DEBOUNCE_SAMPLE_DELAY = (double)DEBOUNCE_SAMPLE_WINDOW / (double)DEBOUNCE_MAX_SAMPLES;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_2d_debouncing[MATRIX_ROWS][DEBOUNCE_MAX_SAMPLES];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

inline
uint8_t matrix_rows(void)
{
  return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
  return MATRIX_COLS;
}

void matrix_init(void)
{
  /* To enable I/O on Port F, turn off JTAG
     by writing value twice within 4 clock cycles.
     Use tmp to avoid compiler optimizations that
     use more than 4 clock cycles. */
  uint8_t Qp = MCUCR;
  Qp |= (1<<JTD); 
    
  MCUCR = Qp;
  MCUCR = Qp;

  // initialize row and col
  unselect_rows();
  init_cols();

  // initialize matrix state: all keys off
  // create false state history with no keys pressed
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    for(uint8_t j=0; j < DEBOUNCE_MAX_SAMPLES; j++) {
      matrix_2d_debouncing[i][j] = 0;
    }
  }
}

/* Based on algorithm from: http://www.eng.utah.edu/~cs5780/debouncing.pdf */
uint8_t matrix_scan(void)
{

  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {

    select_row(i);
    _delay_us(30);  // without this wait read unstable value.
    matrix_row_t cols = read_cols();
    unselect_rows();

    matrix_2d_debouncing[i][DEBOUNCE_INDEX] = cols;
  }

  DEBOUNCE_INDEX++;

  if (DEBOUNCE_INDEX >= DEBOUNCE_MAX_SAMPLES) {
    DEBOUNCE_INDEX = 0;
  }

  for (uint8_t i=0; i < MATRIX_ROWS; i++) {

    matrix[i] ^= matrix[i]; // xor to all 0s
    matrix[i] = ~matrix[i]; 

    for(uint8_t j=0; j < DEBOUNCE_MAX_SAMPLES; j++) {
      matrix[i] &= matrix_2d_debouncing[i][j];
    }
  }
    
  /* will call _delay_ms() instead
     if arg > ( 768 / CPU_FREQ_IN_MHz ) */
  _delay_us(DEBOUNCE_SAMPLE_DELAY);

  return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
  return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  print("\nr/c 0123456789AB\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row); print(": ");
    pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

uint8_t matrix_key_count(void)
{
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += bitpop16(matrix[i]);
  }
  return count;
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11
 * pin: B0  B1  B2  B3  B4  B5  B6  B7  F4  F7  F5  F6  
 */
static void  init_cols(void)
{
  // Input with pull-up(DDR:0, PORT:1)
  DDRF  &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4);
  PORTF |=  (1<<7 | 1<<6 | 1<<5 | 1<<4);
  DDRB  &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
  PORTB |=  (1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
}

static matrix_row_t read_cols(void)
{
  return (
    #ifdef HW_REV_1
    (PINF&(1<<7) ? 0 : ((matrix_row_t)1<<11)) |
    (PINF&(1<<6) ? 0 : ((matrix_row_t)1<<10)) |
    (PINF&(1<<5) ? 0 : ((matrix_row_t)1<<9)) |
    #else
    (PINF&(1<<6) ? 0 : ((matrix_row_t)1<<11)) |
    (PINF&(1<<5) ? 0 : ((matrix_row_t)1<<10)) |
    (PINF&(1<<7) ? 0 : ((matrix_row_t)1<<9)) |
    #endif
    (PINF&(1<<4) ? 0 : ((matrix_row_t)1<<8)) |
    (PINB&(1<<7) ? 0 : ((matrix_row_t)1<<7)) |
    (PINB&(1<<6) ? 0 : ((matrix_row_t)1<<6)) |
    (PINB&(1<<5) ? 0 : ((matrix_row_t)1<<5)) |
    (PINB&(1<<4) ? 0 : ((matrix_row_t)1<<4)) |
    (PINB&(1<<3) ? 0 : ((matrix_row_t)1<<3)) |
    (PINB&(1<<2) ? 0 : ((matrix_row_t)1<<2)) |
    (PINB&(1<<1) ? 0 : ((matrix_row_t)1<<1)) |
    (PINB&(1<<0) ? 0 : ((matrix_row_t)1<<0)) );
}

/* Row pin configuration
 * row: 0   1   2   3   4   5   6
 * pin: D0  D1  D2  D3  D4  D5  D6 
 */
static void unselect_rows(void)
{
  // Hi-Z(DDR:0, PORT:0) to unselect
  DDRD  &= ~0b01111111;
  PORTD &= ~0b01111111;
}

static void select_row(uint8_t row)
{
  // Output low(DDR:1, PORT:0) to select
  switch (row) {
  case 0:
    DDRD  |= (1<<0);
    PORTD &= ~(1<<0);
    break;
  case 1:
    DDRD  |= (1<<1);
    PORTD &= ~(1<<1);
    break;
  case 2:
    DDRD  |= (1<<2);
    PORTD &= ~(1<<2);
    break;
  case 3:
    DDRD  |= (1<<3);
    PORTD &= ~(1<<3);
    break;
  case 4:
    DDRD  |= (1<<4);
    PORTD &= ~(1<<4);
    break;
  case 5:
    DDRD  |= (1<<5);
    PORTD &= ~(1<<5);
    break;
  case 6:
    DDRD  |= (1<<6);
    PORTD &= ~(1<<6);
    break;
  }
}
