#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <time.h>
#include <string.h>

// -----------------------------------------------------------------------------
// CONTROL FLAG: Define this to enable all logs. Comment it out to disable them.
// -----------------------------------------------------------------------------
#define ENABLE_LOGGING

// Extract filename only (remove full path)
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// --- Logging Macros ---
#ifdef ENABLE_LOGGING

#define LOG_INFO(fmt, ...) \
    fprintf(stdout, "[INFO]  [%s] %s:%d: " fmt "\n", \
            get_timestamp(), __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[ERROR] [%s] %s:%d: " fmt "\n", \
            get_timestamp(), __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...) \
    fprintf(stdout, "[DEBUG] [%s] %s:%d: " fmt "\n", \
            get_timestamp(), __FILENAME__, __LINE__, ##__VA_ARGS__)

#else
#define LOG_INFO(fmt, ...)  (void)0
#define LOG_ERROR(fmt, ...) (void)0
#define LOG_DEBUG(fmt, ...) (void)0
#endif

// Correct prototype
const char* get_timestamp();

#endif // LOGGING_H
