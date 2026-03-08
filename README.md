# Keyboard Layouts

Custom QMK keymaps for two split boards:

- `36key/keymap.c` - 36-key layout (`LAYOUT_split_3x5_3`)
- `34key/keymap.c` - 34-key layout (`LAYOUT_split_3x5_2`)

## Shared behavior

- Oneshot mods: `OS_SHFT`, `OS_CTRL`, `OS_ALT`, `OS_CMD`
- Swapper keys:
  - `SW_WIN`: Alt+Tab switcher (`Alt` stays held while you keep pressing `Tab`)
  - `SW_TAB`: Ctrl+Tab switcher (`Ctrl` stays held while you keep pressing `Tab`)
- Hold `OS_SHFT` while swapping to go in reverse
- Tri-layer: holding `NAV` + `SYM` activates `NUM`

## Layout diagram

The full keymap diagram lives in `assets/my_keymap.svg`.

![Keyboard layout diagram](assets/my_keymap.svg)

## Keymap files

- `36key/keymap.c` - 36-key layers and behavior
- `34key/keymap.c` - 34-key layers and behavior

## Legend

- `TRNS`: transparent key (`_______`)
- `NO`: no key (`KC_NO`)
- `OS_SHF/OS_CTRL/OS_ALT/OS_CMD`: oneshot Shift/Ctrl/Alt/Cmd
- `TAB_L`, `TAB_R`: browser tab left/right (`Ctrl+Shift+Tab`, `Ctrl+Tab`)
- `SPC_L`, `SPC_R`: move to previous/next macOS Space
- `SPOT`: Spotlight (`Cmd+Space`)
- `LANG`: input language switch (`Ctrl+Space`)
- `SS_FULL`, `SS_AREA`, `SS_CLP`: full screenshot, area screenshot, area to clipboard
- `RECT_L`, `RECT_R`, `RECT_MX`, `RECT_CT`: Rectangle defaults (`Ctrl+Alt+Arrow`, `Ctrl+Alt+Enter`, `Ctrl+Alt+C`)
- `MISSION`, `APPWIN`: Mission Control / App Expose
- `APP_NXT`, `APP_PRV`: app switch next/previous (`Cmd+Tab`, `Shift+Cmd+Tab`)
- River labels in 36-key `_NUM`: `RIV_PRV`, `RIV_NXT`, `RIV_RD`, `RIV_RI`, `RIV_TRM`, `RIV_CLS`, `RIV_LN`
