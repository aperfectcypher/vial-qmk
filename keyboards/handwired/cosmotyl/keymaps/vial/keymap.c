// Copyright 2024 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_A,    KC_Z,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_LSFT, KC_Q,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_M,    KC_QUOT,
        KC_LCTL, KC_W,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                   KC_LGUI, MO(1),   KC_SPC,      KC_ENT,  MO(2),   KC_BSPC,
                                   KC_LALT, MO(3)
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,     KC_ESC,  _______, KC_DEL,
                                   _______, _______
    ),

    [2] = LAYOUT(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
        _______, _______, _______, KC_LCBR, KC_RCBR, KC_PLUS,     _______, _______, _______, _______, _______, KC_RBRC,
        _______, _______, _______, KC_LBRC, KC_RBRC, KC_EQL,      _______, _______, _______, _______, KC_COLN, KC_DQUO,
        _______, _______, _______, _______, _______, _______,     _______, _______, KC_LT,   KC_GT,   KC_QUES, _______,
                                   _______, _______, _______,     _______, _______, _______,
                                   _______, _______
    ),

    [3] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,     _______, _______, _______, _______, KC_F11,  KC_F12,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
        _______, _______, _______, _______, _______, _______,     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,
        _______, _______, _______, _______, _______, _______,     KC_MPLY, KC_MUTE, _______, _______, _______, _______,
                                   _______, _______, _______,     _______, _______, _______,
                                   _______, _______
    ),

    [4] = LAYOUT(
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,     KC_BTN1, KC_BTN3, KC_BTN2,
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
    [4] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
};
#endif

void keyboard_post_init_user(void) {
    set_auto_mouse_enable(true);
}

report_mouse_t pointing_device_task_user(report_mouse_t report) {
    static int16_t acc_x = 0;
    static int16_t acc_y = 0;
    acc_x += report.x;
    acc_y += report.y;
    report.x = acc_x / 6;
    report.y = acc_y / 6;
    acc_x %= 6;
    acc_y %= 6;
    return report;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    return !layer_state_is(2);
}

static bool game_keypress_flag = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(2) && keycode >= QK_TAP_DANCE && keycode <= QK_TAP_DANCE_MAX) {
        return false;
    }
    if (layer_state_is(2) && record->event.pressed) {
        game_keypress_flag = true;
    }
    return true;
}

#ifdef OLED_ENABLE

#define GRAPH_WIDTH   128
#define GRAPH_TOP      26
#define GRAPH_HEIGHT   38   // y 26..63
#define WPM_MAX       80
#define WPM_SAMPLE_MS 500
#define IDLE_TIMEOUT  30000
#define OLED_OFF_TIMEOUT 900000  // 15 min — turn display off

static uint8_t  wpm_history[GRAPH_WIDTH] = {0};
static uint8_t  wpm_idx = 0;
static uint32_t wpm_timer = 0;

// Simple PRNG (xorshift16)
static uint16_t rng_state = 0xACE1;
static uint16_t xorshift16(void) {
    rng_state ^= rng_state << 7;
    rng_state ^= rng_state >> 9;
    rng_state ^= rng_state << 8;
    return rng_state;
}

// Draw text at 2x scale — reads glyph data into local buffer to avoid
// conflicts when drawing near the scratch area (OLED row 0).
static void oled_write_2x(const char *str, uint8_t px, uint8_t py) {
    uint8_t glyph[48];
    uint8_t len = 0;
    oled_set_cursor(0, 0);
    for (const char *p = str; *p; p++) { oled_write_char(*p, false); len++; }
    oled_buffer_reader_t reader = oled_read_raw(0);
    uint16_t bytes = len * 6;
    if (bytes > sizeof(glyph)) bytes = sizeof(glyph);
    for (uint16_t i = 0; i < bytes && i < reader.remaining_element_count; i++) {
        glyph[i] = reader.current_element[i];
        reader.current_element[i] = 0;
    }
    for (uint16_t i = 0; i < bytes; i++) {
        uint8_t col = glyph[i];
        uint8_t dx = px + i * 2;
        for (uint8_t bit = 0; bit < 8; bit++) {
            bool on = (col >> bit) & 1;
            uint8_t dy = py + bit * 2;
            oled_write_pixel(dx,     dy,     on);
            oled_write_pixel(dx + 1, dy,     on);
            oled_write_pixel(dx,     dy + 1, on);
            oled_write_pixel(dx + 1, dy + 1, on);
        }
    }
}

// ============================================================
//  Screensaver system — one of four chosen at random on idle
// ============================================================
enum { SS_STARFIELD, SS_DVD, SS_MATRIX, SS_SNAKE, SS_PIPES, SS_GOL, NUM_SS };
static uint8_t ss_type  = 0;
static bool    ss_active = false;

// --- Starfield ---
#define NUM_STARS 40
static struct { int16_t x, y, z; } stars[NUM_STARS];
static bool starfield_inited;

static void star_reset(uint8_t i) {
    stars[i].x = (int16_t)(xorshift16() % 256) - 128;
    stars[i].y = (int16_t)(xorshift16() % 128) - 64;
    stars[i].z = 128 + (xorshift16() % 128);
}

static void starfield_draw(void) {
    if (!starfield_inited) {
        for (uint8_t i = 0; i < NUM_STARS; i++) {
            star_reset(i);
            stars[i].z = xorshift16() % 256 + 1;
        }
        starfield_inited = true;
    }
    oled_clear();
    for (uint8_t i = 0; i < NUM_STARS; i++) {
        stars[i].z -= 2;
        if (stars[i].z <= 0) { star_reset(i); continue; }
        int16_t sx = 64 + (stars[i].x * 64) / stars[i].z;
        int16_t sy = 32 + (stars[i].y * 64) / stars[i].z;
        if (sx < 0 || sx >= 128 || sy < 0 || sy >= 64) { star_reset(i); continue; }
        oled_write_pixel(sx, sy, true);
        if (stars[i].z < 80) {
            if (sx + 1 < 128) oled_write_pixel(sx + 1, sy, true);
            if (sy + 1 < 64)  oled_write_pixel(sx, sy + 1, true);
        }
    }
}

// --- DVD bounce ---
// 40×10 bitmap: "DVD" text + disc, row-major, MSB = leftmost pixel
static const uint8_t PROGMEM dvd_logo[] = {
    0xFC, 0xC6, 0xFC, 0x00, 0x00,  // ####### .##...## #######
    0xC6, 0xC6, 0xC6, 0x03, 0xC0,  // ##...## .##...## ##...##       ####
    0xC6, 0x6C, 0xC6, 0x0F, 0xF0,  // ##...##  .##.##  ##...##     ########
    0xC6, 0x6C, 0xC6, 0x18, 0x18,  // ##...##  .##.##  ##...##    ##......##
    0xC6, 0x38, 0xC6, 0x19, 0x98,  // ##...##   .###   ##...##    ##..##..##
    0xC6, 0x38, 0xC6, 0x19, 0x98,  // ##...##   .###   ##...##    ##..##..##
    0xFC, 0x10, 0xFC, 0x18, 0x18,  // #######    .#    #######    ##......##
    0x00, 0x00, 0x00, 0x0F, 0xF0,  //                              ########
    0x00, 0x00, 0x00, 0x03, 0xC0,  //                                ####
    0x00, 0x00, 0x00, 0x00, 0x00,
};
#define DVD_BMP_W 40
#define DVD_BMP_H 10

static int16_t dvd_x, dvd_y;
static int8_t  dvd_dx, dvd_dy;

static void dvd_draw(void) {
    oled_clear();
    for (uint8_t row = 0; row < DVD_BMP_H; row++) {
        for (uint8_t col = 0; col < DVD_BMP_W; col++) {
            uint8_t byte_idx = row * 5 + col / 8;
            if (pgm_read_byte(&dvd_logo[byte_idx]) & (0x80 >> (col % 8))) {
                int16_t px = dvd_x + col;
                int16_t py = dvd_y + row;
                if (px >= 0 && px < 128 && py >= 0 && py < 64)
                    oled_write_pixel(px, py, true);
            }
        }
    }
    dvd_x += dvd_dx;
    dvd_y += dvd_dy;
    if (dvd_x <= 0 || dvd_x + DVD_BMP_W >= 128) { dvd_dx = -dvd_dx; dvd_x += dvd_dx; }
    if (dvd_y <= 0 || dvd_y + DVD_BMP_H >= 64)  { dvd_dy = -dvd_dy; dvd_y += dvd_dy; }
}

// --- Matrix rain ---
#define RAIN_COLS 21   // 128 / 6
#define RAIN_ROWS  8   // 64 / 8

static struct {
    int8_t  head_y;
    uint8_t speed;
    uint8_t trail;
    uint8_t tick;
} rain[RAIN_COLS];
static bool matrix_inited;

static void rain_reset(uint8_t i) {
    rain[i].head_y = -(int8_t)(xorshift16() % 8);
    rain[i].speed  = 2 + (xorshift16() % 3);
    rain[i].trail  = 3 + (xorshift16() % 4);
    rain[i].tick   = 0;
}

static void matrix_draw(void) {
    if (!matrix_inited) {
        for (uint8_t i = 0; i < RAIN_COLS; i++) rain_reset(i);
        matrix_inited = true;
    }
    oled_clear();
    for (uint8_t i = 0; i < RAIN_COLS; i++) {
        rain[i].tick++;
        if (rain[i].tick >= rain[i].speed) {
            rain[i].tick = 0;
            rain[i].head_y++;
        }
        for (int8_t t = 0; t < rain[i].trail; t++) {
            int8_t row = rain[i].head_y - t;
            if (row >= 0 && row < RAIN_ROWS) {
                oled_set_cursor(i, row);
                oled_write_char(33 + (xorshift16() % 94), false);
            }
        }
        if (rain[i].head_y - rain[i].trail >= RAIN_ROWS) rain_reset(i);
    }
}

// --- Snake ---
#define SN_CELL  4
#define SN_GW   32   // 128 / 4
#define SN_GH   16   // 64 / 4
#define SN_MAX  80

static uint8_t  sn_x[SN_MAX], sn_y[SN_MAX];
static uint8_t  sn_len, sn_dir;
static uint8_t  food_x, food_y;
static uint32_t sn_timer;
static bool     snake_inited;

static bool sn_occupied(uint8_t x, uint8_t y) {
    for (uint8_t i = 0; i < sn_len - 1; i++)
        if (sn_x[i] == x && sn_y[i] == y) return true;
    return false;
}

static void sn_place_food(void) {
    uint8_t att = 0;
    do {
        food_x = xorshift16() % SN_GW;
        food_y = xorshift16() % SN_GH;
    } while (sn_occupied(food_x, food_y) && ++att < 200);
}

static void sn_reset(void) {
    sn_len = 3;
    sn_x[0] = SN_GW / 2;     sn_y[0] = SN_GH / 2;
    sn_x[1] = SN_GW / 2 - 1; sn_y[1] = SN_GH / 2;
    sn_x[2] = SN_GW / 2 - 2; sn_y[2] = SN_GH / 2;
    sn_dir = 0;
    sn_place_food();
}

static bool sn_safe(uint8_t x, uint8_t y) {
    return x < SN_GW && y < SN_GH && !sn_occupied(x, y);
}

static void sn_ai(void) {
    uint8_t hx = sn_x[0], hy = sn_y[0];
    int8_t dx = (int8_t)food_x - (int8_t)hx;
    int8_t dy = (int8_t)food_y - (int8_t)hy;
    uint8_t dirs[4], n = 0;
    if (dx > 0 && sn_safe(hx + 1, hy)) dirs[n++] = 0;
    if (dx < 0 && sn_safe(hx - 1, hy)) dirs[n++] = 2;
    if (dy > 0 && sn_safe(hx, hy + 1)) dirs[n++] = 1;
    if (dy < 0 && sn_safe(hx, hy - 1)) dirs[n++] = 3;
    if (n == 0) {
        if (sn_safe(hx + 1, hy)) dirs[n++] = 0;
        if (sn_safe(hx - 1, hy)) dirs[n++] = 2;
        if (sn_safe(hx, hy + 1)) dirs[n++] = 1;
        if (sn_safe(hx, hy - 1)) dirs[n++] = 3;
    }
    if (n > 0) sn_dir = dirs[0]; else sn_reset();
}

static void snake_draw(void) {
    if (!snake_inited) { sn_reset(); snake_inited = true; sn_timer = timer_read32(); }

    if (timer_elapsed32(sn_timer) > 120) {
        sn_timer = timer_read32();
        sn_ai();
        uint8_t nx = sn_x[0], ny = sn_y[0];
        switch (sn_dir) {
            case 0: nx++; break; case 1: ny++; break;
            case 2: nx--; break; case 3: ny--; break;
        }
        bool ate = (nx == food_x && ny == food_y);
        uint8_t shift = (ate && sn_len < SN_MAX) ? sn_len : sn_len - 1;
        for (uint8_t i = shift; i > 0; i--) { sn_x[i] = sn_x[i - 1]; sn_y[i] = sn_y[i - 1]; }
        sn_x[0] = nx; sn_y[0] = ny;
        if (ate && sn_len < SN_MAX) sn_len++;
        if (ate) sn_place_food();
        if (sn_len >= SN_MAX) sn_reset();
    }

    oled_clear();
    for (uint8_t i = 0; i < sn_len; i++) {
        uint8_t px = sn_x[i] * SN_CELL, py = sn_y[i] * SN_CELL;
        for (uint8_t a = 0; a < SN_CELL - 1; a++)
            for (uint8_t b = 0; b < SN_CELL - 1; b++)
                oled_write_pixel(px + a, py + b, true);
    }
    // Food — diamond shape
    uint8_t fx = food_x * SN_CELL, fy = food_y * SN_CELL;
    oled_write_pixel(fx + 1, fy,     true);
    oled_write_pixel(fx,     fy + 1, true);
    oled_write_pixel(fx + 2, fy + 1, true);
    oled_write_pixel(fx + 1, fy + 2, true);
}

// --- Pipes ---
static uint8_t  pipe_x, pipe_y, pipe_dir;
static uint16_t pipe_total;
static uint32_t pipe_timer;
static bool     pipe_inited;

static void pipe_extend(void) {
    int8_t dx = 0, dy = 0;
    switch (pipe_dir) {
        case 0: dx = 1; break;  case 1: dy = 1; break;
        case 2: dx = -1; break; case 3: dy = -1; break;
    }
    // Draw joint (3x3 block at current position)
    for (int8_t a = -1; a <= 1; a++)
        for (int8_t b = -1; b <= 1; b++) {
            int16_t px = (int16_t)pipe_x + a, py = (int16_t)pipe_y + b;
            if (px >= 0 && px < 128 && py >= 0 && py < 64)
                oled_write_pixel(px, py, true);
        }
    // Extend 3-wide segment by 4 pixels
    for (uint8_t s = 0; s < 4; s++) {
        pipe_x += dx; pipe_y += dy;
        for (int8_t w = -1; w <= 1; w++) {
            int16_t px, py;
            if (dx) { px = pipe_x; py = (int16_t)pipe_y + w; }
            else    { px = (int16_t)pipe_x + w; py = pipe_y; }
            if (px >= 0 && px < 128 && py >= 0 && py < 64)
                oled_write_pixel(px, py, true);
        }
    }
    pipe_total++;
    // Random turn (40% chance)
    if (xorshift16() % 5 < 2)
        pipe_dir = (pipe_dir + (xorshift16() & 1 ? 1 : 3)) % 4;
    // Near edge → start new pipe at random spot
    if (pipe_x < 4 || pipe_x > 124 || pipe_y < 4 || pipe_y > 60) {
        pipe_x = 8 + xorshift16() % 112;
        pipe_y = 8 + xorshift16() % 48;
        pipe_dir = xorshift16() % 4;
    }
}

static void pipes_draw(void) {
    if (!pipe_inited || pipe_total > 600) {
        oled_clear();
        pipe_x = 64; pipe_y = 32;
        pipe_dir = xorshift16() % 4;
        pipe_total = 0;
        pipe_inited = true;
        pipe_timer = timer_read32();
    }
    if (timer_elapsed32(pipe_timer) > 80) {
        pipe_timer = timer_read32();
        pipe_extend();
    }
}

// --- Game of Life ---
#define GOL_W 64
#define GOL_H 32

static uint8_t gol_cur[GOL_W * GOL_H / 8];   // 256 bytes
static uint8_t gol_next[GOL_W * GOL_H / 8];
static uint16_t gol_gen;
static uint16_t gol_cs0, gol_cs1;   // checksums for stagnation detection
static uint8_t  gol_stale;
static uint32_t gol_timer;
static bool     gol_inited;

static inline bool gol_get(const uint8_t *g, uint8_t x, uint8_t y) {
    uint16_t idx = (uint16_t)y * GOL_W + x;
    return g[idx / 8] & (1 << (idx % 8));
}
static inline void gol_set(uint8_t *g, uint8_t x, uint8_t y, bool v) {
    uint16_t idx = (uint16_t)y * GOL_W + x;
    if (v) g[idx / 8] |= (1 << (idx % 8));
    else   g[idx / 8] &= ~(1 << (idx % 8));
}

static uint8_t gol_neighbors(uint8_t x, uint8_t y) {
    uint8_t n = 0;
    for (int8_t dy = -1; dy <= 1; dy++)
        for (int8_t dx = -1; dx <= 1; dx++) {
            if (!dx && !dy) continue;
            if (gol_get(gol_cur, (x + dx + GOL_W) % GOL_W, (y + dy + GOL_H) % GOL_H)) n++;
        }
    return n;
}

static void gol_init_random(void) {
    rng_state ^= timer_read();
    for (uint16_t i = 0; i < sizeof(gol_cur); i++)
        gol_cur[i] = xorshift16() & xorshift16();  // ~25% density
    gol_gen = 0; gol_stale = 0; gol_cs0 = 0; gol_cs1 = 0;
    gol_inited = true;
    gol_timer = timer_read32();
}

static void gol_step(void) {
    for (uint16_t i = 0; i < sizeof(gol_next); i++) gol_next[i] = 0;
    for (uint8_t y = 0; y < GOL_H; y++)
        for (uint8_t x = 0; x < GOL_W; x++) {
            uint8_t n = gol_neighbors(x, y);
            bool alive = gol_get(gol_cur, x, y);
            if ((alive && (n == 2 || n == 3)) || (!alive && n == 3))
                gol_set(gol_next, x, y, true);
        }
    uint16_t cs = 0;
    for (uint16_t i = 0; i < sizeof(gol_next); i++) {
        gol_cur[i] = gol_next[i];
        cs += gol_cur[i];
    }
    gol_gen++;
    if (cs == gol_cs0 || cs == gol_cs1) gol_stale++; else gol_stale = 0;
    gol_cs1 = gol_cs0; gol_cs0 = cs;
}

static void gol_draw(void) {
    if (!gol_inited) gol_init_random();
    if (timer_elapsed32(gol_timer) > 100) {
        gol_timer = timer_read32();
        gol_step();
        if (gol_stale > 20 || gol_gen > 500) gol_inited = false;
    }
    oled_clear();
    for (uint8_t y = 0; y < GOL_H; y++)
        for (uint8_t x = 0; x < GOL_W; x++)
            if (gol_get(gol_cur, x, y)) {
                uint8_t px = x * 2, py = y * 2;
                oled_write_pixel(px,     py,     true);
                oled_write_pixel(px + 1, py,     true);
                oled_write_pixel(px,     py + 1, true);
                oled_write_pixel(px + 1, py + 1, true);
            }
}

// --- Gaming mode display (combo counter + particle burst) ---
#define GP_MAX 32

static struct { int16_t x, y; int8_t dx, dy; uint8_t life; } gp[GP_MAX];
static uint16_t game_combo = 0;
static uint32_t game_last_press = 0;

static void gp_spawn(uint8_t count) {
    for (uint8_t c = 0; c < count; c++) {
        for (uint8_t i = 0; i < GP_MAX; i++) {
            if (gp[i].life == 0) {
                gp[i].x = 64; gp[i].y = 44;
                gp[i].dx = (int8_t)(xorshift16() % 9) - 4;
                gp[i].dy = (int8_t)(xorshift16() % 7) - 3;
                if (!gp[i].dx && !gp[i].dy) gp[i].dx = 1;
                gp[i].life = 8 + (xorshift16() % 10);
                break;
            }
        }
    }
}

static void gaming_draw(void) {
    // Process keypress events
    if (game_keypress_flag) {
        game_keypress_flag = false;
        game_combo++;
        if (game_combo > 999) game_combo = 999;
        game_last_press = timer_read32();
        // More particles at higher combos
        uint8_t burst = (game_combo > 50) ? 8 : (game_combo > 20) ? 6 : 4;
        gp_spawn(burst);
    }
    if (timer_elapsed32(game_last_press) > 2000) game_combo = 0;

    oled_clear();

    // Header: combo count left, "Gam" right
    char buf[8];
    buf[0] = 'x';
    uint16_t c = game_combo;
    buf[1] = (c >= 100) ? '0' + c / 100 : ' ';
    buf[2] = (c >= 10)  ? '0' + (c / 10) % 10 : ' ';
    buf[3] = '0' + c % 10;
    buf[4] = '\0';
    oled_write_2x(buf, 0, 10);
    oled_write_2x("Gam", 92, 10);

    // Update and draw particles
    for (uint8_t i = 0; i < GP_MAX; i++) {
        if (gp[i].life == 0) continue;
        gp[i].x += gp[i].dx;
        gp[i].y += gp[i].dy;
        gp[i].life--;
        if (gp[i].x >= 0 && gp[i].x < 128 && gp[i].y >= 26 && gp[i].y < 64) {
            oled_write_pixel(gp[i].x, gp[i].y, true);
            // Bigger particles at high combo
            if (game_combo > 30 && gp[i].x + 1 < 128)
                oled_write_pixel(gp[i].x + 1, gp[i].y, true);
        }
    }

    // Horizontal streak bar at y=63 based on combo
    uint8_t bar_w = (game_combo > 100) ? 128 : game_combo * 128 / 100;
    for (uint8_t x = 0; x < bar_w; x++)
        oled_write_pixel(x, 63, true);
}

// --- Screensaver dispatch ---
#define SS_ROTATE_MS 60000  // switch screensaver every 60s

static uint32_t ss_rotate_timer;

static void ss_init(void) {
    rng_state ^= timer_read();
    ss_type = xorshift16() % NUM_SS;
    ss_active = true;
    starfield_inited = false;
    matrix_inited    = false;
    snake_inited     = false;
    pipe_inited      = false;

    gol_inited       = false;
    dvd_x = 10 + (xorshift16() % 40);
    dvd_y = 10 + (xorshift16() % 30);
    dvd_dx = 1; dvd_dy = 1;
    ss_rotate_timer = timer_read32();
}

static void ss_draw(void) {
    if (timer_elapsed32(ss_rotate_timer) > SS_ROTATE_MS) {
        ss_init();  // picks a new random screensaver and resets timer
    }
    switch (ss_type) {
        case SS_STARFIELD: starfield_draw(); break;
        case SS_DVD:       dvd_draw();       break;
        case SS_MATRIX:    matrix_draw();    break;
        case SS_SNAKE:     snake_draw();     break;
        case SS_PIPES:     pipes_draw();     break;

        case SS_GOL:       gol_draw();       break;
    }
}

// ============================================================

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_left()) return OLED_ROTATION_180;
    return rotation;
}

bool oled_task_kb(void) {
    if (is_keyboard_left()) {
        if (last_input_activity_elapsed() > OLED_OFF_TIMEOUT) {
            oled_off();
            return false;
        }
        if (last_input_activity_elapsed() > IDLE_TIMEOUT) {
            if (!ss_active) ss_init();
            ss_draw();
            return false;
        }
        if (ss_active) { ss_active = false; oled_clear(); }
        oled_on();

        if (layer_state_is(2)) {
            // Gaming mode: combo counter + particle burst
            gaming_draw();
        } else {
            // Normal mode: WPM graph
            if (timer_elapsed32(wpm_timer) > WPM_SAMPLE_MS) {
                wpm_timer = timer_read32();
                uint8_t wpm = get_current_wpm();
                if (wpm > WPM_MAX) wpm = WPM_MAX;
                wpm_history[wpm_idx] = wpm;
                wpm_idx = (wpm_idx + 1) % GRAPH_WIDTH;
            }

            char buf[12];
            const char *wpm_str = get_u8_str(get_current_wpm(), ' ');
            buf[0] = 'W'; buf[1] = 'P'; buf[2] = 'M'; buf[3] = ':';
            buf[4] = wpm_str[0]; buf[5] = wpm_str[1]; buf[6] = wpm_str[2]; buf[7] = '\0';
            oled_write_2x(buf, 0, 10);

            uint8_t layer = get_highest_layer(layer_state | default_layer_state);
            const char *ltag;
            switch (layer) {
                case 1:  ltag = "Nav"; break;
                case 3:  ltag = "Fn "; break;
                case 4:  ltag = "Mse"; break;
                default: ltag = "   "; break;
            }
            oled_write_2x(ltag, 92, 10);

            for (uint8_t x = 0; x < GRAPH_WIDTH; x++) {
                uint8_t hi = (wpm_idx + x) % GRAPH_WIDTH;
                uint8_t bar_h = (uint16_t)wpm_history[hi] * GRAPH_HEIGHT / WPM_MAX;
                for (uint8_t y = 0; y < GRAPH_HEIGHT; y++)
                    oled_write_pixel(x, 63 - y, y < bar_h);
            }
        }
    } else {
        oled_set_cursor(0, 2);
        oled_write_P(PSTR("Cosmotyl\n"), false);
        oled_write_P(PSTR("split 4x6\n"), false);
        oled_write_P(PSTR("trackball\n"), false);
    }
    return false;
}
#endif
