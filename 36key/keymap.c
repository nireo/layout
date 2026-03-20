#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_NUM MO(_NUM)
#define LA_WM MO(_WM)
#define TAB_L C(S(KC_TAB))

#define VIM_U C(KC_U)
#define VIM_D C(KC_D)

#define AER_KITTY A(KC_ENT)
#define AER_RESIZE A(KC_R)
#define AER_FLOAT A(S(KC_SPC))
#define AER_RELOAD A(S(KC_C))

#define KIT_PRE C(KC_W)
#define KIT_SPLIT_H C(KC_MINS)
#define KIT_SPLIT_V C(S(KC_BSLS))

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

#define MAC_APPWIN C(KC_DOWN)
#define MAC_LOCK C(G(KC_Q))
#define MAC_SWITCH_BACK S(G(KC_TAB))
#define MAC_TEXT_INC G(KC_EQL)
#define MAC_TEXT_DEC G(KC_MINS)

enum layers { _DEF,
    _SYM,
    _NAV,
    _NUM,
    _WM };

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    SW_APP, // Switch to next app (cmd-tab)
    SW_WIN, // Switch to next window (alt-tab) - kept for compatibility
    SW_TAB, // Switch to next browser tab (ctrl-tab)
    KIT_FOCUS_L,
    KIT_FOCUS_D,
    KIT_FOCUS_U,
    KIT_FOCUS_R,
    KIT_QUIT,
    KIT_EQ, // Kitty equalize panes (ctrl-w =)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          KC_LCMD, KC_SPC,  LA_NAV,  LA_SYM,  KC_LSFT, LA_WM
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_COLN, KC_HASH, KC_DLR,  KC_PERC, KC_QUOT, KC_DQUO, KC_ASTR, KC_PIPE, KC_BSLS,
        KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN,
        KC_TILD, KC_GRV,  KC_LABK, KC_RABK, KC_QUES, KC_SLSH, KC_AMPR, KC_CIRC, KC_SCLN, KC_AT,
                          _______, _______, _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        TAB_L,   SW_TAB,  SW_APP,  MAC_SWITCH_BACK, VIM_U,   VIM_D,   KC_HOME, KC_UP,   KC_BSPC, KC_DEL,
        OS_CMD,  OS_ALT,  OS_CTRL, KC_ESC,  KC_ENT,  KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        G(KC_Z), G(KC_X), G(KC_V), G(KC_C), KC_TAB,  KC_TAB,  KC_PGUP, KC_PGDN, KC_QUOT, LA_NUM,
                          _______, _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        MAC_SPOTLIGHT, MAC_LANGSW, MAC_SS_FULL, MAC_SS_SEL, MAC_SS_CLIP, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, OS_CTRL, OS_ALT, OS_CMD,
        RECT_LEFT, RECT_CENTER, RECT_RIGHT, RECT_MAX, KC_MPLY, KC_MNXT, MAC_APPWIN, MAC_TEXT_INC, MAC_TEXT_DEC, MAC_LOCK,
                          _______, _______, _______, _______, _______, _______
    ),

    [_WM] = LAYOUT_split_3x5_3(
        A(KC_1),  A(KC_2),  A(KC_3),  A(KC_4),  A(KC_5),  A(KC_6),  A(KC_7),  A(KC_8),  A(KC_9),  A(KC_0),
        OS_ALT,   KIT_PRE,  AER_KITTY, AER_RESIZE, _______,  KIT_FOCUS_L, KIT_FOCUS_D, KIT_FOCUS_U, KIT_FOCUS_R, KIT_QUIT,
        _______,  _______,  AER_RELOAD, AER_FLOAT, _______,  KIT_SPLIT_H, KIT_SPLIT_V, KIT_EQ,  _______, _______,
                          _______, _______, _______, _______, _______, _______
    )
};
// clang-format on

static void send_kitty_prefix(uint16_t keycode)
{
    tap_code16(C(KC_W));
    tap_code16(keycode);
}

bool is_oneshot_cancel_key(uint16_t keycode)
{
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case LA_WM:
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
    case LA_WM:
    case KC_LSFT:
    case KC_LCMD:
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
bool sw_app_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    update_swapper(&sw_app_active, KC_LCMD, KC_TAB, SW_APP, OS_SHFT, keycode,
        record);
    update_swapper(&sw_win_active, KC_LALT, KC_TAB, SW_WIN, OS_SHFT, keycode,
        record);
    update_swapper(&sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, OS_SHFT, keycode,
        record);

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

    switch (keycode) {
    case KIT_FOCUS_L:
        if (record->event.pressed) {
            send_kitty_prefix(KC_H);
        }
        return false;
    case KIT_FOCUS_D:
        if (record->event.pressed) {
            send_kitty_prefix(KC_J);
        }
        return false;
    case KIT_FOCUS_U:
        if (record->event.pressed) {
            send_kitty_prefix(KC_K);
        }
        return false;
    case KIT_FOCUS_R:
        if (record->event.pressed) {
            send_kitty_prefix(KC_L);
        }
        return false;
    case KIT_QUIT:
        if (record->event.pressed) {
            send_kitty_prefix(KC_Q);
        }
        return false;
    case KIT_EQ:
        if (record->event.pressed) {
            send_kitty_prefix(KC_EQL);
        }
        return false;
    default:
        return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
