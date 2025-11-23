#include <stdio.h>
#include <time.h>
#include "logging.h"

/**
 * @brief Logs the quiz result with a precise timestamp to the log file.
 * * It uses the "a" (append) mode for file handling, which is key for continuous logging.
 * * @param score The user's final score.
 * @param total_questions The total number of questions in the quiz.
 */
void log_score(int score, int total_questions) {
    FILE *file = NULL;
    
    // --- 1. Get Current Date and Time ---
    time_t timer;
    char buffer[MAX_LOG_ENTRY_LEN];
    struct tm* tm_info;

    // Get the current calendar time
    time(&timer);
    // Convert to local time structure. This will look correct on your Ubuntu ThinkPad!
    tm_info = localtime(&timer);
    
    // Format the time string (e.g., "YYYY-MM-DD HH:MM:SS")
    // We're using strftime to format the time securely.
    strftime(buffer, MAX_LOG_ENTRY_LEN, "%Y-%m-%d %H:%M:%S", tm_info);
    
    // --- 2. Open File in APPEND Mode ---
    // The "a" mode is critical here. It ensures that the new score is added to 
    // the end of the file, rather than overwriting existing scores!
    file = fopen(LOG_FILENAME, "a");
    if (file == NULL) {
        // If file open fails, print to console instead of crashing the program
        perror("Error opening log file");
        printf("Could not log score to file. Displaying here instead:\n");
        printf("[%s] Score: %d/%d (%.2f%%)\n", buffer, score, total_questions, (float)score * 100 / total_questions);
        return;
    }

    // --- 3. Write Data and Close ---
    // Log entry format: [YYYY-MM-DD HH:MM:SS] Score: X/Y (Z.ZZ%)
    fprintf(file, "[%s] Score: %d/%d (%.2f%%)\n", 
        buffer, 
        score, 
        total_questions, 
        (float)score * 100 / total_questions
    );

    // Always close the file handle!
    fclose(file);
    printf("Score successfully logged to '%s'.\n", LOG_FILENAME);
}
