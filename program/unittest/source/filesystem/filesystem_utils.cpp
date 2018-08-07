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

#include <kw/filesystem/filesystem_utils.h>

#include <gmock/gmock.h>

#include <fstream>

TEST(filesystem, get_path) {
    EXPECT_FALSE(kw::FilesystemUtils::get_executable_path().empty());
    EXPECT_FALSE(kw::FilesystemUtils::get_resource_path().empty());
    EXPECT_FALSE(kw::FilesystemUtils::get_save_path().empty());
}

TEST(filesystem, is_absolute) {
#if defined(KW_WINDOWS)
    EXPECT_TRUE(kw::FilesystemUtils::is_absolute("C:\\work"));
    EXPECT_TRUE(kw::FilesystemUtils::is_absolute("D:\\Program Files\\Game"));
    EXPECT_TRUE(kw::FilesystemUtils::is_absolute("D:\\"));

    EXPECT_FALSE(kw::FilesystemUtils::is_absolute(".\\work2"));
    EXPECT_FALSE(kw::FilesystemUtils::is_absolute("Game"));
    EXPECT_FALSE(kw::FilesystemUtils::is_absolute("MyFolder\\my_file.png"));
#else
    EXPECT_TRUE(kw::FilesystemUtils::is_absolute("/usr/bin"));
    EXPECT_TRUE(kw::FilesystemUtils::is_absolute("/hello/world"));
    EXPECT_TRUE(kw::FilesystemUtils::is_absolute("/"));

    EXPECT_FALSE(kw::FilesystemUtils::is_absolute("hi"));
    EXPECT_FALSE(kw::FilesystemUtils::is_absolute("how"));
    EXPECT_FALSE(kw::FilesystemUtils::is_absolute("are/you"));
#endif
}

TEST(filesystem, join_resolve) {
#if defined(KW_WINDOWS)
    EXPECT_EQ(kw::FilesystemUtils::join("C:\\work", "kurwa"), "C:\\work\\kurwa");
    EXPECT_EQ(kw::FilesystemUtils::join("C:\\work", "D:\\Program Files\\Game\\"),
              "C:\\work\\D:\\Program Files\\Game\\");
    EXPECT_EQ(kw::FilesystemUtils::join("D:\\", "E:\\"), "D:\\E:\\");
    EXPECT_EQ(kw::FilesystemUtils::join("D:\\", "foo\\boo"), "D:\\foo\\boo");

    EXPECT_EQ(kw::FilesystemUtils::resolve("C:\\work", "kurwa"), "C:\\work\\kurwa");
    EXPECT_EQ(kw::FilesystemUtils::resolve("C:\\work", "D:\\Program Files\\Game\\"), "D:\\Program Files\\Game\\");
    EXPECT_EQ(kw::FilesystemUtils::resolve("D:\\", "E:\\"), "E:\\");
    EXPECT_EQ(kw::FilesystemUtils::resolve("D:\\", "foo\\boo"), "D:\\foo\\boo");
#else
    EXPECT_EQ(kw::FilesystemUtils::join("/work", "kurwa"), "/work/kurwa/");
    EXPECT_EQ(kw::FilesystemUtils::join("/work", "/Program Files/Game/"), "/work/Program Files/Game/");
    EXPECT_EQ(kw::FilesystemUtils::join("work", "/"), "work/");
    EXPECT_EQ(kw::FilesystemUtils::join("doo", "foo/boo"), "doo/foo/boo/");

    EXPECT_EQ(kw::FilesystemUtils::resolve("/work", "kurwa"), "/work/kurwa/");
    EXPECT_EQ(kw::FilesystemUtils::resolve("/work", "/Program Files/Game/"), "/Program Files/Game/");
    EXPECT_EQ(kw::FilesystemUtils::resolve("/", "/"), "/");
    EXPECT_EQ(kw::FilesystemUtils::resolve("/", "foo/boo"), "/foo/boo/");
#endif
}

TEST(filesystem, get_filename) {
#if defined(KW_WINDOWS)
    EXPECT_EQ(kw::FilesystemUtils::get_filename("C:\\work"), "work");
    EXPECT_EQ(kw::FilesystemUtils::get_filename("C:\\work\\kurwa\\"), "kurwa");
    EXPECT_EQ(kw::FilesystemUtils::get_filename("C:\\work\\kurwa.h"), "kurwa.h");
    EXPECT_EQ(kw::FilesystemUtils::get_filename("C:\\work\\hello.world.exe"), "hello.world.exe");

    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("C:\\work"), "work");
    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("C:\\work\\kurwa\\"), "kurwa");
    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("C:\\work\\kurwa.h"), "kurwa");
    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("C:\\work\\hello.world.exe"), "hello");
#else
    EXPECT_EQ(kw::FilesystemUtils::get_filename("/work"), "work");
    EXPECT_EQ(kw::FilesystemUtils::get_filename("/work/kurwa/"), "kurwa");
    EXPECT_EQ(kw::FilesystemUtils::get_filename("/work/kurwa.h"), "kurwa.h");
    EXPECT_EQ(kw::FilesystemUtils::get_filename("/work/hello.world.exe"), "hello.world.exe");

    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("/work"), "work");
    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("/work/kurwa/"), "kurwa");
    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("/work/kurwa.h"), "kurwa");
    EXPECT_EQ(kw::FilesystemUtils::get_base_filename("/work/hello.world.exe"), "hello");
#endif
}

TEST(filesystem, create_directory) {
    using namespace kw;

    const String save_path = FilesystemUtils::get_save_path();
    const String my_directory = FilesystemUtils::resolve(save_path, "my_directory");
    const String fake_directory = FilesystemUtils::resolve(save_path, "fake_directory");

    if (FilesystemUtils::exists(my_directory)) {
        EXPECT_TRUE(FilesystemUtils::remove_directory_recursive(my_directory));
    }

    EXPECT_TRUE(FilesystemUtils::create_directory(my_directory));
    EXPECT_TRUE(FilesystemUtils::is_directory(my_directory));
    EXPECT_FALSE(FilesystemUtils::is_directory(fake_directory));
    EXPECT_TRUE(FilesystemUtils::exists(my_directory));
    EXPECT_FALSE(FilesystemUtils::exists(fake_directory));

    const String my_file_a = FilesystemUtils::resolve(my_directory, "my.file.a");
    const String my_file_b = FilesystemUtils::resolve(my_directory, "my.file.b");
    EXPECT_EQ(FilesystemUtils::get_filename(my_file_a), "my.file.a");
    EXPECT_EQ(FilesystemUtils::get_filename(my_file_b), "my.file.b");
    EXPECT_EQ(FilesystemUtils::get_base_filename(my_file_a), "my");
    EXPECT_EQ(FilesystemUtils::get_base_filename(my_file_b), "my");

    std::ofstream stream_a(my_file_a.c_str());
    EXPECT_TRUE(stream_a.is_open());

    std::ofstream stream_b(my_file_b.c_str());
    EXPECT_TRUE(stream_b.is_open());

    Vector<String> files = FilesystemUtils::list(my_directory);
    EXPECT_EQ(files.size(), 2);
    EXPECT_EQ(files[0], my_file_a);
    EXPECT_EQ(files[1], my_file_b);
}
