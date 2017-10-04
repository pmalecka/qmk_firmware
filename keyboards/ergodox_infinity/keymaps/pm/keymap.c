#include QMK_KEYBOARD_H

#include "debug.h"
#include "led.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "version.h"

#define DEFAULT_EDITOR "notepad"

// unsupported hid comsumer id
#define AL_EDITOR 0x185

#define LSS(kc) (kc | QK_LSFT | QK_LGUI)

#define F_TERM LCTL(KC_GRV)

enum {
  TD_TERM_ONLY_ONCE = 0,
  TD_LEFT_BRACE_OR_PRN,
  TD_RIGHT_BRACE_OR_PRN,
  TD_LEFT_OR_MOVE_WIN_TO_OTHER_MONITOR,
  TD_RIGHT_OR_MOVE_WIN_TO_OTHER_MONITOR,
  TD_SEMICOLON_OR_COLON,
  TD_TASKSWITCH,
  TD_WINKEY_OR_LOCK_WORKSTATION
};

#ifdef TAP_DANCE_ENABLE

#define TD_TERM TD(TD_TERM_ONLY_ONCE)
#define TD_LBRC TD(TD_LEFT_BRACE_OR_PRN)
#define TD_RBRC TD(TD_RIGHT_BRACE_OR_PRN)
#define TD_LEFT TD(TD_LEFT_OR_MOVE_WIN_TO_OTHER_MONITOR)
#define TD_RGHT TD(TD_RIGHT_OR_MOVE_WIN_TO_OTHER_MONITOR)
#define TD_SCLN TD(TD_SEMICOLON_OR_COLON)
#define TD_TSKSWCH TD(TD_TASKSWITCH)
#define TD_GUI TD(TD_WINKEY_OR_LOCK_WORKSTATION)

#else

#define TD_TERM F_TERM
#define TD_LBRC KC_LBRC
#define TD_RBRC KC_RBRC
#define TD_RGHT KC_RGHT
#define TD_LEFT KC_LEFT
#define TD_SCLN KC_SCLN
#define TD_TSKSWCH M(TSKSWCH)
#define TD_GUI KC_LGUI

#endif


#ifdef QMK_MOD_SHORTCUT_ENABLED

#define F_MOTION OSL(MOTION)
#define F_NUMPAD OSL(NUMPAD)
#define F_LSFT OSM(MOD_LSFT)
#define F_RSFT OSM(MOD_RSFT)
#define F_LCTL OSM(MOD_LCTL)
#define F_LALT OSM(MOD_LALT)
#else

#define F_MOTION KC_FN0
#define F_NUMPAD KC_FN1
#define F_LSFT KC_FN3
#define F_RSFT KC_FN4
#define F_LCTL KC_FN5
#define F_LALT KC_FN6
#endif

#define TAP_KEY(code) \
  register_code(code); \
  unregister_code(code)

#define TAP_KEY16(code) \
  register_code16(code); \
  unregister_code16(code)

enum keymaps_layers {
  BASE = 0, // default layer
  MOTION,   // Mouse and keyboard motion keys
  NUMPAD    // numpad                                                      
};

enum custom_keycodes {
  PLACE_HOLDER = 0, // can always be here
  TSKSWCH,
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
        GRAVE_ESC,KC_1,    KC_2,    KC_3,  KC_4,       KC_5,     TD_TERM,
        KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,       KC_T,     KC_BSLS,
        KC_LCTL,  KC_A,    KC_S,    KC_D,  KC_F,       KC_G,
        F_LSFT,   KC_Z,    KC_X,    KC_C,  KC_V,       KC_B,     TD_LBRC,
        F_NUMPAD, TD_LEFT, TD_RGHT, F_LALT, F_MOTION,
                                                       KC_HOME,  KC_END,
                                                                 KC_DEL,
                                           KC_SPC,     KC_BSPC,  TD_GUI,
        // right hand
        TD_TSKSWCH,KC_6,    KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        KC_GRV,    KC_Y,    KC_U,     KC_I,     KC_O,     KC_P,     KC_EQL,
                   KC_H,    KC_J,     KC_K,     KC_L,     TD_SCLN,  KC_QUOT,
        TD_RBRC,   KC_N,    KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  F_RSFT,
                            F_MOTION, KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  
        KC_RALT,   KC_RCTL,
        KC_PGUP,
        KC_PGDN,   KC_DEL, KC_ENT
    ),
/* Keymap 1: Motion Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  | F6   |           | F7   |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | MsWhUp  | Lclk | MsUp | Rclk | Vol+ | Vol- | MUTE |           |      |  INS |      | PGUP |  Up  | PGDN |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | MsWhDwn |MsLeft|MsDown|MsRght|      |      |------|           |------| PSCR |      | Left | Down | Rght |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      | Calc |      |      |      | Edit |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | MPLY | MNXT |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Motion
[MOTION] = KEYMAP(
       // lefm.,t hand
       KC_TRNS,   KC_F1,    KC_F2,       KC_F3,     KC_F4,      KC_F5,      KC_F6,
       KC_WH_U,   KC_BTN1,  KC_MS_U,     KC_BTN2,   KC_VOLU,    KC_VOLD,    KC_MUTE,
       KC_WH_D,   KC_MS_L,  KC_MS_D,     KC_MS_R,   KC_NO,      KC_NO,
       KC_TRNS,   KC_NO,    KC_NO,       KC_NO,     KC_NO,      KC_NO,      KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,
                                                                KC_MPLY,    KC_MNXT,
                                                                            KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,    KC_TRNS,
       // right hand
       KC_F7,     KC_F8,     KC_F9,      KC_F10,    KC_F11,     KC_F12,     KC_TRNS,
       KC_NO,     KC_INS,    KC_NO,      KC_PGUP,   KC_UP,      KC_PGDN,    KC_TRNS,
       KC_NO,     KC_PSCR,   KC_NO,      KC_LEFT,   KC_DOWN,    KC_RGHT,
       KC_NO,     KC_CALC,   KC_NO,      KC_NO,     KC_NO,      M(EDITOR),  KC_TRNS,
                             KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
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
 *    |      |      |      |      |      |                                       |      |  P0  |  P.  |      |      |
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
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_ONESHOT(MOTION),
  [1] = ACTION_LAYER_ONESHOT(NUMPAD),
  [3] = ACTION_MODS_ONESHOT(MOD_LSFT),
  [4] = ACTION_MODS_ONESHOT(MOD_RSFT),
  [5] = ACTION_MODS_ONESHOT(MOD_LCTL),
  [6] = ACTION_MODS_ONESHOT(MOD_LALT)
};

static uint16_t tskswch_timer;
static bool tskswch_active = false;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case TSKSWCH:
      if (record->event.pressed) {
          tskswch_timer = timer_read();
          tskswch_active = true;
      } else {
          if (timer_elapsed(tskswch_timer) > TAPPING_TERM) {
              unregister_code(KC_LALT);
          } else {
              tskswch_active = false;
              // switch to last application
              TAP_KEY16(LALT(KC_TAB));
          }
      }
      break;
    case EDITOR:
      if (record->event.pressed) {
        TAP_KEY(KC_LGUI);
        wait_ms(250);
        SEND_STRING(DEFAULT_EDITOR "\n");
      }
      break;
  }

  return MACRO_NONE;
};

#ifdef TAP_DANCE_ENABLE

#define GET_KEYCODE_FROM_VOIDPTR(p) ((uint8_t)*(uint8_t *)&p)

static void td_gui_on_finished(qk_tap_dance_state_t *state, void *user_data) {
  uint8_t kc = GET_KEYCODE_FROM_VOIDPTR(user_data);

  if (state->pressed) {
    register_mods(MOD_BIT(kc));
  } else if (state->count == 1) {
    register_mods(MOD_BIT(kc));
  } else if (state->count == ONESHOT_TAP_TOGGLE) {
    register_mods(MOD_BIT(kc));
  } else if (state->count == 3) {
    TAP_KEY16(LGUI(KC_L));
  }
}

static void td_gui_on_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == ONESHOT_TAP_TOGGLE) {
    return;
  }
  uint8_t kc = GET_KEYCODE_FROM_VOIDPTR(user_data);
  unregister_mods(MOD_BIT(kc));
}

static void td_tskswch_on_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) {
    register_code(KC_LALT);
    wait_ms(250);
    TAP_KEY(KC_TAB);
    state->count = 3;
  } else {
    switch (state->count) {
      case 1:
        register_code16(LALT(KC_TAB));
        break;
      case 2:
        register_code(KC_LALT);
        wait_ms(250);
        TAP_KEY(KC_TAB);
        wait_ms(250);
        TAP_KEY(KC_TAB);
        break;
    }
  }
}

static void td_tskswch_on_reset(qk_tap_dance_state_t *state, void *user_data) {
   switch (state->count) {
      case 1:
        unregister_code16(LALT(KC_TAB));
        break;
      case 2:
        unregister_code(KC_LALT);
        break;
      case 3:
        unregister_code(KC_LALT);
        break;
    }
}

#define ACTION_TAP_DANCE_SHIFT_WITH_DOUBLE(kc) ACTION_TAP_DANCE_DOUBLE(kc, LSFT(kc))

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TERM_ONLY_ONCE] = ACTION_TAP_DANCE_DOUBLE(F_TERM, KC_NO),      // start term
  [TD_LEFT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LPRN),
  [TD_RIGHT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RPRN),
  [TD_LEFT_OR_MOVE_WIN_TO_OTHER_MONITOR] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, LSS(KC_LEFT)),
  [TD_RIGHT_OR_MOVE_WIN_TO_OTHER_MONITOR] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, LSS(KC_RGHT)),
  [TD_SEMICOLON_OR_COLON] = ACTION_TAP_DANCE_SHIFT_WITH_DOUBLE(KC_SCLN),
  [TD_TASKSWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_tskswch_on_finished, td_tskswch_on_reset),  // switch application / switch windows (windows)
  [TD_WINKEY_OR_LOCK_WORKSTATION] = {
    .fn = { NULL, td_gui_on_finished, td_gui_on_reset },
    .user_data = ((void *)KC_LGUI),
  },
};
#endif

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    // When holding the tskswch button show task switcher
    if (tskswch_active && timer_elapsed(tskswch_timer) > TAPPING_TERM) {
        tskswch_active = false;
        register_code(KC_LALT);
        wait_ms(250);
        TAP_KEY(KC_TAB);
    }
};