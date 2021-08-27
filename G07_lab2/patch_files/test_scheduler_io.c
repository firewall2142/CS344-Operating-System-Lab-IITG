#include "types.h"
#include "user.h"


const double workmult = 20000.0;

int
main(int argc, char *argv[])
{

  set_burst_time(1);

//  cps();

  int numforks = 10;
  int work = 100;
  

  if(argc >= 2)
    numforks = atoi(argv[1]);
  
  if(argc >= 3)
    work = atoi(argv[2]);
  

  int id = 0;
  int burstitr = numforks + 2;
  double dummy=0; // variable to waste cpu time


  for(int itr=0; itr < numforks; itr++){
    id = fork();
    if(id < 0) {
      printf(2, "fork failed! (returned %d)\n", id);
    }
    else if(id == 0){
      // child process
      // do some work
      // printf(1, "Setting burst time = %d\n", burstitr);
      // set_burst_time(burstitr);


      for(dummy = 0; dummy < workmult*work*burstitr; dummy += 0.23*4.32);
//      printf(1,"Child %d created\n",getpid());
//      for(int i=0; i<10;i++) sleep(10);
      char arr[6] = "Direc";
      arr[5] = (char)(itr%10)+48;
      mkdir(arr);

      break;

    } 
    else {
      if(chbrst(id, burstitr) == -1)
        printf(1, "pid = %d not found!\n", id);

      printf(1,"Parent %d creating child id = %d with burst = %d\n",getpid(), id, burstitr);

//      burstitr--;
      burstitr = (burstitr*4 + 1) % 19;
      // parent
      // cps();

      // printf(1, "Waiting for child %d to finish\n", id);

      // wait for the child to finish
      // wait();
    }
  }
	printf(1, "Current ptable state:\n");
	cps();
  // wait for the children to finish
  while(wait() != -1);


  printf(1, "finished: burst = %d\n", get_burst_time());
  exit();

}
