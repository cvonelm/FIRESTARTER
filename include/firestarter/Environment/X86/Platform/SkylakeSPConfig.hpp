/******************************************************************************
 * FIRESTARTER - A Processor Stress Test Utility
 * Copyright (C) 2020 TU Dresden, Center for Information Services and High
 * Performance Computing
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/\>.
 *
 * Contact: daniel.hackenberg@tu-dresden.de
 *****************************************************************************/

#pragma once

#include "firestarter/Environment/X86/Payload/AVX512Payload.hpp"
#include "firestarter/Environment/X86/Platform/X86PlatformConfig.hpp"

namespace firestarter::environment::x86::platform {
class SkylakeSPConfig final : public X86PlatformConfig {
public:
  SkylakeSPConfig() noexcept
      : X86PlatformConfig(/*Name=*/"SKL_XEONEP", /*Family=*/6, /*Models=*/{85},
                          /*Settings=*/
                          environment::payload::PayloadSettings(/*Threads=*/{1, 2},
                                                                /*DataCacheBufferSize=*/{32768, 1048576, 1441792},
                                                                /*RamBufferSize=*/1048576000, /*Lines=*/1536,
                                                                /*InstructionGroups=*/
                                                                {{"RAM_S", 3},
                                                                 {"RAM_P", 1},
                                                                 {"L3_S", 1},
                                                                 {"L3_P", 1},
                                                                 {"L2_S", 4},
                                                                 {"L2_L", 70},
                                                                 {"L1_S", 0},
                                                                 {"L1_L", 40},
                                                                 {"REG", 140}}),
                          /*Payload=*/std::make_shared<const payload::AVX512Payload>()) {}
};
} // namespace firestarter::environment::x86::platform
