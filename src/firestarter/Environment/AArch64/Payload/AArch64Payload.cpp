/******************************************************************************
 * FIRESTARTER - A Processor Stress Test Utility
 * Copyright (C) 2020-2023 TU Dresden, Center for Information Services and High
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

#include <chrono>
#include <thread>
#include <type_traits>

#ifdef _MSC_VER
#include <array>
#include <intrin.h>
#endif

#include <firestarter/Environment/AArch64/Payload/AArch64Payload.hpp>

using namespace firestarter::environment::aarch64::payload;

void AArch64Payload::lowLoadFunction(volatile unsigned long long *addrHigh,
                                 unsigned long long period) {
  int nap;

  nap = period / 100;
  __asm__ __volatile__("dmb sy" : : : "memory");
  // while signal low load
  while (*addrHigh == LOAD_LOW) {
    __asm__ __volatile__("dmb sy" : : : "memory");
    std::this_thread::sleep_for(std::chrono::microseconds(nap));
    __asm__ __volatile__("dmb sy" : : : "memory");
  }
}

void AArch64Payload::init(unsigned long long *memoryAddr,
                      unsigned long long bufferSize, double firstValue,
                      double lastValue) {
  unsigned long long i = 0;

  for (; i < INIT_BLOCKSIZE; i++)
    *((double *)(memoryAddr + i)) = 0.25 + (double)i * 8.0 * firstValue;
  for (; i <= bufferSize - INIT_BLOCKSIZE; i += INIT_BLOCKSIZE)
    std::memcpy(memoryAddr + i, memoryAddr + i - INIT_BLOCKSIZE,
                sizeof(unsigned long long) * INIT_BLOCKSIZE);
  for (; i < bufferSize; i++)
    *((double *)(memoryAddr + i)) = 0.25 + (double)i * 8.0 * lastValue;
}

unsigned long long
AArch64Payload::highLoadFunction(unsigned long long *addrMem,
                             volatile unsigned long long *addrHigh,
                             unsigned long long iterations) {
  return this->loadFunction(addrMem, addrHigh, iterations);
}
