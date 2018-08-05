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

#pragma once

#include <kw/reflection/type.h>

namespace eastl {
template <typename T, size_t N>
struct array;
class allocator;
template <typename T, typename Allocator>
class basic_string;
template <typename T>
class basic_string_view;
template <size_t N, typename WordType>
class bitset;
template <typename Allocator, typename Element, typename Container>
class bitvector;
template <typename T, typename Allocator, unsigned kDequeSubarraySize>
class deque;
template <typename Key, typename T, size_t nodeCount, size_t bucketCount, bool bEnableOverflow, typename Hash, typename Predicate, bool bCacheHashCode, typename OverflowAllocator>
class fixed_hash_map;
template <typename Value, size_t nodeCount, size_t bucketCount, bool bEnableOverflow, typename Hash, typename Predicate, bool bCacheHashCode, typename OverflowAllocator>
class fixed_hash_set;
template <typename T, size_t nodeCount, bool bEnableOverflow, typename OverflowAllocator>
class fixed_list;
template <typename Key, typename T, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
class fixed_map;
template <typename Key, typename T, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
class fixed_multimap;
template <typename Key, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
class fixed_multiset;
template <typename Key, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
class fixed_set;
template <typename T, size_t nodeCount, bool bEnableOverflow, typename OverflowAllocator>
class fixed_slist;
template <typename T, int nodeCount, bool bEnableOverflow, typename OverflowAllocator>
class fixed_string;
template <typename T, size_t nodeCount, bool bEnableOverflow, typename OverflowAllocator>
class fixed_vector;
template <typename Key, typename T, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
class hash_map;
template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
class hash_set;
template <typename T, typename Allocator>
class list;
template <typename Key, typename T, typename Compare, typename Allocator>
class map;
template <typename T>
class optional;
template <typename T1, typename T2>
struct pair;
template <typename T, typename Container, typename Compare>
class priority_queue;
template <typename T, typename Container>
class queue;
template <typename T, typename Container, typename Allocator>
class ring_buffer;
template <typename Key, typename Compare, typename Allocator>
class set;
template <typename T>
class shared_ptr;
template <typename T, typename Allocator>
class slist;
template <typename T, typename Container>
class stack;
template <typename T, typename Hash, typename Predicate, typename Allocator>
class string_hash_map;
template <typename T, typename Predicate, typename Allocator>
class string_map;
template <typename... Ts>
class tuple;
template <typename T>
struct default_delete;
template <typename T, typename Deleter>
class unique_ptr;
template <class... Types>
class variant;
template <typename T, typename Allocator>
class vector;
template <typename Key, typename T, typename Compare, typename Allocator, typename RandomAccessContainer>
class vector_map;
template <typename Key, typename T, typename Compare, typename Allocator, typename RandomAccessContainer>
class vector_multimap;
template <typename Key, typename Compare, typename Allocator, typename RandomAccessContainer>
class vector_multiset;
template <typename Key, typename Compare, typename Allocator, typename RandomAccessContainer>
class vector_set;
} // namespace eastl

namespace kw::type_details {
template <typename T>
struct container_type {
    static Type::Container get(Vector<const Type*>&) {
        return Type::Container::NONE;
    }
};

template <typename T, size_t N>
struct container_type<eastl::array<T, N>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::ARRAY;
    }
};

template <typename T, typename Allocator>
struct container_type<eastl::basic_string<T, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::BASIC_STRING;
    }
};

template <typename T>
struct container_type<eastl::basic_string_view<T>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::BASIC_STRING_VIEW;
    }
};

template <size_t N, typename WordType>
struct container_type<eastl::bitset<N, WordType>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        return Type::Container::BITSET;
    }
};
template <typename Allocator, typename Element, typename Container>
struct container_type<eastl::bitvector<Allocator, Element, Container>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        return Type::Container::BITVECTOR;
    }
};

template <typename T, typename Allocator, unsigned kDequeSubarraySize>
struct container_type<eastl::deque<T, Allocator, kDequeSubarraySize>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::DEQUE;
    }
};

template <typename Key, typename T, size_t nodeCount, size_t bucketCount, bool bEnableOverflow, typename Hash, typename Predicate, bool bCacheHashCode, typename OverflowAllocator>
struct container_type<eastl::fixed_hash_map<Key, T, nodeCount, bucketCount, bEnableOverflow, Hash, Predicate, bCacheHashCode, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<Key>());
        template_arguments.push_back(Type::of<T>());
        return Type::Container::FIXED_HASH_MAP;
    }
};

template <typename Value, size_t nodeCount, size_t bucketCount, bool bEnableOverflow, typename Hash, typename Predicate, bool bCacheHashCode, typename OverflowAllocator>
struct container_type<eastl::fixed_hash_set<Value, nodeCount, bucketCount, bEnableOverflow, Hash, Predicate, bCacheHashCode, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<Value>());
        return Type::Container::FIXED_HASH_SET;
    }
};

template <typename T, size_t nodeCount, bool bEnableOverflow, typename OverflowAllocator>
struct container_type<eastl::fixed_list<T, nodeCount, bEnableOverflow, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::FIXED_LIST;
    }
};

template <typename Key, typename T, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
struct container_type<eastl::fixed_map<Key, T, nodeCount, bEnableOverflow, Compare, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<Key>());
        template_arguments.push_back(Type::of<T>());
        return Type::Container::FIXED_MAP;
    }
};

template <typename Key, typename T, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
struct container_type<eastl::fixed_multimap<Key, T, nodeCount, bEnableOverflow, Compare, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<Key>());
        template_arguments.push_back(Type::of<T>());
        return Type::Container::FIXED_MULTIMAP;
    }
};

template <typename Key, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
struct container_type<eastl::fixed_multiset<Key, nodeCount, bEnableOverflow, Compare, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<Key>());
        return Type::Container::FIXED_MULTISET;
    }
};

template <typename Key, size_t nodeCount, bool bEnableOverflow, typename Compare, typename OverflowAllocator>
struct container_type<eastl::fixed_set<Key, nodeCount, bEnableOverflow, Compare, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<Key>());
        return Type::Container::FIXED_SET;
    }
};

template <typename T, size_t nodeCount, bool bEnableOverflow, typename OverflowAllocator>
struct container_type<eastl::fixed_slist<T, nodeCount, bEnableOverflow, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::FIXED_SLIST;
    }
};

template <typename T, int nodeCount, bool bEnableOverflow, typename OverflowAllocator>
struct container_type<eastl::fixed_string<T, nodeCount, bEnableOverflow, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::FIXED_BASIC_STRING;
    }
};

template <typename T, size_t nodeCount, bool bEnableOverflow, typename OverflowAllocator>
struct container_type<eastl::fixed_vector<T, nodeCount, bEnableOverflow, OverflowAllocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::FIXED_VECTOR;
    }
};

template <typename Key, typename T, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
struct container_type<eastl::hash_map<Key, T, Hash, Predicate, Allocator, bCacheHashCode>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<Key>());
        template_arguments.push_back(Type::of<T>());
        return Type::Container::HASH_MAP;
    }
};

template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
struct container_type<eastl::hash_set<Value, Hash, Predicate, Allocator, bCacheHashCode>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<Value>());
        return Type::Container::HASH_SET;
    }
};

template <typename T, typename Allocator>
struct container_type<eastl::list<T, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::LIST;
    }
};

template <typename Key, typename T, typename Compare, typename Allocator>
struct container_type<eastl::map<Key, T, Compare, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<Key>());
        template_arguments.push_back(Type::of<T>());
        return Type::Container::MAP;
    }
};

template <typename T>
struct container_type<eastl::optional<T>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::OPTIONAL;
    }
};

template <typename T1, typename T2>
struct container_type<eastl::pair<T1, T2>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<T1>());
        template_arguments.push_back(Type::of<T2>());
        return Type::Container::PAIR;
    }
};

template <typename T, typename Container, typename Compare>
struct container_type<eastl::priority_queue<T, Container, Compare>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::PRIORITY_QUEUE;
    }
};

template <typename T, typename Container>
struct container_type<eastl::queue<T, Container>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::QUEUE;
    }
};

template <typename T, typename Container, typename Allocator>
struct container_type<eastl::ring_buffer<T, Container, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::RING_BUFFER;
    }
};

template <typename Key, typename Compare, typename Allocator>
struct container_type<eastl::set<Key, Compare, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<Key>());
        return Type::Container::SET;
    }
};

template <typename T>
struct container_type<eastl::shared_ptr<T>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::SHARED_PTR;
    }
};

template <typename T, typename Allocator>
struct container_type<eastl::slist<T, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::SLIST;
    }
};

template <typename T, typename Container>
struct container_type<eastl::stack<T, Container>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::STACK;
    }
};

template <typename T, typename Hash, typename Predicate, typename Allocator>
struct container_type<eastl::string_hash_map<T, Hash, Predicate, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::STRING_HASH_MAP;
    }
};

template <typename T, typename Predicate, typename Allocator>
struct container_type<eastl::string_map<T, Predicate, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::STRING_MAP;
    }
};

template <typename... Ts>
struct container_type<eastl::tuple<Ts...>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(sizeof...(Ts));
        (template_arguments.push_back(Type::of<Ts>()), ...);
        return Type::Container::TUPLE;
    }
};

template <typename T, typename Deleter>
struct container_type<eastl::unique_ptr<T, Deleter>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::UNIQUE_PTR;
    }
};

template <class... Types>
struct container_type<eastl::variant<Types...>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(sizeof...(Types));
        (template_arguments.push_back(Type::of<Types>()), ...);
        return Type::Container::VARIANT;
    }
};

template <typename T, typename Allocator>
struct container_type<eastl::vector<T, Allocator>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<T>());
        return Type::Container::VECTOR;
    }
};

template <typename Key, typename T, typename Compare, typename Allocator, typename RandomAccessContainer>
struct container_type<eastl::vector_map<Key, T, Compare, Allocator, RandomAccessContainer>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<Key>());
        template_arguments.push_back(Type::of<T>());
        return Type::Container::VECTOR_MAP;
    }
};

template <typename Key, typename T, typename Compare, typename Allocator, typename RandomAccessContainer>
struct container_type<eastl::vector_multimap<Key, T, Compare, Allocator, RandomAccessContainer>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(2);
        template_arguments.push_back(Type::of<Key>());
        template_arguments.push_back(Type::of<T>());
        return Type::Container::VECTOR_MULTIMAP;
    }
};

template <typename Key, typename Compare, typename Allocator, typename RandomAccessContainer>
struct container_type<eastl::vector_multiset<Key, Compare, Allocator, RandomAccessContainer>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<Key>());
        return Type::Container::VECTOR_MULTISET;
    }
};

template <typename Key, typename Compare, typename Allocator, typename RandomAccessContainer>
struct container_type<eastl::vector_set<Key, Compare, Allocator, RandomAccessContainer>> {
    static Type::Container get(Vector<const Type*>& template_arguments) {
        template_arguments.reserve(1);
        template_arguments.push_back(Type::of<Key>());
        return Type::Container::VECTOR_SET;
    }
};
} // namespace kw::type_details
