#ifndef CONFIG_PM_H
#define CONFIG_PM_H

#include "../../config.h"

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 1

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 2

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0

//#define ONESHOT_TAP_TOGGLE 2
//#define ONESHOT_TIMEOUT 1000

#undef TAPPING_TERM
#define TAPPING_TERM 180

#define GRAVE_ESC_CTRL_OVERRIDE

// #undef IGNORE_MOD_TAP_INTERRUPT
// #define TAPPING_FORCE_HOLD
#define PERMISSIVE_HOLD //makes tap and hold keys work better for fast typers who don't want tapping term set above 500
#define QMK_KEYS_PER_SCAN 4

#define PREVENT_STUCK_MODIFIERS //prevents stuck modifiers when you switch layers while a key is being held down
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos
//(zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and
//when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x.)
#define TAPPING_FORCE_HOLD //modifiers have to be held, disable the feature of layer tap (LT) where the tap key can be held down

#ifdef DEBUG_ENABLE
#undef NO_PRINT
#undef NO_DEBUG
#endif

#endif
