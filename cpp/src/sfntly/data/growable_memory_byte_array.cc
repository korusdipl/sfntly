/*
 * Copyright 2011 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <limits.h>
#include <algorithm>

#include "sfntly/data/growable_memory_byte_array.h"

namespace sfntly {

GrowableMemoryByteArray::GrowableMemoryByteArray()
    : ByteArray(0, INT_MAX, true) {
}

GrowableMemoryByteArray::~GrowableMemoryByteArray() {}

bool GrowableMemoryByteArray::internalPut(int32_t index, byte_t b) {
  if ((size_t)index >= b_.capacity()) {
    b_.resize((size_t)(index + 1) << 2);  // grow exponentially
  }
  b_[index] = b;
  return true;
}

int32_t GrowableMemoryByteArray::internalPut(int32_t index, ByteVector* b,
                                             int32_t offset, int32_t length) {
  if ((size_t)index + length >= b_.capacity()) {
    b_.resize((size_t)(index + length + 1) << 2);
  }
  std::copy(b->begin() + offset, b->begin() + (offset + length),
            b_.begin() + index);
  return length;
}

byte_t GrowableMemoryByteArray::internalGet(int32_t index) {
  return b_[index];
}

int32_t GrowableMemoryByteArray::internalGet(int32_t index, ByteVector* b,
                                             int32_t offset, int32_t length) {
  std::copy(b_.begin() + index, b_.begin() + (index + length),
            b->begin() + offset);
  return length;
}

void GrowableMemoryByteArray::close() {
  b_.clear();
}

byte_t* GrowableMemoryByteArray::begin() {
  return &(b_[0]);
}

}  // namespace sfntly
