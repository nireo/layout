# Keyboard Layout

This keyboard layout uses oneshot mods meaning that there are no delays. Pressing a one shot mod key queues up that key until a non-modifier key is pressed. This layout is mainly focused on programming and using a tiling window manager.

## 36 key layout

### Default Layer (_DEF)

```
Q   | W   | E   | R   | T   |   | Y   | U   | I   | O   | P
A   | S   | D   | F   | G   |   | H   | J   | K   | L   | ;
Z   | X   | C   | V   | B   |   | N   | M   | ,   | .   | /
            EXT | SPC | NAV |   | SYM | LSFT| RIV
```

### Symbol Layer (_SYM)

```
!   | :   | #   | $   | %   |   | '   | "   | *   | |   | \
-   | +   | =   | _   | [   |   | ]   | {   | }   | (   | )
~   | `   | <   | >   | ?   |   | /   | &   | ^   | ;   | @
```

### Navigation Layer (_NAV)

```
STAB| SWIN| TABL| TABR| SFHT|   | ESC | HOME| UP  | BSPC | DEL
CMD | ALT | CTRL| ESC | ENT |   | ENT | LEFT| DOWN| RGHT | END
SPCL| SPCR| UNDO| REDO| TAB |   | TAB | PGUP| PGDN| '    | NUM
```


### Window and extra manager Layer (_RIV)
```
TAG1| TAG2| TAG3| TAG4| TAG5|   | TAG6| TAG7| TAG8| TAG9| CLOS
LAUN| LAST| PREV| NEXT| FLOT|   | FULL| LEFT| DOWN| UP  | RGHT
TERM| ___ | C+C | C+V | RDEC|   | RINC| C+R | C+T | C+F | ___
```

### Number Layer (_NUM)
```
1     | 2       | 3         | 4    | 5   |   | 6   | 7   | 8   | 9   | 0
MPRV  | MNXT    | MPLY      | VOLUP| F11 |   | F12 | SHFT| CTRL| ALT | CMD
VOLUP | VOLDOWN | VOLDOWN   | F4   | F5  |   | F6  | F7  | F8  | F9  | F10
```

### Extra Layer (_NUM)
```
AF4   | CTRLW | _____ | CTRLR | CTRLT |   | .   | 1   | 2   | 3  | 0
CTRLA | CTRLS | CTRLD | CTRLF | +     |   | 0   | 4   | 5   | 6  | CMDTAB
/     | *     | CTRLC | CTRLV | -     |   | ,   | 7   | 8   | 9  | F10
```

## 34 key layout

More minimal layout with 34 keys. Focusing mainly on a simple layout for programming and using a tiling window manager. I mainly use this keyboard on my desktop linux machine and the other one is for my mac laptop. Therefore, some of the navigation keys will be different.

```
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
        KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, RIV_FOCUS_PREV, RIV_FOCUS_NEXT,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, RIV_LAUNCHER, RIV_RATIO_DEC, RIV_RATIO_INC, RIV_TERM, RIV_CLOSE, KC_F8, KC_F9, KC_F10,
                                   _______, _______, _______, _______
    )
```
