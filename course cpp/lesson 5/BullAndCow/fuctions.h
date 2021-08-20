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
 * * Function compares two bytes from word1 and word2 and returns bull or cow on RU language
 * ! Russian symbol has size of two bite
 */
const int searchBullOrCowRU(char byte1, char byte2, int indexSimbol, std::string word2)
{
    for(int index = 0; index < word2.length()-1; index += 2)
    {
        if(byte1 == word2[index] && byte2 == word2[index + 1] && indexSimbol != index)
        {
            return COW;
        }    
        if(byte1 == word2[index] && byte2 == word2[index + 1] && indexSimbol == index)
        {
            return BULL;
        }
    }
    return -1;
} 
//----------------------------------------------------------------
/**
 * searchBullOrCowEN
 * * Function compares char from word1 and word2 and returns bull or cow on EN language
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
 * compareWords
 * * Function compares two words and changes count bulls and cows on EN language
 */
const void compareWords(std::string word1, std::string word2, 
        int* countBulls, int* countCows, int language)
{
    int result;
    if(language == LANGUAGE_EN)
    {
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
    else // LANGUAGE_RU
    {
        for(int index = 0; index < word1.length()-1; index+=2) // not look '\0'
        {
            result = searchBullOrCowRU(word1[index],word1[index+1],index,word2);
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
    
}
//********Work with dictionary*************
#define EASY 0
#define NORMAL 1
#define HARD 2
/**
 * isTrueDifficultyLevel
 * * Fuction checks word is true for a difficulty level
 */
bool isTrueDifficultyLevel(int difficultyLevel, int lengthWord, int language)
{
    if (language == LANGUAGE_EN)
    {
        switch(difficultyLevel)
        {
            case EASY: if(lengthWord <= 5 && lengthWord >= 4) return true; break;
            case NORMAL: if(lengthWord <= 7 && lengthWord >= 6) return true; break;
            case HARD: if(lengthWord <= 9 && lengthWord >= 8) return true; break;
        }
    }
    else // LANGUAGE_RU ! Russian symbol has size of two bite
    {
        switch(difficultyLevel)
        {
            case EASY: if(lengthWord <= 10 && lengthWord >= 8) return true; break;
            case NORMAL: if(lengthWord <= 14 && lengthWord >= 12) return true; break;
            case HARD: if(lengthWord <= 18 && lengthWord >= 16) return true; break;
        }
    }
    return false;
}
//-------------------------------------------------------------
#define DICTIONARY_MAX_RU 67774
#define DICTIONARY_MAX_EN 1775
std::string randomWord(int difficultyLevel, int language)
{
    /*std::random_device rd; // need for random number 
    std::mt19937 mersenne(rd()); // initialization algorithm by Mersenne */
    std::ifstream dictionary;
    int maxWords {0};
    if(language == LANGUAGE_EN)
    {
        dictionary.open("./dictionary/engwords.txt");
        maxWords = DICTIONARY_MAX_EN;
    }
    else //LANGUAGE_RU
    {
       dictionary.open("./dictionary/ruwords.txt"); 
       maxWords = DICTIONARY_MAX_RU;
    }
    std::string word; 
    srand(time(0));
    for(int index = rand()%maxWords; index >= 0; index--) // go to random word
    {
        std::getline(dictionary, word);
    }
    dictionary.close();
    if(isTrueDifficultyLevel(difficultyLevel, word.length(), language))
    {
        return word;
    }
    return randomWord(difficultyLevel,language);
    
}
//*****************************************
#endif 