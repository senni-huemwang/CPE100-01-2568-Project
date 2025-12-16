#include <stdio.h>
#include <time.h>
#include "logging.h"

// Logs the quiz result with a precise timestamp to the log file.
void log_score(int score, int total_questions) {
    FILE *file = NULL;

    // Get Current Date and Time
    time_t timer;
    char buffer[MAX_LOG_ENTRY_LEN];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, MAX_LOG_ENTRY_LEN, "%Y-%m-%d %H:%M:%S", tm_info);

    // Open File in APPEND Mode
    file = fopen(LOG_FILENAME, "a");
    if (file == NULL) {
        // If file open fails, print to console instead of crashing the program
        perror("Error opening log file");
        printf("Could not log score to file. Displaying here instead:\n");
        printf("[%s] Score: %d/%d (%.2f%%)\n", buffer, score, total_questions, (float)score * 100 / total_questions);
        return;
    }

    // Write Data - Log entry format: [YYYY-MM-DD HH:MM:SS] Score: X/Y (Z.ZZ%)
    fprintf(file, "[%s] Score: %d/%d (%.2f%%)\n",
        buffer,
        score,
        total_questions,
        (float)score * 100 / total_questions
    );

    fclose(file);
    printf("Score successfully logged to '%s'.\n", LOG_FILENAME);
}
