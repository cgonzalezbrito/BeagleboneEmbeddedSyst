/**
 * Note: This file was auto-generated by TI PinMux on 11/14/2016 at 8:09:19 PM.
 *
 * \file  am335x_gpevm_pinmux_data.c
 *
 * \brief  This file contains the pin mux configurations for the boards.
 *         These are prepared based on how the peripherals are extended on
 *         the boards.
 *
 * \copyright Copyright (CU) 2016 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/**
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "types.h"
#include "pinmux.h"
#include "am335x_pinmux.h"

/** Peripheral Pin Configurations */

#ifndef BUILDCFG_MOD_I2C
#define BUILDCFG_MOD_I2C
#endif /* BUILDCFG_MOD_I2C */


#if defined(BUILDCFG_MOD_I2C)

static pinmuxPerCfg_t gI2c1PinCfg[] =
{
    {
       /* I2C2 -> I2C1_SCL -> J15 */
       PIN_GMII1_RXER, 0, \
       ( \
           PIN_MODE(3) | \
           ((PIN_PULL_UD_EN | PIN_RX_ACTIVE) & (~PIN_PULL_TYPE_SEL)) \
       ) \
    },
    {
       /* I2C2 -> I2C1_SDA -> H17 */
       PIN_GMII1_CRS, 0, \
       ( \
           PIN_MODE(3) | \
           ((PIN_PULL_UD_EN | PIN_RX_ACTIVE) & (~PIN_PULL_TYPE_SEL)) \
       ) \
    },
    {PINMUX_INVALID_PIN}
};

static pinmuxPerCfg_t gI2c0PinCfg[] =
{
    {
       /* I2C3 -> I2C0_SCL -> C16 */
       PIN_I2C0_SCL, 0, \
       ( \
           PIN_MODE(0) | \
           ((PIN_PULL_UD_EN | PIN_RX_ACTIVE) & (~PIN_PULL_TYPE_SEL)) \
       ) \
    },
    {
       /* I2C3 -> I2C0_SDA -> C17 */
       PIN_I2C0_SDA, 0, \
       ( \
           PIN_MODE(0) | \
           ((PIN_PULL_UD_EN | PIN_RX_ACTIVE) & (~PIN_PULL_TYPE_SEL)) \
       ) \
    },
    {PINMUX_INVALID_PIN}
};

static pinmuxModuleCfg_t gI2cPinCfg[] =
{
    {1, TRUE, gI2c1PinCfg},
    {0, TRUE, gI2c0PinCfg},
    {CHIPDB_INVALID_INSTANCE_NUM}
};

#endif /* if defined(BUILDCFG_MOD_I2C) */

/** EVM pin configurations for EVM */

pinmuxBoardCfg_t gGpevmPinmuxData[] =
{
#if defined(BUILDCFG_MOD_I2C)
    {CHIPDB_MOD_ID_I2C, gI2cPinCfg},
#endif /* if defined(BUILDCFG_MOD_I2C) */
    {CHIPDB_MOD_ID_INVALID}
};