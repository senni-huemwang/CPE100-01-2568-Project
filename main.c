#include <stdio.h>
#include "data_structs.h"
#include "quiz_engine.h"

int main() {
    printf("TuxQuiz: Simple Linux/UNIX Command Quiz.\n");

    Question quiz_bank[MAX_QUESTIONS];
    int total_questions = 0;

    total_questions = load_questions(quiz_bank);

    if (total_questions > 0) {
        run_quiz(quiz_bank, total_questions);
    } else {
        printf("\nCritical error: Failed to load questions. Check that '%s' is in the same directory as the executable.\n", QUESTION_FILENAME);
    }

    return 0;
}
