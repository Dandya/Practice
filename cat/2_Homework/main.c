#include "mem.c"
int main(int argc, char* argv[]) 
{
  //mallopt( MALLOC_CHECK_ , 0); 
  //mtrace();
  

  void* ptr;
  for (int i = 0; i<100; i++)
  {
    ptr = new(1000);
    printf("%lld\n", ptr);
  }
  //free(ptr);
  getchar();
}