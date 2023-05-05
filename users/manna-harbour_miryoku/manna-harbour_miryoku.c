// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"
#include "features/layer_lock.h"

enum layers { MIRYOKU_LAYER_NAMES };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]   = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_BASE),
  [QWERTY] = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_ALTERNATIVES_BASE_QWERTY),
  [NAV]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_NAV),
  [MOUSE]  = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_MOUSE),
  [MEDIA]  = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_MEDIA),
  [NUM]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_NUM),
  [SYM]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_SYM),
  [FUN]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_FUN),
  [BUTTON] = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_BUTTON)
};

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(SYM, KC_ENT), LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(NAV, KC_SPC), LT(MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN1, KC_BTN3, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(thumbcombos_base_right, LT(FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN2),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif

/* -------------------------------------------------------------------------- */
/*                                 My changes                                 */
/* -------------------------------------------------------------------------- */

#define TOGGLE_KEYBOARD_LAYOUT KC_F13

enum combos {
  DH_CAPS_WORD,
  SPC_BSPC_TOGGLE_KEYBOARD_LAYOUT,
};
const uint16_t PROGMEM caps_word_combo[] = {LCAG_T(KC_D), LCAG_T(KC_H), COMBO_END};
const uint16_t PROGMEM toggle_layout_combo[] = {LT(NAV, KC_SPC), LT(SYM, KC_BSPC), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  [DH_CAPS_WORD] = COMBO(caps_word_combo, CAPSWRD),
  [SPC_BSPC_TOGGLE_KEYBOARD_LAYOUT] = COMBO(toggle_layout_combo, TOGGLE_KEYBOARD_LAYOUT),
};

struct language_state_t {
    bool is_colemak;
};
struct language_state_t language_state = {true};

struct os_state_t {
    bool is_mac_os;
};
struct os_state_t os_state = {true};

void toggle_os_language(void) {
    register_code(KC_LCTL);
    register_code(KC_LALT);
    register_code(KC_K);
    unregister_code(KC_K);
    unregister_code(KC_LALT);
    unregister_code(KC_LCTL);
}

void toggle_language_state(void) {
    language_state.is_colemak = !language_state.is_colemak;
    set_single_persistent_default_layer(language_state.is_colemak ? BASE : QWERTY);
}

void toggle_os_state(void) {
    os_state.is_mac_os = !os_state.is_mac_os;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
    switch(keycode) {
        case TOGGLE_KEYBOARD_LAYOUT:
            if (record->event.pressed) {
                toggle_language_state();
                toggle_os_language();
                return false;
            }
            break;

        case KC_F14:
            if (record->event.pressed) {
                toggle_os_state();
                return true;
            }
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // default behavior if undefined
    if (IS_LAYER_ON(MEDIA)) {
        if (index == 1) {
        #ifdef ENCODERS_B_REVERSE
            if (!clockwise) {
        #else
            if (clockwise) {
        #endif
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    } else {
        if (index == 0) {
            #ifdef ENCODERS_A_REVERSE
                if (!clockwise) {
            #else
                if (clockwise) {
            #endif
                tap_code16(C(KC_PGDN));
            } else {
                tap_code16(C(KC_PGUP));
            }
        } else if (index == 1) {
        #ifdef ENCODERS_B_REVERSE
            if (!clockwise) {
        #else
            if (clockwise) {
        #endif
                if (os_state.is_mac_os) {
                    tap_code16(A(KC_RGHT));
                } else {
                    tap_code16(C(KC_RGHT));
                }
            } else {
                if (os_state.is_mac_os) {
                    tap_code16(A(KC_LEFT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
            }
        }
    }

    return true;
}
#endif
