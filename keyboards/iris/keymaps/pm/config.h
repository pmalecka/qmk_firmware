#ifndef CONFIG_PM_H
#define CONFIG_PM_H

#include "../../config.h"

//Iris Specific Stuff
/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef DEBUG_ENABLE
#undef NO_PRINT
#undef NO_DEBUG
#endif

#endif
