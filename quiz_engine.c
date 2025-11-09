#include <stdio.h>
#include "data_structs.h"
#include "quiz_engine.h"

void run_quiz(Question quiz_bank[], int total_questions) {
    if (total_questions == 0) {
        printf("ERROR: Cannot run quiz. No questions loaded.\n");
        return;
    }

    printf("\n\n--- Starting Linux Command Quiz ---\n");
    printf("--- Total Questions: %d ---\n", total_questions);

    for (int i = 0; i < total_questions; i++) {
        display_question(&quiz_bank[i], i + 1);

        // This is where the actual game logic would go:
        // 1. Get user input (A, B, C, or D)
        // 2. Check the answer against quiz_bank[i].correct_answer_index
        // 3. Update score
    }

    printf("\n--- Demonstration Complete. You're ready to add the input/scoring logic! ---\n");
}
