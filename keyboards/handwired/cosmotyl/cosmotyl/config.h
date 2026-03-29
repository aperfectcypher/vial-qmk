// Copyright 2024 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* Split handedness stored in EEPROM — flash left with uf2-split-left, right with uf2-split-right */
#define EE_HANDS

/* OLED on left half — I2C0 with GP29 as alt SCL (GP1 is reserved for TRRS) */
#define I2C_DRIVER   I2CD0
#define I2C0_SDA_PIN GP0
#define I2C0_SCL_PIN GP29
#define OLED_DISPLAY_128X64

/* Trackball (PMW3360) on right half — SPI0 via bottom pads */
#define SPI_DRIVER   SPID0
#define SPI_SCK_PIN  GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP20
#define PMW33XX_CS_PIN GP13

/* Pointing device is on right half only */
#define POINTING_DEVICE_RIGHT
#define SPLIT_POINTING_ENABLE
