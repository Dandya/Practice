//Choose interface:
#define CLI_H
// or
#define WSI_H
// ! And delete last
#include "functions.h"
#include "cli.h"
//----------------------------------------------------------------
int main()
{
    int result {0};
    result = startGame();
    return result;
}