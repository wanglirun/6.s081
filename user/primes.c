#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	char prime[1];
	int p[2];
	pipe(p);
	if(fork()==0){
		close(p[1]);
		while(read(p[0],prime,1)!=0)
		{
			printf("prime %d\n",prime[0]);
			int divider=prime[0];
			char arr[35];
			int i=0;
			while(read(p[0],prime,1)!=0)
				if((int)prime[0]%divider!=0) 
					arr[i++]=prime[0];
			close(p[0]);
			pipe(p);
			for(int j=0;j<i;++j){
				if(write(p[1],arr+j,1)!=1){
					printf("write error");
					exit(1);
				}
			}
			close(p[1]);
			if(fork()==0) continue;
			else {
				close(p[0]);
				wait(0);
				exit(0);
			}	
		}
					
	}	
	else{
		char arr[1];
		for(int i=2;i<=35;++i){
			arr[0]=i;
			if(write(p[1],arr,1)!=1){
				printf("write error");
				exit(1);
			}
		}
		close(p[1]);
		wait(0);
		exit(0);
	}
	exit(0);			
}
