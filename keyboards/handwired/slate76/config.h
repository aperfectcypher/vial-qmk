// Copyright 2026 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

/* OLED — SSD1306 128x32 on I2C0 (default pins GP0/GP1) */
#define I2C_DRIVER   I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP1
