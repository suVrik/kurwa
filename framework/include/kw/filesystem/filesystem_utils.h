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

#pragma once

#include <kw/base/string.h>
#include <kw/base/vector.h>

namespace kw {
/**
 * FilesystemUtils provides a basic interface to communicate with the filesystem.
 */
class FilesystemUtils {
public:
    /**
     * Return executable path.
     */
    static String get_executable_path() noexcept;

    /**
     * Return resource directory.
     */
    static String get_resource_path() noexcept;

    /**
     * Change default organization name and application name.
     * Default value for `organization` is "kurwa" and for `application` is "game".
     */
    static void set_save_path(const String& organization, const String& application) noexcept;

    /**
     * Return directory in which application is allowed to write.
     * It is cached after the very first call and `set_save_path` does not change it.
     */
    static String get_save_path() noexcept(false);

    /**
     * Return true if the given `path` is absolute. Return false otherwise.
     */
    static bool is_absolute(const String& path) noexcept;

    /**
     * Join paths `a` and `b`. Use platform-dependent separator. If `a` already ends with a separator,
     * just join the strings. Keep in mind, if `b` is absolute path, the result will be invalid path, prefer
     * `resolve` function overall.
     */
    static String join(const String& a, const String& b) noexcept;

    /**
     * If `b` is absolute path, return `b`. Otherwise join `a` and `b`.
     */
    static String resolve(const String& a, const String& b) noexcept;

    /**
     * Return name of the file (or directory) with specified `path`.
     */
    static String get_filename(const String& path) noexcept;

    /**
     * Return filename without extension (for directory return directory name).
     */
    static String get_base_filename(const String& path) noexcept;

    /**
     * Return true if the given `path` (file or directory) exists. Return false otherwise.
     */
    static bool exists(const String& path) noexcept;

    /**
     * Return true if the given `path` is a directory. Return false otherwise.
     */
    static bool is_directory(const String& path) noexcept;

    /**
     * Create directory with specified `path`. Return true on success and false otherwise.
     */
    static bool create_directory(const String& path) noexcept;

    /**
     * Remove directory and its contents with specified `path`. Return true on success and false otherwise.
     */
    static bool remove_directory(const String& path) noexcept;

    /**
     * Remove directory with specified `path`. Return true on success and false otherwise.
     */
    static bool remove_directory_recursive(const String& path) noexcept;

    /**
     * Remove file with specified `path`. Return true on success and false otherwise.
     */
    static bool remove_file(const String& path) noexcept;

    /**
     * Return list of files and directories in the given `directory`.
     */
    static Vector<String> list(const String& directory) noexcept;

    FilesystemUtils() = delete;
};
} // namespace kw
