#include <stdio.h>
#include <ctype.h>
#include "data_structs.h"
#include "quiz_engine.h"
#include "logging.h"

int check_answer(char user_input, int correct_index) {
    char upper_input = toupper(user_input);
    int user_index = upper_input - 'A';
    if (user_index >= 0 && user_index < NUM_OPTIONS) {
        return user_index == correct_index;
    }
    return 0;
}

void run_quiz(Question quiz_bank[], int total_questions) {
    if (total_questions == 0) {
        printf("ERROR: Cannot run quiz. No questions loaded.\n");
        return;
    }

    int score = 0;
    char user_input;

    printf("\n\n--- Starting Linux Command Quiz ---\n");
    printf("--- Total Questions: %d ---\n", total_questions);

    for (int i = 0; i < total_questions; i++) {
        display_question(&quiz_bank[i], i + 1);

        if (scanf(" %c", &user_input) != 1) {
            printf("Invalid input. Skipping question.\n");
            while (getchar() != '\n');
            continue;
        }

        int result = check_answer(user_input, quiz_bank[i].correct_answer_index);

        if (result) {
            score++;
            printf("✅ Correct! Current score: %d/%d\n", score, i + 1);
        } else {
            char correct_char = 'A' + quiz_bank[i].correct_answer_index;
            printf("❌ Incorrect. The correct answer was %c.\n", correct_char);
        }
    }

    printf("\n\n--- Quiz Finished! ---\n");
    printf("Your final score is: %d out of %d (%.2f%%)\n",
           score, total_questions, (float)score * 100 / total_questions);
    log_score(score,total_questions);

    printf("\n--- Great work! You finished the quiz! ---\n");
}
