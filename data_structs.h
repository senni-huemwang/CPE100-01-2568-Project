#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#define MAX_QUESTION_LEN 512
#define MAX_OPTION_LEN 128
#define NUM_OPTIONS 4
#define MAX_QUESTIONS 50
#define DATA_FILE_PATH "questions.txt"
#define QUESTION_FILENAME "questions.txt"

typedef struct {
    char question[MAX_QUESTION_LEN];
    char options[NUM_OPTIONS][MAX_OPTION_LEN];
    int correct_answer_index;
} Question;

int load_questions(Question quiz_bank[]);
void display_question(const Question *q, int q_number);
#endif
