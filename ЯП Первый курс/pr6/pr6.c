#include <malloc.h>
/*********************************************************/
struct brackets
{
	char bracketType;
	struct brackets* nextBracket;
	struct brackets* lastBracket;
};
/*********************************************************/
int comparisonBrackets(char openBracket, char closeBracket)
{
	if(openBracket == '{' &&  closeBracket == '}')
	{
		return 1;
	}
	if(openBracket == '[' && closeBracket == ']')
	{
		return 1;
	}
	if(openBracket == '(' && closeBracket == ')')
	{
		return 1;
	}
	return 0;
}
/*********************************************************/
int correctBrackets(char* str)
{
	if(str == NULL)
	{
		return -1;
	}
	int indexOpenBracket = -1;
	int indexChar = 0;
	struct brackets nullBracket;
	nullBracket.bracketType = '\0';
	struct brackets * nowBracket = &nullBracket ;	
	while(str[indexChar] != '\0')
	{
		if(str[indexChar] == '{' || str[indexChar] == '[' || str[indexChar] == '(')
		{
			struct brackets * pastBracket = nowBracket;
			nowBracket = (struct brackets *)malloc(1*sizeof(struct brackets));
			if(nowBracket == NULL)
			{
				return -1;
			}
			nowBracket->bracketType = str[indexChar];
			pastBracket->nextBracket = (struct brackets *)nowBracket;
			nowBracket->lastBracket = pastBracket;
			indexOpenBracket++;
		}
		else if(str[indexChar] == '}' || str[indexChar] == ']' || str[indexChar] == ')')
		{
			if(comparisonBrackets(nowBracket->bracketType, str[indexChar]))
			{
				struct brackets * buff = nowBracket; 
				nowBracket = nowBracket->lastBracket;
				free(buff);
				indexOpenBracket--;
			}
			else
			{
				return 0;
			}
		}
		indexChar++;
	}
	if(indexOpenBracket == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*********************************************************/
