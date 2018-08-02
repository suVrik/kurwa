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

TEST(reflection, basic) {
    using namespace kw;

    // Structure, reflection of which we're about to create
    struct MyClass {
        uint32 my_variable;
    };

    // Always cache your FastNames
    FastName field_name("my_variable");

    // Add reflection for MyClass
    Reflection* reflection = Reflection::add_reflection<MyClass>();
    reflection->add_field<uint32>(field_name, 0);

    // Create Any with MyClass inside
    MyClass my_class = { 1337 };
    Any my_class_any(my_class);

    // Get reflection of the field from reflection of the object and use that reflection
    // to get a reference to actual field from actual object.
    const Reflection::Field* field = reflection->get_field(field_name);
    Any my_variable = field->get(my_class);

    // 'my_variable' is a pointer to field actually stored in 'my_class_any'.
    EXPECT_TRUE(my_variable.get_type()->is_pointer());

    //    // Verify variable type and value
    //    EXPECT_TRUE(my_variable.get_type()->remove_pointer()->is_same<uint32>());
    //    EXPECT_EQ(**my_variable.cast<uint32*>(), 1337);
}