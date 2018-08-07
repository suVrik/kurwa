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
#include <kw/debug/runtime_error.h>

#include <SDL2/SDL_filesystem.h>

#if defined(KW_WINDOWS)
#include <shlwapi.h>
#endif

namespace kw {
namespace filesystem_details {
String organization_name = "kurwa";
String application_name = "game";

#if defined(KW_WINDOWS)
char PLATFORM_SEPARATOR = '\\';
#else
char PLATFORM_SEPARATOR = '/';
#endif
} // namespace filesystem_details

String FilesystemUtils::get_executable_path() noexcept {
#if defined(KW_WINDOWS)
    String result;
    DWORD length = MAX_PATH;
    do {
        result.resize(length * 2, '\0');
        length = GetModuleFileNameA(nullptr, &result[0], MAX_PATH + 1);
    } while (length >= result.size());
    return result.c_str(); // Normalize string that may contain many `\0`
#else
    // TODO: Unix
#endif
}

String FilesystemUtils::get_resource_path() noexcept {
    // This is not necessarily a fast call, though, so you should call this once near startup
    // and save the string if you need it.
    static String result = [] {
        char* base_path_c_str = SDL_GetBasePath();
        String base_path(base_path_c_str);
        SDL_free(base_path_c_str);
        return base_path;
    }();
    return result;
}

void FilesystemUtils::set_save_path(const String& organization, const String& application) noexcept {
    filesystem_details::organization_name = organization;
    filesystem_details::application_name = application;
}

String FilesystemUtils::get_save_path() noexcept(false) {
    static String result = []() {
        char* pref_path_c_str = SDL_GetPrefPath(filesystem_details::organization_name.c_str(),
                                                filesystem_details::application_name.c_str());
        if (pref_path_c_str == nullptr) {
            throw RuntimeError("Failed to get preferences path!");
        }
        String pref_path(pref_path_c_str);
        SDL_free(pref_path_c_str);
        return pref_path;
    }();
    return result;
}

bool FilesystemUtils::is_absolute(const String &path) noexcept {
#if defined(KW_WINDOWS)
    return PathIsRelativeA(path.c_str()) == FALSE;
#else
    return !path.empty() && path[0] == '/';
#endif
}

String FilesystemUtils::join(const String &a, const String &b) noexcept {
    if (a.empty()) {
        return b;
    }
    if (b.empty()) {
        return a;
    }
    if (a.back() != filesystem_details::PLATFORM_SEPARATOR) {
        if (b.front() != filesystem_details::PLATFORM_SEPARATOR) {
            return a + filesystem_details::PLATFORM_SEPARATOR + b;
        } else {
            return a + b;
        }
    } else {
        if (b.front() != filesystem_details::PLATFORM_SEPARATOR) {
            return a + b;
        } else {
            return a.substr(0, a.size() - 1) + b;
        }
    }
}

String FilesystemUtils::resolve(const String &a, const String &b) noexcept {
    if (is_absolute(b)) {
        return b;
    }
    return join(a, b);
}

String FilesystemUtils::get_filename(const String &path) noexcept {
    size_t last_separator = path.find_last_of(filesystem_details::PLATFORM_SEPARATOR);
    if (last_separator != String::npos) {
        if (last_separator + 1 != path.size()) {
            return path.substr(last_separator + 1);
        } else if (last_separator > 0) {
            // Path ends with a separator, which is typical for directories.
            last_separator = path.find_last_of(filesystem_details::PLATFORM_SEPARATOR, last_separator - 1);
            if (last_separator != String::npos) {
                return path.substr(last_separator + 1, path.size() - (last_separator + 2));
            }
            return path;
        } else {
            // Return empty string for such path.
            return {};
        }
    }
    return path;
}

String FilesystemUtils::get_base_filename(const String &path) noexcept {
    String filename = get_filename(path);
    if (!is_directory(path)) {
        size_t first_period = filename.find_first_of('.');
        if (first_period != String::npos) {
            return filename.substr(0, first_period);
        }
    }
    return filename;
}

bool FilesystemUtils::exists(const String &path) noexcept {
#if defined(KW_WINDOWS)
    return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
#else
    // TODO: Unix
#endif
}

bool FilesystemUtils::is_directory(const String &path) noexcept {
#if defined(KW_WINDOWS)
    const DWORD attributes = GetFileAttributesA(path.c_str());
    return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    // TODO: Unix
#endif
}

bool FilesystemUtils::create_directory(const String &path) noexcept {
#if defined(KW_WINDOWS)
    return CreateDirectoryA(path.c_str(), nullptr) == TRUE;
#else
    // TODO: Unix
#endif
}

bool FilesystemUtils::remove_directory(const String& path) noexcept {
#if defined(KW_WINDOWS)
    return RemoveDirectoryA(path.c_str()) == TRUE;
#else
    // TODO: Unix
#endif
}

bool FilesystemUtils::remove_directory_recursive(const String& path) noexcept {
    String target_path(path.size() + 1, '\0');
    eastl::copy_n(&path[0], path.size(), &target_path[0]);
    SHFILEOPSTRUCTA file_op = { nullptr, FO_DELETE, target_path.c_str(), "",
                                FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT, false, 0, "" };
    return SHFileOperationA(&file_op) == 0;
}

bool FilesystemUtils::remove_file(const String& path) noexcept {
#if defined(KW_WINDOWS)
    return DeleteFileA(path.c_str()) == TRUE;
#else
    // TODO: Unix
#endif
}

Vector<String> FilesystemUtils::list(String directory) noexcept {
#if defined(KW_WINDOWS)
    Vector<String> result;

    if (!directory.empty() && directory.back() != '\\') {
        directory.append(1, '\\');
    }

    WIN32_FIND_DATAA find_data;
    HANDLE find = FindFirstFileA((directory + "*").c_str(), &find_data);
    if (find != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(find_data.cFileName, ".") != 0 && strcmp(find_data.cFileName, "..") != 0) {
                result.push_back(directory + find_data.cFileName);
            }
        } while(FindNextFile(find, &find_data) != 0);
        FindClose(find);
    }

    return result;
#else
    // TODO: Unix
#endif
}
} // namespace kw
