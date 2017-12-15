/*

Copyright (c) 2016 D. F. Hall

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject
to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP(F1,   F2,   F3,   F4,   F5,  F6,   F7,    F8,   F9,   F10,  F11,  F12,  \
           GRV,  1,    2,    3,    4,   5,    6,     7,    8,    9,    0,    EQL,  \
           MINS, Q,    W,    E,    R,   T,    Y,     U,    I,    O,    P,    BSLS , \
           CAPS, A,    S,    D,    F,   G,    H,     J,    K,    L,    SCLN, QUOT, \
           LSFT, Z,    X,    C,    V,   B,    N,     M,    COMM, DOT,  SLSH, RSFT, \
           LCTL, LALT, LGUI, LBRC, ESC, HOME, RIGHT, DEL,  RBRC, RGUI, RALT, RCTL, \
           BSPC,  TAB,  PGDN, PGUP, END, NO,   NO,    LEFT, UP,   DOWN, ENT, SPC),
};

const uint16_t PROGMEM fn_actions[] = {};
