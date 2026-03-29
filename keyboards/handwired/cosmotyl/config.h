// Copyright 2024 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

/* Split handedness stored in EEPROM — flash left with uf2-split-left, right with uf2-split-right */
#define EE_HANDS

/* OLED on left half — I2C0 with GP29 as alt SCL (GP1 is reserved for TRRS) */
#define I2C_DRIVER   I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP29
#define OLED_DISPLAY_128X64

/* Trackball (PMW3360) on right half — SPI1 on side pins GP26/27/28 */
#define SPI_DRIVER   SPID1
#define SPI_SCK_PIN  GP26
#define SPI_MOSI_PIN GP27
#define SPI_MISO_PIN GP28
#define PMW33XX_CS_PIN GP13
#define PMW33XX_CPI 100

/* Trackball orientation — sensor is rotated 90° relative to expected */
#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_INVERT_X

/* Pointing device is on right half only */
#define POINTING_DEVICE_RIGHT
#define SPLIT_POINTING_ENABLE

/* Encoder is on left half only — prevents right half from scanning GP13 (= PMW33XX_CS_PIN) */
#define NUM_ENCODERS_RIGHT 0

/* Auto mouse layer — activates layer 4 when trackball moves */
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 4
#define AUTO_MOUSE_TIME 1500   // ms before mouse layer deactivates (default 650)

/* Sync WPM to slave so left-side OLED can display it when right is master */
#define SPLIT_WPM_ENABLE
#define SPLIT_LAYER_STATE_ENABLE

