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

#include <kw/base/signal.h>

#include <gmock/gmock.h>

struct SignalTest {
    void method(kw::int32& value) {
        data = value + 136;
    }

    void const_method(kw::int32& value) const {
        value = data + 337;
    }

    kw::int32 data = 0;
};

TEST(signal, connect) {
    kw::int32 result = 0;
    SignalTest test;
    kw::Signal<void(kw::int32 & value)> my_signal;
    my_signal.connect([&result](kw::int32& value) { result = 48; });
    my_signal.connect(&test, [](kw::int32& value) { value *= 18; });
    my_signal.connect(&test, &SignalTest::method);
    my_signal.connect(const_cast<const SignalTest*>(&test), &SignalTest::const_method);
    my_signal.emit(result);

    EXPECT_EQ(result, 1337);
}

TEST(signal, void_callback_order) {
    kw::int32 test = 1;
    kw::Signal<void()> my_signal;
    my_signal.connect([&test]() { test *= test + 5; });
    my_signal.connect([&test]() { test *= test + 10; });
    my_signal.connect([&test]() { test *= test + 20; });
    my_signal.emit();

    EXPECT_EQ(test, 11136);
}

TEST(signal, non_void_callback_order) {
    kw::Signal<kw::int32()> my_signal;
    my_signal.connect([]() { return 1; });
    my_signal.connect([]() { return 3; });
    my_signal.connect([]() { return 5; });
    kw::int32 test = my_signal.emit([](kw::int32 a, kw::int32 b) { return b << a; });

    EXPECT_EQ(test, 320);
}

TEST(signal, disconnect_by_token) {
    kw::int32 test = 0;
    kw::Signal<void()> my_signal;
    kw::uint32 token1 = my_signal.connect([&test]() { test += 1; });
    kw::uint32 token2 = my_signal.connect([&test]() { test += 2; });
    my_signal.emit();

    EXPECT_EQ(test, 3);

    my_signal.disconnect(token1);
    my_signal.emit();

    EXPECT_EQ(test, 5);

    my_signal.disconnect(token2);
    my_signal.emit();

    EXPECT_EQ(test, 5);
}

TEST(signal, disconnect_by_object) {
    kw::int32 test = 0;
    kw::int32 object_a, object_b;
    kw::Signal<void()> my_signal;
    my_signal.connect(&object_a, [&test]() { test += 1; });
    my_signal.connect(&object_b, [&test]() { test += 2; });
    my_signal.emit();

    EXPECT_EQ(test, 3);

    my_signal.disconnect(&object_a);
    my_signal.emit();

    EXPECT_EQ(test, 5);

    my_signal.disconnect(&object_b);
    my_signal.emit();

    EXPECT_EQ(test, 5);
}

// TODO: look at signal test in BZ
