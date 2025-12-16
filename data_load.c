#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structs.h"

 // Attempts to load questions from the questions file into the quiz bank array.

int load_questions(Question quiz_bank[]) {
    FILE *file = NULL;
    char line[MAX_QUESTION_LEN * 5];
    int question_count = 0;

    file = fopen(DATA_FILE_PATH, "r");
    if (file == NULL) {
        printf("Error: Could not open the question bank file '%s'.\n", QUESTION_FILENAME);
        return 0;
    }

    printf("Success: Opened '%s' file for loading.\n", QUESTION_FILENAME);

    while (fgets(line, sizeof(line), file) != NULL) {

        // Skip empty lines or lines that would exceed the array limit
        if (line[0] == '\n' || line[0] == '\r' || question_count >= MAX_QUESTIONS) {
            continue;
        }

        line[strcspn(line, "\n\r")] = 0;

        // Make a mutable copy of the line to work with
        char *temp_line = strdup(line);
        if (temp_line == NULL) {
            perror("Memory allocation error");
            break;
        }

        char *current_pos = temp_line;
        char *delimiter_pos = NULL;
        int field_count = 0;
        Question *current_q = &quiz_bank[question_count];

        // Loop through all 7 expected fields (ID, Q, A, B, C, D, Index)
        while (field_count < 7) {

            // Use strchr to find the next pipe delimiter '|'
            // We search from current_pos onwards
            delimiter_pos = strchr(current_pos, '|');

            // If delimiter_pos is not NULL, we found a pipe.
            if (delimiter_pos != NULL) {
                // Crucial step: Replace the pipe with a null terminator.
                // This 'closes' the current field string.
                *delimiter_pos = '\0';
            }

            // At this point, 'current_pos' points to the start of the field,
            // and the field is properly null-terminated.
            char *token = current_pos;

            // --- Assign Field Based on Count ---
            switch (field_count) {
                case 0: // Field 1: Question ID (We consume this token, but don't store it)
                    break;
                case 1: // Field 2: Question Text
                    strncpy(current_q->question, token, MAX_QUESTION_LEN - 1);
                    current_q->question[MAX_QUESTION_LEN - 1] = '\0';
                    break;
                case 2: // Field 3: Option A (i=0)
                case 3: // Field 4: Option B (i=1)
                case 4: // Field 5: Option C (i=2)
                case 5: { // Field 6: Option D (i=3)
                    int option_index = field_count - 2; // Converts field count (2-5) to array index (0-3)
                    strncpy(current_q->options[option_index], token, MAX_OPTION_LEN - 1);
                    current_q->options[option_index][MAX_OPTION_LEN - 1] = '\0';
                    break;
                }
                case 6: // Field 7: Correct Answer Index (This is the last field)
                    current_q->correct_answer_index = atoi(token);
                    break;
            }

            // --- Advance the Pointer for the Next Field ---
            if (delimiter_pos != NULL) {
                // If we found a delimiter, the next field starts one character after it.
                current_pos = delimiter_pos + 1;
            } else {
                // If delimiter_pos is NULL, we processed the last field in the line. Exit loop.
                field_count = 6; // Set to 6 so the next iteration ends the while loop correctly.
            }

            field_count++;
        }

        // Only count the question if we successfully parsed exactly 7 fields
        if (field_count == 7) {
            question_count++;
        } else {
            printf("Warning: Skipping malformed line %d in questions.txt (expected 7 fields, found %d).\n", question_count + 1, field_count);
        }

        // Free the dynamically allocated copy of the line
        free(temp_line);
    }

    fclose(file);
    return question_count;
}

void display_question(const Question *q, int q_number) {
    printf("\n------------------------------------------------\n");
    printf("(%d). %s\n", q_number, q->question);

    // Loop through the 4 options
    for (int i = 0; i < NUM_OPTIONS; i++) {
        printf("  %s\n", q->options[i]);
    }

    printf("------------------------------------------------\n");
    printf("   Your answer (A, B, C, or D): ");
}
