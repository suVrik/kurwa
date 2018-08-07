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

#include <clang-c/Index.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>

struct ProcessingData {
    /// TODO
    std::ofstream output_stream;
    /// Defined as true if the next access specifier is considered to have reflection.
    bool apply_reflection_on_access_specifier;
    /// While defined as true all the methods and fields are considered to have reflection.
    bool is_reflection;
    /// Defined as true if abort is required (if in reflection scope invalid declarations occurred).
    bool need_abort;
    /// Number of reflection fields in current compilation unit.
    unsigned reflection_fields_count;
    /// Number of reflection methods in current compilation unit.
    unsigned reflection_methods_count;
    /// Number of reflection classes, fields and methods with meta in current compilation unit.
    unsigned reflection_meta_count;
};

std::ostream &operator<<(std::ostream &stream, const CXString& string) {
    const char *c_string = clang_getCString(string);
    const std::string std_string = c_string;
    clang_disposeString(string);
    return stream << std_string;
}

void diagnostic(CXClientData client_data, CXDiagnosticSet diagnostic_set, void*) {
    auto* processing_data = static_cast<ProcessingData*>(client_data);
    const unsigned diagnostics_num = clang_getNumDiagnosticsInSet(diagnostic_set);
    for (unsigned i = 0; i < diagnostics_num; i++) {
        CXDiagnostic diagnostic = clang_getDiagnosticInSet(diagnostic_set, i);

        CXDiagnosticSeverity severity = clang_getDiagnosticSeverity(diagnostic);

        const char *severity_str;
        switch (severity) {
            case CXDiagnostic_Ignored:
                severity_str = "Ignored";
                break;
            case CXDiagnostic_Note:
                severity_str = "Note";
                break;
            case CXDiagnostic_Warning:
                severity_str = "Warning";
                break;
            case CXDiagnostic_Error:
                severity_str = "Error";
                break;
            case CXDiagnostic_Fatal:
                severity_str = "Fatal Error";
                break;
            default:
                severity_str = "Undefined";
        }

        CXSourceLocation source_location = clang_getDiagnosticLocation(diagnostic);
        CXFile file;
        unsigned line, column, offset;
        clang_getExpansionLocation(source_location, &file, &line, &column, &offset);
        CXString file_name = clang_getFileName(file);

        CXString spelling = clang_getDiagnosticSpelling(diagnostic);
        CXString option = clang_getDiagnosticOption(diagnostic, nullptr);
        CXString category = clang_getDiagnosticCategoryText(diagnostic);

        processing_data->output_stream << "Diagnostic Message:" << std::endl;
        processing_data->output_stream << "    Severity: " << severity_str << std::endl;
        processing_data->output_stream << "    File name: " << file_name << std::endl;
        processing_data->output_stream << "    Line: " << line << std::endl;
        processing_data->output_stream << "    Column: " << column << std::endl;
        processing_data->output_stream << "    Offset: " << offset << std::endl;
        processing_data->output_stream << "    Text: " << spelling << std::endl;
        processing_data->output_stream << "    Option: " << option << std::endl;
        processing_data->output_stream << "    Category: " << category << std::endl;

        clang_disposeDiagnostic(diagnostic);
    }
}

int abort_query(CXClientData client_data, void*) {
    auto* processing_data = static_cast<ProcessingData*>(client_data);
    return static_cast<int>(processing_data->need_abort);
}

CXIdxClientFile handle_include(CXClientData client_data, const CXIdxIncludedFileInfo *index_included_file_info) {
    auto* processing_data = static_cast<ProcessingData*>(client_data);
    processing_data->output_stream << "Include file '" << index_included_file_info->filename << "'..." << std::endl;

    // TODO: do it manually for each class/field/method?

    // TODO: Remember all included headers.
    // TODO: Headers are processed after sources.
    // TODO: Headers that were in sources are not processed.

    return nullptr;
}

void print_location(CXCursor cursor, ProcessingData* processing_data) {
    CXFile file;
    unsigned line;
    clang_getExpansionLocation(clang_getCursorLocation(cursor), &file, &line, nullptr, nullptr);
    processing_data->output_stream << clang_getFileName(file) << "(" << line << "):" << std::endl;
}

void handle_access_specifier(CXCursor cursor, ProcessingData* processing_data) {
    // Apply reflection, if this access specifier follows the ReflectionRegistrator friend declaration.
    processing_data->is_reflection = processing_data->apply_reflection_on_access_specifier;
    processing_data->apply_reflection_on_access_specifier = false;

    if (processing_data->is_reflection) {
        CX_CXXAccessSpecifier access_specifier = clang_getCXXAccessSpecifier(cursor);
        const char* access_specifier_spelling;
        switch (access_specifier) {
            case CX_CXXPublic:
                access_specifier_spelling = "public";
                break;
            case CX_CXXProtected:
                access_specifier_spelling = "protected";
                break;
            case CX_CXXPrivate:
                access_specifier_spelling = "private";
                break;
            default:
                access_specifier_spelling = "invalid";
        }

        print_location(cursor, processing_data);
        processing_data->output_stream << "Found " << access_specifier_spelling
                                       << " reflection access specifier." << std::endl;
    }
}

CXChildVisitResult visit_friend_declaration_children(CXCursor cursor, CXCursor, CXClientData client_data) {
    assert(clang_Cursor_isNull(cursor) == 0);

    CXChildVisitResult result = CXChildVisit_Break;

    const CXCursorKind cursor_kind = clang_getCursorKind(cursor);
    if (cursor_kind == CXCursor_ClassTemplate) {
        CXString type_spelling = clang_getCursorSpelling(cursor);
        const char* type_spelling_str = clang_getCString(type_spelling);
        if (strcmp(type_spelling_str, "ReflectionRegistrator") == 0) {
            auto processing_data = reinterpret_cast<ProcessingData*>(client_data);
            processing_data->apply_reflection_on_access_specifier = true;

            print_location(cursor, processing_data);
            processing_data->output_stream << "Found reflection registrator" << std::endl;

            result = CXChildVisit_Continue;
        }
        clang_disposeString(type_spelling);
    }

    return result;
}

CXChildVisitResult visit_structure_children(CXCursor cursor, CXCursor, CXClientData client_data) {
    assert(clang_Cursor_isNull(cursor) == 0);

    const CXCursorKind cursor_kind = clang_getCursorKind(cursor);
    auto processing_data = reinterpret_cast<ProcessingData*>(client_data);

    // Here I split the logic by 'inside of reflection scope' an outside.
    // Inside of reflection scope very limited number of tokens can be used:
    // * Field;
    // * Method;
    // * Access specifier (which switches the reflection scope);
    // * Friend declaration of template class 'ReflectionRegistrator' (a side-kick of access specifier).
    if (processing_data->is_reflection) {
        if (processing_data->apply_reflection_on_access_specifier && cursor_kind != CXCursor_CXXAccessSpecifier) {
            std::cerr << "Friend declaration of template class 'ReflectionRegistrator' "
                         "must be followed by an access specifier." << std::endl;
            return CXChildVisit_Break;
        } else {
            // TODO: attributes?
            switch (cursor_kind) {
                case CXCursor_FieldDecl: {
                    print_location(cursor, processing_data);
                    processing_data->output_stream << "Found reflection field '"
                                                   << clang_getCursorSpelling(cursor) << "'." << std::endl;
                    break;
                }
                case CXCursor_CXXMethod: {
                    print_location(cursor, processing_data);
                    processing_data->output_stream << "Found reflection method '"
                                                   << clang_getCursorSpelling(cursor) << "'." << std::endl;
                    break;
                }
                case CXCursor_CXXAccessSpecifier:
                    handle_access_specifier(cursor, processing_data);
                    break;
                case CXCursor_FriendDecl: {
                    // Search for 'ReflectionRegistrator' template.
                    if (clang_visitChildren(cursor, visit_friend_declaration_children, client_data) != 0) {
                        // Friend declaration is also is not allowed (except 'ReflectionRegistrator' friend declaration)
                        std::cerr << "Invalid reflection token!" << std::endl;
                        return CXChildVisit_Break;
                    }
                    break;
                }
                default: {
                    std::cerr << "Invalid reflection token '" << clang_getCursorSpelling(cursor) << "'!" << std::endl;
                    return CXChildVisit_Break;
                }
            }
        }
    } else {
        if (processing_data->apply_reflection_on_access_specifier && cursor_kind != CXCursor_CXXAccessSpecifier) {
            std::cerr << "Friend declaration of template class 'ReflectionRegistrator' "
                         "must be followed by an access specifier." << std::endl;
            return CXChildVisit_Break;
        } else {
            switch (cursor_kind) {
                case CXCursor_StructDecl:
                case CXCursor_ClassDecl: {
                    print_location(cursor, processing_data);
                    processing_data->output_stream << "Parsing class '" << clang_getCursorSpelling(cursor)
                                                   << "'..." << std::endl;

                    if (clang_visitChildren(cursor, visit_structure_children, client_data) != 0) {
                        // Some error occurred inside of a structure.
                        return CXChildVisit_Break;
                    }

                    // Class ends, reflection ends.
                    processing_data->is_reflection = false;

                    break;
                }
                case CXCursor_Namespace: {
                    print_location(cursor, processing_data);
                    processing_data->output_stream << "Parsing namespace '" << clang_getCursorSpelling(cursor)
                                                   << "'..." << std::endl;

                    return CXChildVisit_Recurse;
                }
                case CXCursor_CXXAccessSpecifier:
                    handle_access_specifier(cursor, processing_data);
                    break;
                case CXCursor_FriendDecl: {
                    // Search for 'ReflectionRegistrator' template.
                    clang_visitChildren(cursor, visit_friend_declaration_children, client_data);
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
    return CXChildVisit_Continue;
}

void index_declaration_callback(CXClientData client_data, const CXIdxDeclInfo *index_declaration_info) {
    // As far as the second parameter is not used, we can pass whatever we want there.
    if (visit_structure_children(index_declaration_info->cursor, {}, client_data) == CXChildVisit_Break) {
        auto processing_data = reinterpret_cast<ProcessingData*>(client_data);
        processing_data->need_abort = true;
    }
}

struct EasyReflectionSettings {
    std::vector<std::string> sources;
    std::vector<std::string> include_directories;
    size_t num_threads = 8;
    bool is_verbose = false;
};

bool ends_with(const std::string& string, const std::string& suffix) {
    if (string.length() >= suffix.length()) {
        return string.compare(string.length() - suffix.length(), suffix.length(), suffix) == 0;
    }
    return false;
}

std::string escape_string(const std::string& string) {
    if (std::find(string.begin(), string.end(), ' ') != string.end()) {
        return "\"" + string + "\"";
    }
    return string;
}

std::string get_file_name(const std::string& string) {
    size_t pos = string.find_last_of("\\/");
    if (pos == std::string::npos) {
        return string;
    }
    return string.substr(pos + 1);
}

EasyReflectionSettings process_arguments(int argc, char* argv[]) {
    EasyReflectionSettings result {};

    for (int i = 1; i < argc; i++) {
        const char* argument = argv[i];
        if (argument[0] == '-') {
            if (strcmp(argument, "--verbose") == 0) {
                result.is_verbose = true;
            } else if (strcmp(argument, "-I") == 0) {
                if (argc > i) {
                    result.include_directories.emplace_back("-I" + escape_string(argv[++i]));
                } else {
                    std::cerr << "Unexpected end of arguments! Include directory is required!" << std::endl;
                    exit(1);
                }
            } else if (strcmp(argument, "--num-threads") == 0) {
                if (argc > i) {
                    result.num_threads = static_cast<size_t>(std::stoul(argv[++i]));
                } else {
                    std::cerr << "Unexpected end of arguments! Number of threads is required!" << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Invalid flag '" << argument << "'!" << std::endl;
                exit(1);
            }
        } else {
            result.sources.emplace_back(argument);
        }
    }

    // First non-sort files. Then header files. Then source files. Sorted alphabetically in each group.
    std::sort(result.sources.begin(), result.sources.end(), [](const std::string& a, const std::string& b) {
        const bool is_a_header = ends_with(a, ".h");
        const bool is_b_header = ends_with(b, ".h");
        const bool is_a_source = ends_with(a, ".cpp");
        const bool is_b_source = ends_with(b, ".cpp");

        if (is_a_source) {
            if (is_b_source) {
                return a > b;
            }
            return false;
        } else if (is_a_header) {
            if (is_b_source) {
                return true;
            } else if (is_b_header) {
                return a > b;
            }
            return false;
        } else {
            if (is_b_source || is_b_header) {
                return true;
            }
            return a > b;
        }
    });

    return result;
}

int main(int argc, char* argv[]) {
    EasyReflectionSettings settings = process_arguments(argc, argv);

    if (settings.sources.empty()) {
        std::cerr << "No source files given to easy-reflection!" << std::endl;
        return 1;
    }

    IndexerCallbacks indexer_callbacks {};
    indexer_callbacks.abortQuery = abort_query;
    indexer_callbacks.diagnostic = diagnostic;
    indexer_callbacks.ppIncludedFile = handle_include;
    indexer_callbacks.indexDeclaration = index_declaration_callback;

    auto** command_line_args = new const char*[settings.include_directories.size()];
    for (size_t i = 0; i < settings.include_directories.size(); i++) {
        command_line_args[i] = settings.include_directories[i].c_str();
    }
    //command_line_args[settings.include_directories.size()] = "-std=c++17";
    auto num_command_line_args = static_cast<int>(settings.include_directories.size());

    // We do not need more threads than we have source files.
    std::vector<std::thread> threads;
    threads.reserve(std::max(settings.num_threads, settings.sources.size()));

    // We're going to pop from sources from many threads.
    std::mutex sources_mutex;

    CXIndex index = clang_createIndex(0, 0);
    CXIndexAction index_action = clang_IndexAction_create(index);

    for (size_t i = 0; i < threads.capacity(); i++) {
        threads.emplace_back([&settings, &indexer_callbacks, &sources_mutex, command_line_args,
                                     num_command_line_args, index_action] {
            while (true) {
                std::string source_filename;
                {
                    std::lock_guard<std::mutex> guard(sources_mutex);
                    if (!settings.sources.empty()) {
                        // TODO: For now we can parse this source file even if it was already parsed before (using include directive, for example).
                        source_filename = settings.sources.back();
                        settings.sources.pop_back();
                    } else {
                        // No more source files available.
                        break;
                    }
                }

                const unsigned index_options = CXIndexOpt_SuppressWarnings | CXIndexOpt_SkipParsedBodiesInSession;
                const unsigned translation_unit_options = CXTranslationUnit_SkipFunctionBodies;

                ProcessingData processing_data {};
                processing_data.output_stream.open(get_file_name(source_filename) + ".log");

                CXTranslationUnit translation_unit;
                const int result = clang_indexSourceFile(index_action,
                                                         &processing_data,
                                                         &indexer_callbacks,
                                                         sizeof(indexer_callbacks),
                                                         index_options,
                                                         source_filename.c_str(),
                                                         command_line_args,
                                                         num_command_line_args,
                                                         nullptr,
                                                         0,
                                                         &translation_unit,
                                                         translation_unit_options);
                if (result != 0) {
                    // TODO: return real result
                }
                clang_disposeTranslationUnit(translation_unit);
            }
        });
    }

    // Now wait until all the threads are done.
    for (auto& thread : threads) {
        thread.join();
    }

    clang_IndexAction_dispose(index_action);
    clang_disposeIndex(index);

    delete[] command_line_args;

    // TODO: return real result
    return 0;
}
