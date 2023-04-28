#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
char* tranverse(char *file){
	char *p=file+strlen(file);
	while(*p!='/'&&p>=file)
		--p;
	++p;
	return p;
}
void find(char *root,char *filename){
	char buf[512],*p;
	struct dirent de;
	struct stat st;
	int fd;
	
	if((fd=open(root,0))<0){
		printf("find:can't open file:%s\n",root);
		return ;
	}
	if(fstat(fd,&st)!=0){
		printf("find:can't stat file:%s\n",root);
		close(fd);
		return ;
	}
	if(strcmp(filename,tranverse(root))==0)
		printf("%s\n",root);
	if(st.type==T_DIR){
		//printf("%s is a directory\n",root);
		if(strlen(root)+1+DIRSIZ+1>sizeof(buf))
		{
			printf("root too long");
			return ;
		}
		strcpy(buf,root);
		p=buf+strlen(buf);
		*p++='/';
		while(read(fd,&de,sizeof(de))==sizeof(de)){
			if(de.inum==0||strcmp(de.name,".")==0
			||strcmp(de.name,"..")==0) continue;
			memmove(p,de.name,DIRSIZ);
			find(buf,filename);
		}	
	}
	close(fd);
	return ;
	
}

int
main(int argc, char *argv[])
{

	if(argc!=3)
	{
		printf("ARGUMENTS ERROR!");
		exit(0);
	}
	find(argv[1],argv[2]);
	exit(0);

}
