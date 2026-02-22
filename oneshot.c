#include "oneshot.h"

static bool* repeat_tab_flag(uint16_t mod)
{
    static bool cmd_tab_repeat = false;
    static bool ctrl_tab_repeat = false;

    switch (mod) {
    case KC_LCMD:
        return &cmd_tab_repeat;
    case KC_LCTL:
        return &ctrl_tab_repeat;
    default:
        return 0;
    }
}

void update_oneshot(
    oneshot_state* state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t* record)
{
    bool* tab_repeat = repeat_tab_flag(mod);

    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (tab_repeat) {
                *tab_repeat = false;
            }

            if (*state == os_up_unqueued) {
                register_code(mod);
            }

            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);

                if (tab_repeat) {
                    *tab_repeat = false;
                }

                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);

                if (tab_repeat) {
                    *tab_repeat = false;
                }
            }
        } else {
            if (tab_repeat && *tab_repeat && is_oneshot_cancel_key(keycode)
                && *state != os_up_unqueued) {
                // End Cmd/Ctrl+Tab repeating when layer hold key is released.
                *state = os_up_unqueued;
                unregister_code(mod);
                *tab_repeat = false;
            } else if (!is_oneshot_ignored_key(keycode)) {
                if (tab_repeat && keycode == KC_TAB && *state == os_up_queued) {
                    *tab_repeat = true;
                    return;
                }

                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);

                    if (tab_repeat) {
                        *tab_repeat = false;
                    }

                    break;
                default:
                    break;
                }
            }
        }
    }
}
