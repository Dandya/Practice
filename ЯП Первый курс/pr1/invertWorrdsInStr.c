#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*******************************************************************/
void test();
/*******************************************************************/
void invert( char* text, int end)
{
  /*
    Функция инвертирует символы в слове или тексте на промежутке от text[0] 
    до text[end]. Принимает соответственно указатель на массив символов
    text и целое число, обозначающее разность индексов последнего и первого
    индекса в слове или тексте end.
  */
  for(int o = 0; o<=end/2; o++)
  {
    char tmp = text[end-o];
    text[end-o]=text[o];
    text[o]=tmp;
  }
}
/*******************************************************************/
int main()
{
  char text[] = "Hello World!\n(My Name is Sasha)";
  char* newText = (char*)malloc((strlen(text)+1)*sizeof(char));
  int i = 0;
  while (text[i]!='\0')
  {
    newText[i]=text[i];
    i++;  
  }
  newText[i] = text[i];
  printf("%s\n\n", newText);
  int beginWord = 0;
  int process = 0;
  for (int hod = 0; hod<=i; hod++)
  {
    if ((newText[hod]<='Z'&&newText[hod]>='A'||newText[hod]<='z'&&newText[hod]>='a')&&!process)
    {  
      beginWord = hod;
      process = 1;
    }
    else if (!(newText[hod]<='Z'&&newText[hod]>='A'||newText[hod]<='z'&&newText[hod]>='a')&&process)
    {
      invert(newText+beginWord, hod-1-beginWord);
      process = 0;
    }                                                  
  }
  printf("%s\n", newText);
  free(newText);
  return 0;
}
/*******************************************************************/
void test()
{
    char str[30] = {'\0'};
    fgets(str, 30, stdin);
    int x = strlen(str);
    invert(str,x-1);
    printf("\n%s",str);
}


