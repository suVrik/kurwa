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

/**
 * This test case is written to check if all thirdparty libraries linked successfully.
 */

#include <GL/glew.h>
#include <cstring>
#include <enet/enet.h>
#include <fmt/format.h>
#include <gmock/gmock.h>
#include <imgui.h>
#include <kw/base/vector.h>
#include <lz4.h>

GTEST_TEST(LibraryTest, eastl) {
    kw::Vector<int> u;

    // kw::Vector does not allocate memory until it's really needed
    ASSERT_TRUE(u.data() == nullptr);

    u.push_back(1337);
    ASSERT_TRUE(u.data() != nullptr);

    kw::Vector<int> v = std::move(u);
    ASSERT_TRUE(u.data() == nullptr);
    ASSERT_TRUE(v.data() != nullptr);
}

GTEST_TEST(LibraryTest, enet) {
    ASSERT_TRUE(enet_linked_version() == ENET_VERSION);
}

GTEST_TEST(LibraryTest, fmt) {
    ASSERT_TRUE(fmt::format("{0}{1}{0}", "abra", "cad") == "abracadabra");
}

GTEST_TEST(LibraryTest, glew) {
    // TODO: later unittest must run in a window and this function must work
    ASSERT_TRUE(glewInit() != GLEW_OK);
}

GTEST_TEST(LibraryTest, imgui) {
    ASSERT_TRUE(std::strcmp(ImGui::GetVersion(), IMGUI_VERSION) == 0);
}

GTEST_TEST(LibraryTest, lz4) {
    ASSERT_TRUE(LZ4_versionNumber() == LZ4_VERSION_NUMBER);
}
