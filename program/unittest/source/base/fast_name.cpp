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

#include <kw/base/fast_name.h>
#include <kw/base/types.h>

#include <gmock/gmock.h>

TEST(fast_name, basic) {
    using namespace kw;

    FastName a;
    FastName b;

    EXPECT_EQ(a, b);

    FastName c("lol");
    FastName d("lol");

    EXPECT_EQ(c, d);

    c = FastName("abc");
    d = FastName("def");

    EXPECT_NE(c, d);

    FastName e("mark", 4);
    FastName f("mark", 4);

    EXPECT_EQ(e, f);
    EXPECT_LE(c, e);

    FastName g(e);

    EXPECT_EQ(e, g);

    FastName h(String("abc"));

    EXPECT_EQ(c, h);

    int32 result = 0;
    FastName loop(String("ooo"));
    for (char ch : loop) {
        result += ch;
    }
    EXPECT_EQ(result, 'o' * 3);
}
