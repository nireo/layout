#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

#define RESET QK_BOOT
#define ___ KC_NO
#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define QUOT S(KC_GRV)
#define PIPE S(KC_BSLS)
#define DPIPE S(RALT(KC_BSLS))
#define SCLN S(KC_LBRC)
#define CLN S(KC_RBRC)
#define GRV RALT(KC_GRV)
#define BSL RALT(KC_BSLS)
#define NBSP RALT(KC_SPC)
#define SPACE_L C(G(KC_LEFT))
#define SPACE_R C(G(KC_RGHT))
#define TAB_L C(S(KC_TAB))
#define TAB_R C(KC_TAB)

enum layers {
  _DEF,
  _SYM,
  _NAV,
  _NUM,
};

enum keycodes {
  // Custom oneshot mod implementation with no timers.
  OS_SHFT = SAFE_RANGE,
  OS_CTRL,
  OS_ALT,
  OS_CMD,
  SW_WIN, // Switch to next window (alt-tab)
  SW_TAB, // Switch to next browser tab (ctrl-tab)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_ESC,  KC_SPC,  LA_NAV,  LA_SYM,  KC_LSFT, KC_LGUI
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_SCLN, GRV,     KC_GRV,  QUOT,    KC_MINS, KC_PLUS, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        BSL,     DPIPE,   SCLN,    KC_LBRC, KC_UNDS, KC_EQL,  KC_RBRC, CLN,     PIPE,    KC_BSLS,
        _______,  _______, _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        SW_TAB,  SW_WIN,  TAB_L,   TAB_R,   KC_ESC,  KC_ESC,  KC_HOME, KC_END,  KC_BSPC, KC_DEL,
        OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, KC_ENT,  KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        SPACE_L, SPACE_R, _______, KC_PSCR, KC_TAB,  KC_TAB,  KC_PGUP, KC_PGDN, KC_QUOT, KC_NUM,
        _______, _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,
        OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, KC_F11,  KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        _______, _______, _______, _______, _______, _______
    )
};
// clang-format on

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case LA_SYM:
  case LA_NAV:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case LA_SYM:
  case LA_NAV:
  case KC_LSFT:
  case OS_SHFT:
  case OS_CTRL:
  case OS_ALT:
  case OS_CMD:
    return true;
  default:
    return false;
  }
}

bool sw_win_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  update_swapper(&sw_win_active, KC_LALT, KC_TAB, SW_WIN, OS_SHFT, keycode,
                 record);
  update_swapper(&sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, OS_SHFT, keycode,
                 record);

  update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
  update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
  update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
  update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYM, _NAV, _NUM);
