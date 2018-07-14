/**
 *  Copyright (c) 2018, 21DOGZ.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 *  except in compliance with the License. You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is
 *  distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and limitations under the License.
 */

#define EASTL_USER_DEFINED_ALLOCATOR
#include <EASTL/allocator.h>
#include <cstdlib>

namespace eastl {
allocator::allocator(const char* name) {
#if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
#endif
}

allocator::allocator(const allocator& alloc) {
#if EASTL_NAME_ENABLED
    mpName = alloc.mpName;
#endif
}

allocator::allocator(const allocator& a, const char* name) {
#if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
#endif
}

allocator& allocator::operator=(const allocator& alloc) {
#if EASTL_NAME_ENABLED
    mpName = alloc.mpName;
#endif
    return *this;
}

const char* allocator::get_name() const {
#if EASTL_NAME_ENABLED
    return mpName;
#else
    return EASTL_ALLOCATOR_DEFAULT_NAME;
#endif
}

void allocator::set_name(const char* name) {
#if EASTL_NAME_ENABLED
    mpName = pName;
#endif
}

void* allocator::allocate(size_t n, int flags) {
#if defined(_MSC_VER)
    // See another allocate overload for commentary on this
    return _aligned_malloc(n, 1);
#else
    return std::malloc(n);
#endif
}

void* allocator::allocate(size_t n, size_t alignment, size_t offset, int flags) {
#if defined(__APPLE__)
    // Apple standart library is retarted and does not have aligned_alloc yet
    void* result;
    if (posix_memalign(&result, alignment, n)) {
        return nullptr;
    }
    return result;
#elif defined(_MSC_VER)
    // The Windows standart library is completely retarded and they're not even planning to provide std::aligned_alloc
    return _aligned_malloc(n, alignment);
#else
    // The Linux standart library is a little bit retarded too,
    // and the aligned_alloc function is out of 'std' namespace
    return aligned_alloc(n, alignment);
#endif
}

void allocator::deallocate(void* p, size_t n) {
#if defined(_MSC_VER)
    _aligned_free(p);
#else
    std::free(p);
#endif
}

bool operator==(const allocator& a, const allocator& b) {
    return true; // All allocators are considered equal, as they merely use global new/delete.
}

bool operator!=(const allocator& a, const allocator& b) {
    return false; // All allocators are considered equal, as they merely use global new/delete.
}
} // namespace eastl