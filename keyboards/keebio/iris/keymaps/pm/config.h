#ifndef CONFIG_PM_H
#define CONFIG_PM_H

#include "../../config.h"

//Iris Specific Stuff
/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

#ifdef RGBLIGHT_ENABLE
#undef RGBLED_NUM
#define RGBLED_NUM 12     // Number of LEDs

#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1

#define RGBLIGHT_LIMIT_VAL 225
#endif // RGBLIGHT_ENABLE

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef DEBUG_ENABLE
#undef NO_PRINT
#undef NO_DEBUG
#endif

#endif
