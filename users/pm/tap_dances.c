#include "tap_dances.h"
#include "action.h"
#include "action_layer.h"
#include "action_util.h"
#include "quantum.h"
#include "wait.h"


//define diablo macro timer variables
uint16_t diablo_timer[4];
uint8_t diablo_times[] = { 0, 1, 3, 5, 10, 30 };
uint8_t diablo_key_time[4];

// has the correct number of seconds elapsed (as defined by diablo_times)
bool check_dtimer(uint8_t dtimer) { return (timer_elapsed(diablo_timer[dtimer]) < (diablo_key_time[dtimer] * 1000)) ? false : true; };

// Cycle through the times for the macro, starting at 0, for disabled.
// Max of six values, so don't exceed
void diablo_tapdance_master(qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
  if (state->count >= 7) {
    diablo_key_time[diablo_key] = diablo_times[0];
    reset_tap_dance(state);
  }  else {
    diablo_key_time[diablo_key] = diablo_times[state->count - 1];
  }
}

// Would rather have one function for all of this, but no idea how to do that...
void diablo_tapdance1(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 0); }
void diablo_tapdance2(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 1); }
void diablo_tapdance3(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 2); }
void diablo_tapdance4(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 3); }

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // tap once to disable, and more to enable timed micros
  [TD_LEFT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(KC_LBRC, KC_LPRN),
  [TD_RIGHT_BRACE_OR_PRN] = ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(KC_RBRC, KC_RPRN),
  [TD_SEMICOLON_OR_COLON] = ACTION_TAP_DANCE_SHIFT_WITH_DOUBLE(KC_SCLN),
  [TD_TASKSWITCH] = ACTION_TAP_DANCE_TSKSWCH(),  // switch application / switch windows (windows)
  [TD_GUI_OR_LOCK_WORKSTATION] = {
    .fn = { NULL, td_gui_on_finished, td_gui_on_reset },
    .user_data = ((void *)KC_LGUI),
  },
  [TD_ALT_OR_LOCK_WORKSTATION] = ACTION_TAP_DANCE_MULTITAP(KC_SPC, KC_LALT, KC_ENT, KC_LALT),
  //  [TD_GUI_OR_ESC] = ACTION_TAP_DANCE_DOUBLE_RESTORE_MODS(KC_LGUI, KC_ESC)
  [TD_GUI_OR_ESC] = ACTION_TAP_DANCE_MULTITAP(KC_ENT, KC_LGUI, KC_ENT, KC_RGUI)
};

void td_mod_tap_on_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->pressed && state->count == 1) {
        register_mods(pair->kc1);
        state->count = TD_PRESSED_EVENT; // magic number for reset
    } else if (state->count >= 1) {
        register_code16(pair->kc2);
    }
}

void td_mod_tap_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == TD_PRESSED_EVENT) {
        unregister_mods(pair->kc1);
    } else if (state->count >= 1) {
        unregister_code16(pair->kc2);
    }
}

void td_mod_tap_lock_on_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->pressed) {
        register_mods(pair->kc1);
    }
#ifndef NO_ACTION_ONESHOT
    else if (state->count == 1) {
        if (!(pair->kc1 & get_oneshot_locked_mods())) { // if match we need to clear the oneshot locked mods 1st
            register_code16(pair->kc2);
            unregister_code16(pair->kc2);
            state->count = TD_PRESSED_EVENT; // magic count that skip reset
        }
    }
#if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE > 1
    else if (state->count == ONESHOT_TAP_TOGGLE) {
        set_oneshot_locked_mods(pair->kc1);
        register_mods(pair->kc1);
    }
#endif
#endif
}

void td_mod_tap_lock_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

#if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE > 1
    if (state->count == ONESHOT_TAP_TOGGLE) { // locking mods
        return;
    }
#endif

    if (state->count >= 1) {
        unregister_mods(pair->kc1);
#ifndef NO_ACTION_ONESHOT
        clear_oneshot_locked_mods();
#endif
    }
}


void td_tskswch_on_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) {
    register_code(KC_LALT);
    wait_ms(250);
    register_code(KC_TAB);
    unregister_code(KC_TAB);
    state->count = 3;
  } else {
    switch (state->count) {
      case 1:
        register_code16(LALT(KC_TAB));
        break;
      case 2:
        register_code(KC_LALT);
        wait_ms(250);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        wait_ms(250);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        break;
    }
  }
}

void td_tskswch_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
      case 1:
        unregister_code16(LALT(KC_TAB));
        break;
      case 2:
        unregister_code(KC_LALT);
        break;
      case 3:
        unregister_code(KC_LALT);
        break;
    }
}

#define GET_KEYCODE_FROM_VOIDPTR(p) ((uint8_t)*(uint8_t *)&p)

void td_gui_on_finished(qk_tap_dance_state_t *state, void *user_data) {
  uint8_t kc = GET_KEYCODE_FROM_VOIDPTR(user_data);

  if (state->pressed) {
    register_mods(MOD_BIT(kc));
  } else if (state->count == 1) {
    register_mods(MOD_BIT(kc));
  // } else if (state->count == ONESHOT_TAP_TOGGLE) {
  //   register_mods(MOD_BIT(kc));
  } else if (state->count == 2) {
    register_code16(KC_ENT);
    unregister_code16(KC_ENT);
  } else if (state->count == 3) {
    register_code16(LGUI(KC_L));
    unregister_code16(LGUI(KC_L));
  }
}

void td_gui_on_reset(qk_tap_dance_state_t *state, void *user_data) {
  // if (state->count == ONESHOT_TAP_TOGGLE) {
  //   return;
  // }
  if (state->count == 2) {
    return;
  }
  uint8_t kc = GET_KEYCODE_FROM_VOIDPTR(user_data);
  unregister_mods(MOD_BIT(kc));
}

void td_layer_toggle_on_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc2);
    } else if (state->count == 2) {
        if (IS_LAYER_ON(pair->kc1)) {
            layer_off(pair->kc1);
        } else {
            layer_on(pair->kc1);
        }
    }
}

void td_layer_toggle_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        unregister_code16(pair->kc2);
    }
}

#define tp_get_mods(kc) ((uint8_t)(kc >> 8) & 0x1f)

void tp_register_code(uint16_t kc) {
    uint8_t mods = tp_get_mods(kc);
    if (mods) {
        add_weak_mods(mods);
    }
    register_code(kc);
}

void tp_unregister_code(uint16_t kc) {
    uint8_t mods = tp_get_mods(kc);
    if (mods) {
        del_weak_mods(mods);
    }
    unregister_code(kc);
}

void td_pair_restore_mods_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        tp_register_code(pair->kc1);
    } else if (state->count == 2) {
        tp_register_code(pair->kc2);
    }
}

void td_pair_restore_mods_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        tp_unregister_code(pair->kc1);
    } else if (state->count == 2) {
        tp_unregister_code(pair->kc2);
    }
}

//td quad region

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
};

typedef struct {
  bool is_press_action;
  int state;
} td_quad_tap;

int td_quad_cur_dance (qk_tap_dance_state_t *state) {
  if (state->pressed) {
    return SINGLE_HOLD;
  }
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || state->pressed == 0) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `xx` instead of `Escape`.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'td_quad_tap' for the 'td_quad' tap dance.
static td_quad_tap td_quad_state = {
  .is_press_action = true,
  .state = 0
};

void td_quad_finished (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_quad_t *quadruple = (qk_tap_dance_quad_t *)user_data;
  td_quad_state.state = td_quad_cur_dance(state);
  switch (td_quad_state.state) {
    case SINGLE_TAP: register_code16(quadruple->kc1); break;
    case SINGLE_HOLD: register_code16(quadruple->kc2); break;
    case DOUBLE_TAP: register_code16(quadruple->kc3); break;
    case DOUBLE_HOLD: register_code16(quadruple->kc4); break;
    case DOUBLE_SINGLE_TAP: register_code16(quadruple->kc1); unregister_code16(quadruple->kc1); register_code16(quadruple->kc1);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void td_quad_reset (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_quad_t *quadruple = (qk_tap_dance_quad_t *)user_data;
  switch (td_quad_state.state) {
    case SINGLE_TAP: unregister_code16(quadruple->kc1); break;
    case SINGLE_HOLD: unregister_code16(quadruple->kc2); break;
    case DOUBLE_TAP: unregister_code16(quadruple->kc3); break;
    case DOUBLE_HOLD: unregister_code16(quadruple->kc4);
    case DOUBLE_SINGLE_TAP: unregister_code16(quadruple->kc1);
  }
  td_quad_state.state = 0;
}
