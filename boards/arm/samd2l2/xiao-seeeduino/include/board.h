/****************************************************************************
 * boards/arm/samd2l2/xiao-seeeduino/include/board.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_ARM_SAMD2L2_XIAO_SEEEDUINO_INCLUDE_BOARD_H
#define __BOARDS_ARM_SAMD2L2_XIAO_SEEEDUINO_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
#  include <stdint.h>
#  ifdef CONFIG_SAMD2L2_GPIOIRQ
#    include <arch/irq.h>
#  endif
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

/* Overview
 *
 * OSC8M              Output = 8MHz
 *  `- GCLK1          Input  = 8MHz  Prescaler    = 1 output         = 8MHz
 *      `- DFLL       Input  = 8MHz  Multiplier   = 6 output         = 48MHz
 *          `- GCLK0  Input  = 48MHz Prescaler    = 1 output         = 48MHz
 *              `- PM Input  = 48Mhz CPU divider  = 1 CPU frequency  = 48MHz
 *                                   APBA divider = 1 APBA frequency = 48MHz
 *                                   APBB divider = 1 APBB frequency = 48MHz
 *                                   APBC divider = 1 APBC frequency = 48MHz
 *
 * The SAMD21 Xplained Pro has one on-board crystal:
 *
 *   XC101 32.768KHz XOSC32
 *
 * REVISIT: Not currently used, may want to use as GCLK1 source with
 * DFLL multiplier of ((48000000+16384)/32768) = 1465 which would yield
 * a clock of 48,005,120 MHz.
 */

/* XOSC Configuration -- Not available
 *
 *   BOARD_XOSC_ENABLE          - Boolean (defined / not defined)
 *   BOARD_XOSC_FREQUENCY       - In Hz
 *   BOARD_XOSC_STARTUPTIME     - See SYSCTRL_XOSC_STARTUP_* definitions
 *   BOARD_XOSC_ISCRYSTAL       - Boolean (defined / not defined)
 *   BOARD_XOSC_AMPGC           - Boolean (defined / not defined)
 *   BOARD_XOSC_ONDEMAND        - Boolean (defined / not defined)
 *   BOARD_XOSC_RUNINSTANDBY    - Boolean (defined / not defined)
 */

#undef  BOARD_XOSC_ENABLE
#define BOARD_XOSC_FREQUENCY         12000000UL
#define BOARD_XOSC_STARTUPTIME       SYSCTRL_XOSC_STARTUP_1S
#define BOARD_XOSC_ISCRYSTAL         1
#define BOARD_XOSC_AMPGC             1
#define BOARD_XOSC_ONDEMAND          1
#undef  BOARD_XOSC_RUNINSTANDBY

/* XOSC32 Configuration -- Not used
 *
 *   BOARD_XOSC32K_ENABLE       - Boolean (defined / not defined)
 *   BOARD_XOSC32K_FREQUENCY    - In Hz
 *   BOARD_XOSC32K_STARTUPTIME  - See SYSCTRL_XOSC32K_STARTUP_* definitions
 *   BOARD_XOSC32K_ISCRYSTAL    - Boolean (defined / not defined)
 *   BOARD_XOSC32K_AAMPEN       - Boolean (defined / not defined)
 *   BOARD_XOSC32K_EN1KHZ       - Boolean (defined / not defined)
 *   BOARD_XOSC32K_EN32KHZ      - Boolean (defined / not defined)
 *   BOARD_XOSC32K_ONDEMAND     - Boolean (defined / not defined)
 *   BOARD_XOSC32K_RUNINSTANDBY - Boolean (defined / not defined)
 */

#undef  BOARD_XOSC32K_ENABLE
#define BOARD_XOSC32K_FREQUENCY      32768    /* 32.768KHz XTAL */
#define BOARD_XOSC32K_STARTUPTIME    SYSCTRL_XOSC32K_STARTUP_2S
#define BOARD_XOSC32K_ISCRYSTAL      1
#define BOARD_XOSC32K_AAMPEN         1
#undef  BOARD_XOSC32K_EN1KHZ
#define BOARD_XOSC32K_EN32KHZ        1
#define BOARD_XOSC32K_ONDEMAND       1
#undef  BOARD_XOSC32K_RUNINSTANDBY

/* OSC32 Configuration -- not used
 *
 *   BOARD_OSC32K_ENABLE        - Boolean (defined / not defined)
 *   BOARD_OSC32K_FREQUENCY     - In Hz
 *   BOARD_OSC32K_STARTUPTIME   - See SYSCTRL_OSC32K_STARTUP_* definitions
 *   BOARD_OSC32K_EN1KHZ        - Boolean (defined / not defined)
 *   BOARD_OSC32K_EN32KHZ       - Boolean (defined / not defined)
 *   BOARD_OSC32K_ONDEMAND      - Boolean (defined / not defined)
 *   BOARD_OSC32K_RUNINSTANDBY  - Boolean (defined / not defined)
 */

#undef  BOARD_OSC32K_ENABLE
#define BOARD_OSC32K_FREQUENCY       32768    /* 32.768kHz internal oscillator */
#define BOARD_OSC32K_STARTUPTIME     SYSCTRL_OSC32K_STARTUP_4MS
#define BOARD_OSC32K_EN1KHZ          1
#define BOARD_OSC32K_EN32KHZ         1
#define BOARD_OSC32K_ONDEMAND        1
#undef  BOARD_OSC32K_RUNINSTANDBY

/* OSC8M Configuration -- always enabled
 *
 *   BOARD_OSC8M_PRESCALER      - See SYSCTRL_OSC8M_PRESC_DIV* definitions
 *   BOARD_OSC8M_ONDEMAND       - Boolean (defined / not defined)
 *   BOARD_OSC8M_RUNINSTANDBY   - Boolean (defined / not defined)
 */

#define BOARD_OSC8M_PRESCALER        SYSCTRL_OSC8M_PRESC_DIV1
#define BOARD_OSC8M_ONDEMAND         1
#undef  BOARD_OSC8M_RUNINSTANDBY

#define BOARD_OSC8M_FREQUENCY        8000000  /* 8MHz high-accuracy internal oscillator */

/* OSCULP32K Configuration -- not used. */

#define BOARD_OSCULP32K_FREQUENCY    32000    /* 32kHz ultra-low-power internal oscillator */

/* Digital Frequency Locked Loop configuration.  In closed-loop mode, the
 * DFLL output frequency (Fdfll) is given by:
 *
 *  Fdfll = DFLLmul * Frefclk
 *        = 6 * 8000000 = 48MHz
 *
 * Where the reference clock is Generic Clock Channel 0 output of GLCK1.
 * GCLCK1 provides OSC8M, undivided.
 *
 * When operating in open-loop mode, the output frequency of the DFLL will
 * be determined by the values written to the DFLL Coarse Value bit group
 * and the DFLL Fine Value bit group in the DFLL Value register.
 *
 *   BOARD_DFLL_OPENLOOP            - Boolean (defined / not defined)
 *   BOARD_DFLL_TRACKAFTERFINELOCK  - Boolean (defined / not defined)
 *   BOARD_DFLL_KEEPLOCKONWAKEUP    - Boolean (defined / not defined)
 *   BOARD_DFLL_ENABLECHILLCYCLE    - Boolean (defined / not defined)
 *   BOARD_DFLL_QUICKLOCK           - Boolean (defined / not defined)
 *   BOARD_DFLL_ONDEMAND            - Boolean (defined / not defined)
 *
 * Closed loop mode only:
 *   BOARD_DFLL_GCLKGEN             - GCLK index
 *   BOARD_DFLL_MULTIPLIER          - Value
 *   BOARD_DFLL_MAXCOARSESTEP       - Value
 *   BOARD_DFLL_MAXFINESTEP         - Value
 *
 *   BOARD_DFLL_FREQUENCY           - The resulting frequency
 */

#define BOARD_DFLL_ENABLE            1
#define BOARD_DFLL_OPENLOOP          1
#undef  BOARD_DFLL_ONDEMAND
#undef  BOARD_DFLL_RUNINSTANDBY

/* DFLL closed loop mode configuration */

#define BOARD_DFLL_SRCGCLKGEN         1
#define BOARD_DFLL_MULTIPLIER         6
#define BOARD_DFLL_QUICKLOCK          1
#define BOARD_DFLL_TRACKAFTERFINELOCK 1
#define BOARD_DFLL_KEEPLOCKONWAKEUP   1
#define BOARD_DFLL_ENABLECHILLCYCLE   1
#define BOARD_DFLL_MAXCOARSESTEP      (0x1f / 4)
#define BOARD_DFLL_MAXFINESTEP        (0xff / 4)

#define BOARD_DFLL_FREQUENCY          (48000000)

/* GCLK Configuration
 *
 * Global enable/disable.
 *
 *   BOARD_GCLK_ENABLE            - Boolean (defined / not defined)
 *
 * For n=1-7:
 *   BOARD_GCLKn_ENABLE           - Boolean (defined / not defined)
 *
 * For n=0-8:
 *   BOARD_GCLKn_RUN_IN_STANDBY   - Boolean (defined / not defined)
 *   BOARD_GCLKn_CLOCK_SOURCE     - See GCLK_GENCTRL_SRC_* definitions
 *   BOARD_GCLKn_PRESCALER        - Value
 *   BOARD_GCLKn_OUTPUT_ENABLE    - Boolean (defined / not defined)
 */

#define BOARD_GCLK_ENABLE             1

/* GCLK generator 0 (Main Clock) - Source is the DFLL */

#undef  BOARD_GCLK0_RUN_IN_STANDBY
#define BOARD_GCLK0_CLOCK_SOURCE      GCLK_GENCTRL_SRC_DFLL48M
#define BOARD_GCLK0_PRESCALER         1
#undef  BOARD_GCLK0_OUTPUT_ENABLE
#define BOARD_GCLK0_FREQUENCY         (BOARD_DFLL_FREQUENCY / BOARD_GCLK0_PRESCALER)

/* Configure GCLK generator 1 - Drives the DFLL */

#define BOARD_GCLK1_ENABLE            1
#undef  BOARD_GCLK1_RUN_IN_STANDBY
#define BOARD_GCLK1_CLOCK_SOURCE      GCLK_GENCTRL_SRC_OSC8M
#define BOARD_GCLK1_PRESCALER         1
#undef  BOARD_GCLK1_OUTPUT_ENABLE
#define BOARD_GCLK1_FREQUENCY         (BOARD_OSC8M_FREQUENCY / BOARD_GCLK1_PRESCALER)

/* Configure GCLK generator 2 (RTC) */

#undef  BOARD_GCLK2_ENABLE
#undef  BOARD_GCLK2_RUN_IN_STANDBY
#define BOARD_GCLK2_CLOCK_SOURCE      GCLK_GENCTRL_SRC_OSC32K
#define BOARD_GCLK2_PRESCALER         32
#undef  BOARD_GCLK2_OUTPUT_ENABLE
#define BOARD_GCLK2_FREQUENCY         (BOARD_OSC8M_FREQUENCY / BOARD_GCLK2_PRESCALER)

/* Configure GCLK generator 3 */

#undef  BOARD_GCLK3_ENABLE
#undef  BOARD_GCLK3_RUN_IN_STANDBY
#define BOARD_GCLK3_CLOCK_SOURCE      GCLK_GENCTRL_SRC_OSC8M
#define BOARD_GCLK3_PRESCALER         1
#undef  BOARD_GCLK3_OUTPUT_ENABLE
#define BOARD_GCLK3_FREQUENCY         (BOARD_OSC8M_FREQUENCY / BOARD_GCLK3_PRESCALER)

/* Configure GCLK generator 4 */

#undef  BOARD_GCLK4_ENABLE
#undef  BOARD_GCLK4_RUN_IN_STANDBY
#define BOARD_GCLK4_CLOCK_SOURCE      GCLK_GENCTRL_SRC_OSC8M
#define BOARD_GCLK4_PRESCALER         1
#undef  BOARD_GCLK4_OUTPUT_ENABLE
#define BOARD_GCLK4_FREQUENCY         (BOARD_OSC8M_FREQUENCY / BOARD_GCLK4_PRESCALER)

/* Configure GCLK generator 5 */

#undef  BOARD_GCLK5_ENABLE
#undef  BOARD_GCLK5_RUN_IN_STANDBY
#define BOARD_GCLK5_CLOCK_SOURCE      GCLK_GENCTRL_SRC_OSC8M
#define BOARD_GCLK5_PRESCALER         1
#undef  BOARD_GCLK5_OUTPUT_ENABLE
#define BOARD_GCLK5_FREQUENCY         (BOARD_OSC8M_FREQUENCY / BOARD_GCLK5_PRESCALER)

/* Configure GCLK generator 6 */

#undef  BOARD_GCLK6_ENABLE
#undef  BOARD_GCLK6_RUN_IN_STANDBY
#define BOARD_GCLK6_CLOCK_SOURCE      GCLK_GENCTRL_SRC_OSC8M
#define BOARD_GCLK6_PRESCALER         1
#undef  BOARD_GCLK6_OUTPUT_ENABLE
#define BOARD_GCLK6_FREQUENCY         (BOARD_OSC8M_FREQUENCY / BOARD_GCLK6_PRESCALER)

/* Configure GCLK generator 7 */

#undef  BOARD_GCLK7_ENABLE
#undef  BOARD_GCLK7_RUN_IN_STANDBY
#define BOARD_GCLK7_CLOCK_SOURCE      GCLK_GENCTRL_SRC_OSC8M
#define BOARD_GCLK7_PRESCALER         1
#undef  BOARD_GCLK7_OUTPUT_ENABLE
#define BOARD_GCLK7_FREQUENCY         (BOARD_OSC8M_FREQUENCY / BOARD_GCLK7_PRESCALER)

/* The source of the main clock is always GCLK_MAIN.  Also called GCLKGEN[0],
 * this is the clock feeding the Power Manager.
 * The Power Manager, in turn, generates main clock which is divided down to
 * produce the CPU, AHB, and APB clocks.
 *
 * The main clock is initially OSC8M divided by 8.
 */

#define BOARD_GCLK_MAIN_FREQUENCY     BOARD_GCLK0_FREQUENCY

/* Main clock dividers
 *
 *    BOARD_CPU_DIVIDER    - See PM_CPUSEL_CPUDIV_* definitions
 *    BOARD_CPU_FREQUENCY  - In Hz
 *    BOARD_CPU_FAILDECT   - Boolean (defined / not defined)
 *    BOARD_APBA_DIVIDER   - See M_APBASEL_APBADIV_* definitions
 *    BOARD_APBA_FREQUENCY - In Hz
 *    BOARD_APBB_DIVIDER   - See M_APBBSEL_APBBDIV_* definitions
 *    BOARD_APBB_FREQUENCY - In Hz
 *    BOARD_APBC_DIVIDER   - See M_APBCSEL_APBCDIV_* definitions
 *    BOARD_APBC_FREQUENCY - In Hz
 */

#define BOARD_CPU_FAILDECT           1
#define BOARD_CPU_DIVIDER            PM_CPUSEL_CPUDIV_1
#define BOARD_APBA_DIVIDER           PM_APBASEL_APBADIV_1
#define BOARD_APBB_DIVIDER           PM_APBBSEL_APBBDIV_1
#define BOARD_APBC_DIVIDER           PM_APBCSEL_APBCDIV_1

/* Resulting frequencies */

#define BOARD_MCK_FREQUENCY          (BOARD_GCLK_MAIN_FREQUENCY)
#define BOARD_CPU_FREQUENCY          (BOARD_MCK_FREQUENCY)
#define BOARD_PBA_FREQUENCY          (BOARD_MCK_FREQUENCY)
#define BOARD_PBB_FREQUENCY          (BOARD_MCK_FREQUENCY)
#define BOARD_PBC_FREQUENCY          (BOARD_MCK_FREQUENCY)
#define BOARD_PBD_FREQUENCY          (BOARD_MCK_FREQUENCY)

/* FLASH wait states
 *
 * Vdd Range     Wait states    Maximum Operating Frequency
 * ------------- -------------- ---------------------------
 * 1.62V to 2.7V  0             14 MHz
 *                1             28 MHz
 *                2             42 MHz
 *                3             48 MHz
 * 2.7V to 3.63V  0             24 MHz
 *                1             48 MHz
 */

#if 0 /* REVISIT -- should not be necessary */
#  define BOARD_FLASH_WAITSTATES     1
#else
#  define BOARD_FLASH_WAITSTATES     2
#endif

/* SERCOM definitions *******************************************************/

/* This is the source clock generator for the GCLK_SERCOM_SLOW clock that is
 * common to all SERCOM modules.
 */

#define BOARD_SERCOM05_SLOW_GCLKGEN  0

/* The SERCOM4 USART is available on the pins below.
 *
 *   PIN   EXT1  GPIO Function
 *   ----  ----  ------------------
 *    13   PB09  SERCOM4 / USART RX
 *    14   PB08  SERCOM4 / USART TX
 *    19   GND   N/A
 *    20   VCC   N/A
 *
 * If you have a TTL to RS-232 converter then this is the most convenient
 * serial console to use (because you don't lose the console device each time
 * you lose the USB connection). It is the default in all of the SAMD21
 * configurations.
 */

#define BOARD_SERCOM4_GCLKGEN        0
#define BOARD_SERCOM4_SLOW_GCLKGEN   BOARD_SERCOM05_SLOW_GCLKGEN

#if defined(CONFIG_USART4_SERIAL_CONSOLE)
#  define BOARD_SERCOM4_MUXCONFIG    (USART_CTRLA_RXPAD1 | USART_CTRLA_TXPAD0_1)
#  define BOARD_SERCOM4_PINMAP_PAD0  PORT_SERCOM4_PAD0_3 /* USART TX */
#  define BOARD_SERCOM4_PINMAP_PAD1  PORT_SERCOM4_PAD1_3 /* USART RX */
#  define BOARD_SERCOM4_PINMAP_PAD2  0
#  define BOARD_SERCOM4_PINMAP_PAD3  0
#endif /* CONFIG_USART4_SERIAL_CONSOLE */

#define BOARD_SERCOM4_FREQUENCY      BOARD_GCLK0_FREQUENCY

/* USB definitions **********************************************************/

/* This is the source clock generator for the GCLK_USB clock
 */

#define BOARD_USB_GCLKGEN            0
#define BOARD_USB_FREQUENCY          BOARD_GCLK0_FREQUENCY

/* default USB Pad calibration (not used yet by USB driver) */

#define BOARD_USB_PADCAL_P       29
#define BOARD_USB_PADCAL_N       5
#define BOARD_USB_PADCAL_TRIM    3

/* LED definitions **********************************************************/

/* LED index values for use with board_userled() */

#define BOARD_STATUS_LED             0
#define BOARD_NLEDS                  1

/* LED bits for use with board_userled_all() */

#define BOARD_STATUS LED_BIT         (1 << BOARD_STATUS_LED)

/* When CONFIG_ARCH_LEDS is defined in the NuttX configuration, NuttX will
 * control the LED as defined below.  Thus if the LED is statically on, NuttX
 * has successfully booted and is, apparently, running normally.
 * If the LED is flashing at approximately 2Hz, then a fatal error
 * has been detected and the system has halted.
 */

#define LED_STARTED                  0 /* STATUS LED=OFF */
#define LED_HEAPALLOCATE             0 /* STATUS LED=OFF */
#define LED_IRQSENABLED              0 /* STATUS LED=OFF */
#define LED_STACKCREATED             1 /* STATUS LED=ON */
#define LED_INIRQ                    2 /* STATUS LED=no change */
#define LED_SIGNAL                   2 /* STATUS LED=no change */
#define LED_ASSERTION                2 /* STATUS LED=no change */
#define LED_PANIC                    3 /* STATUS LED=flashing */

#endif /* __BOARDS_ARM_SAMD2L2_XIAO_SEEEDUINO_INCLUDE_BOARD_H */
