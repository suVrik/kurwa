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

#include <kw/base/vector.h>
#include <kw/debug/stacktrace.h>

#include <fmt/format.h>

#if defined(KW_WINDOWS)
#include <DbgHelp.h>
#include <windows.h>
#endif

namespace kw {

#if !defined(KW_DEBUG)

String Stacktrace::get_stacktrace(uint32 skip_count, uint32 offset) noexcept {
    // No stacktrace in Release builds.
    return {};
}

#elif defined(KW_WINDOWS)

String Stacktrace::get_stacktrace(uint32 skip_count, uint32 offset) noexcept {
    // Ignore this function itself.
    skip_count++;

    HANDLE process = GetCurrentProcess();
    HANDLE thread  = GetCurrentThread();

    CONTEXT context{};
    context.ContextFlags = CONTEXT_FULL;
    RtlCaptureContext(&context);

    SymInitialize(process, nullptr, TRUE);
    SymSetOptions(SYMOPT_LOAD_LINES);

    STACKFRAME64 frame{};
    frame.AddrPC.Offset    = context.Rip;
    frame.AddrPC.Mode      = AddrModeFlat;
    frame.AddrFrame.Offset = context.Rbp;
    frame.AddrFrame.Mode   = AddrModeFlat;
    frame.AddrStack.Offset = context.Rsp;
    frame.AddrStack.Mode   = AddrModeFlat;

    String result;
    while (StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread, &frame, &context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr) == TRUE) {
        if (skip_count > 0) {
            skip_count--;
            continue;
        }

        String symbol_name;
        String file_name;
        uint32 line_number = 0;

        char symbol_buffer[sizeof(IMAGEHLP_SYMBOL64) + 255];
        auto* symbol          = reinterpret_cast<IMAGEHLP_SYMBOL64*>(symbol_buffer);
        symbol->SizeOfStruct  = sizeof(symbol_buffer);
        symbol->MaxNameLength = 254;
        if (SymGetSymFromAddr64(process, frame.AddrPC.Offset, nullptr, symbol) == TRUE) {
            symbol_name = symbol->Name;
        }

        DWORD displacement = 0;
        IMAGEHLP_LINE64 line;
        line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
        if (SymGetLineFromAddr64(process, frame.AddrPC.Offset, &displacement, &line) == TRUE) {
            file_name   = line.FileName;
            line_number = line.LineNumber;
        }

        // Ignore weird stacktrace items.
        if (line_number != 0) {
            result += fmt::format("{}{}:{} (in '{}')\n", String(offset, ' '), file_name, line_number, symbol_name);
        }
    }

    SymCleanup(process);

    return result;
}

#else

String Stacktrace::get_stacktrace(uint32 skip_count, uint32 offset) noexcept {
    // TODO: implement for OSX and Linux!!!
    return "";
}

#endif

} // namespace kw