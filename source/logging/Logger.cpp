#include "logging/Logger.h"

#include <Windows.h>

#include <cstdarg>
#include <cstdio>

#include "config/Config.h"

void Log(const char* format, ...) {
    if (!Config::Get().debugLogging)
        return;

    FILE* file = std::fopen(Config::LogPath().c_str(), "a");
    if (!file)
        return;

    std::fprintf(file, "[%10lu] ", GetTickCount());

    va_list args;
    va_start(args, format);
    std::vfprintf(file, format, args);
    va_end(args);

    std::fputc('\n', file);
    std::fclose(file);
}
