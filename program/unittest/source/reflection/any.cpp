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

#include <kw/base/hash_map.h>
#include <kw/base/map.h>
#include <kw/base/vector.h>
#include <kw/reflection/any.h>

#include <EASTL/sort.h>

#include <gmock/gmock.h>

TEST(any, basic) {
    using namespace kw;

    Any a;
    Any b;

    EXPECT_TRUE(a.get_type()->is_same<void>());
    EXPECT_TRUE(b.get_type()->is_same<void>());

    EXPECT_EQ(a, b);
    EXPECT_LE(a, b);
    EXPECT_GE(a, b);

    b.cast<void>(); // No result, but must compile.
    EXPECT_EQ(b.cast<int32>(), nullptr);

    EXPECT_EQ(b.get_type(), Type::of<void>());
}

TEST(any, by_move) {
    using namespace kw;

    int32 va = 13;
    int32 vb = 37;

    Any a(va);
    Any b(vb);

    EXPECT_NE(a, b);
    EXPECT_LT(a, b);
    EXPECT_GT(b, a);

    EXPECT_NE(a.cast<int32>(), nullptr);
    EXPECT_NE(b.cast<int32>(), nullptr);
    EXPECT_EQ(*a.cast<int32>(), 13);
    EXPECT_EQ(*b.cast<int32>(), 37);

    EXPECT_EQ(a.get_type(), Type::of<int32>());
    EXPECT_EQ(a.get_type(), b.get_type());

    EXPECT_TRUE(a.get_type()->is_same<int32>());
}

TEST(any, structure_by_move) {
    using namespace kw;

    struct small {
        int16 a;
        int16 b;
    };
    struct big {
        int64 a;
        int64 b;
    };

    small va = { 10, 20 };
    big vb = { 30, 40 };

    Any a(va);
    Any b(vb);

    EXPECT_TRUE(a.get_type()->is_small_object());
    EXPECT_FALSE(b.get_type()->is_small_object());

    EXPECT_NE(a.cast<small>(), nullptr);
    EXPECT_NE(b.cast<big>(), nullptr);
    EXPECT_EQ(a.cast<small>()->a, 10);
    EXPECT_EQ(a.cast<small>()->b, 20);
    EXPECT_EQ(b.cast<big>()->a, 30);
    EXPECT_EQ(b.cast<big>()->b, 40);

    EXPECT_TRUE(a.get_type()->is_same<small>());
    EXPECT_TRUE(b.get_type()->is_same<big>());
}

TEST(any, big_inheritance) {
    using namespace kw;

    struct BaseA {
        int64 a_1 = 1001;
        int32 a_2 = 1002;
    };

    struct BaseB {
        int64 b_1 = 1003;
        int32 b_2 = 1004;
        int16 b_3 = 1005;
    };

    struct BaseC {
        int64 c_1 = 1006;
    };

    struct MiddleBase : BaseA, BaseB, BaseC {
        int16 mid = 1007;
    };

    struct Child : MiddleBase {
        int16 val = 1008;
    };

    Type::register_parents<MiddleBase, BaseA, BaseB, BaseC>();
    Type::register_parents<Child, MiddleBase>();

    Child c;

    Any a(c);

    EXPECT_EQ(a.get_type(), Type::of<Child>());
    EXPECT_TRUE(a.get_type()->is_same<Child>());

    EXPECT_NE(a.cast<Child>(), nullptr);
    EXPECT_NE(a.cast<MiddleBase>(), nullptr);
    EXPECT_NE(a.cast<BaseC>(), nullptr);
    EXPECT_NE(a.cast<BaseB>(), nullptr);
    EXPECT_NE(a.cast<BaseA>(), nullptr);

    EXPECT_EQ(a.cast<Child>()->val, 1008);
    EXPECT_EQ(a.cast<MiddleBase>()->mid, 1007);
    EXPECT_EQ(a.cast<BaseC>()->c_1, 1006);
    EXPECT_EQ(a.cast<BaseB>()->b_3, 1005);
    EXPECT_EQ(a.cast<BaseB>()->b_2, 1004);
    EXPECT_EQ(a.cast<BaseB>()->b_1, 1003);
    EXPECT_EQ(a.cast<BaseA>()->a_2, 1002);
    EXPECT_EQ(a.cast<BaseA>()->a_1, 1001);

    EXPECT_FALSE(a.get_type()->is_base_of<Child>().first);
    EXPECT_FALSE(a.get_type()->is_base_of<MiddleBase>().first);
    EXPECT_FALSE(a.get_type()->is_base_of<BaseC>().first);
    EXPECT_FALSE(a.get_type()->is_base_of<BaseB>().first);
    EXPECT_FALSE(a.get_type()->is_base_of<BaseA>().first);

    EXPECT_FALSE(a.get_type()->is_inherited_from<Child>().first);
    EXPECT_TRUE(a.get_type()->is_inherited_from<MiddleBase>().first);
    EXPECT_TRUE(a.get_type()->is_inherited_from<BaseC>().first);
    EXPECT_TRUE(a.get_type()->is_inherited_from<BaseB>().first);
    EXPECT_TRUE(a.get_type()->is_inherited_from<BaseA>().first);
}

TEST(any, big_repeating_inheritance) {
    using namespace kw;

    struct Grandpa {
        int64 a_1;
        int32 a_2;
    };

    struct Grandma {
        int64 d;
    };

    struct Mother : Grandpa {
        int64 b_1;
        int32 b_2;
        int16 b_3;
    };

    struct Father : Grandpa, Grandma {
        int64 c_1;
    };

    struct Child : Mother, Father {
        Child(int64 a_1, int32 a_2, int64 b_1, int32 b_2, int16 b_3, int64 c_1, int16 mid) {
            this->Mother::a_1 = a_1;
            this->Mother::a_2 = a_2;
            this->Father::a_1 = a_1;
            this->Father::a_2 = a_2;
            this->b_1 = b_1;
            this->b_2 = b_2;
            this->b_3 = b_3;
            this->c_1 = c_1;
            this->d = 1997;
            this->mid = mid;
        }

        int16 mid;
    };

    Type::register_parents<Mother, Grandpa>();

    Type::register_parents<Father, Grandpa, Grandma>();

    Type::register_parents<Child, Mother, Father>();

    Any a;
    a.emplace<Child>(1001, 1002, 1003, 1004, 1005, 1006, 1007);

    EXPECT_EQ(a.get_type(), Type::of<Child>());
    EXPECT_TRUE(a.get_type()->is_same<Child>());

    EXPECT_NE(a.cast<Child>(), nullptr);
    EXPECT_NE(a.cast<Mother>(), nullptr);
    EXPECT_NE(a.cast<Father>(), nullptr);
    EXPECT_NE(a.cast<Grandpa>(), nullptr);
    EXPECT_NE(a.cast<Grandma>(), nullptr);

    EXPECT_EQ(a.cast<Child>()->mid, 1007);
    EXPECT_EQ(a.cast<Father>()->c_1, 1006);
    EXPECT_EQ(a.cast<Mother>()->b_3, 1005);
    EXPECT_EQ(a.cast<Mother>()->b_2, 1004);
    EXPECT_EQ(a.cast<Mother>()->b_1, 1003);
    EXPECT_EQ(a.cast<Mother>()->a_1, 1001);
    EXPECT_EQ(a.cast<Mother>()->a_2, 1002);
    EXPECT_EQ(a.cast<Father>()->a_1, 1001);
    EXPECT_EQ(a.cast<Father>()->a_2, 1002);
    EXPECT_EQ(a.cast<Grandpa>()->a_2, 1002);
    EXPECT_EQ(a.cast<Grandpa>()->a_1, 1001);
    EXPECT_EQ(a.cast<Grandma>()->d, 1997);

    a.cast<Grandpa>()->a_1 = 1337;
    a.cast<Grandpa>()->a_2 = 1338;

    EXPECT_EQ(a.cast<Mother>()->a_1, 1337);
    EXPECT_EQ(a.cast<Mother>()->a_2, 1338);
    EXPECT_EQ(a.cast<Father>()->a_1, 1001); // Because Father and Mother have different Grandpa
    EXPECT_EQ(a.cast<Father>()->a_2, 1002); // Because Father and Mother have different Grandpa
    EXPECT_EQ(a.cast<Grandpa>()->a_1, 1337);
    EXPECT_EQ(a.cast<Grandpa>()->a_2, 1338);

    EXPECT_FALSE(a.get_type()->is_base_of<Child>().first);
    EXPECT_FALSE(a.get_type()->is_base_of<Mother>().first);
    EXPECT_FALSE(a.get_type()->is_base_of<Father>().first);
    EXPECT_FALSE(a.get_type()->is_base_of<Grandpa>().first);

    EXPECT_FALSE(a.get_type()->is_inherited_from<Child>().first);
    EXPECT_TRUE(a.get_type()->is_inherited_from<Mother>().first);
    EXPECT_TRUE(a.get_type()->is_inherited_from<Father>().first);
    EXPECT_TRUE(a.get_type()->is_inherited_from<Grandpa>().first);
}

TEST(any, create_from_type) {
    using namespace kw;

    struct big {
        int64 a = 15;
        int64 b = 16;
    };
    struct small {
        int16 a = 15;
        int16 b = 16;
    };

    const Type* type1 = Type::of<big>();
    const Type* type2 = Type::of<small>();

    Any a(type1);
    Any b(type2);

    EXPECT_NE(a.cast<big>(), nullptr);
    EXPECT_EQ(a.cast<big>()->a, 15);
    EXPECT_EQ(a.cast<big>()->b, 16);

    EXPECT_NE(b.cast<small>(), nullptr);
    EXPECT_EQ(b.cast<small>()->a, 15);
    EXPECT_EQ(b.cast<small>()->b, 16);
}

TEST(any, move_constructor) {
    using namespace kw;

    Any a(1000);
    Any b(std::move(a));

    EXPECT_TRUE(a.get_type()->is_same<void>());

    EXPECT_TRUE(b.get_type()->is_same<int32>());
    EXPECT_EQ(*b.cast<int32>(), 1000);
}

TEST(any, sort) {
    using namespace kw;

    Vector<Any> vv;
    for (int32 i = 9; i >= 0; i--) {
        vv.push_back(Any(i));
    }
    for (int32 i = 0; i < 10; i++) {
        EXPECT_TRUE(vv[i].get_type()->is_same<int32>());
        EXPECT_EQ(*vv[i].cast<int32>(), 9 - i);
    }
    eastl::sort(vv.begin(), vv.end());
    for (int32 i = 0; i < 10; i++) {
        EXPECT_EQ(*vv[i].cast<int32>(), i);
    }
}

TEST(any, map) {
    using namespace kw;

    Map<Any, Any> mm;
    for (int32 i = 9; i >= 0; i--) {
        mm.insert(make_pair(Any(i), Any(9 - i)));
    }
    int32 c = 0;
    for (auto& it : mm) {
        EXPECT_TRUE(it.first.get_type()->is_same<int32>());
        EXPECT_EQ(*it.first.cast<int32>(), c++);
    }
}

TEST(any, hash_map) {
    using namespace kw;

    HashMap<Any, Any> mm;
    for (int32 i = 9; i >= 0; i--) {
        mm.insert(make_pair(Any(i), Any(9 - i)));
    }
    int32 result = 0;
    for (auto& it : mm) {
        EXPECT_TRUE(it.first.get_type()->is_same<int32>());
        result |= 1 << *it.first.cast<int32>();
    }
    EXPECT_EQ(result, 1023);
}
