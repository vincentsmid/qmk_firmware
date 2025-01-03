/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum cncpad_layers {
    _LAYER1,
    _LAYER2,
    _LAYER3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER1] = LAYOUT( KC_MUTE, KC_MPRV, KC_BRID, KC_MPLY, KC_BRIU, KC_MNXT, KC_MUTE, TO(_LAYER2) ),
    [_LAYER2] = LAYOUT( RGB_HUD, RGB_HUI, RGB_TOG, KC_4, KC_5, KC_6, KC_7, TO(_LAYER3) ),
    [_LAYER3] = LAYOUT( KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_DEL, TO(_LAYER1) ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _LAYER2:
            if (clockwise) {
                tap_code(KC_MS_WH_UP);
            } else {
                tap_code(KC_MS_WH_DOWN);
            }
            return true;
            break;
        case _LAYER3:
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
            return true;
            break;            
        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            return true;
            break;
    }   
}

#ifdef OLED_ENABLE
const char *read_logo(void);
void oled_task_user(void){
    switch (biton32(layer_state)){
        case _LAYER1:
            oled_write_ln_P(PSTR("LAYER 1"), false);
            break;
        case _LAYER2:
            oled_write_ln_P(PSTR("LAYER 2"), false);
            break;
        case _LAYER3:
            oled_write_ln_P(PSTR("LAYER 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
  oled_write(read_logo(), false);
}
#endif
