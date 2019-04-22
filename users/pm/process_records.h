#pragma once
#include "pm.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
  VRSN = PLACEHOLDER_SAFE_RANGE,              // Prints QMK Firmware and board info
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
  NEW_SAFE_RANGE     //use "NEWPLACEHOLDER for keymap specific codes
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

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
