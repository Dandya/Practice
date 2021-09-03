#ifdef CLI_H
/**
 * chooseCountUsers
 * * Function returns count users who will be to play
 * ! add second player
 */
int chooseCountUsers() 
{
    std::cout << "Choose count of users:" << std::endl;
    std::cout << "1) One;" << std::endl;
    std::cout << "2) Two(not supported)." << std::endl;
    clearInputBuffer();
    int count {0};
    std::cout << "-> ";
    std::cin >> count;
    while( count < 1 || count > 1 )
    {
        std::cout << "Unknown mode!" << std::endl;
        std::cout << "Please, input again" << std::endl << "-> ";
        std::cin >> count;
    }
    return count; 
}
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
    clearInputBuffer();
    int level {0};
    std::cout << "-> ";
    std::cin >> level;
    while( level < 1 || level > 3 )
    {
        std::cout << "Unknown level!" << std::endl;
        std::cout << "Please, input again" << std::endl << "-> ";
        std::cin >> level;
    }
    return level-1; // because constants start with 0
}
/**
 * chooseMod
 * * Function returns mode of game
 */
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
}
/**
 * startGame
 * * Function begins game
 */
int startGame()
{
    std::cout << "\tThe Bulls and Cows" << std::endl;
    int mode, difficultyLevel, countUsers;
    mode = chooseMod();
    difficultyLevel = chooseDifficultyLevel();
    countUsers = chooseCountUsers();
    int result {0};
    if(countUsers == 1)
    {
        result = simpleGame(mode, difficultyLevel);
    }
    return result;
}
#endif