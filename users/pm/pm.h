#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "action_layer.h"
#include "eeconfig.h"

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"
#endif

#define DEFAULT_EDITOR "notepad"

/* Define layer names */
enum userspace_layers {
  _BASE = 0,
  _NUMLOCK = 0,
  _COLEMAK,
  _DVORAK,
  _WORKMAN,
  _MODS,
  _GAMEPAD,
  _DIABLO,
  _MACROS,
  _MEDIA,
  _LOWER,
  _RAISE,
  _ADJUST,
};

/*
define modifiers here, since MOD_* doesn't seem to work for these
 */
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK  (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))


/*
RGB color codes are no longer located here anymore.  Instead, you will want to
head to https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h
*/

#ifdef RGBLIGHT_ENABLE
void rgblight_sethsv_default_helper(uint8_t index);
#endif // RGBLIGHT_ENABLE

bool mod_key_press_timer (uint16_t code, uint16_t mod_code, bool pressed);
bool mod_key_press (uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
    bool     is_overwatch     :1;
    bool     nuke_switch      :1;
    uint8_t  unicode_mod      :4;
  };
} userspace_config_t;

#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
  EPRM = PLACEHOLDER_SAFE_RANGE, // Resets EEPROM do defaults (as in eeconfig_init)
  VRSN,              // Prints QMK Firmware and board info
  KC_BASE,           // Sets default layer to BASE
  KC_COLEMAK,        // Sets default layer to COLEMAK
  KC_DVORAK,         // Sets default layer to DVORAK
  KC_WORKMAN,        // Sets default layer to WORKMAN
  LOWER,             // Tri Layer Update when LOWER layer is selected
  RAISE,             // Tri Layer Update when RAISE layer is selected
  ADJUST,            // Tri Layer Update when ADJUST layer is selected
  KC_EDITOR,         // Runs the default editor
  KC_MAKE,           // Run keyboard's customized make command
  KC_RGB_T,          // Toggles RGB Layer Indication mode
  KC_SECRET_1,       // test1
  KC_SECRET_2,       // test2
  KC_SECRET_3,       // test3
  KC_SECRET_4,       // test4
  KC_SECRET_5,       // test5
  KC_CCCV,           // Hold to copy, tap to paste
  KC_NUKE,           // NUCLEAR LAUNCH DETECTED!!!
  UC_FLIP,           // (ಠ痊ಠ)┻━┻
  UC_TABL,           // ┬─┬ノ( º _ ºノ)
  UC_SHRG,           // ¯\_(ツ)_/¯
  UC_DISA,           // ಠ_ಠ
  NEW_SAFE_RANGE     //use "NEWPLACEHOLDER for keymap specific codes
};

#define LSS(kc) (kc | QK_LSFT | QK_LGUI)

#define F_TERM LCTL(KC_GRV) // default CMDER global shortcut
#define F_KPAT LCA(KC_F10) // default global shortcut for keepass autotype
#define F_LEFTMON LSS(KC_LEFT)
#define F_RIGHTMON LSS(KC_RIGHT)
#define F_CAD LCA(KC_DEL) //CTRL + ALT + DELETE

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define OSL_LWR OSL(_LOWER)
#define OSL_RSE OSL(_RAISE)

#define TG_MODS TG(_MODS)
#define TG_GAME TG(_GAMEPAD)

#define KC_SCRT1 KC_SECRET_1
#define KC_SCRT2 KC_SECRET_2
#define KC_SCRT3 KC_SECRET_3
#define KC_SCRT4 KC_SECRET_4
#define KC_SCRT5 KC_SECRET_5

#define BASE KC_BASE
#define DVORAK KC_DVORAK
#define COLEMAK KC_COLEMAK
#define WORKMAN KC_WORKMAN

#define KC_RESET RESET
#define KC_RST KC_RESET

#ifdef SWAP_HANDS_ENABLE
#define KC_C1R3 SH_TT
#else // SWAP_HANDS_ENABLE
#define KC_C1R3 KC_BSPC
#endif // SWAP_HANDS_ENABLE

#define BK_LWER LT(_LOWER, KC_BSPC)
#define SP_LWER LT(_LOWER, KC_SPC)
#define DL_RAIS LT(_RAISE, KC_DEL)
#define ET_RAIS LT(_RAISE, KC_ENTER)

/* OSM keycodes, to keep things clean and easy to change */
#define KC_MLSF OSM(MOD_LSFT)
#define KC_MRSF OSM(MOD_RSFT)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define ALT_APP ALT_T(KC_APP)

#define MG_NKRO MAGIC_TOGGLE_NKRO

#define UC_IRNY UC(0x2E2E)
#define UC_CLUE UC(0x203D)

#ifdef TAP_DANCE_ENABLE
enum {
  TD_TASKSWITCH = 0,
  TD_LEFT_BRACE_OR_PRN,
  TD_RIGHT_BRACE_OR_PRN,
  TD_SEMICOLON_OR_COLON,
  TD_ALT_OR_LOCK_WORKSTATION,
  TD_GUI_OR_ESC,
  TD_GUI_OR_LOCK_WORKSTATION
};
#endif // TAP_DANCE_ENABLE


/*
Custom Keycodes For Tap Dance
But since TD() doesn't work when tap dance is disabled
We use custom codes here, so we can substitute the right stuff
*/
#ifdef TAP_DANCE_ENABLE
#define TD_TSKSWCH TD(TD_TASKSWITCH)
#define TD_LBRC TD(TD_LEFT_BRACE_OR_PRN)
#define TD_RBRC TD(TD_RIGHT_BRACE_OR_PRN)
#define TD_SCLN TD(TD_SEMICOLON_OR_COLON)
#define TD_ALT TD(TD_ALT_OR_LOCK_WORKSTATION)
#define TD_GUI TD(TD_GUI_OR_ESC)
#define TD_GUI_LOCK TD(TD_GUI_OR_LOCK_WORKSTATION)
#else // TAP_DANCE_ENABLE
#define TD_TSKSWCH M(VRSN)
#define TD_LBRC KC_LBRC
#define TD_RBRC KC_RBRC
#define TD_SCLN KC_SCLN
#define TD_ALT KC_LALT
#define TD_GUI KC_LGUI
#define TD_GUI_LOCK KC_LGUI
#endif // TAP_DANCE_ENABLE



