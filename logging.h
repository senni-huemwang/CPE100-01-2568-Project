#ifndef LOGGING_H
#define LOGGING_H

#include <time.h> // Necessary for the time-related structures in the implementation

// Define the name of the file where scores will be appended
#define LOG_FILENAME "quiz_scores.log"
#define MAX_LOG_ENTRY_LEN 256

// Function prototype for the logging function defined in logging.c
// This is the function run_quiz will call.
void log_score(int score, int total_questions);

#endif // LOGGING_H
