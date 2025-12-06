#ifndef LOGGING_H
#define LOGGING_H

#include <time.h>

#define LOG_FILENAME "quiz_scores.log"
#define MAX_LOG_ENTRY_LEN 256

void log_score(int score, int total_questions);

#endif // LOGGING_H
