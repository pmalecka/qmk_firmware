#pragma once

/* Use I2C or Serial, not both */

#define USE_SERIAL
#undef USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

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

#undef PRODUCT
#ifdef KEYBOARD_iris_rev2
#define PRODUCT         PM Awesome Iris Rev.2
#endif



#define BOOTMAGIC_LITE_ROW 4
#define BOOTMAGIC_LITE_COLUMN 3
