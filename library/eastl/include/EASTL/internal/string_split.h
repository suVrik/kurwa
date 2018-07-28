#ifndef EASTL_STRING_SPLIT_H
#define EASTL_STRING_SPLIT_H

#include <EASTL/string_view.h>
#include <EASTL/vector.h>

namespace eastl {
    namespace string_details {
        template <typename T, typename Allocator = EASTLAllocatorType>
        vector<basic_string_view<T>, Allocator> string_split(const T* word, size_t word_size, const T* delim, size_t delim_size) {
            vector<basic_string_view<T>, Allocator> result;
            for (size_t word_offset = 0; word_offset < word_size; word_offset++) {
                size_t delim_offset = 0;
                while (delim_offset < delim_size && word_offset + delim_offset < word_size && word[word_offset + delim_offset] == delim[delim_offset]) {
                    delim_offset++;
                }
                if (delim_offset == delim_size) {
                    // str[word_offset]...str[word_offset + delim_offset - 1] is delimiter
                    result.push_back(basic_string_view<T>(word, word_offset));
                    word += word_offset + delim_offset;
                    word_size -= word_offset + delim_offset;
                    word_offset = numeric_limits<size_t>::max(); // We want overflow.
                }
            }
            // Yea, I know, it could be an empty sting. But that's how it's meant to be,
            // when the delimiter is at the very end.
            result.push_back(basic_string_view<T>(word, word_size));
            return result;
        }
    }
} // namespace eastl

#endif // Header include guard
