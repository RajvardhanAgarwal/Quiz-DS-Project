#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPTIONS 4
#define MAX_PLAYERS 2

typedef struct {
    char prompt[100];
    char options[MAX_OPTIONS][50];
    int correctOption;
} Question;

typedef struct {
    char name[50];
    int score;
} Player;

typedef struct {
    Player players[MAX_PLAYERS];
    Question questions[10];
} QuizGame;

void addQuestion(QuizGame* quiz, Question question, int* numQuestions) {
    quiz->questions[*numQuestions] = question;
    (*numQuestions)++;
}

void addPlayer(QuizGame* quiz, const char* playerName, int* numPlayers) {
    if (*numPlayers < MAX_PLAYERS) {
        strcpy(quiz->players[*numPlayers].name, playerName);
        quiz->players[*numPlayers].score = 0;
        (*numPlayers)++;
    }
}

void runQuizSession(QuizGame* quiz, int numQuestions, int numPlayers) {
    for (int i = 0; i < numQuestions; i++) {
        printf("%s\n", quiz->questions[i].prompt);

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("%d. %s\n", j + 1, quiz->questions[i].options[j]);
        }

        printf("Your answer (enter the option number): ");
        int userAnswer;
        scanf("%d", &userAnswer);

        if (userAnswer == quiz->questions[i].correctOption) {
            printf("Correct!\n\n");
            for (int k = 0; k < numPlayers; k++) {
                quiz->players[k].score++;
            }
        } else {
            printf("Wrong! The correct answer was %d: %s\n\n", quiz->questions[i].correctOption,
                   quiz->questions[i].options[quiz->questions[i].correctOption - 1]);
        }
    }

    printf("Quiz Session completed. Scoreboard:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%s: %d points\n", quiz->players[i].name, quiz->players[i].score);
    }
}

int main() {
    QuizGame quiz;
    int numQuestions = 0;
    int numPlayers = 0;

    Question question1 = {"Which sorting is stable?", {"Bubble", "Quick", "Selection", "Insertion"}, 1};
    Question question2 = {"Which is non-linear data structure?", {"Array", "Linked List", "Tree", "Stack"}, 3};
    Question question3 = {"Which data structure follow FIFO?", {"Stack", "Queue", "Array", "Linked list"}, 2};
    Question question4 = {"Which data structure follow LIFO?", {"Stack", "Queue", "Array", "Linked list"}, 1};
    Question question5 = {"Which data structure has fixed size?", {"Stack", "Queue", "Array", "Linked list"}, 3};



    addQuestion(&quiz, question1, &numQuestions);
    addQuestion(&quiz, question2, &numQuestions);
    addQuestion(&quiz, question3, &numQuestions);
    addQuestion(&quiz, question4, &numQuestions);
    addQuestion(&quiz, question5, &numQuestions);

    addPlayer(&quiz, "Player1", &numPlayers);
 

    runQuizSession(&quiz, numQuestions, numPlayers);

    return 0;
}