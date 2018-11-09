#include QMK_KEYBOARD_H
#include "pm.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   4  |   5  | Term |           | SWCH |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   E  |   R  |   T  |  \   |           |  `   |   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCTRL  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  [   |           |  ]   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ~L2  | LEFT | RGHT | LALT |  ~L1 |                                       | ~L1  | LEFT | DWN  |  UP  | RGHT |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | HOME | END  |       | RALT | RCTL |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | DEL  |       | PGUP |        |      |
 *                                 | []   | BKSP |------|       |------|  DEL   | ENT  |
 *                                 |      |      | LGUI |       | PGDN |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[_BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        GRAVE_ESC,KC_1,    KC_2,    KC_3,  KC_4,       KC_5,     F_TERM,
        KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,       KC_T,     KC_BSLS,
        OS_LCTL, KC_A,    KC_S,    KC_D,  KC_F,       KC_G,
        OS_LSFT,   KC_Z,    KC_X,    KC_C,  KC_V,       KC_B,     TD_LBRC,
        OSL_RSE, F_LEFTMON, F_RIGHTMON, OS_RALT, OSL_LWR,
                                                       KC_HOME,  KC_END,
                                                                 KC_DEL,
                                           KC_SPC,     KC_BSPC,  TD_GUI_LOCK,
        // right hand
        TD_TSKSWCH,KC_6,    KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        KC_GRV,    KC_Y,    KC_U,     KC_I,     KC_O,     KC_P,     KC_EQL,
                   KC_H,    KC_J,     KC_K,     KC_L,     TD_SCLN,  KC_QUOT,
        TD_RBRC,   KC_N,    KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  OS_RSFT,
                            OSL_LWR, KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,
        KC_RALT,   KC_RCTL,
        KC_PGUP,
        KC_PGDN,   KC_DEL, KC_ENT
    ),
/* Keymap 1: Motion Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      | Lclk | MsUp | Rclk | Vol+ | MUTE |           |      |  INS | PGUP |  Up  | PGDN |      |  F12   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |MsWhUp|MsLeft|MsDown|MsRght| Vol- |------|           |------| PSCR | Left | Down | Rght |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |MsWhDn|      |      |      |      |      |           |      | Calc |      |      |      | Edit |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      | HOME | PGDN | PGUP | END  |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | MPLY | MNXT |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Navigation
[_LOWER] = LAYOUT_ergodox(
       // lef hand
       KC_TRNS,   KC_F1,    KC_F2,       KC_F3,     KC_F4,      KC_F5,      KC_NO,
       KC_TRNS,   KC_NO,    KC_BTN1,     KC_MS_U,   KC_BTN2,    KC_VOLU,    KC_MUTE,
       KC_TRNS,   KC_WH_U,  KC_MS_L,     KC_MS_D,   KC_MS_R,    KC_VOLD,
       KC_TRNS,   KC_WH_D,  KC_NO,       KC_NO,     KC_NO,      KC_NO,      KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,
                                                                KC_MPLY,    KC_MNXT,
                                                                            KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,    KC_TRNS,
       // right hand
       KC_NO,     KC_F6,     KC_F7,      KC_F8,     KC_F9,      KC_F10,     KC_F11,
       KC_NO,     KC_INS,    KC_PGUP,    KC_UP,     KC_PGDN,    KC_NO,      KC_F12,
                  KC_PSCR,   KC_LEFT,    KC_DOWN,   KC_RGHT,    KC_NO,      KC_TRNS,
       KC_NO,     KC_CALC,   KC_NO,      KC_NO,     KC_NO,      KC_EDITOR,  KC_TRNS,
                             KC_TRNS,    KC_HOME,   KC_PGDN,    KC_PGUP,    KC_END,
       KC_TRNS,   KC_TRNS,
       KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS
       ),
/* Keymap 2: Symbol and Numpad
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      | NMLK |  P/  |  P*  |  P-  |        |
 * |---------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |  \   |  P7  |  P8  |  P9  |  P+  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------|  *   |  P4  |  P5  |  P6  |  P+  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [   |  ]  |   ~  |      |           |      |  &   |  P1  |  P2  |  P3  | PEnt |        |
 * `---------+------+------+------+------+------+------'           `------+------+------+------+------+------+--------'
 *    |      |AUTOTYP|      |      |      |                                       |      |  P0  |  P.  |      |      |
 *    `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Symbol and Numpad
[_RAISE] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_NO,
       KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
       KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_NO,
                KC_TRNS, F_KPAT,  KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_NO,
       KC_NO,   KC_BSLS, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_DQT,
                KC_ASTR, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_QUOT,
       KC_NO,   KC_AMPR, KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_TRNS,
                         KC_TRNS, KC_P0,   KC_PDOT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};


// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// /* Keymap 0: Basic layer
//  *
//  * ,--------------------------------------------------.           ,--------------------------------------------------.
//  * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
//  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
//  * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
//  * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
//  * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
//  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
//  *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
//  *   `----------------------------------'                                       `----------------------------------'
//  *                                        ,-------------.       ,-------------.
//  *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
//  *                                 ,------|------|------|       |------+--------+------.
//  *                                 |      |      | Home |       | PgUp |        |      |
//  *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
//  *                                 |      |ace   | End  |       | PgDn |        |      |
//  *                                 `--------------------'       `----------------------'
//  */
// // If it accepts an argument (i.e, is a function), it doesn't need KC_.
// // Otherwise, it needs KC_*
// [BASE] = LAYOUT_ergodox(  // layer 0 : default
//         // left hand
//         KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
//         KC_DELT,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(SYMB),
//         KC_BSPC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
//         KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
//         LT(SYMB,KC_GRV),KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
//                                               ALT_T(KC_APP),  KC_LGUI,
//                                                               KC_HOME,
//                                                KC_SPC,KC_BSPC,KC_END,
//         // right hand
//              KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
//              TG(SYMB),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
//                           KC_H,   KC_J,  KC_K,   KC_L,   LT(MDIA, KC_SCLN),GUI_T(KC_QUOT),
//              MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
//                                   KC_UP, KC_DOWN,KC_LBRC,KC_RBRC,          KC_FN1,
//              KC_LALT,        CTL_T(KC_ESC),
//              KC_PGUP,
//              KC_PGDN,KC_TAB, KC_ENT
//     ),
// /* Keymap 1: Symbol Layer
//  *
//  * ,---------------------------------------------------.           ,--------------------------------------------------.
//  * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
//  * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
//  * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
//  * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
//  * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
//  * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
//  *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
//  *   `-----------------------------------'                                       `----------------------------------'
//  *                                        ,-------------.       ,-------------.
//  *                                        |Animat|      |       |Toggle|Solid |
//  *                                 ,------|------|------|       |------+------+------.
//  *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
//  *                                 |ness- |ness+ |------|       |------|      |      |
//  *                                 |      |      |      |       |      |      |      |
//  *                                 `--------------------'       `--------------------'
//  */
// // SYMBOLS
// [SYMB] = LAYOUT_ergodox(
//        // left hand
//        VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
//        KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
//        KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
//        KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
//           EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
//                                        RGB_MOD,KC_TRNS,
//                                                KC_TRNS,
//                                RGB_VAD,RGB_VAI,KC_TRNS,
//        // right hand
//        KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
//        KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
//                 KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
//        KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
//                          KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
//        RGB_TOG, RGB_SLD,
//        KC_TRNS,
//        KC_TRNS, RGB_HUD, RGB_HUI
// ),
// /* Keymap 2: Media and mouse keys
//  *
//  * ,--------------------------------------------------.           ,--------------------------------------------------.
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
//  * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
//  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
//  *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
//  *   `----------------------------------'                                       `----------------------------------'
//  *                                        ,-------------.       ,-------------.
//  *                                        |      |      |       |      |      |
//  *                                 ,------|------|------|       |------+------+------.
//  *                                 |      |      |      |       |      |      |Brwser|
//  *                                 |      |      |------|       |------|      |Back  |
//  *                                 |      |      |      |       |      |      |      |
//  *                                 `--------------------'       `--------------------'
//  */
// // MEDIA AND MOUSE
// [MDIA] = LAYOUT_ergodox(
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
//                                            KC_TRNS, KC_TRNS,
//                                                     KC_TRNS,
//                                   KC_TRNS, KC_TRNS, KC_TRNS,
//     // right hand
//        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
//        KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
//                           KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
//        KC_TRNS, KC_TRNS,
//        KC_TRNS,
//        KC_TRNS, KC_TRNS, KC_WBAK
// ),
// };

// Runs whenever there is a layer state change.
uint32_t layer_state_set_keymap(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
