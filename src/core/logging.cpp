#include "logging.h"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string>

#define LOG(level, handle, file, line, msg) \
    do {                                     \
        va_list _clog_args;                  \
        va_start(_clog_args, msg);           \
        fprintf(                             \
            handle,                          \
            "%-5s : [%s:%d] : ",             \
            level_labels[level], file, line  \
        );                                   \
        vfprintf(handle, msg, _clog_args);   \
        fprintf(handle, "\n");               \
        va_end(_clog_args);                  \
    } while(0)

namespace logging {
    static struct clogger {
        FILE *handle; /* logging file to which messages should be written */
        Level level;  /* control what messages should be printed */
        Echo echo;    /* echo logging messages to stderr if true */
    } clogger = { 
        .handle = nullptr, 
        .level = Level::debug, 
        .echo = Echo::on
    };

    static char const * level_labels[] = { R"(OFF)", R"(ERROR)", R"(WARN)", R"(INFO)", R"(DEBUG)" };

    int
    open(const char *fname) {	
        clogger.handle = fopen(fname, "w");
        return clogger.handle != nullptr;
    }

    void
    message (Level const level, char const *file, int const line, char const *msg, ...) {	
        if (level > clogger.level) {
            return;
        }

        if (clogger.echo == Echo::on) {
            LOG(level, stderr, file, line, msg);
        }	

        if (clogger.handle != nullptr) {
            LOG(level, clogger.handle, file, line, msg);
        }
    }

    void
    set_echo(Echo const echo) {
        clogger.echo = echo;
    }

    void
    set_level(Level const level) {
        clogger.level = level;
    }

    void 
    close() {
        if (clogger.handle != nullptr) {
            fflush(clogger.handle);
            fclose(clogger.handle);
        }
    }
}
