#include "pm.h"

uint16_t copy_paste_timer;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
  #if defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_iris_rev2)
    xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.row, record->event.key.col, record->event.pressed);
  #else
    xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
#endif //KEYLOGGER_ENABLE

  switch (keycode) {
  case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
    //   update_tri_layer(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_LOWER);
    //   update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    break;
  case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
    //   update_tri_layer(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_RAISE);
    //   update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    break;
  case ADJUST:
    if (record->event.pressed) {
      layer_on(_ADJUST);
    } else {
      layer_off(_ADJUST);
    }
    break;

  case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
    if (!record->event.pressed) {
      uint8_t temp_mod = get_mods();
      uint8_t temp_osm = get_oneshot_mods();
      clear_mods(); clear_oneshot_mods();
      send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), MACRO_TIMER);
#ifndef MAKE_BOOTLOADER
      if ( ( temp_mod | temp_osm ) & MOD_MASK_SHIFT )
#endif
      {
        #if defined(__arm__)
          send_string_with_delay_P(PSTR(":dfu-util"), MACRO_TIMER);
        #elif defined(BOOTLOADER_DFU)
          send_string_with_delay_P(PSTR(":dfu"), MACRO_TIMER);
        #elif defined(BOOTLOADER_HALFKAY)
          send_string_with_delay_P(PSTR(":teensy"), MACRO_TIMER);
        #elif defined(BOOTLOADER_CATERINA)
          send_string_with_delay_P(PSTR(":avrdude"), MACRO_TIMER);
        #endif // bootloader options
       }
      if ( ( temp_mod | temp_osm ) & MOD_MASK_CTRL) { send_string_with_delay_P(PSTR(" -j8 --output-sync"), MACRO_TIMER); }
      send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), MACRO_TIMER);
      set_mods(temp_mod);
      set_oneshot_mods(temp_osm);
    }
    break;

  case VRSN: // Prints firmware version
    if (record->event.pressed) {
      send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), MACRO_TIMER);
    }
    break;

  case KC_CCCV:                                    // One key copy/paste
    if(record->event.pressed){
      copy_paste_timer = timer_read();
    } else {
      if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {   // Hold, copy
        register_code(KC_LCTL);
        tap_code(KC_C);
        unregister_code(KC_LCTL);
      } else {                                // Tap, paste
        register_code(KC_LCTL);
        tap_code(KC_V);
        unregister_code(KC_LCTL);
      }
    }
    break;
  }
  return process_record_keymap(keycode, record) &&
#ifdef RGBLIGHT_ENABLE
    process_record_user_rgb(keycode, record) &&
#endif // RGBLIGHT_ENABLE
    process_record_secrets(keycode, record);
}
