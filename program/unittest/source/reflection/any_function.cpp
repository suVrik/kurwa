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

#include <kw/reflection/any_function.h>

#include <gmock/gmock.h>

#define GENERATE_NUMERIC_METHOD(num, return_type, type_a, type_b, type_c) \
    return_type method##num(type_a a, type_b b, type_c c) { \
        return static_cast<return_type>(a + b + c); \
    }

#define GENERATE_POINTER_METHOD(num, return_type, type_a, type_b, type_c) \
    return_type* method##num(type_a* a, type_b* b, type_c* c) { \
        value_##return_type = static_cast<return_type>(*a + *b + *c); \
        return &value_##return_type; \
    }

#define GENERATE_REFERENCE_METHOD(num, return_type, type_a, type_b, type_c) \
    return_type& method##num(const type_a& a, const type_b& b, const type_c& c) { \
        value_##return_type = static_cast<return_type>(a + b + c); \
        return value_##return_type; \
    }

#define GENERATE_CONST_METHOD(num, return_type, type_a, type_b, type_c) \
    return_type method##num(type_a a, type_b b, type_c c) const { \
        return static_cast<return_type>(a + b + c); \
    }

#define GENERATE_VOID_METHOD(num, type_a, type_b, type_c) \
    void method##num(const type_a& a, const type_b& b, const type_c& c) { \
        value_##type_a = static_cast<type_a>(a + b + c); \
    }

#define GENERATE_NO_ARGUMENTS_METHOD(num, return_type) \
    return_type method##num() { \
        return value_##return_type; \
    }

#define GENERATE_VIRTUAL_METHOD(num, return_type) \
    virtual return_type method##num() { \
        return num; \
    }

#define CHECK_RESULT(any_value, required_type, required_result) \
    { \
        Any result = any_value; \
        EXPECT_TRUE(result.is_same<required_type>()); \
        EXPECT_EQ(*result.template cast<required_type>(), required_result); \
    }

#define CHECK_POINTER_RESULT(any_value, required_type, required_result) \
    { \
        Any result = any_value; \
        EXPECT_TRUE(result.is_same<required_type*>()); \
        EXPECT_EQ(**result.template cast<required_type*>(), required_result); \
    }

#define CHECK_VOID_RESULT(any_value, variable_type, required_result) \
    { \
        any_value; \
        EXPECT_EQ(object.template cast<Type>()->variable_type, required_result); \
    }

namespace any_function_test_details {
using namespace kw;

uint32 copy_counter = 0;
uint32 move_counter = 0;

struct MoveStruct {
    MoveStruct() = default;

    MoveStruct(MoveStruct&& original) noexcept
        : secret_key(original.secret_key) {
        move_counter++;
    }

    MoveStruct(const MoveStruct& original)
        : secret_key(original.secret_key) {
        copy_counter++;
    }

    MoveStruct& operator=(MoveStruct&& original) noexcept {
        secret_key = original.secret_key;
        move_counter++;
        return *this;
    }

    MoveStruct& operator=(const MoveStruct& original) {
        secret_key = original.secret_key;
        copy_counter++;
        return *this;
    }

    int32 secret_key = 0;
};

struct MyStruct {
    virtual ~MyStruct() = default;

    GENERATE_NUMERIC_METHOD(1, int8, int16, int32, int64);
    GENERATE_NUMERIC_METHOD(2, int16, int32, int64, int8);
    GENERATE_NUMERIC_METHOD(3, int32, int64, int8, int16);
    GENERATE_NUMERIC_METHOD(4, int64, int8, int16, int32);
    GENERATE_POINTER_METHOD(5, int8, int16, int32, int64);
    GENERATE_POINTER_METHOD(6, int16, int32, int64, int8);
    GENERATE_POINTER_METHOD(7, int32, int64, int8, int16);
    GENERATE_POINTER_METHOD(8, int64, int8, int16, int32);
    GENERATE_REFERENCE_METHOD(9, int8, int16, int32, int64);
    GENERATE_REFERENCE_METHOD(10, int16, int32, int64, int8);
    GENERATE_REFERENCE_METHOD(11, int32, int64, int8, int16);
    GENERATE_REFERENCE_METHOD(12, int64, int8, int16, int32);
    GENERATE_CONST_METHOD(13, int8, int16, int32, int64);
    GENERATE_CONST_METHOD(14, int16, int32, int64, int8);
    GENERATE_CONST_METHOD(15, int32, int64, int8, int16);
    GENERATE_CONST_METHOD(16, int64, int8, int16, int32);
    GENERATE_VOID_METHOD(17, int8, int16, int32);
    GENERATE_VOID_METHOD(18, int16, int32, int64);
    GENERATE_VOID_METHOD(19, int32, int64, int8);
    GENERATE_VOID_METHOD(20, int64, int8, int16);
    GENERATE_NO_ARGUMENTS_METHOD(21, int8);
    GENERATE_NO_ARGUMENTS_METHOD(22, int16);
    GENERATE_NO_ARGUMENTS_METHOD(23, int32);
    GENERATE_NO_ARGUMENTS_METHOD(24, int64);

    String method25(const String& a, const String& b) const {
        return a + b;
    }

    Vector<uint32> method26(const Vector<uint32>& a, const Vector<uint32>& b) const {
        Vector<uint32> result = a;
        result.insert(result.end(), b.begin(), b.end());
        return result;
    }

    String method27(String a, String b) const {
        return a + b;
    }

    Vector<uint32> method28(Vector<uint32> a, Vector<uint32> b) const {
        Vector<uint32> result = a;
        result.insert(result.end(), b.begin(), b.end());
        return result;
    }

    GENERATE_VIRTUAL_METHOD(29, int8);
    GENERATE_VIRTUAL_METHOD(30, int16);
    GENERATE_VIRTUAL_METHOD(31, int32);
    GENERATE_VIRTUAL_METHOD(32, int64);

    MoveStruct&& method33(MoveStruct&& st) const {
        st.secret_key = 1337;
        return std::move(st);
    }

    // For convenient test
    template <typename T>
    MyStruct* cast() {
        return this;
    }

    int8 value_int8 = 0;
    int16 value_int16 = 0;
    int32 value_int32 = 0;
    int64 value_int64 = 0;
};

struct MyChildStruct : MyStruct {
    int8 method29() override {
        return 39;
    }

    int16 method30() override {
        return 40;
    }

    int32 method31() override {
        return 41;
    }

    int64 method32() override {
        return 42;
    }
};

template <typename Type, typename Container>
void test_any_function(int32 offset = 0) {
    AnyFunction any_function1(&Type::method1);
    AnyFunction any_function2(&Type::method2);
    AnyFunction any_function3(&Type::method3);
    AnyFunction any_function4(&Type::method4);
    AnyFunction any_function5(&Type::method5);
    AnyFunction any_function6(&Type::method6);
    AnyFunction any_function7(&Type::method7);
    AnyFunction any_function8(&Type::method8);
    AnyFunction any_function9(&Type::method9);
    AnyFunction any_function10(&Type::method10);
    AnyFunction any_function11(&Type::method11);
    AnyFunction any_function12(&Type::method12);
    AnyFunction any_function13(&Type::method13);
    AnyFunction any_function14(&Type::method14);
    AnyFunction any_function15(&Type::method15);
    AnyFunction any_function16(&Type::method16);
    AnyFunction any_function17(&Type::method17);
    AnyFunction any_function18(&Type::method18);
    AnyFunction any_function19(&Type::method19);
    AnyFunction any_function20(&Type::method20);
    AnyFunction any_function21(&Type::method21);
    AnyFunction any_function22(&Type::method22);
    AnyFunction any_function23(&Type::method23);
    AnyFunction any_function24(&Type::method24);
    AnyFunction any_function25(&Type::method25);
    AnyFunction any_function26(&Type::method26);
    AnyFunction any_function27(&Type::method27);
    AnyFunction any_function28(&Type::method28);
    AnyFunction any_function29(&Type::method29);
    AnyFunction any_function30(&Type::method30);
    AnyFunction any_function31(&Type::method31);
    AnyFunction any_function32(&Type::method32);
    AnyFunction any_function33(&Type::method33);

    Container object = Type();

    int8 ptr8 = 8;
    int16 ptr16 = 16;
    int32 ptr32 = 32;
    int64 ptr64 = 64;

    const int8 cptr8 = 8;
    const int16 cptr16 = 16;
    const int32 cptr32 = 32;
    const int64 cptr64 = 64;

    CHECK_RESULT(any_function1(object, static_cast<int16>(8), static_cast<int32>(16), static_cast<int64>(32)), int8, 56);
    CHECK_RESULT(any_function2(object, static_cast<int32>(8), static_cast<int64>(16), static_cast<int8>(32)), int16, 56);
    CHECK_RESULT(any_function3(object, static_cast<int64>(8), static_cast<int8>(16), static_cast<int16>(32)), int32, 56);
    CHECK_RESULT(any_function4(object, static_cast<int8>(8), static_cast<int16>(16), static_cast<int32>(32)), int64, 56);

    CHECK_POINTER_RESULT(any_function5(object, &ptr16, &ptr32, &ptr64), int8, 112);
    CHECK_POINTER_RESULT(any_function6(object, &ptr32, &ptr64, &ptr8), int16, 104);
    CHECK_POINTER_RESULT(any_function7(object, &ptr64, &ptr8, &ptr16), int32, 88);
    CHECK_POINTER_RESULT(any_function8(object, &ptr8, &ptr16, &ptr32), int64, 56);

    // The previous set of functions had changed the object
    EXPECT_EQ(object.template cast<Type>()->value_int8, 112);
    EXPECT_EQ(object.template cast<Type>()->value_int16, 104);
    EXPECT_EQ(object.template cast<Type>()->value_int32, 88);
    EXPECT_EQ(object.template cast<Type>()->value_int64, 56);
    object = Type();

    CHECK_POINTER_RESULT(any_function9(object, &cptr16, &cptr32, &cptr64), int8, 112);
    CHECK_POINTER_RESULT(any_function10(object, &cptr32, &cptr64, &cptr8), int16, 104);
    CHECK_POINTER_RESULT(any_function11(object, &cptr64, &cptr8, &cptr16), int32, 88);
    CHECK_POINTER_RESULT(any_function12(object, &cptr8, &cptr16, &cptr32), int64, 56);

    // The previous set of functions had changed the object
    EXPECT_EQ(object.template cast<Type>()->value_int8, 112);
    EXPECT_EQ(object.template cast<Type>()->value_int16, 104);
    EXPECT_EQ(object.template cast<Type>()->value_int32, 88);
    EXPECT_EQ(object.template cast<Type>()->value_int64, 56);
    object = Type();

    CHECK_RESULT(any_function13(object, static_cast<int16>(8), static_cast<int32>(16), static_cast<int64>(32)), int8, 56);
    CHECK_RESULT(any_function14(object, static_cast<int32>(8), static_cast<int64>(16), static_cast<int8>(32)), int16, 56);
    CHECK_RESULT(any_function15(object, static_cast<int64>(8), static_cast<int8>(16), static_cast<int16>(32)), int32, 56);
    CHECK_RESULT(any_function16(object, static_cast<int8>(8), static_cast<int16>(16), static_cast<int32>(32)), int64, 56);

    CHECK_VOID_RESULT(any_function17(object, &cptr8, &cptr16, &cptr32), value_int8, 56);
    CHECK_VOID_RESULT(any_function18(object, &cptr16, &cptr32, &cptr64), value_int16, 112);
    CHECK_VOID_RESULT(any_function19(object, &cptr32, &cptr64, &cptr8), value_int32, 104);
    CHECK_VOID_RESULT(any_function20(object, &cptr64, &cptr8, &cptr16), value_int64, 88);

    // The previous set of functions had changed the object, keep them for the next set of functions

    CHECK_RESULT(any_function21(object), int8, 56);
    CHECK_RESULT(any_function22(object), int16, 112);
    CHECK_RESULT(any_function23(object), int32, 104);
    CHECK_RESULT(any_function24(object), int64, 88);

    // Reset values changed by void functions
    object = Type();

    // Weird types like strings, vectors, reference strings and reference vectors
    const String hello("Hello");
    const String world(" world!");
    const Vector<uint32> veca{ 10, 20, 30 };
    const Vector<uint32> vecb{ 40, 50, 60 };

    CHECK_RESULT(any_function25(object, &hello, &world), String, String("Hello world!"));
    CHECK_RESULT(any_function26(object, &veca, &vecb), Vector<uint32>, Vector<uint32>({ 10, 20, 30, 40, 50, 60 }));
    CHECK_RESULT(any_function27(object, hello, world), String, String("Hello world!"));
    CHECK_RESULT(any_function28(object, veca, vecb), Vector<uint32>, Vector<uint32>({ 10, 20, 30, 40, 50, 60 }));

    // Virtual functions
    CHECK_RESULT(any_function29(object), int8, 29 + offset);
    CHECK_RESULT(any_function30(object), int16, 30 + offset);
    CHECK_RESULT(any_function31(object), int32, 31 + offset);
    CHECK_RESULT(any_function32(object), int64, 32 + offset);

    // RValue arguments
    MoveStruct movestruct;
    EXPECT_EQ(movestruct.secret_key, 0);
    Any movestruct_any = any_function33(object, &movestruct);
    EXPECT_TRUE(movestruct_any.is_same<MoveStruct>());
    EXPECT_EQ(movestruct_any.cast<MoveStruct>()->secret_key, 1337);
    EXPECT_GT(move_counter, 0U);
    EXPECT_EQ(copy_counter, 0U);
}
} // namespace any_function_test_details

TEST(any_function, basic) {
    using namespace any_function_test_details;

    Type::register_parents<MyChildStruct, MyStruct>();

    test_any_function<MyStruct, MyStruct>();
    test_any_function<MyChildStruct, MyChildStruct>(10);
    test_any_function<MyStruct, Any>();
    test_any_function<MyChildStruct, Any>(10);
}

#undef GENERATE_NUMERIC_METHOD
#undef GENERATE_POINTER_METHOD
#undef GENERATE_REFERENCE_METHOD
#undef GENERATE_CONST_METHOD
#undef GENERATE_VOID_METHOD
#undef GENERATE_NO_ARGUMENTS_METHOD
#undef GENERATE_VIRTUAL_METHOD
#undef CHECK_RESULT
#undef CHECK_POINTER_RESULT
#undef CHECK_VOID_RESULT
