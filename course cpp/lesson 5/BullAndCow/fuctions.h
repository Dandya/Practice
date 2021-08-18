#include <iostream>
#include <fstream>
#include <random> // для std::random_device и std::mt19937
#ifndef BULL_AND_COW_H
#define BULL_AND_COW_H
//*********Work with words************
/**
 * inputWord
 * * Function returns input word it was written by user
 */
const std::string inputWord()
{
    std::cout << "->  ";
    std::string input;
    std::cin >> input;
    return input;
}
//----------------------------------------------------------------
#define LANGUAGE_RU 1
#define LANGUAGE_EN 0
#define BULL 1
#define COW 0
/**
 * searchBullOrCowRU
 * * Function compares char16_t from word1 and returns bull or cow on RU language
 */
const int searchBullOrCowRU(char16_t symbol,int indexSimbol,std::u16string word2)
{
    for(int index = 0; index < word2.length(); index++)
    {
        if(symbol == word2[index] && indexSimbol != index)
        {
            return COW;
        }    
        if(symbol == word2[index] && indexSimbol == index)
        {
            return BULL;
        }
    }
    return -1;
} 
//----------------------------------------------------------------
/**
 * searchBullOrCowEN
 * * Function compares char16_t from word1 and returns bull or cow on EN language
 */
const int searchBullOrCowEN(char symbol,int indexSimbol, std::string word2)
{
    for(int index = 0; index < word2.length(); index++)
    {
        if(symbol == word2[index] && indexSimbol != index)
        {
            return COW;
        }    
        if(symbol == word2[index] && indexSimbol == index)
        {
            return BULL;
        }
    }
    return -1;
} 
//----------------------------------------------------------------
/**
 * compareWordsRU
 * * Function compares two words and changes count bulls and cows on RU language
 */
const void compareWordsRU(std::u16string word1, std::u16string word2,
        int* countBulls, int* countCows)
{
    int result;
    for(int index = 0; index < word1.length()-1; index++) // not look '\0'
    {
        result = searchBullOrCowRU(word1[index],index, word2);
        if (result == BULL)
        {
            (*countBulls)++;
        }
        else if (result == COW)
        {
            (*countCows)++;
        }
    }
}
//----------------------------------------------------------------
/**
 * compareWordsEN
 * * Function compares two words and changes count bulls and cows on EN language
 */
const void compareWordsEN(std::string word1, std::string word2, 
        int* countBulls, int* countCows)
{
    int result;
    for(int index = 0; index < word1.length()-1; index++) // not look '\0'
    {
        result = searchBullOrCowEN(word1[index],index, word2);
        if (result == BULL)
        {
            (*countBulls)++;
        }
        else if (result == COW)
        {
            (*countCows)++;
        }
    }
}
//********Work with dictionary*************
#define EASY 0
#define NORMAL 1
#define HARD 2
/**
 * isTrueDifficultyLevel
 * * Fuction checks word is true for a difficulty level
 */
bool isTrueDifficultyLevel(int difficultyLevel, int lengthWord)
{
    switch(difficultyLevel)
    {
        case EASY: if(lengthWord <= 4 && lengthWord >= 3) return true; break;
        case NORMAL: if(lengthWord <= 6 && lengthWord >= 5) return true; break;
        case HARD: if(lengthWord <= 8 && lengthWord >= 7) return true; break;
    }
    return false;
}
//-------------------------------------------------------------
std::string randomWordEN(int difficultyLevel)
{
    std::random_device rd; // need for random number 
    std::mt19937 mersenne(rd()); // initialization algorithm by Mersenne 
    ifstream dictionary;
    dictionary.open("./dictionary/engwords.txt");
    std::string word; 
    for(int index = mersenne(rd()); index >= 0; index--) // go to random word
    {
        getline(dictionary, word);
    }
}
//*****************************************
#endif 