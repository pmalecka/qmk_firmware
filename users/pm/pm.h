#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE
#ifdef RGBLIGHT_ENABLE
  #include "rgb_stuff.h"
#endif


/* Define layer names */
enum userspace_layers {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};


void matrix_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
uint32_t layer_state_set_keymap (uint32_t state);
uint32_t default_layer_state_set_keymap (uint32_t state);
void led_set_keymap(uint8_t usb_led);
void eeconfig_init_keymap(void);

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} userspace_config_t;

extern userspace_config_t userspace_config;
