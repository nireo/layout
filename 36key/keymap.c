#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

#define RESET QK_BOOT
#define ___ KC_NO
#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_MAC MO(_MAC)
#define LA_NUM MO(_NUM)
#define LA_EXT MO(_EXT)
#define QUOT S(KC_GRV)
#define PIPE S(KC_BSLS)
#define DPIPE S(RALT(KC_BSLS))
#define SCLN S(KC_LBRC)
#define CLN S(KC_RBRC)
#define GRV RALT(KC_GRV)
#define BSL RALT(KC_BSLS)
#define NBSP RALT(KC_SPC)
#define SPACE_L C(KC_LEFT)
#define SPACE_R C(KC_RGHT)
#define TAB_L C(S(KC_TAB))
#define TAB_R C(KC_TAB)

#define MAC_SPOTLIGHT G(KC_SPC)
#define MAC_ALFRED G(KC_SPC)
#define MAC_MISSION C(KC_UP)
#define MAC_APP_EXPOSE C(KC_DOWN)
#define MAC_DESKTOP KC_F11
#define MAC_LAUNCHPAD KC_F4
#define MAC_DOCK G(A(KC_D))

#define WIN_CLOSE G(KC_W)
#define WIN_QUIT G(KC_Q)
#define WIN_MINIMIZE G(KC_M)
#define WIN_HIDE G(KC_H)
#define WIN_CYCLE G(KC_TAB)
#define WIN_CYCLE_REV G(S(KC_TAB))
#define WIN_FULL G(C(KC_F))

#define SCREENSHOT_FULL G(S(KC_3))
#define SCREENSHOT_AREA G(S(KC_4))
#define SCREENSHOT_WINDOW G(S(KC_4))
#define SCREENSHOT_CLIPBOARD G(C(S(KC_3)))
#define SCREENSHOT_AREA_CLIP G(C(S(KC_4)))

#define LANG_SWITCH G(KC_SPC)
#define LANG_NEXT C(KC_SPC)
#define LANG_PREV C(S(KC_SPC))

#define APP_FINDER G(A(KC_SPC))

#define SYS_LOCK C(G(KC_Q))
#define SYS_SLEEP G(A(KC_POWER))
#define SYS_RESTART C(G(KC_POWER))
#define SYS_SHUTDOWN C(A(G(KC_POWER)))

#define VIM_U C(KC_U)
#define VIM_D C(KC_D)
#define CTRL_V G(KC_V)
#define CTRL_C G(KC_C)
#define CTRL_R G(KC_R)
#define CTRL_T G(KC_T)
#define CTRL_F G(KC_F)
#define CTRL_A G(KC_A)
#define CTRL_S G(KC_S)
#define CTRL_Z G(KC_Z)
#define CTRL_Y G(S(KC_Z))

enum layers { _DEF, _SYM, _NAV, _MAC, _NUM, _EXT };

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    SW_WIN, // Switch to next window (cmd-tab)
    SW_TAB, // Switch to next browser tab (cmd-shift-])
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          LA_EXT,  KC_SPC,  LA_NAV,  LA_SYM,  KC_LSFT, LA_MAC
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_COLN, KC_HASH, KC_DLR,  KC_PERC, KC_QUOT, KC_DQUO, KC_ASTR, KC_PIPE, KC_BSLS,
        KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN,
        KC_TILD, KC_GRV,  KC_LABK, KC_RABK, KC_QUES, KC_SLSH, KC_AMPR, KC_CIRC, KC_SCLN, KC_AT,
                          _______, _______, _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        SW_TAB,  SW_WIN,  TAB_L,   TAB_R,   OS_SHFT, KC_ESC,  KC_HOME, KC_UP,   KC_BSPC, KC_DEL,
        OS_CMD,  OS_ALT,  OS_CTRL, KC_ESC,  KC_ENT,  KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        SPACE_L, SPACE_R, CTRL_Z,  G(S(KC_Z)), KC_TAB, KC_TAB, KC_PGUP, KC_PGDN, KC_QUOT, KC_NUM,
                          _______, _______, _______, _______, _______, _______
    ),

    [_MAC] = LAYOUT_split_3x5_3(
        _______,       _______,       MAC_MISSION,      MAC_APP_EXPOSE,   MAC_DESKTOP,     SCREENSHOT_FULL, SCREENSHOT_AREA, SCREENSHOT_CLIPBOARD, SCREENSHOT_AREA_CLIP, WIN_CLOSE,
        MAC_SPOTLIGHT, WIN_CYCLE,     WIN_MINIMIZE,     WIN_HIDE,         WIN_FULL,        LANG_NEXT,       LANG_PREV,       WIN_QUIT,             MAC_LAUNCHPAD,        MAC_DOCK,
        _______,       APP_FINDER,    CTRL_C,           CTRL_V,           SYS_LOCK,        SYS_SLEEP,       CTRL_A,          CTRL_S,               CTRL_F,               SYS_SHUTDOWN,
                            _______, _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, KC_VOLU, KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        KC_VOLD, KC_VOLU, KC_MUTE, KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                          _______, _______, _______, _______, _______, _______
    ),

    [_EXT] = LAYOUT_split_3x5_3(
        G(KC_W),  G(KC_W), KC_MS_U,  CTRL_R,  CTRL_T,    KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_9,
        CTRL_A,   CTRL_S,  KC_MS_D,  CTRL_F,  KC_PLUS,   KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, G(KC_TAB),
        KC_SLSH,  KC_ASTR, CTRL_C,   CTRL_V,  KC_MINS,   KC_COMM, KC_BTN1, KC_WH_D, KC_BTN2, KC_LCMD,
                          _______, _______, _______, _______, _______, _______
    )
};
// clang-format on

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case LA_EXT:
        case LA_MAC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_EXT:
        case LA_NAV:
        case LA_MAC:
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
    // Mac uses Cmd+Tab for app switching, Cmd+Shift+] for browser tabs
    update_swapper(&sw_win_active, KC_LCMD, KC_TAB, SW_WIN, OS_SHFT, keycode, record);
    update_swapper(&sw_tab_active, KC_LCMD, G(S(KC_RBRC)), SW_TAB, OS_SHFT, keycode, record);

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
