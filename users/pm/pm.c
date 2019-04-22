#include "pm.h"

userspace_config_t userspace_config;

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
  userspace_config.raw = eeconfig_read_user();

  #ifdef BOOTLOADER_CATERINA
    // This will disable the red LEDs on the ProMicros
    DDRD &= ~(1<<5);
    PORTD &= ~(1<<5);

    DDRB &= ~(1<<0);
    PORTB &= ~(1<<0);
  #endif

  matrix_init_keymap();
}

__attribute__((weak))
void keyboard_post_init_keymap(void){ }

void keyboard_post_init_user(void){
#ifdef RGBLIGHT_ENABLE
  keyboard_post_init_rgb();
#endif
  keyboard_post_init_keymap();
}

__attribute__ ((weak))
void shutdown_keymap(void) {}

void shutdown_user (void) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb_red();
  #endif // RGBLIGHT_ENABLE
  shutdown_keymap();
}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
    suspend_power_down_keymap();
}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
  suspend_wakeup_init_keymap();
}


__attribute__ ((weak))
void matrix_scan_keymap(void) {}

// No global matrix scan code, so just run keymap's matrix
// scan function
void matrix_scan_user(void) {
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
    startup_user();
  }

#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif // RGBLIGHT_ENABLE

  matrix_scan_keymap();
}


__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
  state = layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
  return layer_state_set_keymap (state);
}


__attribute__ ((weak))
uint32_t default_layer_state_set_keymap (uint32_t state) {
  return state;
}

// Runs state check and changes underglow color and animation
uint32_t default_layer_state_set_user(uint32_t state) {
  state = default_layer_state_set_keymap(state);
#if 0
#ifdef RGBLIGHT_ENABLE
  state = default_layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
#endif
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led) {
  led_set_keymap(usb_led);
}

__attribute__ ((weak))
void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
  userspace_config.raw = 0;
  userspace_config.rgb_layer_change = true;
  eeconfig_update_user(userspace_config.raw);
}
