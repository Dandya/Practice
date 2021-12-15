#include <stdlib.h>
#include <stdio.h>
int main(int argc, char * argv[])
{
    char str[] = "0x000055e37881c8c0";
    void* ptr = (void*)strtoll(str, NULL, 16);
    printf("%lld", ptr);
    return 0;
}94435467708608