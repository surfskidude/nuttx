# ##############################################################################
# boards/arm/tms570/tms570ls31x-usb-kit/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

set(SRCS tms570_initialize.c tms570_bringup.c tms570_spi.c)

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS tms570_autoleds.c)
else()
  list(APPEND SRCS tms570_userleds.c)
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS tms570_buttons.c)
endif()

if(CONFIG_BOARDCTL)
  list(APPEND SRCS tms570_appinit.c)
endif()

if(CONFIG_MMCSD)
  list(APPEND SRCS tms570_sdmmc.c)
endif()

target_sources(board PRIVATE ${SRCS})

set_property(GLOBAL PROPERTY LD_SCRIPT
                             "${NUTTX_BOARD_DIR}/scripts/flash-sram.ld")
