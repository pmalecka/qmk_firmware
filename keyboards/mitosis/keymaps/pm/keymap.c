// This is the Dvorak-friendly layout for the Mitosis by CarVac (/u/CarVac)
// It features space on the left thumb, shift on the right thumb, a
//  number layer with all the numbers on the home row, and a function layer
//  that provides mouse keys among other things.

#include "mitosis.h"

#define LCA(kc) (kc | QK_LCTL | QK_LALT)
#define LSS(kc) (kc | QK_LSFT | QK_LGUI)

#define F_TERM LCTL(KC_GRV)
#define F_KPAT LCA(KC_F10)

#if (__has_include("secrets.h"))
#include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familar enough to know which is better or why...
PROGMEM const char secret[][64] = {
  "test1",
  "test2",
  "test3",
  "test4",
  "test5"
};
#endif

enum userspace_custom_keycodes {
  EPRM = SAFE_RANGE, // can always be here
  KC_SECRET_1,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
  LT_ONE_OR_ENTER,
  NEW_SAFE_RANGE //use "NEWPLACEHOLDER for keymap specific codes
};

#ifdef TAP_DANCE_ENABLE
#include "tap_dance_extra.h"
#endif

#ifdef TAP_DANCE_ENABLE
#define TD_CTRL_SCLN_QUOT TD(TD_SCLN_OR_QUOT_HOLD_CTRL)
#define TD_SFT_SLSH_BSLS TD(TD_SLSH_OR_BSLS_HOLD_SFT)
#define TD_LBRC TD(TD_LEFT_BRACE_OR_PRN)
#define TD_RBRC TD(TD_RIGHT_BRACE_OR_PRN)
#define TD_SCLN TD(TD_SEMICOLON_OR_COLON)

enum {
  TD_SCLN_OR_QUOT_HOLD_CTRL = 0,
  TD_SLSH_OR_BSLS_HOLD_SFT,
  TD_LEFT_BRACE_OR_PRN,
  TD_RIGHT_BRACE_OR_PRN,
  TD_SEMICOLON_OR_COLON,
  TD_TASKSWITCH
};
#endif

enum mitosis_layers
{
	_STD,
	_NUM,
	_FN
};

// Macro definitions for readability
enum mitosis_macros
{
	VOLU,
	VOLD,
	ESCM
};

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------..--------------------------------------------.
 * | Q      | W      | E      | R      | T      || Y      | U      | I      | O      | P      |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | CTRL(A)| S      | D      | F      | G      || H      | J      | K      | L      | CTRL(;)|
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | SHFT(Z)| X      | C      | V      | B      || N      | M      | ,      | .      |SHIFT(/)|
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          | ESC    | TAB    | LCTRL  | LGUI   || LEFT   | UP     | DOWN   | RIGHT  |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          | [      | ALT    | SPACE  |BSP(NUM)|| DEL(FN)| ENTER  | TAB    | ]      |
 *          '-----------------------------------''-----------------------------------'
 */
//CTL_T(KC_A)
[_STD] = { /* Standard */
  {KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,     KC_O,    KC_P    },
  {CTL_T(KC_A),    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,     KC_L,    TD_CTRL_SCLN_QUOT },
  {SFT_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM,  KC_DOT,  TD_SFT_SLSH_BSLS },
  {XXXXXXX, M(ESCM),KC_TAB,  KC_LCTL, KC_LGUI,            KC_LEFT, KC_UP,   KC_DOWN,  KC_RIGHT, XXXXXXX },
  {XXXXXXX, TD_LBRC,KC_LALT, KC_SPC,  LT(_NUM,KC_BSPC),   LT(_FN, KC_DEL), KC_ENT,  KC_TAB,   TD_RBRC,   XXXXXXX }
},

/* Number layout, for data entry and programming purposes
 * .--------------------------------------------..--------------------------------------------.
 * | TASKSW | Secret1| Secret2| (      | )      || [      | ]      | '      | -      | =      |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | CTRL(1)| 2      | 3      | 4      | 5      || 6      | 7      | 8      | 9      | CTRL(0)|
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | SFT(F1)| F2     | F3     | F4     | F5     || F6     | F7     | F8     | F9     |SFT(F10)|
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          | TERM   | KPAUTOT|        | GRESC  ||        |        | VOLU   | F11    |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          |        |        | ENTER  | NUM    ||        |        | VOLD   | F12    |
 *          '-----------------------------------''-----------------------------------'
 */

[_NUM] = { /* Number layout along the home row for maximum speed*/
  {TD(TD_TASKSWITCH), KC_SECRET_1, KC_SECRET_2, KC_LPRN, KC_RPRN,    KC_LBRC, KC_RBRC, KC_QUOT, KC_MINS, KC_EQL },
  {CTL_T(KC_1),    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    CTL_T(KC_0)    },
  {SFT_T(KC_F1),   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   SFT_T(KC_F10)  },
  {XXXXXXX, F_TERM,  F_KPAT, _______, GRAVE_ESC,             _______, _______, M(VOLU), KC_F11, XXXXXXX },
  {XXXXXXX, _______, _______, KC_ENT, _______,               _______, _______, M(VOLD), KC_F12, XXXXXXX }
},


/* Fn layout, for typing purposes
 * .--------------------------------------------..--------------------------------------------.
 * | -      | =      |  \     | [      | ]      ||        |        |        |        |        |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | !      | @      | #      | $      | %      || ^      | &      | *      | (      | )      |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | ^      | &      | *      | (      | )      ||        |        |        |        | VOLD   |
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          |        |        |        |        || HOME   | PGUP   | PGDN   | END    |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          |        |        |        |        || FN     |        |        |        |
 *          '-----------------------------------''-----------------------------------'
 */

[_FN] = { /* Function Layer, primary alternative layer featuring numpad on right hand,
                                   cursor keys on left hand, and all symbols*/
  {KC_MINS,  KC_EQL , KC_BSLS, KC_LBRC, KC_RBRC,        _______, _______, _______, _______, KC_RPRN },
  {KC_EXLM,  KC_AT  , KC_HASH, KC_DOLLAR, KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN },
  {KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,       _______, _______, _______, _______, KC_VOLD  },
  {XXXXXXX,  _______ , _______, _______, _______,       KC_HOME, KC_PGUP, KC_PGDN, KC_END,  XXXXXXX },
  {XXXXXXX,  _______ , _______, _______, _______,       _______, _______, _______, _______, XXXXXXX }
},

/* blank key layout template
 * .--------------------------------------------..--------------------------------------------.
 * |        |        |        |        |        ||        |        |        |        |        |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * |        |        |        |        |        ||        |        |        |        |        |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * |        |        |        |        |        ||        |        |        |        |        |
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          |        |        |        |        ||        |        |        |        |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          |        |        |        |        ||        |        |        |        |
 *          '-----------------------------------''-----------------------------------'
 */

};
#ifdef TAP_DANCE_ENABLE
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(KC_LBRC, KC_LPRN),
  [TD_RIGHT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(KC_RBRC, KC_RPRN),
  [TD_SEMICOLON_OR_COLON] = ACTION_TAP_DANCE_SHIFT_WITH_DOUBLE(KC_SCLN),
  [TD_SCLN_OR_QUOT_HOLD_CTRL] = ACTION_TAP_DANCE_MULTITAP(KC_SCLN, KC_LCTL, KC_QUOT, KC_RCTL),
  [TD_SLSH_OR_BSLS_HOLD_SFT] = ACTION_TAP_DANCE_MULTITAP(KC_SLSH, KC_RSFT, KC_BSLS, KC_RSFT),
  [TD_TASKSWITCH] = ACTION_TAP_DANCE_TSKSWCH(),  // switch application / switch windows (windows)
};
#endif

static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {

      	//switch multiplexing for media, short tap for volume up, long press for play/pause
        case VOLU:
            if (record->event.pressed) {
            	key_timer = timer_read(); // if the key is being pressed, we start the timer.
          	} else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
            	if (timer_elapsed(key_timer) > LONGPRESS_DELAY) { // LONGPRESS_DELAY being 150ms, the threshhold we pick for counting something as a tap.
                  return MACRO(T(MPLY), END);
                } else {
                  return MACRO(T(VOLU), END);
                }
          	}
          	break;

		//switch multiplexing for media, short tap for volume down, long press for next track
        case VOLD:
            if (record->event.pressed) {
            	key_timer = timer_read();
          	} else {
            	if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
                  return MACRO(T(MNXT), END);
                } else {
                  return MACRO(T(VOLD), END);
                }
          	}
          	break;

        //switch multiplexing for escape, short tap for escape, long press for context menu
        case ESCM:
            if (record->event.pressed) {
            	key_timer = timer_read();
          	} else {
            	if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
                  return MACRO(T(APP), END);
                } else {
                  return MACRO(T(ESC), END);
                }
          	}
          	break;

        break;
    }
    return MACRO_NONE;
};

// uint16_t custom_lt_timer;
// keypos_t prv_key_pressed;
// #define IS_KEYPOS_SAME(keyone,keytwo)  ((keyone.col==keytwo.col)&&(keyone.row==keytwo.row))
// #define ANOTHER_KEY_PRESSED (!IS_KEYPOS_SAME(prv_key_pressed, record->event.key))

// Defines actions for global custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_1 ... KC_SECRET_5: // Custom
      if (!record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        send_string_P(secret[keycode - KC_SECRET_1]);
      }
      return false;
    break;
  }

  // // if key is pressed, do nothing
  // // if another key is pressed(and released) while this one is pressed, then send the combo on release of this key
  // // if no other key is pressed(and released) while this one is pressed, then send the original key
  // if(record->event.pressed) prv_key_pressed = record->event.key;
  // if(keycode == LT_ONE_OR_ENTER) {
  //   if(record->event.pressed) {
  //     custom_lt_timer = timer_read();
  //     // layer_on(1);
  //     register_mods(MOD_BIT(KC_LCTL));
  //   }else{
  //     // layer_off(1);
  //     unregister_mods(MOD_BIT(KC_LCTL));
  //     if (timer_elapsed(custom_lt_timer) < TAPPING_TERM && (!ANOTHER_KEY_PRESSED)) {
  //       register_code(KC_A);
  //       unregister_code(KC_A);
  //     }
  //   }
  //   return true;
  // }

  return true;
}

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
    	case _STD:
    		set_led_off;
    		break;
      case _FN:
        set_led_blue;
        break;
      case _NUM:
        set_led_red;
        break;
      default:
        break;
    }
};

