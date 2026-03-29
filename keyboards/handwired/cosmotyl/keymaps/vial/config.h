// Copyright 2024 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0xFF, 0x4A, 0x96, 0x68, 0x9A, 0x95, 0x13, 0x0C}

/* Unlock combo: hold top-left key of each half simultaneously */
#define VIAL_UNLOCK_COMBO_ROWS {0, 5}
#define VIAL_UNLOCK_COMBO_COLS {0, 0}

/* 4 remappable layers */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* Tell keymap_introspection.c that Vial owns combos/tap-dance/key-overrides */
#define VIAL_COMBO_ENABLE
#define VIAL_TAP_DANCE_ENABLE
#define VIAL_KEY_OVERRIDE_ENABLE
