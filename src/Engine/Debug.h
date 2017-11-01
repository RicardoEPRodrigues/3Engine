/*
 * File Debug.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_DEBUG_H
#define THREEENGINE_DEBUG_H

#include <iostream>
#include <string>
#include <sstream>

#include <cstdarg>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include <cstring>

#if defined DEBUG && defined OS_LINUX
#include <csignal>
#endif

namespace ThreeEngine {

    inline void DebugBreakpoint() {
#ifdef DEBUG
#if OS_WIN
        __debugbreak();
#else
        std::raise(SIGINT);
#endif
#endif
    }

    class Debug {
        private:
            Debug() = default;


            static std::string string_format(const std::string& fmt_str, ...) {
                int final_n, n = ((int) fmt_str.size()) *
                                 2; /* Reserve two times as much as the length of the fmt_str */
                std::unique_ptr<char[]> formatted;
                va_list ap;
                while (true) {
                    /* Wrap the plain char array into the unique_ptr */
                    formatted.reset(new char[n]);
#if OS_WIN
                    strcpy_s(&formatted[0], n, fmt_str.c_str());
#else
                    strncpy(&formatted[0], fmt_str.c_str(), n);
#endif
                    va_start(ap, fmt_str);
                    final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
                    va_end(ap);
                    if (final_n < 0 || final_n >= n)
                        n += abs(final_n - n + 1);
                    else
                        break;
                }
                return std::string((char*)formatted.get());
            }

        public:
            static void Print(const std::string& message) {
#ifdef DEBUG
                std::cout << message << std::endl;
#endif
            }

            template<typename... Args>
            static void Print(const std::string& fmt_str, Args... args) {
#ifdef DEBUG
                Print(string_format(fmt_str, args...));
#endif
            }

            static void Log(const std::string& message) {
#ifdef DEBUG
                std::cout << "LOG: " << message << std::endl;
#endif
            }

            template<typename... Args>
            static void Log(const std::string& fmt_str, Args... args) {
#ifdef DEBUG
                Log(string_format(fmt_str, args...));
#endif
            }

            static void Warn(const std::string& message) {
#ifdef DEBUG
                std::cerr << "WARNING: " << message << std::endl;
#endif
            }

            template<typename... Args>
            static void Warn(const std::string& fmt_str, Args... args) {
#ifdef DEBUG
                Warn(string_format(fmt_str, args...));
#endif
            }

            static void Error(const std::string& message) {
                std::cerr << "ERROR: " << message << std::endl;
            }

            template<typename... Args>
            static void Error(const std::string& fmt_str, Args... args) {
                Error(string_format(fmt_str, args...));
            }
    };
}

#endif //THREEENGINE_DEBUG_H
