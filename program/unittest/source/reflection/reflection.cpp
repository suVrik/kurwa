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

#include <kw/reflection/reflection.h>

#include <gmock/gmock.h>

#include <cstddef>

namespace reflection_test_details {
template <typename T>
void no_fields_no_meta() {
    using namespace kw;

    Reflection::add<T>();

    const Reflection* reflection = Reflection::of<T>();

    EXPECT_NE(reflection, nullptr);

    EXPECT_TRUE(reflection->get_type()->is_same<T>());
}

template <typename T>
void fields_meta_get_part(const kw::Reflection* reflection, int offset = 0) {
    using namespace kw;

    EXPECT_NE(reflection, nullptr);

    T object{};
    Any any_object = object;

    T* check_correct_any = any_object.cast<T>();
    EXPECT_NE(check_correct_any, nullptr);
    EXPECT_EQ(check_correct_any->a, 10);
    EXPECT_EQ(check_correct_any->b, 20);

    {
        const Reflection::Field* field_a = reflection->get_field(FastName("a"));
        EXPECT_NE(field_a, nullptr);

        EXPECT_TRUE(field_a->is_same<int32>());
        EXPECT_EQ(field_a->get_name(), FastName("a"));

        Any any_a1 = field_a->get<T>(object);
        EXPECT_TRUE(any_a1.is_same<int32*>());
        int32** any_a1_value = any_a1.cast<int32*>();
        EXPECT_NE(any_a1_value, nullptr);
        EXPECT_EQ(**any_a1_value, 10);

        Any any_a2 = field_a->get(any_object);
        EXPECT_TRUE(any_a1.is_same<int32*>());
        int32** any_a2_value = any_a1.cast<int32*>();
        EXPECT_NE(any_a2_value, nullptr);
        EXPECT_EQ(**any_a2_value, 10);

        {
            const Reflection::Meta* meta_a = field_a->get_meta(FastName("c"));
            EXPECT_NE(meta_a, nullptr);

            EXPECT_EQ(meta_a->get_name(), FastName("c"));
            const Any& meta_a_value = meta_a->get_value();
            EXPECT_TRUE(meta_a_value.is_same<int32>());
            EXPECT_EQ(*meta_a_value.cast<int32>(), 300);

            const Reflection::Meta* meta_b = field_a->get_meta(FastName("d"));
            EXPECT_NE(meta_b, nullptr);

            EXPECT_EQ(meta_b->get_name(), FastName("d"));
            const Any& meta_b_value = meta_b->get_value();
            EXPECT_TRUE(meta_b_value.is_same<int32>());
            EXPECT_EQ(*meta_b_value.cast<int32>(), 400);

            const Reflection::Meta* meta_c = field_a->get_meta(FastName("a"));
            EXPECT_EQ(meta_c, nullptr);

            {
                bool a_found = false;
                bool b_found = false;
                for (const Reflection::Meta* meta : field_a->get_meta()) {
                    a_found = a_found || meta == meta_a;
                    b_found = b_found || meta == meta_b;
                }

                EXPECT_TRUE(a_found && b_found);
            }
        }

        const Reflection::Field* field_b = reflection->get_field(FastName("b"));
        EXPECT_NE(field_b, nullptr);

        EXPECT_TRUE(field_b->is_same<int32>());
        EXPECT_EQ(field_b->get_name(), FastName("b"));

        Any any_b1 = field_b->get<T>(object);
        EXPECT_TRUE(any_b1.is_same<int32*>());
        int32** any_b1_value = any_b1.cast<int32*>();
        EXPECT_NE(any_b1_value, nullptr);
        EXPECT_EQ(**any_b1_value, 20);

        Any any_b2 = field_b->get(any_object);
        EXPECT_TRUE(any_b1.is_same<int32*>());
        int32** any_b2_value = any_b1.cast<int32*>();
        EXPECT_NE(any_b2_value, nullptr);
        EXPECT_EQ(**any_b2_value, 20);

        {
            const Reflection::Meta* meta_a = field_b->get_meta(FastName("c"));
            EXPECT_NE(meta_a, nullptr);

            EXPECT_EQ(meta_a->get_name(), FastName("c"));
            const Any& meta_a_value = meta_a->get_value();
            EXPECT_TRUE(meta_a_value.is_same<int32>());
            EXPECT_EQ(*meta_a_value.cast<int32>(), 500);

            const Reflection::Meta* meta_b = field_b->get_meta(FastName("d"));
            EXPECT_NE(meta_b, nullptr);

            EXPECT_EQ(meta_b->get_name(), FastName("d"));
            const Any& meta_b_value = meta_b->get_value();
            EXPECT_TRUE(meta_b_value.is_same<int32>());
            EXPECT_EQ(*meta_b_value.cast<int32>(), 600);

            const Reflection::Meta* meta_c = field_b->get_meta(FastName("a"));
            EXPECT_EQ(meta_c, nullptr);

            {
                bool a_found = false;
                bool b_found = false;
                for (const Reflection::Meta* meta : field_b->get_meta()) {
                    a_found = a_found || meta == meta_a;
                    b_found = b_found || meta == meta_b;
                }

                EXPECT_TRUE(a_found && b_found);
            }
        }

        const Reflection::Field* field_c = reflection->get_field(FastName("c"));
        EXPECT_EQ(field_c, nullptr);

        EXPECT_EQ(reflection->get_fields().size(), 2);

        {
            bool a_found = false;
            bool b_found = false;
            for (const Reflection::Field* field : reflection->get_fields()) {
                a_found = a_found || field == field_a;
                b_found = b_found || field == field_b;
            }

            EXPECT_TRUE(a_found && b_found);
        }
    }

    {
        const Reflection::Method* method_ohmy = reflection->get_method(FastName("ohmy"));
        EXPECT_NE(method_ohmy, nullptr);

        EXPECT_EQ(method_ohmy->get_name(), FastName("ohmy"));

        Any result = (*method_ohmy)(object, 10, 20);
        EXPECT_TRUE(result.is_same<int32>());
        EXPECT_EQ(*result.cast<int32>(), 30 + offset);

        result = (*method_ohmy)(any_object, 10, 20);
        EXPECT_TRUE(result.is_same<int32>());
        EXPECT_EQ(*result.cast<int32>(), 30 + offset);

        const Reflection::Meta* meta_a = method_ohmy->get_meta(FastName("c"));
        EXPECT_NE(meta_a, nullptr);

        EXPECT_EQ(meta_a->get_name(), FastName("c"));
        const Any& meta_a_value = meta_a->get_value();
        EXPECT_TRUE(meta_a_value.is_same<int32>());
        EXPECT_EQ(*meta_a_value.cast<int32>(), 700);

        const Reflection::Meta* meta_b = method_ohmy->get_meta(FastName("d"));
        EXPECT_NE(meta_b, nullptr);

        EXPECT_EQ(meta_b->get_name(), FastName("d"));
        const Any& meta_b_value = meta_b->get_value();
        EXPECT_TRUE(meta_b_value.is_same<int32>());
        EXPECT_EQ(*meta_b_value.cast<int32>(), 800);

        const Reflection::Meta* meta_c = method_ohmy->get_meta(FastName("a"));
        EXPECT_EQ(meta_c, nullptr);

        {
            bool a_found = false;
            bool b_found = false;
            for (const Reflection::Meta* meta : method_ohmy->get_meta()) {
                a_found = a_found || meta == meta_a;
                b_found = b_found || meta == meta_b;
            }

            EXPECT_TRUE(a_found && b_found);
        }
    }

    {
        const Reflection::Meta* meta_a = reflection->get_meta(FastName("c"));
        EXPECT_NE(meta_a, nullptr);

        EXPECT_EQ(meta_a->get_name(), FastName("c"));
        const Any& meta_a_value = meta_a->get_value();
        EXPECT_TRUE(meta_a_value.is_same<int32>());
        EXPECT_EQ(*meta_a_value.cast<int32>(), 100);

        const Reflection::Meta* meta_b = reflection->get_meta(FastName("d"));
        EXPECT_NE(meta_b, nullptr);

        EXPECT_EQ(meta_b->get_name(), FastName("d"));
        const Any& meta_b_value = meta_b->get_value();
        EXPECT_TRUE(meta_b_value.is_same<int32>());
        EXPECT_EQ(*meta_b_value.cast<int32>(), 200);

        const Reflection::Meta* meta_c = reflection->get_meta(FastName("a"));
        EXPECT_EQ(meta_c, nullptr);

        {
            bool a_found = false;
            bool b_found = false;
            for (const Reflection::Meta* meta : reflection->get_meta()) {
                a_found = a_found || meta == meta_a;
                b_found = b_found || meta == meta_b;
            }

            EXPECT_TRUE(a_found && b_found);
        }
    }

    EXPECT_TRUE(reflection->get_type()->is_same<T>());
}

template <typename T>
void fields_meta() {
    using namespace kw;

    FastName meta_a("c");
    FastName meta_b("d");

    // Separate reflection adding and using to imitate different scopes
    {
        Reflection* reflection = Reflection::add<T>();
        EXPECT_NE(reflection, nullptr);
        reflection->add_meta(meta_a, 100);
        reflection->add_meta(meta_b, 200);

        Reflection::Field* field_a = reflection->add_field<int32>(FastName("a"), offsetof(T, a));
        EXPECT_NE(field_a, nullptr);
        field_a->add_meta(meta_a, 300);
        field_a->add_meta(meta_b, 400);

        Reflection::Field* field_b = reflection->add_field<int32>(FastName("b"), offsetof(T, b));
        EXPECT_NE(field_b, nullptr);
        field_b->add_meta(meta_a, 500);
        field_b->add_meta(meta_b, 600);

        Reflection::Method* method_ohmy = reflection->add_method(FastName("ohmy"), &T::ohmy);
        EXPECT_NE(method_ohmy, nullptr);
        method_ohmy->add_meta(meta_a, 700);
        method_ohmy->add_meta(meta_b, 800);
    }

    {
        Any any_t = T();

        fields_meta_get_part<T>(Reflection::of<T>());
        fields_meta_get_part<T>(Reflection::of(Type::of<T>()));
        fields_meta_get_part<T>(Reflection::of(any_t));
    }
}
} // namespace reflection_test_details

// Test for basic types without fields and meta
TEST(reflection, no_fields_no_meta) {
    using namespace kw;

    reflection_test_details::no_fields_no_meta<void>();
    reflection_test_details::no_fields_no_meta<bool>();
    reflection_test_details::no_fields_no_meta<int8>();
    reflection_test_details::no_fields_no_meta<int16>();
    reflection_test_details::no_fields_no_meta<int32>();
    reflection_test_details::no_fields_no_meta<int64>();
    reflection_test_details::no_fields_no_meta<void*>();
    reflection_test_details::no_fields_no_meta<bool*>();
    reflection_test_details::no_fields_no_meta<int8*>();
    reflection_test_details::no_fields_no_meta<int16*>();
    reflection_test_details::no_fields_no_meta<int32*>();
    reflection_test_details::no_fields_no_meta<int64*>();
    reflection_test_details::no_fields_no_meta<void**>();
    reflection_test_details::no_fields_no_meta<bool**>();
    reflection_test_details::no_fields_no_meta<int8**>();
    reflection_test_details::no_fields_no_meta<int16**>();
    reflection_test_details::no_fields_no_meta<int32**>();
    reflection_test_details::no_fields_no_meta<int64**>();
    // These must be equal to their non-reference bothers.
    // References are not supported.
    reflection_test_details::no_fields_no_meta<bool&>();
    reflection_test_details::no_fields_no_meta<int8&>();
    reflection_test_details::no_fields_no_meta<int16&>();
    reflection_test_details::no_fields_no_meta<int32&>();
    reflection_test_details::no_fields_no_meta<int64&>();
}

TEST(reflection, fields_meta) {
    using namespace kw;
    using namespace reflection_test_details;

    // Must use SOO
    struct MyClass {
        int32 a = 10;
        int32 b = 20;

        virtual int32 ohmy(int32 d, int32 e) {
            return d + e;
        }
    };

    // Must use separate pointer
    struct MyBigClass {
        int32 a = 10;
        int32 b = 20;
        int32 c = 30;
        int32 d = 40;

        virtual int32 ohmy(int32 d, int32 e) {
            return d + e;
        }
    };

    struct MyFatherClass {
        int32 c;
        int32 d;
    };

    struct MyInheritanceClass : MyFatherClass {
        int32 a = 10;
        int32 b = 20;

        virtual int32 ohmy(int32 d, int32 e) {
            return d + e;
        }
    };

    Type::register_parents<MyInheritanceClass, MyFatherClass>();

    struct MyMotherClass {
        int32 e;
        int32 f;
    };

    struct MyMultipleInheritanceClass : MyFatherClass, MyMotherClass {
        int32 a = 10;
        int32 b = 20;

        virtual int32 ohmy(int32 d, int32 e) {
            return d + e;
        }
    };

    Type::register_parents<MyMultipleInheritanceClass, MyFatherClass, MyMotherClass>();

    fields_meta<MyClass>();
    fields_meta<MyBigClass>();
    fields_meta<MyInheritanceClass>();
    fields_meta<MyMultipleInheritanceClass>();

    struct WeirdInheritance : MyMultipleInheritanceClass {
        int32 ohmy(int32 d, int32 e) override {
            return d + e + 10;
        }
    };

    Type::register_parents<WeirdInheritance, MyMultipleInheritanceClass>();
    Reflection::add<WeirdInheritance>();

    {
        Any any_t = WeirdInheritance();

        fields_meta_get_part<WeirdInheritance>(Reflection::of<WeirdInheritance>(), 10);
        fields_meta_get_part<WeirdInheritance>(Reflection::of(Type::of<WeirdInheritance>()), 10);
        fields_meta_get_part<WeirdInheritance>(Reflection::of(any_t), 10);
    }
}
