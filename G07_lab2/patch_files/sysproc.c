#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processInfo.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int
sys_wolfie(void)
{
  
  char wolfie[] = "\
  \n\
..`````..```````````````.....----..````.````......````````......``````````````.......-------------.-\n\
````````..---:.````..:oosyysoooshhhhhyhhhhddhddhhyyo+:-..```````....`````...----...-----..``````````\n\
``.`````....--`...-+yhhmddhhhhhhdhddmdddddhdmhhmmddhhhhyyo+/:-....-.`````..-+/---...:--..```````````\n\
````````..```...:oyyhhdhhhddhhyyhyhhddmmdmmmddhyhhdhhhhdhhhhhhyo/:/...```...::----..--..``````````..\n\
``....```````.:oyyyhddhhhhddhhhyhhhhhdddmmmmmmyhdddddddddddddddhhhyssso/:-:..---:----..````````.....\n\
````````````.+yssyyyyhyhdddhhyyyhhhhhhdddddmNdhhdddhyyhhhyhddyyhhhhyhyyyysooo/::+--.````-+.`.......`\n\
..````````-+yssyyyysohhhhddhhyhhhhhhdhhdhdmmNdhddhsyyyhhddhdyddhhhhhddhdhydhhys+/.```-+ydd....-...``\n\
```````.:oyyysyyyyssyhyyhddhhhhhhhhhhddddddmNNmhsysyddddddddyddhhddhddddhhddhdhhhhysydmmd+..-....```\n\
``````./yhysssyyyssshhhyhddhyyhhhyhhhdhddddNNNdsyyhhmmmmdddhdmdhdmddhsyhmmmmmmdddmmmmmNms-.----...``\n\
````./yhhhyyyyysssoshhhhyhmyyyyhyhhhhhdddmmmNdysyhdmNNNmmmddddddmdmm+oooshmNNmmmmmNNNNNds:.---....``\n\
``.-ohhhhhhhhyyysooshddhhhmhssyyyyyhhhhddmmNmdyhdddmNNmmNmddmmmmmdmd/shs+smmNNmNNNmmNNNdys:.......`.\n\
``-+yhhdddddddhys//sshhhdddhssssyyyhhhhdddmmmdhddddmNmmmNdhdmmmmmddm/ohhssmNNNNmNNNmmmdddho-..`..`..\n\
``-oydmmmmmmdho:-.:ssyhhddddssyyyhyhyhhhddmmmdhddddmmdmmmhdddmmdddddysddmdmmmmNNNNNNmmmddhhy/.```...\n\
`./ohmmmmdhs:-.```-soyyydddhyosyyhyyhhhhddmmmhhdddddddddhhdhdddhddddddmmmdmmmmNNNNNNmmmmddddy:`..``.\n\
`.-oyhhyo/:.``````-ssssyddhyyoosyyyhhhhhhhdmhyhhdmddddhhyydhhhhdddhhhdmmddmmmmmmNmmmNmdddddhds.`````\n\
``-::/:-.`````````-ososhddhyys+osyyhhhhhhhddhyyhdmddddddssyyhhdhdhyhddddddddmmmddmNmNddmddhhh/..````\n\
``````````````````.+ssyhhhhhhho+oosyhhhhhhhyyyyhdmddddhhsssyyyyhdyhdmdddddddmddddNNNdyhdddso/..`````\n\
```````````````````:yyyyhhhhhhs+++osyyyhhdyooyhhdmmdddhhhhddhyyyhydmddhyhhhddmmhsdmmdhmdhy:.`..`````\n\
```````````````````./yhhhhhyhyo+///+osyyhdy++oyddmmhdddhhddddyyyhhhhyso//shhyhddyhdddhddh+-.`..`````\n\
`````````````````````.yhyyyyss+//:.-:/+osyysooyddddhyhyyhhddhhyyhhhhyo///osyhddhhhdmdhdh+.`....`````\n\
`````````````````````.oyyyyhs+/:-.``.:++oooosoosddhhyssyyyhddhhhhhhddyo//+///oshhhddhhho.......`````\n\
`````````````````````/soosys+/-``````-+++++++++/yddhyys+/osyyhdddhhhhhhyoo+/://syyhdhhy+.`..````````\n\
````````````````````.so///:-.````````.++++++/:`.+shdhhyo:///+oosyyhhhdhhhyso+syysshdddho:.....``````\n\
````````````````````:o+//-```````````:o++o+/-``./osyhhhyo:::////+ossssyyysssoshd++ydmmds:```````````\n\
````````````````````o+///.``````````.++++o/.````:ossyyyy/``....-:/ossoo++oshyssys/ymNmdo.```````````\n\
```````````````````.+//++.`````````.++++++.`````.+oossss-````````.:+sssssyyhy+-:shdmd:-```........``\n\
````````````````..`-o//++``````````:o++++:``````./++osss.`````````.:+ooooooyy+``./++-````.......````\n\
```````````````````-+//++.`````.```-++o++-```````:/+ossy-``..```````-/++o++sh+````````````..````....\n\
`````````````````.:/+/+++-`````````./+oo+-````...-/++osy+.......`````./+++++ho``````````............\n\
`````.```````````.:///++/..`....````./+o+/.`......-/++oys....---.`````.:/+++sh-.`````````````...````\n\
`````````````````./o++//.```.........-/+++:.``...../+++oy-```....``..``.//+++s+`````````````.......`\n\
.````````.`.......-:+/-................/+++:.......:++/++:.......`......-//++o+..`.........`........\n\
......................................../+++/-.....:+++++/...............-/++o+-....``...```.....```\n\
.............--.-----------..-..-..---.-:+++++++:-..:+++++:..............-/++++:`................```\n\
............--------------------:::::::/+o+osyooyo:--+++++/:.............:+++++-....................\n\
........-----.--------------------:--::::-:::::///:--/+++++/-------.....-+s++//.........--........--\n\
........-----....------------------------------------/++oo+++//:------..:oo+///.........---.........\n\
...-.............---------------------------------:-/os+ohsosyso:-------:++++//.....................\n\
.......--...........------------------------:::::--::::/+o+//+::-------:++++//:-...........----.--..\n\
.............................................................-....--------.........................`\n\
  \n\
  ";

  const uint len = 3750;
  void *buf;
  uint size;  
  if ((argptr(0, (void*)&buf, sizeof(*buf)) < 0) || (argint(1, (int*)&size) < 0))
    return -1;
  if (size < len)
    return -1;
  memmove(buf, wolfie, len);
  return len;
}

int
sys_getNumProc(void)
{
  return getNumProc();
}

int
sys_getMaxPid(void)
{
  return getMaxPid();
}

int
sys_getProcInfo(void)
{
	int pid;
	struct processInfo* p;
	argint(0,(int*)&pid);
	argint(1,(int*)&p);
	return getProcInfo(pid,p);
} 

int
sys_get_burst_time(void)
{
	return get_burst_time();
}

int
sys_set_burst_time(void)
{
	int n;
	argint(0,(int*)&n);
	if(n<1||n>20) return -1;
	else {set_burst_time(n);
	return 0;}
}

int
sys_cps(void)
{
  return cps();
}

int
sys_chbrst(void)
{
  int pid, bursts;
  argint(0, &pid);
  argint(1, &bursts);
  return chbrst(pid, bursts);
}
