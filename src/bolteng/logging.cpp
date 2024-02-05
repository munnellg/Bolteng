#include "logging.h"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string>

#ifdef NDEBUG
// don't reveal information about the source code if we're in release mode
#define LOG(level, handle, file, line, func, msg) \
    do {                                          \
        va_list logging_args;                     \
        va_start(logging_args, msg);              \
        fprintf(                                  \
            handle,                               \
            "%-5s",                               \
            level_labels[level]                   \
        );                                        \
        vfprintf(handle, msg, logging_args);      \
        fprintf(handle, "\n");                    \
        va_end(logging_args);                     \
    } while(0)
#else
#define LOG(level, handle, file, line, func, msg) \
    do {                                          \
        va_list logging_args;                     \
        va_start(logging_args, msg);              \
        fprintf(                                  \
            handle,                               \
            "%-5s : [%s:%d:%s] : ",               \
            level_labels[level],                  \
            file,                                 \
            line,                                 \
            func                                  \
        );                                        \
        vfprintf(handle, msg, logging_args);      \
        fprintf(handle, "\n");                    \
        va_end(logging_args);                     \
    } while(0)
#endif
namespace logging {

    static char const * level_labels[] = { R"(OFF)", R"(ERROR)", R"(WARN)", R"(INFO)", R"(DEBUG)" };

    static FILE *g_handle = nullptr;      // logging file to which messages should be written
    static Level g_level  = Level::debug; // control what messages should be printed
    static Echo g_echo    = Echo::on;     // echo logging messages to stderr if true

    int open(const char *fname) {	
        g_handle = fopen(fname, "w");
        return g_handle != nullptr;
    }

    void message (Level const level, char const *file, int const line, char const *func, char const *msg, ...) {	
        if (level > g_level) {
            return;
        }

        if (g_echo == Echo::on) {
            LOG(level, stderr, file, line, func, msg);
        }	

        if (g_handle != nullptr) {
            LOG(level, g_handle, file, line, func, msg);
        }
    }

    void set_echo(Echo const echo) {
        g_echo = echo;
    }

    void set_level(Level const level) {
        g_level = level;
    }

    void close() {
        if (g_handle != nullptr) {
            fflush(g_handle);
            fclose(g_handle);
        }
    }
}
