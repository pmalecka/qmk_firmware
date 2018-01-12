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
#define TAPPING_TERM 200

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#define GRAVE_ESC_CTRL_OVERRIDE

// //experimental, to resolve weird OSM issues
// #define QMK_KEYS_PER_SCAN 8
// #undef IGNORE_MOD_TAP_INTERRUPT
// #define PERMISSIVE_HOLD

#ifdef DEBUG_ENABLE
#undef NO_PRINT
#undef NO_DEBUG
#endif

// #define USING_QK_FUNCTION

#endif
