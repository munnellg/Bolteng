#ifndef LOGGING_H
#define LOGGING_H

#include <cstring>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define LOG_ERROR(...) do { \
    logging::message(logging::Level::error, __FILENAME__, __LINE__, __VA_ARGS__); \
} while (0)

#define LOG_WARN(...) do { \
    logging::message(logging::Level::warn, __FILENAME__, __LINE__, __VA_ARGS__); \
} while (0)

#define LOG_INFO(...) do { \
    logging::message(logging::Level::info, __FILENAME__, __LINE__, __VA_ARGS__); \
} while (0)

#define LOG_DEBUG(...) do { \
    logging::message(logging::Level::debug, __FILENAME__, __LINE__, __VA_ARGS__); \
} while (0)

namespace logging {
    enum Level {
        none,  /* disable logging */
        error, /* logging only error messages */
        warn,  /* Log warnings and errors */
        info,  /* logging warnings, errors and info messages */
        debug  /* logging all messages including debug messages */
    };

    enum Echo {
        off, /* disable echoing to stderr */
        on   /* enable echoing to stderr */
    };

    int open(char const *fname);

    void set_echo(Echo const echo);

    void set_level(Level const level);

    void close();

    void message(Level const level, char const *file, int const line, char const *msg, ...);
}
#endif // LOGGING_H
