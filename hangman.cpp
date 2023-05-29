#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

#define clsr() printf("\033[H\033[J")

const int IGNORE_CHARS = 256;
const int DEFAULT_NUMBER_TRIES = 0;

void PlayGame();
bool WantToPlayAgain();
char GetCharacter(const char * prompt, const char * error);
char GetCharacter(const char * prompt, const char * error, const char inputValid[], const int inputValidLength);
bool IsGameOver(const int numberOfTries, const char * resultPhrase);
bool HasLetterInSecretPhrase(const char * secretPhrase, const char * resultPhrase, const char guessLetter);
void DrawBoard(const int numberOfTries);
void UpdateSecretPhrase(const char * secretPhrase, char * resultPhrase, const char guessLetter);
int findCharIndex(const char * secretNumer, const char c);
void DisplayResult(const int numberOfTries, const char * secretPhrase);
char * MakeHiddenPhrase(const char * phrase);

char * GetSecretPhrase();

int main() {

    do {
        PlayGame();
    } while (WantToPlayAgain());

    return 0;
}

void PlayGame() {
    int numberOfTries = DEFAULT_NUMBER_TRIES;
    const char * secretPhrase = GetSecretPhrase();
    char * resultPhrase = MakeHiddenPhrase(secretPhrase);
    // const char * question = "Where is the capital of Vietnam located?";

    cout << endl;
    DrawBoard(numberOfTries);
    cout << endl;

    do {
        // cout << question << endl;
        cout << "The secret phrase: " << resultPhrase << endl;

        char letter = GetCharacter("Guess the letter you think: ", "Input Error! Please Try Again!");

        if (HasLetterInSecretPhrase(secretPhrase, resultPhrase, letter)) {
            // draw letter in secret phrase UI
            letter = tolower(letter);
            UpdateSecretPhrase(secretPhrase, resultPhrase, letter);            
            cout << "You're correct!" << endl;
        } else {
            // update state
            ++numberOfTries;
            cout << "You didn't got it! Guess Again!" << endl;
        }
        // draw more body for the man
        cout << endl;
        DrawBoard(numberOfTries);
        cout << endl;

    } while (!IsGameOver(numberOfTries, resultPhrase));

    DisplayResult(numberOfTries, secretPhrase);

    delete[] secretPhrase;
    delete[] resultPhrase;

    secretPhrase = nullptr;
    resultPhrase = nullptr;
}

char * GetSecretPhrase() {
    char * secretPhrase = new char[100];
    cout << "Please enter the secet phrase you want: ";
    cin.getline(secretPhrase, 100);

    return secretPhrase;   
}

void DisplayResult(const int numberOfTries, const char * secretPhrase) {
    if (numberOfTries == 6) {
        cout << "The secret phrase is: " << secretPhrase << endl;
    }  else {
        cout << "You got it! The secret phrase is: " << secretPhrase << endl;
    }
}

char * MakeHiddenPhrase(const char * phrase) {
    int nPhrase = strlen(phrase);
    char * hiddenPhrase = new char[nPhrase];

    for (int i = 0; i < nPhrase; ++i) {
        hiddenPhrase[i] = phrase[i] != ' ' ? '-' : ' ';
    }

    return hiddenPhrase;
}

int findCharIndex(const char * phrase, const char c) {
    int n = strlen(phrase);
    
    for (int i = 0; i < n; ++i) {
        if (phrase[i] == c) {
            return i;
        }
    }

    return -1;
}

void UpdateSecretPhrase(const char * secretPhrase, char * resultPhrase, const char guessLetter) {
    int nSecPhrase = strlen(secretPhrase);

    if (guessLetter != '\0') {
        for (int i = 0; i < nSecPhrase; ++i) {
            if (secretPhrase[i] == guessLetter) {
                resultPhrase[i] = guessLetter;
            }
        }
    } 
}

void DrawBoard(int numberOfTries) {
    switch (numberOfTries)
    {
    case 1:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |    " << endl;
        cout << " |    " << endl;
        cout << "-+-   " << endl;

        break;

    case 2:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |   |" << endl;
        cout << " |    " << endl;
        cout << "-+-   " << endl;

        break;
    
    case 3:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|" << endl;
        cout << " |    " << endl;
        cout << "-+-   " << endl;

        break;

    case 4:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|\\" << endl;
        cout << " |    " << endl;
        cout << "-+-   " << endl;

        break;

    case 5:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|\\" << endl;
        cout << " |  / " << endl;
        cout << "-+-   " << endl;

        break;

    case 6:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|\\" << endl;
        cout << " |  / \\" << endl;
        cout << "-+-   " << endl;

        break;
    
    default:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |    " << endl;
        cout << " |    " << endl;
        cout << " |    " << endl;
        cout << "-+-   " << endl;

        break;
    }
}

bool HasLetterInSecretPhrase(const char * secretPhrase, const char * resultPhrase, char guessLetter) {
    int idxGuessLetter = findCharIndex(secretPhrase, guessLetter), 
        idxResultLetter = findCharIndex(resultPhrase, guessLetter);

    return idxGuessLetter != -1 && idxResultLetter == -1;
}

bool IsGameOver(int numberOfTries, const char * resultPhrase) {
    return numberOfTries == 6 || findCharIndex(resultPhrase, '-') == -1;
}

bool WantToPlayAgain() {
    char input;
    bool failure;
    const char validInput[] = { 'y', 'n' };

    input = GetCharacter("Do you want to paly again? (y/n)", "Input Error! Please Try Again!", validInput, 2);

    return input == 'y';
}

char GetCharacter(const char * prompt, const char * error) {
    char input;
    bool failure;

    do {
        failure = false;

        cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            failure = true;
            cout << error << endl;
        } else {
            cin.ignore(IGNORE_CHARS, '\n');

            if (isalpha(input)) {
                input = tolower(input);

                return input;
            } 

            failure = true;
            cout << error << endl;
        }


    } while (failure);

    return input;
}

char GetCharacter(const char * prompt, const char * error, const char inputValid[], const int inputValidLength) {
    char input;
    bool failure;

    do {
        failure = false;

        cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            failure = true;
            cout << error << endl;
        } else {
            cin.ignore(IGNORE_CHARS, '\n');

            if (isalpha(input)) {

                input = tolower(input);

                for (int i = 0; i < inputValidLength; ++i) {
                    if (inputValid[i] == input)
                        return input;
                }

            } 

            failure = true;
            cout << error << endl;
        }


    } while (failure);

    return input;
}
