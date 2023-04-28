#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//#include "param.h"
int
main(int argc, char *argv[])
{

	char buf[512];
	char *p=buf;
	while(read(0,p,1)==1)
	{
		if(*p=='\n')	*p='\0';
		++p;
	}
	char *a=buf;
	while(a<=p){
		//printf("%s",a);
		if(fork()==0){
			char *myargs[argc+1];
			//printf("%d\n",argc);
			for(int i=0;i<argc-1;++i){
				myargs[i]=argv[i+1];
				//printf("%s\n",myargs[i]);
			}
			myargs[argc-1]=a;
			myargs[argc]='\0';
			exec(myargs[0],myargs);
			exit(0);
		}
		else	wait(0);
		a=a+strlen(a)+1;
	}
	exit(0);
}
