#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  const int n=atoi(argv[1]);

  if(n <= 0){
    printf(2, "Burst time must be +ve\n");
  } else {
    set_burst_time(n);
    printf(1,"Burst time set to %d\n", n);
  }
  exit();
}
