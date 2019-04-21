#pragma once



#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_SLEEP
  #undef RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
#endif // RGBLIGHT_ENABLE


#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 1

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 2

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0

#ifndef ONESHOT_TAP_TOGGLE
  #define ONESHOT_TAP_TOGGLE 2
#endif // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
  #define ONESHOT_TIMEOUT 1000
#endif// !ONESHOT_TIMEOUT

#ifndef QMK_KEYS_PER_SCAN
  #define QMK_KEYS_PER_SCAN 4
#endif // !QMK_KEYS_PER_SCAN

#define GRAVE_ESC_CTRL_OVERRIDE



// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD //makes tap and hold keys work better for fast typers who don't want tapping term set above 500
#define TAPPING_FORCE_HOLD //modifiers have to be held, disable the feature of layer tap (LT) where the tap key can be held down
//#define RETRO_TAPPING

#define PREVENT_STUCK_MODIFIERS //prevents stuck modifiers when you switch layers while a key is being held down

#define FORCE_NKRO

#ifndef TAPPING_TOGGLE
  #define TAPPING_TOGGLE  1
#endif

#ifdef TAPPING_TERM
  #undef TAPPING_TERM
#endif // TAPPING_TERM
#define TAPPING_TERM 180


// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define MACRO_TIMER 5
