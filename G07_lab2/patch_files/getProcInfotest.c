#include "types.h"
#include "user.h"
#include "processInfo.h"

int getProcInfo(int,struct processInfo *p);

int
main(int argc, char *argv[])
{
  const int pid = atoi(argv[1]);
  struct processInfo *p= malloc(sizeof(struct processInfo));
  if (getProcInfo(pid,p) != -1){
    printf(1,"Parent Pid: %d", p->ppid);
    printf(1," Process size in bytes: %d", p->psize);
    printf(1," Number of Context switches: %d", p->numberContextSwitches);}
  else printf(1,"No process Found");
  exit();
}
