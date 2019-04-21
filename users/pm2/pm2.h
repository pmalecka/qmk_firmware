#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  #include "rgb_stuff.h"
#endif


/* Define layer names */
enum userspace_layers {
  _BASE = 0,
  _NUMLOCK = 0,
  _COLEMAK,
  _DVORAK,
  _WORKMAN,
  _NORMAN,
  _MALTRON,
  _EUCALYN,
  _CARPLAX,
  _MODS, /* layer 8 */
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


bool mod_key_press_timer (uint16_t code, uint16_t mod_code, bool pressed);
bool mod_key_press (uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);
bool send_game_macro(const char *str, keyrecord_t *record, bool override);
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
    bool     is_overwatch     :1;
    bool     nuke_switch      :1;
    uint8_t  unicode_mod      :4;
    bool     swapped_numbers  :1;
  };
} userspace_config_t;

extern userspace_config_t userspace_config;
