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

#include <gmock/gmock.h>

TEST(string_view, convert_to) {
    EXPECT_EQ(kw::StringView("123").to<kw::uint8>(), 123);
    EXPECT_EQ(kw::StringView("32123").to<kw::uint16>(), 32123);
    EXPECT_EQ(kw::StringView("1234567890").to<kw::uint32>(), 1234567890);
    EXPECT_EQ(kw::StringView("1234567890987654321").to<kw::uint64>(), 1234567890987654321);

    EXPECT_EQ(kw::StringView("-123").to<kw::int8>(), -123);
    EXPECT_EQ(kw::StringView("-32123").to<kw::int16>(), -32123);
    EXPECT_EQ(kw::StringView("-1234567890").to<kw::int32>(), -1234567890);
    EXPECT_EQ(kw::StringView("-1234567890987654321").to<kw::int64>(), -1234567890987654321);

    EXPECT_FLOAT_EQ(kw::StringView("-12345.67890").to<float>(), -12345.67890f);
    EXPECT_DOUBLE_EQ(kw::StringView("-1234567890.1234567890").to<double>(), -1234567890.1234567890);
    EXPECT_DOUBLE_EQ(kw::StringView("-1234567890.1234567890").to<long double>(), -1234567890.1234567890);

    EXPECT_EQ(kw::StringView("true").to<bool>(), true);
    EXPECT_EQ(kw::StringView("false").to<bool>(), false);
    EXPECT_EQ(kw::StringView("anything but 'true'").to<bool>(), false);
}

// Split StringView test is done in String test
