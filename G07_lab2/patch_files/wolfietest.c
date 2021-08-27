#include "types.h"
#include "user.h"

int wolfie(void*,uint);

int
main(int argc, char *argv[])
{
  uint size;
  if(argc < 2){
    size = 3750;
  } else {
    size = atoi(argv[1]);
  }
  void* buffer=malloc(size);
  if (wolfie(buffer, size) != -1)
    printf(1, "%s", buffer);
  else printf(1,"-1");
  exit();
}
