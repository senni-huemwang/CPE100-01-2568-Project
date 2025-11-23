#include <stdio.h>
#include <ctype.h>
#include "data_structs.h"
#include "quiz_engine.h"

int check_answer(char user_input, int correct_index) {
    // Convert input to uppercase for case-insensitive checking (A/a, B/b, etc.)
    char upper_input = toupper(user_input);

    // This is a classic C trick: 'A' - 'A' = 0, 'B' - 'A' = 1, etc.
    int user_index = upper_input - 'A';

    // Check if the input is a valid choice (A-D) and if it matches the correct index
    if (user_index >= 0 && user_index < NUM_OPTIONS) {
        return user_index == correct_index;
    }

    // If the input wasn't A, B, C, or D, treat it as incorrect
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
        // 1. Display Question (function defined in data_load.c)
        display_question(&quiz_bank[i], i + 1);

        // 2. Get User Input (scanf with space to consume leftover newlines)
        if (scanf(" %c", &user_input) != 1) {
            printf("Invalid input. Skipping question.\n");
            // Clear the input buffer to prevent infinite loops from bad input
            while (getchar() != '\n');
            continue;
        }

        // 3. Check the Answer and Update Score
        int result = check_answer(user_input, quiz_bank[i].correct_answer_index);

        if (result) {
            score++;
            printf("✅ Correct! Current score: %d/%d\n", score, i + 1);
        } else {
            // Convert the correct index (0-3) back to a character (A-D) for feedback
            char correct_char = 'A' + quiz_bank[i].correct_answer_index;
            printf("❌ Incorrect. The correct answer was %c.\n", correct_char);
        }
    }

    printf("\n\n--- Quiz Finished! ---\n");
    printf("Your final score is: %d out of %d (%.2f%%)\n",
           score, total_questions, (float)score * 100 / total_questions);

    printf("\n--- Great work! You finished the quiz! ---\n");
}
