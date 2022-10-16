#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float numberOfWords(string text);
float numberOfLetters(string text);
float numberOfSentences(string text);
int colemanLiau(float words, float letters, float sentences);

int main() {

    //prompts user for their string
    string text = get_string("Text: ");

    float words = numberOfWords(text);
    float letters = numberOfLetters(text);
    float sentences = numberOfSentences(text);
    if (colemanLiau(words, letters, sentences) < 1) {
        printf("Before Grade 1\n");
        return 0;
    }
    if (colemanLiau(words, letters, sentences) >= 16) {
        printf("Grade 16+\n");
        return 0;
    }
    if (colemanLiau(words, letters, sentences) >= 1 || colemanLiau(words, letters, sentences) < 16) {
        printf("Grade %i\n", colemanLiau(words, letters, sentences));
        return 0;
    }


}

int colemanLiau(float words, float letters, float sentences) {

    float per100 = words/100.0;
    letters = letters / per100;
    sentences = sentences / per100;
    float grade = (0.0588 * letters) - (0.296 * sentences) - 15.8;
    return round((0.0588 * letters) - (0.296 * sentences) - 15.8);
}

float numberOfWords(string text) {

    int sumOfWords = 0;
    //iterating through every character
    for (int i = 0, n = strlen(text); i < n; i++) {
        //32 stands for a space
        if (text[i] == 32) {
            sumOfWords += 1;
        }
    }
    //since there is one less space than the entire sum of numbers, add one
    sumOfWords += 1;
    return sumOfWords;
}

float numberOfLetters(string text) {

    int sumOfLetters = 0;
    //iterating through every character
    for (int i = 0, n = strlen(text); i < n; i++) {
        //65-90, 97-122 stands for letters
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122)) {
            sumOfLetters += 1;
        }
    }
    return sumOfLetters;
}

float numberOfSentences(string text) {

    int sumOfSentences = 0;
    //iterating through every character
    for (int i = 0, n = strlen(text); i < n; i++) {
        //33 = exclamation point, 63 = question mark, 46 = period
        if (text[i] == 33 || text[i] == 63 || text[i] == 46) {
            sumOfSentences += 1;
        }
    }
    return sumOfSentences;
}