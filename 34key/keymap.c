#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

#define RESET QK_BOOT
#define ___ KC_NO
#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_NUM MO(_NUM)
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

#define RIV_FOCUS_NEXT G(KC_J) // Super+J: focus next window
#define RIV_FOCUS_PREV G(KC_K) // Super+K: focus prev window
#define RIV_RATIO_DEC G(KC_H)  // Super+H: decrease main ratio
#define RIV_RATIO_INC G(KC_L)  // Super+L: increase main ratio
#define RIV_CLOSE G(KC_Q)      // Super+Q: close window
#define RIV_LAUNCHER G(KC_D)   // Super+D: launcher
#define RIV_FLOAT G(KC_SPC)    // Super+Space: toggle float
#define RIV_FULL G(KC_F)       // Super+F: fullscreen
#define RIV_LAST G(KC_TAB)     // Super+Tab: focus last window
#define RIV_TERM G(KC_ENT)     // Super+Enter: open terminal
#define RIV_TAG1 G(KC_1)       // Super+1: tag 1
#define RIV_TAG2 G(KC_2)       // Super+2: tag 2
#define RIV_TAG3 G(KC_3)       // Super+3: tag 3
#define RIV_TAG4 G(KC_4)       // Super+4: tag 4
#define RIV_TAG5 G(KC_5)       // Super+5: tag 5
#define RIV_TAG6 G(KC_6)       // Super+6: tag 6
#define RIV_TAG7 G(KC_7)       // Super+7: tag 7
#define RIV_TAG8 G(KC_8)       // Super+8: tag 8
#define RIV_TAG9 G(KC_9)       // Super+9: tag 9
#define VIM_U C(KC_U)          // Ctrl+U: page up in vim
#define VIM_D C(KC_D)          // Ctrl+D: page down in vim
#define CTRL_V C(KC_V)
#define CTRL_C C(KC_C)
#define CTRL_R C(KC_R)
#define CTRL_T C(KC_T)
#define CTRL_F C(KC_F)

enum layers { _DEF, _SYM, _NAV, _NUM };

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    SW_WIN, // Switch to next window (alt-tab) - kept for compatibility
    SW_TAB, // Switch to next browser tab (ctrl-tab)
    // River WM shortcuts accessed via tap-hold
    RIV_SPC, // Space/River layer
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT_split_3x5_2(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                   KC_SPC,  LA_NAV,  LA_SYM,  KC_LSFT
    ),

    [_SYM] = LAYOUT_split_3x5_2(
        KC_EXLM, KC_COLN, KC_HASH, KC_DLR,  KC_PERC, KC_QUOT, KC_DQUO, KC_ASTR, KC_PIPE, KC_BSLS,
        KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN,
        KC_TILD, KC_GRV,  KC_LABK, KC_RABK, KC_QUES, KC_SLSH, KC_AMPR, KC_CIRC, KC_SCLN, KC_AT,
                                   _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_2(
        SW_TAB,  SW_WIN,  TAB_L,   TAB_R,   OS_SHFT, KC_ESC,  KC_HOME, KC_UP,   KC_BSPC, KC_DEL,
        OS_CMD,  OS_ALT,  OS_CTRL, KC_ESC,  KC_ENT,  KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        SPACE_L, SPACE_R, C(KC_Z), C(KC_Y), KC_TAB,  KC_TAB,  KC_PGUP, KC_PGDN, KC_QUOT, KC_NUM,
                                   _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_2(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, KC_VOLU, KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_VOLD, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
                                   _______, _______, _______, _______
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
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_cmd_state  = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LALT, KC_TAB, SW_WIN, OS_SHFT, keycode, record);
    update_swapper(&sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, OS_SHFT, keycode, record);

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
