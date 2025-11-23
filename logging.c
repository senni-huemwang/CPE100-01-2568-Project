/**
 * @file logging.c
 * @brief Source file for the logging module. Implements the get_timestamp function.
 */

#include "logging.h"
#include <time.h> // Include time.h here as well, although included in logging.h, 
                  // it's good practice for the implementation file.

/**
 * @brief Retrieves the current formatted timestamp.
 * * Implementation moved here for better modularity and link stability.
 * @return A static char pointer containing the time string [YYYY-MM-DD HH:MM:SS].
 */
const char* get_timestamp() {
    // NOTE: Using a static buffer is necessary here because the pointer 
    // must persist after the function returns.
    static char buffer[20];
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    
    // Format the time as YYYY-MM-DD HH:MM:SS
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_struct);
    return buffer;
}
