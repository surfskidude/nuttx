/****************************************************************************
 * arch/arm64/src/common/arm64_pthread_start.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <pthread.h>
#include <nuttx/arch.h>
#include <assert.h>

#include <arch/syscall.h>

#include "arm64_internal.h"

#include "sched/sched.h"

#if !defined(CONFIG_BUILD_FLAT) && defined(__KERNEL__) && \
    !defined(CONFIG_DISABLE_PTHREAD)

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_pthread_start
 *
 * Description:
 *   In this kernel mode build, this function will be called to execute a
 *   pthread in user-space.  When the pthread is first started, a kernel-mode
 *   stub will first run to perform some housekeeping functions.  This
 *   kernel-mode stub will then be called transfer control to the user-mode
 *   pthread.
 *
 *   Normally the a user-mode start-up stub will also execute before the
 *   pthread actually starts.  See libc/pthread/pthread_create.c
 *
 * Input Parameters:
 *   startup - The user-space pthread startup function
 *   entrypt - The user-space address of the pthread entry point
 *   arg     - Standard argument for the pthread entry point
 *
 * Returned Value:
 *   This function should not return.  It should call the user-mode start-up
 *   stub and that stub should call pthread_exit if/when the user pthread
 *   terminates.
 *
 ****************************************************************************/

void up_pthread_start(pthread_trampoline_t startup,
                      pthread_startroutine_t entrypt, pthread_addr_t arg)
{
  struct tcb_s *rtcb = this_task();

  /* Set up to enter the user-space pthread start-up function in
   * unprivileged mode. We need:
   *
   *   R0   = entrypt
   *   R1   = arg
   *   ELR  = startup
   *   SPSR = user mode
   */

  arm64_jump_to_user((uint64_t)startup, (uint64_t)entrypt, (uint64_t)arg,
                     (uint64_t)rtcb->xcp.ustkptr, rtcb->xcp.initregs);
}

#endif /* !CONFIG_BUILD_FLAT && __KERNEL__ && !CONFIG_DISABLE_PTHREAD */
