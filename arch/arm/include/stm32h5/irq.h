/****************************************************************************
 * arch/arm/include/stm32h5/irq.h
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

/* This file should never be included directed but, rather,
 * only indirectly through nuttx/irq.h
 */

#ifndef __ARCH_ARM_INCLUDE_STM32H5_IRQ_H
#define __ARCH_ARM_INCLUDE_STM32H5_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* IRQ numbers.  The IRQ number corresponds vector number and hence map
 * directly to bits in the NVIC.  This does, however, waste several words of
 * memory in the IRQ to handle mapping tables.
 */

/* Processor Exceptions (vectors 0-15) */

#define STM32_IRQ_RESERVED       (0) /* Reserved vector (only used with CONFIG_DEBUG_FEATURES) */
                                     /* Vector  0: Reset stack pointer value */
                                     /* Vector  1: Reset (not handler as an IRQ) */
#define STM32_IRQ_NMI            (2) /* Vector  2: Non-Maskable Interrupt (NMI) */
#define STM32_IRQ_HARDFAULT      (3) /* Vector  3: Hard fault */
#define STM32_IRQ_MEMFAULT       (4) /* Vector  4: Memory management (MPU) */
#define STM32_IRQ_BUSFAULT       (5) /* Vector  5: Bus fault */
#define STM32_IRQ_USAGEFAULT     (6) /* Vector  6: Usage fault */
                                     /* Vectors 7-10: Reserved */
#define STM32_IRQ_SVCALL        (11) /* Vector 11: SVC call */
#define STM32_IRQ_DBGMONITOR    (12) /* Vector 12: Debug Monitor */
                                     /* Vector 13: Reserved */
#define STM32_IRQ_PENDSV        (14) /* Vector 14: Pendable system service request */
#define STM32_IRQ_SYSTICK       (15) /* Vector 15: System tick */

/* External interrupts (vectors >= 16).  These definitions are
 * chip-specific
 */

#define STM32_IRQ_FIRST         (16) /* Vector number of the first external interrupt */

#if defined(CONFIG_STM32H5_STM32H52XXX) || defined(CONFIG_STM32H5_STM32H53XXX) || \
    defined(CONFIG_STM32H5_STM32H56XXX) || defined(CONFIG_STM32H5_STM32H57XXX)
#  include <arch/stm32h5/stm32h5xx_irq.h>
#else
#  error "Unsupported STM32 H5 chip"
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__
#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#undef EXTERN
#ifdef __cplusplus
}
#endif
#endif

#endif /* __ARCH_ARM_INCLUDE_STM32H5_IRQ_H */
