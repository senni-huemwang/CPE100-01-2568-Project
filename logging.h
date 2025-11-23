#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <time.h>

// -----------------------------------------------------------------------------
// CONTROL FLAG: Define this to enable all logs. Comment it out to disable them.
// -----------------------------------------------------------------------------
#define ENABLE_LOGGING 

// --- Logging Macros ---

#ifdef ENABLE_LOGGING
    /**
     * @brief Logs informational messages.
     * @param fmt The format string.
     * @param ... Variable arguments for the format string.
     */
    #define LOG_INFO(fmt, ...) \
        fprintf(stdout, "[INFO] [%s] %s:%d: " fmt "\n", \
                get_timestamp(), __FILE__, __LINE__, ##__VA_ARGS__)

    /**
     * @brief Logs error messages (always prints to stderr).
     * @param fmt The format string.
     * @param ... Variable arguments for the format string.
     */
    #define LOG_ERROR(fmt, ...) \
        fprintf(stderr, "[ERROR] [%s] %s:%d: " fmt "\n", \
                get_timestamp(), __FILE__, __LINE__, ##__VA_ARGS__)

    /**
     * @brief Logs data/debug messages (e.g., variable values during development).
     * @param fmt The format string.
     * @param ... Variable arguments for the format string.
     */
    #define LOG_DEBUG(fmt, ...) \
        fprintf(stdout, "[DEBUG] [%s] %s:%d: " fmt "\n", \
                get_timestamp(), __FILE__, __LINE__, ##__VA_ARGS__)
#else
    // When logging is disabled, these macros expand to nothing.
    #define LOG_INFO(fmt, ...) (void)0
    #define LOG_ERROR(fmt, ...) (void)0
    #define LOG_DEBUG(fmt, ...) (void)0
#endif

#endif // LOGGING_H
```
eof

## How to Use This in Your Project

1.  **Include the Header:** In any C file (`main.c`, `data_load.c`, `quiz_engine.c`), just add:
    ```c
    #include "logging.h"
    ```

2.  **Log Messages:** Call the macros like functions.

    * **In `data_load.c`:**
        ```c
        FILE *fp = fopen("questions.txt", "r");
        if (fp == NULL) {
            LOG_ERROR("Failed to open questions.txt file!");
            return 0;
        }
        LOG_INFO("Successfully opened questions.txt for reading.");
        // ... after loading 10 questions ...
        LOG_DEBUG("Loaded %d questions into quiz_bank array.", num_questions_loaded); 
        ```

3.  **To Disable All Logging:** If you want a clean final version, simply **comment out** the control flag line in `logging.h`:

    ```c
    // #define ENABLE_LOGGING // <-- Commented out to disable all logs
