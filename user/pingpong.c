#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p[2];
	pipe(p);//check dead lock problem
	if(fork()==0){
		char rec[1];
		if(read(p[0],rec,1)!=1)
		{	
			printf("parent->child READ ERROR");
			exit(1);
		}
		printf("%d: received ping\n",getpid());
		if(write(p[1],rec,1)!=1)
		{
			printf("child->parent WRITE ERROR");
			exit(1);
		}
		exit(0);
	}
	else{
		char rec[1]={'a'};
		if(write(p[1],rec,1)!=1)
		{
			printf("parent->child WRITE ERROR");
			exit(1);
		}
		wait((int*)0);
		if(read(p[0],rec,1)!=1)
		{	
			printf("child->parent READ ERROR");
			exit(1);
		}
		printf("%d: received pong\n",getpid());
		exit(0);	
	}
	
}
