// Copyright 2024 tla
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include_next <mcuconf.h>

/* Enable I2C0 for OLED */
#undef  RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

/* Enable SPI0 for PMW3360 trackball */
#undef  RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
