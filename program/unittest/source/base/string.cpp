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

#include <kw/base/string.h>
#include <kw/base/string_view.h>
#include <kw/base/types.h>
#include <kw/base/vector.h>

#include <kw/utilities/trace.h>

#include <gmock/gmock.h>

TEST(string, convert_to) {
    EXPECT_EQ(kw::String("123").to<kw::uint8>(), 123);
    EXPECT_EQ(kw::String("32123").to<kw::uint16>(), 32123);
    EXPECT_EQ(kw::String("1234567890").to<kw::uint32>(), 1234567890);
    EXPECT_EQ(kw::String("1234567890987654321").to<kw::uint64>(), 1234567890987654321);

    EXPECT_EQ(kw::String("-123").to<kw::int8>(), -123);
    EXPECT_EQ(kw::String("-32123").to<kw::int16>(), -32123);
    EXPECT_EQ(kw::String("-1234567890").to<kw::int32>(), -1234567890);
    EXPECT_EQ(kw::String("-1234567890987654321").to<kw::int64>(), -1234567890987654321);

    EXPECT_EQ(kw::String("-12345.67890").to<float>(), -12345.67890f);
    EXPECT_EQ(kw::String("-1234567890.1234567890").to<double>(), -1234567890.1234567890);
    EXPECT_EQ(kw::String("-1234567890.1234567890").to<long double>(), -1234567890.1234567890);

    EXPECT_EQ(kw::String("true").to<bool>(), true);
    EXPECT_EQ(kw::String("false").to<bool>(), false);
    EXPECT_EQ(kw::String("anything but 'true'").to<bool>(), false);
}

TEST(string, convert_from) {
    // Even tho here, in this test, for 'from' template function I provide a template parameter, it is not required.
    // You can use it like this: String::from(123) or String::from(true) and so on.

    EXPECT_EQ(kw::String::from<kw::uint8>(123), kw::String("123"));
    EXPECT_EQ(kw::String::from<kw::uint16>(32123), kw::String("32123"));
    EXPECT_EQ(kw::String::from<kw::uint32>(1234567890), kw::String("1234567890"));
    EXPECT_EQ(kw::String::from<kw::uint64>(1234567890987654321), kw::String("1234567890987654321"));

    EXPECT_EQ(kw::String::from<kw::int8>(-123), kw::String("-123"));
    EXPECT_EQ(kw::String::from<kw::int16>(-32123), kw::String("-32123"));
    EXPECT_EQ(kw::String::from<kw::int32>(-1234567890), kw::String("-1234567890"));
    EXPECT_EQ(kw::String::from<kw::int64>(-1234567890987654321), kw::String("-1234567890987654321"));

    // Floating-point numbers are difficult to check, but they work. With poor precision tho.

    EXPECT_EQ(kw::String::from<bool>(true), kw::String("true"));
    EXPECT_EQ(kw::String::from<bool>(false), kw::String("false"));
}

TEST(string, split) {
    kw::String str("10;11;12;13;14;15");
    kw::Vector<kw::StringView> result = str.split(';');
    EXPECT_EQ(result.size(), 6);

    for (kw::uint32 i = 0; i < result.size(); i++) {
        EXPECT_EQ(kw::String(result[i]), kw::String::from(10 + i));
    }

    kw::String str2("0,1,2,3,4,5;1,2,3,4,5,6;2,3,4,5,6,7;3,4,5,6,7,8;4,5,6,7,8,9;5,6,7,8,9,10");
    result = str2.split(';');
    EXPECT_EQ(result.size(), 6);

    for (kw::uint32 i = 0; i < result.size(); i++) {
        kw::Vector<kw::StringView> result2 = result[i].split(',');
        EXPECT_EQ(result2.size(), 6);

        for (kw::uint32 j = 0; j < result2.size(); j++) {
            EXPECT_EQ(kw::String(result2[j]), kw::String::from(i + j));
        }
    }

    kw::String str3("1;2;");
    result = str3.split(';');
    EXPECT_EQ(result.size(), 3);
}
