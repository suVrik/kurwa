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

#include <kw/reflection/type.h>

#include <gmock/gmock.h>

TEST(type, of) {
    using namespace kw;

    const Type* a = Type::of<kw::int32>();
    const Type* b = Type::of<kw::int32>();
    const Type* c = Type::of<kw::int32&>();
    const Type* d = Type::of<kw::int32&&>();
    const Type* e = Type::of<const kw::int32>();
    const Type* f = Type::of<const kw::int32&>();
    const Type* g = Type::of<const kw::int32&&>();
    const Type* h = Type::of<kw::int64>();

    EXPECT_EQ(a, b);
    EXPECT_EQ(b, c);
    EXPECT_EQ(c, d);
    EXPECT_EQ(d, e);
    EXPECT_EQ(e, f);
    EXPECT_EQ(f, g);
    EXPECT_NE(g, h);
}

// Even tho the test's name is 'register_parents', besides that, it also tests the following methods:
// * get_parents();
// * is_inherited_from();
// * is_inherited_from<>();
// * is_base_of();
// * is_base_of<>();
TEST(type, register_parents) {
    using namespace kw;

    struct DummyBaseA {};
    struct DummyBaseB {};
    struct DummyChildA : DummyBaseA {};
    struct DummyChildB : DummyBaseA, DummyBaseB {};

    Type::register_parents<DummyChildA, DummyBaseA>();
    Type::register_parents<DummyChildB, DummyBaseA, DummyBaseB>();

    const Type* base_a = Type::of<DummyBaseA>();
    const Type* base_b = Type::of<DummyBaseB>();
    const Type* a      = Type::of<DummyChildA>();
    const Type* b      = Type::of<DummyChildB>();

    EXPECT_TRUE(base_a->get_parents().empty());

    EXPECT_FALSE(base_a->is_inherited_from<DummyChildA>().first);
    EXPECT_FALSE(base_a->is_inherited_from<DummyChildB>().first);
    EXPECT_FALSE(base_a->is_inherited_from<DummyBaseA>().first);
    EXPECT_FALSE(base_a->is_inherited_from<DummyBaseB>().first);

    EXPECT_FALSE(base_a->is_inherited_from(a).first);
    EXPECT_FALSE(base_a->is_inherited_from(b).first);
    EXPECT_FALSE(base_a->is_inherited_from(base_a).first);
    EXPECT_FALSE(base_a->is_inherited_from(base_b).first);

    EXPECT_TRUE(base_a->is_base_of<DummyChildA>().first);
    EXPECT_TRUE(base_a->is_base_of<DummyChildB>().first);
    EXPECT_FALSE(base_a->is_base_of<DummyBaseA>().first);
    EXPECT_FALSE(base_a->is_base_of<DummyBaseB>().first);

    EXPECT_TRUE(base_a->is_base_of(a).first);
    EXPECT_TRUE(base_a->is_base_of(b).first);
    EXPECT_FALSE(base_a->is_base_of(base_a).first);
    EXPECT_FALSE(base_a->is_base_of(base_b).first);

    EXPECT_TRUE(base_b->get_parents().empty());

    EXPECT_FALSE(base_b->is_inherited_from<DummyChildA>().first);
    EXPECT_FALSE(base_b->is_inherited_from<DummyChildB>().first);
    EXPECT_FALSE(base_b->is_inherited_from<DummyBaseA>().first);
    EXPECT_FALSE(base_b->is_inherited_from<DummyBaseB>().first);

    EXPECT_FALSE(base_b->is_inherited_from(a).first);
    EXPECT_FALSE(base_b->is_inherited_from(b).first);
    EXPECT_FALSE(base_b->is_inherited_from(base_a).first);
    EXPECT_FALSE(base_b->is_inherited_from(base_b).first);

    EXPECT_FALSE(base_b->is_base_of<DummyChildA>().first);
    EXPECT_TRUE(base_b->is_base_of<DummyChildB>().first);
    EXPECT_FALSE(base_b->is_base_of<DummyBaseA>().first);
    EXPECT_FALSE(base_b->is_base_of<DummyBaseB>().first);

    EXPECT_FALSE(base_b->is_base_of(a).first);
    EXPECT_TRUE(base_b->is_base_of(b).first);
    EXPECT_FALSE(base_b->is_base_of(base_a).first);
    EXPECT_FALSE(base_b->is_base_of(base_b).first);

    EXPECT_EQ(a->get_parents().size(), 1);
    EXPECT_EQ(a->get_parents()[0].type, base_a);

    EXPECT_FALSE(a->is_inherited_from<DummyChildA>().first);
    EXPECT_FALSE(a->is_inherited_from<DummyChildB>().first);
    EXPECT_TRUE(a->is_inherited_from<DummyBaseA>().first);
    EXPECT_FALSE(a->is_inherited_from<DummyBaseB>().first);

    EXPECT_FALSE(a->is_inherited_from(a).first);
    EXPECT_FALSE(a->is_inherited_from(b).first);
    EXPECT_TRUE(a->is_inherited_from(base_a).first);
    EXPECT_FALSE(a->is_inherited_from(base_b).first);

    EXPECT_FALSE(a->is_base_of<DummyChildA>().first);
    EXPECT_FALSE(a->is_base_of<DummyChildB>().first);
    EXPECT_FALSE(a->is_base_of<DummyBaseA>().first);
    EXPECT_FALSE(a->is_base_of<DummyBaseB>().first);

    EXPECT_FALSE(a->is_base_of(a).first);
    EXPECT_FALSE(a->is_base_of(b).first);
    EXPECT_FALSE(a->is_base_of(base_a).first);
    EXPECT_FALSE(a->is_base_of(base_b).first);

    EXPECT_EQ(b->get_parents().size(), 2);
    EXPECT_EQ(b->get_parents()[0].type, base_a);
    EXPECT_EQ(b->get_parents()[1].type, base_b);

    EXPECT_FALSE(b->is_inherited_from<DummyChildA>().first);
    EXPECT_FALSE(b->is_inherited_from<DummyChildB>().first);
    EXPECT_TRUE(b->is_inherited_from<DummyBaseA>().first);
    EXPECT_TRUE(b->is_inherited_from<DummyBaseB>().first);

    EXPECT_FALSE(b->is_inherited_from(a).first);
    EXPECT_FALSE(b->is_inherited_from(b).first);
    EXPECT_TRUE(b->is_inherited_from(base_a).first);
    EXPECT_TRUE(b->is_inherited_from(base_b).first);

    EXPECT_FALSE(b->is_base_of<DummyChildA>().first);
    EXPECT_FALSE(b->is_base_of<DummyChildB>().first);
    EXPECT_FALSE(b->is_base_of<DummyBaseA>().first);
    EXPECT_FALSE(b->is_base_of<DummyBaseB>().first);

    EXPECT_FALSE(b->is_base_of(a).first);
    EXPECT_FALSE(b->is_base_of(b).first);
    EXPECT_FALSE(b->is_base_of(base_a).first);
    EXPECT_FALSE(b->is_base_of(base_b).first);
}

// Even tho the test's name is 'get_type_info', besides that, it also tests the following methods:
// * get_size();
// * get_name();
// * is_small_object();
// * is_same<>();
TEST(type, get_type_info) {
    const kw::Type* a = kw::Type::of<kw::int32>();
    EXPECT_EQ(a->get_type_info(), typeid(kw::int32));
    EXPECT_EQ(a->get_size(), sizeof(kw::int32));
    EXPECT_EQ(a->get_name(), typeid(kw::int32).name());
    EXPECT_TRUE(a->is_small_object());

    EXPECT_TRUE(a->is_same<kw::int32>());
    EXPECT_TRUE(a->is_same<int>());
    EXPECT_TRUE(a->is_same<int32_t>());
    EXPECT_FALSE(a->is_same<kw::int64>());
}

TEST(type, inheritance_offsets) {
    using namespace kw;

    struct DummyBaseA {
        int32 dummy_a;
    };
    struct DummyBaseB {
        int32 dummy_b;
    };
    struct DummyChild : DummyBaseA, DummyBaseB {};

    EXPECT_EQ(sizeof(DummyChild), sizeof(int32) * 2);

    Type::register_parents<DummyChild, DummyBaseA, DummyBaseB>();

    const Type* a = Type::of<DummyChild>();

    EXPECT_TRUE(a->is_inherited_from<DummyBaseA>().first);
    EXPECT_TRUE(a->is_inherited_from<DummyBaseB>().first);

    EXPECT_EQ(a->is_inherited_from<DummyBaseA>().second, 0);
    EXPECT_EQ(a->is_inherited_from<DummyBaseB>().second, sizeof(int32));
}