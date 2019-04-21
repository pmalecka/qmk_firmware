#pragma once
#include "pm2.h"

//define diablo macro timer variables
extern uint16_t diablo_timer[4];
extern uint8_t diablo_times[];
extern uint8_t diablo_key_time[4];


void run_diablo_macro_check(void);

#ifdef TAP_DANCE_ENABLE
enum {
  TD_TASKSWITCH = 0,
  TD_LEFT_BRACE_OR_PRN,
  TD_RIGHT_BRACE_OR_PRN,
  TD_SEMICOLON_OR_COLON,
  TD_ALT_OR_LOCK_WORKSTATION,
  TD_GUI_OR_ESC,
  TD_GUI_OR_LOCK_WORKSTATION,
  TD_D3_1,
  TD_D3_2,
  TD_D3_3,
  TD_D3_4
};
#endif // TAP_DANCE_ENABLE


#include "process_keycode/process_tap_dance.h"

#define TD_PRESSED_EVENT 0xFF

typedef struct
{
  uint16_t kc1;
  uint16_t kc2;
  uint16_t kc3;
  uint16_t kc4;
} qk_tap_dance_quad_t;

// kc1 is a mods and kc2 is a keycode
// ACTION_TAP_DANCE_MOD_TAP(MOD_LALT, KC_LBRC)
#define ACTION_TAP_DANCE_MOD_TAP(kc1, kc2) {                            \
    .fn = { NULL, td_mod_tap_on_finished, td_mod_tap_on_reset },        \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),         \
  }

#define ACTION_TAP_DANCE_MOD_TAP_LOCK(kc1, kc2) {                          \
    .fn = { NULL, td_mod_tap_lock_on_finished, td_mod_tap_lock_on_reset }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),            \
  }

#define ACTION_TAP_DANCE_TSKSWCH() {                                    \
    .fn = { NULL, td_tskswch_on_finished, td_tskswch_on_reset },        \
    .user_data = NULL,                                                  \
  }

#define ACTION_TAP_DANCE_LAYER_TAP(kc1, kc2) {                  \
    .fn = { NULL, td_layer_toggle_on_finished, td_layer_toggle_on_reset }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }), \
  }

#define ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(kc1, kc2) {                \
    .fn = { NULL, td_pair_restore_mods_finished, td_pair_restore_mods_reset}, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),         \
  }

#define ACTION_TAP_DANCE_SHIFT_WITH_DOUBLE(kc)          \
  ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(kc, LSFT(kc))

#define ACTION_TAP_DANCE_MULTITAP(kc1, kc2, kc3, kc4) {                \
    .fn = { NULL, td_quad_finished, td_quad_reset}, \
    .user_data = (void *)&((qk_tap_dance_quad_t) { kc1, kc2, kc3, kc4 }),         \
  }

void td_mod_tap_on_finished(qk_tap_dance_state_t *state, void *user_data);
void td_mod_tap_on_reset(qk_tap_dance_state_t *state, void *user_data);

void td_mod_tap_lock_on_finished(qk_tap_dance_state_t *state, void *user_data);
void td_mod_tap_lock_on_reset(qk_tap_dance_state_t *state, void *user_data);

void td_tskswch_on_finished(qk_tap_dance_state_t *state, void *user_data);
void td_tskswch_on_reset(qk_tap_dance_state_t *state, void *user_data);

void td_gui_on_finished(qk_tap_dance_state_t *state, void *user_data);
void td_gui_on_reset(qk_tap_dance_state_t *state, void *user_data);

void td_layer_toggle_on_finished(qk_tap_dance_state_t *state, void *user_data);
void td_layer_toggle_on_reset(qk_tap_dance_state_t *state, void *user_data);

void td_pair_restore_mods_finished(qk_tap_dance_state_t *state, void *user_data);
void td_pair_restore_mods_reset(qk_tap_dance_state_t *state, void *user_data);

void td_quad_finished (qk_tap_dance_state_t *state, void *user_data);
void td_quad_reset (qk_tap_dance_state_t *state, void *user_data);
