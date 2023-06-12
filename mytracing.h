#pragma once
#include <crtdbg.h>
#include <windows.h>

#include <stdio.h>
#include <thread>
#include <sstream>
#include <unordered_map>

#include "D:\Utils\Utils\plog\Log.h"
#include "D:\Utils\Utils\plog\Initializers\RollingFileInitializer.h"

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

enum ThreadsID
{
    One = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Eleven

};

int N = 10;

struct Tracer
{
    char const* m_filename;
    unsigned m_line;
    char const* m_functionname;
    static std::unordered_map<std::string, int> m_threads;
    static int m_counter;

    Tracer(char const* filename, unsigned const line, char const* functionname) :
        m_filename{ filename },
        m_line{ line },
        m_functionname{ functionname }
    {
    }

    void createLogFile() const
    {
        std::string str = "log_" + std::to_string(m_counter) + ".txt";
        switch (m_counter)
        {
        case 0:
            plog::init(plog::debug, str.c_str());
            break;
        case 1:
            plog::init<ThreadsID::One>(plog::debug, str.c_str());
            break;
        case 2:
            plog::init<ThreadsID::Two>(plog::debug, str.c_str());
            break;
        case 3:
            plog::init<ThreadsID::Three>(plog::debug, str.c_str());
            break;
        case 4:
            plog::init<ThreadsID::Four>(plog::debug, str.c_str());
            break;
        case 5:
            plog::init<ThreadsID::Five>(plog::debug, str.c_str());
            break;
        case 6:
            plog::init<ThreadsID::Six>(plog::debug, str.c_str());
            break;
        case 7:
            plog::init<ThreadsID::Seven>(plog::debug, str.c_str());
            break;
        case 8:
            plog::init<ThreadsID::Eight>(plog::debug, str.c_str());
            break;
        case 9:
            plog::init<ThreadsID::Nine>(plog::debug, str.c_str());
            break;
        case 10:
            plog::init<ThreadsID::Ten>(plog::debug, str.c_str());
            break;
        }
    }

    void logThis(wchar_t const* buffer, int logger)
    {
        switch (logger)
        {
        case 0:
            PLOGD << buffer;
            break;
        case 1:
            PLOGD_(ThreadsID::One) << buffer;
            break;
        case 2:
            PLOGD_(ThreadsID::Two) << buffer;
            break;
        case 3:
            PLOGD_(ThreadsID::Three) << buffer;
            break;
        case 4:
            PLOGD_(ThreadsID::Four) << buffer;
            break;
        case 5:
            PLOGD_(ThreadsID::Five) << buffer;
            break;
        case 6:
            PLOGD_(ThreadsID::Six) << buffer;
            break;
        case 7:
            PLOGD_(ThreadsID::Seven) << buffer;
            break;
        case 8:
            PLOGD_(ThreadsID::Eight) << buffer;
            break;
        case 9:
            PLOGD_(ThreadsID::Nine) << buffer;
            break;
        case 10:
            PLOGD_(ThreadsID::Ten) << buffer;
            break;
        }
    }

    template <typename... Args>
    auto operator()(wchar_t const* format, Args... args) -> void
    {
        wchar_t buffer[256];

        //std::thread::id this_id = std::this_thread::get_id();
        //std::stringstream ss;
        //ss << this_id;
        //std::string thread_id = ss.str();

        int myint = rand() % N;
        std::string thread_id = std::to_string(myint);

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


        auto iter = m_threads.find(thread_id);
        if (iter != m_threads.end())
        {
            logThis(buffer, iter->second);
        }
        else
        {
            createLogFile();
            m_threads[thread_id] = m_counter;
            logThis(buffer, m_counter);
            m_counter++;
        }

        OutputDebugString(buffer);
    }
};

int Tracer::m_counter = 0;
std::unordered_map<std::string, int> Tracer::m_threads;

#define MYOWNTRACEMINE Tracer(__FILE__, __LINE__, __FUNCTION__)


/*
Usage:

std::wstring str = std::to_wstring((int)operation->Type);
wchar_t str3[] = L"operation type is ";
std::wstring str2 = str3 + str;
MYOWNTRACEMINE(L"%s\n", str2.c_str());

MYOWNTRACEMINE(L"logging the operation %s\n", str2.c_str());

*/