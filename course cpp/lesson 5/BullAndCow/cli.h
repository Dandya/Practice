#ifdef CLI_H
/**
 * chooseCountUsers
 * * Function returns count users who will be to play
 * ! add second player
 *
int chooseCountUsers() 
{
    std::cout << "Choose count of users:" << std::endl;
    std::cout << "1) One;" << std::endl;
    std::cout << "2) Two(not supported)." << std::endl;
    int count {0};
    std::string numStr = inputStr();
    if(numStr == "exit")
    {
        exit(2);
    }
    count = atoi(numStr.c_str());
    while( count < 1 || count > 1 )
    {
        std::cout << "Unknown mode!" << std::endl;
        std::cout << "Please, input again" << std::endl;
        numStr = inputStr();
        if(numStr == "exit")
        {
            exit(2);
        }
        count = atoi(numStr.c_str());
    }
    return count; 
}*/
/**
 * chooseDifficultyLevel
 * * Function returns difficulty level
 */
int chooseDifficultyLevel()
{
    std::cout << "Choose difficulty level(number):" << std::endl;
    std::cout << "1) Easy;" << std::endl;
    std::cout << "2) Normal;" << std::endl;
    std::cout << "3) Hard." << std::endl;
    int level {0};
    std::string numStr = inputStr();
    if(numStr == "exit")
    {
        exit(2);
    }
    level = atoi(numStr.c_str());
    while( level < 1 || level > 3 )
    {
        std::cout << "Unknown level!" << std::endl;
        std::cout << "Please, input again" << std::endl;
        numStr = inputStr();
        if(numStr == "exit")
        {
            exit(2);
        }
        level = atoi(numStr.c_str());
    }
    return level-1; // because constants start with 0
}
/**
 * chooseMod
 * * Function returns mode of game
 *
int chooseMod()
{
    std::cout << "Choose mode(number):" << std::endl;
    std::cout << "1) English;" << std::endl;
    std::cout << "2) Russian;" << std::endl;
    std::cout << "3) Digits." << std::endl;
    int mode {0};
    std::cout << "-> ";
    std::cin >> mode;
    while( mode < 1 || mode > 3 )
    {
        std::cout << "Unknown mode!" << std::endl;
        std::cout << "Please, input again" << std::endl << "-> ";
        std::cin >> mode;
    }
    return mode-1; // because constants start with 0
}*/
/**
 * startGame
 * * Function begins game
 */
int startGame()
{
    std::cout << "\tThe Bulls and Cows" << std::endl;
    std::cout << "Input \'exit\' for poweroff this game" << std::endl;
    int difficultyLevel;
    difficultyLevel = chooseDifficultyLevel();
    int result {0};
    result = simpleGame(difficultyLevel);
    std::cout << "Thank you!" << std::endl;
    return result;
}
#endif