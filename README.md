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

## 36-key layout (`36key/keymap.c`)

### `_DEF` (base)

```text
Q      W      E      R      T      | Y      U      I      O      P
A      S      D      F      G      | H      J      K      L      ;
Z      X      C      V      B      | N      M      ,      .      /
              CMD    SPC    NAV    | SYM    SFT    MAC
```

### `_SYM` (symbols)

```text
!      :      #      $      %      | '      "      *      |      \
-      +      =      _      [      | ]      {      }      (      )
~      `      <      >      ?      | /      &      ^      ;      @
              TRNS   TRNS   TRNS   | TRNS   TRNS   TRNS
```

### `_NAV` (navigation + editing)

```text
SW_TAB SW_WIN TAB_L  TAB_R  OS_SHF | ESC    HOME   UP     BSPC   DEL
OS_CMD OS_ALT OS_CTRL ESC    ENT    | ENT    LEFT   DOWN   RGHT   END
SPC_L  SPC_R  UNDO   REDO   TAB    | TAB    PGUP   PGDN   QUOT   NUM
              TRNS   TRNS   TRNS   | TRNS   TRNS   TRNS
```

### `_NUM` (numbers + media + River)

```text
1      2      3      4      5      | 6      7      8      9      0
MPRV   MNXT   MSTP   MPLY   RIV_PRV | RIV_NXT OS_SHF OS_CTRL OS_ALT OS_CMD
VOL-   VOL+   RIV_LN RIV_RD RIV_RI | RIV_TRM RIV_CLS RIV_LN F9     F10
              TRNS   TRNS   TRNS   | TRNS   TRNS   TRNS
```

### `_MAC` (macOS helpers)

```text
SPOT   LANG   SS_FULL SS_AREA SS_CLP | RECT_L RECT_R RECT_MX RECT_CT TRNS
MISSION APPWIN LOCK    APP_NXT APP_PRV | CMD+W  CMD+T  CMD+N  CMD+Q  TRNS
RESET  MUTE   VOL-    VOL+    MPLY   | MPRV   MNXT   BRI-   BRI+   NO
                TRNS  TRNS    TRNS   | TRNS   TRNS   TRNS
```

## 34-key layout (`34key/keymap.c`)

### `_DEF` (base)

```text
Q      W      E      R      T      | Y      U      I      O      P
A      S      D      F      G      | H      J      K      L      ;
Z      X      C      V      B      | N      M      ,      .      /
                     SPC    NAV    | SYM    SFT
```

### `_SYM` (symbols)

```text
!      :      #      $      %      | '      "      *      |      \
-      +      =      _      [      | ]      {      }      (      )
~      `      <      >      ?      | /      &      ^      ;      @
                     TRNS   TRNS   | TRNS   TRNS
```

### `_NAV` (navigation + editing)

```text
SW_TAB TAB_L  SW_WIN RELOAD VIM_U  | VIM_D  HOME   UP     BSPC   DEL
OS_CMD OS_ALT OS_CTRL ESC    ENT    | ENT    LEFT   DOWN   RGHT   END
UNDO   CUT    PASTE  COPY   TAB    | TAB    PGUP   PGDN   QUOT   NUM
                     TRNS   TRNS   | TRNS   TRNS
```

### `_NUM` (numbers + macOS tools)

```text
1      2      3      4      5      | 6      7      8       9       0
SPOT   LANG   SS_FULL SS_AREA SS_CLP | RECT_L RECT_R RECT_MX RECT_CT MISSION
VOL-   VOL+   MUTE    MPRV    MPLY  | MNXT   APPWIN APP_NXT APP_PRV LOCK
                     TRNS    TRNS   | TRNS   TRNS
```

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
