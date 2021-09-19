#include <dlfcn.h>
#include <stdio.h>


int main(int argc, char** argv)
{
    char* handle;
    char* (*pushkin)(char* text);
    char *nLines = NULL;
    //char *nplus1Lines = NULL;
    if(argc > 1) 
    {
        for(int i = 1; i < argc; i++)
        {
            handle = dlopen(argv[i], RTLD_LAZY);
            if(handle == NULL)
            {
                fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
	            return -1;
            }
            pushkin = (char* (*)(char*)) dlsym(handle, "pushkin");
            if(pushkin != NULL)
            {
                nLines = pushkin(nLines);
            }
            else 
            {
	            fprintf(stderr, "Ошибка получения функции: %s\n", dlerror());
            }
            dlclose(handle);
        }
    }
    else
    {
        printf("Ошибка отсутствия библиотек\n");
    }
    printf("%s", nLines);
    return 0;
}