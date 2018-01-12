#include "action_layer.h"
#include "action_util.h"
#include "debug.h"
#include "eeconfig.h"
#include "ergodox_infinity.h"
#include "led.h"
#include "version.h"

#ifdef TAP_DANCE_ENABLE
#include "tap_dance_extra.h"
#endif

#define LCA(kc) (kc | QK_LCTL | QK_LALT)
#define LSS(kc) (kc | QK_LSFT | QK_LGUI)

#define F_RALT KC_RALT
#define F_RCTL KC_RCTL
#define F_TERM LCTL(KC_GRV)
#define F_LOCK LGUI(KC_L)
#define F_LEFTMON LSS(KC_LEFT)
#define F_RIGHTMON LSS(KC_RIGHT)
#define F_KPAUTOTYPE LCA(KC_F10)

#define OSL_NAV OSL(NAV)
#define OSL_NUM OSL(NUMPAD)
#define TG_NUM TG(NUMPAD)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_RSFT OSM(MOD_RSFT)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_RALT OSM(MOD_RALT)

enum {
  TD_TASKSWITCH = 0,
  TD_LEFT_BRACE_OR_PRN,
  TD_RIGHT_BRACE_OR_PRN,
  TD_SEMICOLON_OR_COLON,
  TD_WINKEY_OR_LOCK_WORKSTATION
};

#ifdef TAP_DANCE_ENABLE
#define TD_TSKSWCH TD(TD_TASKSWITCH)
#define TD_LBRC TD(TD_LEFT_BRACE_OR_PRN)
#define TD_RBRC TD(TD_RIGHT_BRACE_OR_PRN)
#define TD_SCLN TD(TD_SEMICOLON_OR_COLON)
#define TD_GUI TD(TD_WINKEY_OR_LOCK_WORKSTATION)
#else
#define TD_TSKSWCH M(VRSNS)
#define TD_LBRC KC_LBRC
#define TD_RBRC KC_RBRC
#define TD_SCLN KC_SCLN
#define TD_GUI KC_LGUI
#endif

enum keymaps_layers {
  BASE = 0, // default layer
  NAV,   // Mouse and keyboard motion keys
  NUMPAD    // numpad
};

enum custom_keycodes {
  PLACE_HOLDER = 0, // can always be here
  VRSN,
  EDITOR
};

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
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        GRAVE_ESC,KC_1,    KC_2,    KC_3,  KC_4,       KC_5,     F_TERM,
        KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,       KC_T,     KC_BSLS,
        OSM_LCTL, KC_A,    KC_S,    KC_D,  KC_F,       KC_G,
        OSM_LSFT,   KC_Z,    KC_X,    KC_C,  KC_V,       KC_B,     TD_LBRC,
        OSL_NUM, F_LEFTMON, F_RIGHTMON, OSM_RALT, OSL_NAV,
                                                       KC_HOME,  KC_END,
                                                                 KC_DEL,
                                           KC_SPC,     KC_BSPC,  TD_GUI,
        // right hand
        TD_TSKSWCH,KC_6,    KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        KC_GRV,    KC_Y,    KC_U,     KC_I,     KC_O,     KC_P,     KC_EQL,
                   KC_H,    KC_J,     KC_K,     KC_L,     TD_SCLN,  KC_QUOT,
        TD_RBRC,   KC_N,    KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  OSM_RSFT,
                            OSL_NAV, KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,
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
[NAV] = KEYMAP(
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
       KC_NO,     KC_CALC,   KC_NO,      KC_NO,     KC_NO,      M(EDITOR),  KC_TRNS,
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
[NUMPAD] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_NO,
       KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
       KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_NO,
                KC_TRNS, F_KPAUTOTYPE, KC_TRNS, KC_TRNS, KC_TRNS,
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
)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
  }

  return MACRO_NONE;
};

#ifdef TAP_DANCE_ENABLE
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(KC_LBRC, KC_LPRN),
  [TD_RIGHT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(KC_RBRC, KC_RPRN),
  [TD_SEMICOLON_OR_COLON] = ACTION_TAP_DANCE_SHIFT_WITH_DOUBLE(KC_SCLN),
  [TD_TASKSWITCH] = ACTION_TAP_DANCE_TSKSWCH(),  // switch application / switch windows (windows)
  [TD_WINKEY_OR_LOCK_WORKSTATION] = {
    .fn = { NULL, td_gui_on_finished, td_gui_on_reset },
    .user_data = ((void *)KC_LGUI),
  }
};

#endif

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

#define IS_MOD_ACTIVE(kc) (get_mods() & MOD_BIT(kc) \
                           || ((get_oneshot_mods() & MOD_BIT(kc)) && !has_oneshot_mods_timed_out()))

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    // ergodox_board_led_off();
    // ergodox_right_led_1_off();
    // ergodox_right_led_2_off();
    // ergodox_right_led_3_off();

    // if (IS_LAYER_ON(1)) {
    //     ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
    //     ergodox_right_led_1_on();
    // }

    // if (IS_LAYER_ON(2)) {
    //     ergodox_right_led_2_set(LED_BRIGHTNESS_LO);
    //     ergodox_right_led_2_on();
    // }

    // if (IS_LAYER_ON(3)) {
    //     ergodox_right_led_3_set(LED_BRIGHTNESS_LO);
    //     ergodox_right_led_3_on();
    // }

    // if (IS_MOD_ACTIVE(KC_LCTL) || IS_MOD_ACTIVE(KC_RCTL)) {
    //     ergodox_right_led_1_set(LED_BRIGHTNESS_HI);
    //     ergodox_right_led_1_on();
    // }

    // if (IS_MOD_ACTIVE(KC_LSFT) || IS_MOD_ACTIVE(KC_RSFT)) {
    //     ergodox_right_led_2_set(LED_BRIGHTNESS_HI);
    //     ergodox_right_led_2_on();
    // }

    // if (IS_MOD_ACTIVE(KC_LALT) || IS_MOD_ACTIVE(KC_RALT)) {
    //     ergodox_right_led_3_set(LED_BRIGHTNESS_HI);
    //     ergodox_right_led_3_on();
    // }

};
