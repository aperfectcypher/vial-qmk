// Copyright 2026 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0 — Base (AZERTY)
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │ Esc │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Tab │  A  │  Z  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │Caps │  Q  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  M  │  '  │ Bks │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │Shift│  W  │  X  │  C  │  V  │  B  │  N  │  ;  │  ,  │  .  │  /  │  Up │Shift│
     * ├─────┼─────┼─────┼─────┼─────┴─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     * │Ctrl │ GUI │ Alt │ Mo1 │   Space   │   Enter   │RAlt │RCtl │Left │Down │Right│ Enc
     * └─────┴─────┴─────┴─────┴───────────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_TAB,  KC_A,    KC_Z,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_CAPS, KC_Q,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_M,    KC_QUOT, KC_BSPC,
        KC_LSFT, KC_W,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(1),   KC_SPC,                    KC_ENT,  KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE
    ),

    /* Layer 1 — Navigation */
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______,
        KC_DEL,  _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______
    ),

    /* Layer 2 — Symbols / Numpad */
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,
        _______, _______, _______, KC_LCBR, KC_RCBR, KC_PLUS, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_LBRC, KC_RBRC, KC_EQL,  _______, _______, _______, _______, KC_COLN, KC_DQUO, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LT,   KC_GT,   KC_QUES, _______,
        _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______
    ),

    /* Layer 3 — Media / System */
    [3] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MUTE, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______
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

static void draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    for (uint8_t dy = 0; dy < h; dy++)
        for (uint8_t dx = 0; dx < w; dx++)
            oled_write_pixel(x + dx, y + dy, true);
}

static void draw_logo(void) {
    oled_clear();

    const uint8_t Y  = 6;
    const uint8_t S  = 3;
    const uint8_t H  = 20;
    const uint8_t W  = 10;
    const uint8_t G  = 3;
    uint8_t x;

    // S
    x = 20;
    draw_rect(x, Y, W, S);
    draw_rect(x, Y, S, H / 2 + 1);
    draw_rect(x, Y + H / 2 - 1, W, S);
    draw_rect(x + W - S, Y + H / 2 - 1, S, H / 2 + 1);
    draw_rect(x, Y + H - S, W, S);

    // L
    x += W + G;
    draw_rect(x, Y, S, H);
    draw_rect(x, Y + H - S, W, S);

    // A
    x += W + G;
    draw_rect(x, Y, W, S);
    draw_rect(x, Y, S, H);
    draw_rect(x + W - S, Y, S, H);
    draw_rect(x, Y + H / 2 - 1, W, S);

    // T
    x += W + G;
    draw_rect(x, Y, W, S);
    draw_rect(x + (W - S) / 2, Y, S, H);

    // E
    x += W + G;
    draw_rect(x, Y, W, S);
    draw_rect(x, Y, S, H);
    draw_rect(x, Y + H / 2 - 1, W - S, S);
    draw_rect(x, Y + H - S, W, S);

    // 7
    x += W + G;
    draw_rect(x, Y, W, S);
    draw_rect(x + W - S, Y, S, H / 2 + 1);
    draw_rect(x + (W - S) / 2, Y + H / 2, S, H / 2);

    // 6
    x += W + G;
    draw_rect(x, Y, W, S);
    draw_rect(x, Y, S, H);
    draw_rect(x, Y + H / 2 - 1, W, S);
    draw_rect(x + W - S, Y + H / 2 - 1, S, H / 2 + 1);
    draw_rect(x, Y + H - S, W, S);

    for (uint8_t i = 0; i < 88; i++) {
        oled_write_pixel(20 + i, 2, true);
        oled_write_pixel(20 + i, 29, true);
    }
}

bool oled_task_user(void) {
    static bool drawn = false;
    if (!drawn) {
        draw_logo();
        drawn = true;
    }
    return false;
}
#endif
