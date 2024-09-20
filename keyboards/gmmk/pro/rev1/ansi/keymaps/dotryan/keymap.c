 /*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Del           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Home
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        RGB_TOG, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_INS,           _______,
        _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, KC_DEL,           KC_SCRL,
        _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, KC_APP , _______, _______, KC_SCRL,          _______, KC_PGUP, _______,
        _______, GU_TOGG, _______,                            KC_PSCR,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),


};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(1)){
        if (clockwise) {
            rgblight_increase_val();
        }else{
            rgblight_decrease_val();
        }
    }else{
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
              tap_code(KC_VOLD);
        }   
    }
    
    return false;
}

#endif // ENCODER_ENABLE



#ifdef RGB_MATRIX_ENABLE
static void set_rgb_caps_leds(void);
static uint8_t get_current_brightness(void);
static uint8_t get_flipped_hue(void);
static void set_rgb_scroll_lock_leds(void);
static void set_no_gui_leds(void);


// RGB led number layout, function of the key

//  67, led 01   0, ESC    6, F1      12, F2      18, F3   23, F4   28, F5      34, F6   39, F7   44, F8      50, F9   56, F10   61, F11    66, F12    69, Prt       Rotary(Mute)   68, led 12
//  70, led 02   1, ~      7, 1       13, 2       19, 3    24, 4    29, 5       35, 6    40, 7    45, 8       51, 9    57, 0     62, -_     78, (=+)   85, BackSpc   72, Home       71, led 13
//  73, led 03   2, Tab    8, Q       14, W       20. E    25, R    30, T       36, Y    41, U    46, I       52, O    58, P     63, [{     89, ]}     93, \|        75, PgUp       74, led 14
//  76, led 04   3, Caps   9, A       15, S       21, D    26, F    31, G       37, H    42, J    47, K       53, L    59, ;:    64, '"                96, Enter     86, PgDn       77, led 15
//  80, led 05   4, Sh_L   10, Z      16, X       22, C    27, V    32, B       38, N    43, M    48, ,<      54, .<   60, /?               90, Sh_R   94, Up        82, End        81, led 16
//  83, led 06   5, Ct_L   11,Win_L   17, Alt_L                     33, SPACE                     49, Alt_R   55, FN             65, Ct_R   95, Left   97, Down      79, Right      84, led 17
//  87, led 07                                                                                                                                                                      88, led 18
//  91, led 08     

uint8_t CAPS_LOCK_LEDS[] = {
     6, //F1
    12, //F2 
    18, //F3
    23, //F4
    28, //F5
    34, //F6
    39, //F7
    44, //F8
    50, //F9
    56, //F10
    61, //F11
    66  //F12
};

uint8_t SCROLL_LOCK_LEDS[] = {
    72, //Home 
    75, //PgUp 
    86, //PgDn 
    82, //End  
    68, //led 12
    71, //led 13
    74, //led 14
    77, //led 15
    81, //led 16
    84, //led 17
    88, //led 18
};

uint8_t NO_GUI_LEDS[] = {
    5, //Ct_L 
    11, //Home
    17, //Alt_L    
    14, //W
    9, //A
    15, //S
    21, //D
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


static void set_no_gui_leds(){

     HSV hsv = {get_flipped_hue(), rgblight_get_sat(), get_current_brightness()};
     RGB rgb = hsv_to_rgb(hsv);
    for(uint8_t i=0; i < sizeof(NO_GUI_LEDS); i++ ){
        rgb_matrix_set_color(NO_GUI_LEDS[i], rgb.r, rgb.g, rgb.b);
    }
}



bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
         set_rgb_caps_leds();
    }

        if (host_keyboard_led_state().scroll_lock) {
         set_rgb_scroll_lock_leds();
    }


    if(keymap_config.no_gui){
        set_no_gui_leds();
    }

    return false;
 // color only the leds that have an FN key pressed
 // if (get_highest_layer(layer_state) > 0) {
 //        uint8_t layer = get_highest_layer(layer_state);

 //        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
 //            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
 //                uint8_t index = g_led_config.matrix_co[row][col];


 //                if (index >= led_min && index <= led_max && index != NO_LED &&
 //                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
 //                    rgb_matrix_set_color(index, RGB_PURPLE);
 //                }
 //            }
 //        }
 //    }

}


#endif //RGB_MATRIX_ENABLE



