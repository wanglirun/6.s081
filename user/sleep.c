#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	if(argc<=1){
		printf("ERROR!Please input the ticks number");
		exit(0);
	}
	if(argc>=3){
		printf("Too many arguments!");
		exit(0);
	}
	int num=atoi(argv[1]);
	int status=sleep(num);
	if(status==-1)
		printf("SLEEP ERROR!");
	exit(0);	
}
