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

#define VIM_U C(KC_U)
#define VIM_D C(KC_D)
#define CTRL_V C(KC_V)
#define CTRL_C C(KC_C)
#define CTRL_R C(KC_R)
#define CTRL_T C(KC_T)
#define CTRL_F C(KC_F)

// macOS helpers
#define MAC_SPOTLIGHT G(KC_SPC)
#define MAC_LANGSW C(KC_SPC)
#define MAC_SS_FULL S(G(KC_3))
#define MAC_SS_SEL S(G(KC_4))
#define MAC_SS_CLIP C(S(G(KC_4)))

// Rectangle defaults: Ctrl+Alt+Arrow / Enter / C
#define RECT_LEFT C(A(KC_LEFT))
#define RECT_RIGHT C(A(KC_RGHT))
#define RECT_MAX C(A(KC_ENT))
#define RECT_CENTER C(A(KC_C))

#define MAC_MISSION C(KC_UP)
#define MAC_APPWIN C(KC_DOWN)
#define MAC_LOCK C(G(KC_Q))
#define MAC_SWITCH G(KC_TAB)
#define MAC_SWITCH_BACK S(G(KC_TAB))

enum layers { _DEF,
    _SYM,
    _NAV,
    _NUM };

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    SW_WIN, // Switch to next window (alt-tab) - kept for compatibility
    SW_TAB, // Switch to next browser tab (ctrl-tab)
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
        SW_TAB,  TAB_L,   SW_WIN,  C(KC_R), VIM_U,   VIM_D,   KC_HOME, KC_UP,   KC_BSPC, KC_DEL,
        OS_CMD,  OS_ALT,  OS_CTRL, KC_ESC,  KC_ENT,  KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        C(KC_Z), C(KC_X), C(KC_V), C(KC_C), KC_TAB,  KC_TAB,  KC_PGUP, KC_PGDN, KC_QUOT, KC_NUM,
                                   _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_2(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        MAC_SPOTLIGHT, MAC_LANGSW, MAC_SS_FULL, MAC_SS_SEL, MAC_SS_CLIP, RECT_LEFT, RECT_RIGHT, RECT_MAX, RECT_CENTER, MAC_MISSION,
        KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, MAC_APPWIN, MAC_SWITCH, MAC_SWITCH_BACK, MAC_LOCK,
                                   _______, _______, _______, _______
    )
};
// clang-format on

bool is_oneshot_cancel_key(uint16_t keycode)
{
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode)
{
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

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
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

layer_state_t layer_state_set_user(layer_state_t state)
{
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
