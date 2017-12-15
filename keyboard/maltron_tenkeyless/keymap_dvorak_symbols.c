/*

Copyright (c) 2017 D. F. Hall

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
    /* 0: dvorak */
    [0] = KEYMAP(F1,   F2,   F3,   F4,   F5,  F6,   F7,    F8,   F9,   F10,  F11,  F12,  \
           GRV,  1,    2,    3,    4,   5,    6,     7,    8,    9,    0,    EQL,  \
           BSLS, QUOT, COMM, DOT,  P,   Y,    F,     G,    C,    R,    L,    SLSH, \
           CAPS, A,    O,    E,    U,   I,    D,     H,    T,    N,    S,    MINS, \
           LSFT, SCLN, Q,    J,    K,   X,    B,     M,    W,    V,    Z,    RSFT, \
           LCTL, LALT, LGUI, FN0,  ESC, HOME, RIGHT, DEL,  FN0,  RGUI, RALT, RCTL, \
           SPC,  TAB,  PGDN, PGUP, END, NO,   NO,    LEFT, UP,   DOWN, ENT,  BSPC),
	/* 1: symbols */
    [1] = KEYMAP(NO, NO, NO,  NO,   NO,  NO,   NO,   NO,   NO,   NO,  NO, NO, \
           NO, NO, NO,  NO,   NO,  NO,   NO,   NO,   NO,   NO,  NO, NO, \
           NO, NO, NO,  FN7,  FN6, NO,   NO,   FN4,  FN5,  NO,  NO, NO, \
	   TRNS, NO, SLSH,  EQL,  FN1, GRV, NO, FN8,  FN9,  BSLS,  NO, NO, \
           NO, NO, NO,  FN3,  FN2, NO,   NO,   LBRC, RBRC, NO,  NO, NO, \
           NO, NO, NO,  TRNS, NO,  NO,   NO,   NO,   TRNS, NO,  NO, NO, \
           NO, NO, NO,  NO,   NO,  NO,   NO,   NO,   NO,   NO,  NO, NO),
};

const action_t PROGMEM fn_actions[] = {
/*	[0] = ACTION_LAYER_MODS(1, MOD_LSFT), */
	[0] = ACTION_LAYER_MOMENTARY(1),
	[1] = ACTION_MODS_KEY(MOD_LSFT, KC_SLSH),	/* question */
	[2] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),	/* pipe */
	[3] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),	/* tilde */
	[4] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC),	/* left bracket */
	[5] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),	/* right bracket */
	[6] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),	/* plus */
	[7] = ACTION_MODS_KEY(MOD_LSFT, KC_1),	/* excalamation */
	[8] = ACTION_MODS_KEY(MOD_LSFT, KC_9),	/* left paren */
	[9] = ACTION_MODS_KEY(MOD_LSFT, KC_0),	/* right paren */
};
