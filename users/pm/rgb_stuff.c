#include "pm.h"
#include "rgb_stuff.h"
#include "eeprom.h"

extern rgblight_config_t rgblight_config;
extern animation_status_t animation_status;
bool has_initialized;

void rgblight_sethsv_default_helper(uint8_t index) {
  rgblight_sethsv_at(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, index);
}

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  switch (keycode) {

  case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
    if (record->event.pressed) {
      userspace_config.rgb_layer_change ^= 1;
      xprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
      eeconfig_update_user(userspace_config.raw);
      if (userspace_config.rgb_layer_change) {
        layer_state_set(layer_state); // This is needed to immediately set the layer color (looks better)
      }
    }
    return false; break;
  case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // quantum_keycodes.h L400 for definitions
    if (record->event.pressed) { //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
      if (userspace_config.rgb_layer_change) {
        userspace_config.rgb_layer_change = false;
        xprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
        eeconfig_update_user(userspace_config.raw);
      }
    }
    return true; break;
  }
    return true;
}

void keyboard_post_init_rgb(void) {
    // startup animation
	rgblight_enable_noeeprom();
	layer_state_set_user(layer_state);
    uint16_t old_hue = rgblight_config.hue;
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	for (uint16_t i = 360; i > 0; i--) {
		rgblight_sethsv_noeeprom( ( i + old_hue) % 360, 255, 255);
        wait_ms(10);
	}
	layer_state_set_user(layer_state);
}

void matrix_scan_rgb(void) {

}

uint32_t layer_state_set_rgb(uint32_t state) {
  if (userspace_config.rgb_layer_change) {
    switch (biton32(state)) {
    case _RAISE:
      rgblight_sethsv_noeeprom_chartreuse();
      rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
      break;
    case _LOWER:
      rgblight_sethsv_noeeprom_green();
      rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
      break;
    case _ADJUST:
      rgblight_sethsv_noeeprom_red();
      rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_noeeprom_blue();
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    }
  }

  return state;
}
