/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum custom_layers {
    _BL,
    _FL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT_65_ansi_blocker(
  QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_PGDN,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT_65_ansi_blocker(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    _______,  KC_INS,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
  _______,  RM_HUEU,  RM_HUED,  RM_SPDD,  RM_SPDU,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,             RM_VALU,  KC_HOME,
  QK_BOOT,  _______,  _______,                                _______,                                _______,  _______,  RM_PREV,  RM_VALD,  RM_NEXT
  )
};





#ifdef RGB_MATRIX_ENABLE

static void set_rgb_caps_leds(void);
static uint8_t get_current_brightness(void);
static uint8_t get_flipped_hue(void);
static void set_rgb_scroll_lock_leds(void);


uint8_t CAPS_LOCK_LEDS[] = {
     30, //CAPS
};

uint8_t SCROLL_LOCK_LEDS[] = {
};


static uint8_t get_current_brightness(){
     uint8_t value = rgblight_get_val();
     if(value < 64){
        value = 192;
     }else if(value < 128){
        value = 128;
     }
     return value;
}

static uint8_t get_flipped_hue(){
    uint8_t hue = rgblight_get_hue();
    uint8_t value = hue + 127;
    if(value > 255){
        return value - 255;
    }
    return value;
}



static void set_rgb_caps_leds(){

     HSV hsv = {get_flipped_hue(), rgblight_get_sat(), get_current_brightness()};
     RGB rgb = hsv_to_rgb(hsv);
    for(uint8_t i=0; i < sizeof(CAPS_LOCK_LEDS); i++ ){
        rgb_matrix_set_color(CAPS_LOCK_LEDS[i], rgb.r, rgb.g, rgb.b);
    }
}


static void set_rgb_scroll_lock_leds(){

     HSV hsv = {get_flipped_hue(), rgblight_get_sat(), get_current_brightness()};
     RGB rgb = hsv_to_rgb(hsv);
    for(uint8_t i=0; i < sizeof(SCROLL_LOCK_LEDS); i++ ){
        rgb_matrix_set_color(SCROLL_LOCK_LEDS[i], rgb.r, rgb.g, rgb.b);
    }
}



bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
         set_rgb_caps_leds();
    }

        if (host_keyboard_led_state().scroll_lock) {
         set_rgb_scroll_lock_leds();
    }

    return false;
}
#endif //RGB_MATRIX_ENABLE
