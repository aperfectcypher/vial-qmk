// Copyright 2024 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// VIA requires exactly the number of layers declared in config.h (DYNAMIC_KEYMAP_LAYER_COUNT).
// Default is 4. All entries are KC_TRNS so VIA can overwrite them at runtime.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                   KC_LGUI, MO(1),   KC_SPC,      KC_ENT,  MO(2),   KC_BSPC,
                                   KC_LALT, MO(3)
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
                                   _______, _______, _______,     KC_ESC,  _______, KC_DEL,
                                   _______, _______
    ),

    [2] = LAYOUT(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
        _______, _______, _______, KC_LCBR, KC_RCBR, KC_PLUS,     _______, _______, _______, _______, _______, KC_RBRC,
        _______, _______, _______, KC_LBRC, KC_RBRC, KC_EQL,      _______, _______, _______, _______, KC_COLN, KC_DQUO,
        _______, _______, _______, _______, _______, _______,     _______, _______, KC_LT,   KC_GT,   KC_QUES,
                                   _______, _______, _______,     _______, _______, _______,
                                   _______, _______
    ),

    [3] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,     _______, _______, _______, _______, KC_F11,  KC_F12,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
        _______, _______, _______, _______, _______, _______,     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,
        _______, _______, _______, _______, _______, _______,     KC_MPLY, KC_MUTE, _______, _______, _______,
                                   _______, _______, _______,     _______, _______, _______,
                                   _______, _______
    ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [2] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [3] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

bool oled_task_kb(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:  oled_write_P(PSTR("Base\n"), false); break;
            case 1:  oled_write_P(PSTR("Nav \n"), false); break;
            case 2:  oled_write_P(PSTR("Sym \n"), false); break;
            case 3:  oled_write_P(PSTR("Fn  \n"), false); break;
            default: oled_write_P(PSTR("?   \n"), false); break;
        }
        oled_write_P(PSTR("WPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), ' '), false);
    } else {
        oled_write_P(PSTR("Cosmotyl\n"), false);
        oled_write_P(PSTR("split 4x6\n"), false);
        oled_write_P(PSTR("trackball\n"), false);
    }
    return false;
}
#endif
