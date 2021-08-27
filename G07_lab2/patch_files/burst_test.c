#include "types.h"
#include "user.h"

int main(void){
  printf(1, "setting burst time to 2\n");
  set_burst_time(2);
  printf(1, "New burst time = %d\n", get_burst_time());
  cps();
  exit();
}
