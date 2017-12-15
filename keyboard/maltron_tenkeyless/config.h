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


#ifndef CONFIG_H
#define CONFIG_H


/* USB Device descriptor parameter */
/* 0xFEED is already used by InterBiometrics ProgramGyar AVR-IR Sender    */
/* According to http://www.linux-usb.org/usb.ids 0xFADE is not take (yet) */
/* This, of course, means absolutely nothing.                             */
#define VENDOR_ID       0xFADE
#define PRODUCT_ID      0x7321
#ifdef HW_REV_1
#define DEVICE_VER      0x0001
#else
#define DEVICE_VER      0x0002
#endif
#define MANUFACTURER    dfhall
#define PRODUCT         Maltron Tenkeyless
#define DESCRIPTION     t.m.k. keyboard firmware for tenkeyless Maltron

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 12

#define DEBOUNCE_MAX_SAMPLES    10
/* The minimum period in micro seconds (u) of positive key press */
#define DEBOUNCE_SAMPLE_WINDOW  5000

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
