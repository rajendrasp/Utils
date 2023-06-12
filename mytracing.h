#pragma once
#include <crtdbg.h>
#include <windows.h>

#include <stdio.h>
#include <thread>
#include <sstream>

inline auto Trace(wchar_t const* format, ...) -> void
{
    va_list args;
    va_start(args, format);

    wchar_t buffer[256];

    _vsnwprintf_s(buffer,
        _countof(buffer) - 1,
        format,
        args);

    va_end(args);

    OutputDebugString(buffer);
}

struct Tracer
{
    char const* m_filename;
    unsigned m_line;
    char const* m_functionname;

    Tracer(char const* filename, unsigned const line, char const* functionname) :
        m_filename{ filename },
        m_line{ line },
        m_functionname{ functionname }
    {

    }

    template <typename... Args>
    auto operator()(wchar_t const* format, Args... args) const -> void
    {
        wchar_t buffer[256];

        std::thread::id this_id = std::this_thread::get_id();
        std::stringstream ss;
        ss << this_id;
        std::string thread_id = ss.str();

        auto count = swprintf_s(buffer,
            L"DEBUG_TRACING Thread: %S %S(%d)%S: ",
            thread_id.c_str(),
            m_filename,
            m_line,
            m_functionname);

        //ASSERT(-1 != count);

        _snwprintf_s(buffer + count,
            _countof(buffer) - count,
            _countof(buffer) - count - 1,
            format,
            args...);

        OutputDebugString(buffer);
    }
};

#define MYOWNTRACEMINE Tracer(__FILE__, __LINE__, __FUNCTION__)


/*
Usage:

std::wstring str = std::to_wstring((int)operation->Type);
wchar_t str3[] = L"operation type is ";
std::wstring str2 = str3 + str;
MYOWNTRACEMINE(L"%s\n", str2.c_str());

MYOWNTRACEMINE(L"logging the operation %s\n", str2.c_str());

*/
