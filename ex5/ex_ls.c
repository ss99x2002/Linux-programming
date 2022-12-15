#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>
#include <sys/sysmacros.h>

int flag_a,flag_l,flag_R = 0;

void list(const char * dir_path)
{
	DIR* dirp;
	struct dirent * entry;

	if ((dirp=opendir(dir_path))==NULL) {
		perror("Directory cannot be opened\n");
	}

	while((entry=readdir(dirp))!=NULL) {
		if (flag_a|entry->d_name[0]!='.')
			printf("%-15s\t", entry->d_name);
	}
	printf("\n");
	closedir(dirp);
}
void list_long(const char* dir_path) {
	DIR * dirp;
	struct dirent*entry;
	struct stat buf;
	char prev_dir[512];
	static short octarray[9] = {0400, 0200, 0100, 0040, 0020, 0010, 0004, 0002, 0001};
	static char perms[10] = "rwxrwxrwx";
	char descrip[10];

	if (getcwd(prev_dir,512)==NULL) perror("getcwd error");
	if ((dirp=opendir(dir_path))==NULL) perror("Directory open error");
	if (chdir(dir_path) != 0 ) perror ("chdir error");
	while ((entry = readdir(dirp))!=NULL) {
		if (flag_a|entry->d_name[0] !='.'){
			if (stat(entry->d_name,&buf)==-1) continue;
			switch((buf.st_mode & 0170000))
			{
				case 0010000:
					descrip[0] ='p';
					break;
				case 0020000:
					descrip[0] = 'c';
					break;
				case 0040000:
					descrip[0]= 'd';
					break;
				case 0060000:
					descrip[0]='b';
					break;
				case 0100000:
					descrip[0] ='-';
					break;
				case 0120000:
					descrip[0]='l';
					break;
			}
			for (int j=1; j<10; j++)
			{
				if (buf.st_mode & octarray[j])
					descrip[j]=perms[j];
				else 
					descrip[j]='-';
			}
			descrip[9] = '\0';
			printf("%3s\t",descrip);		
			printf("%3ld\t", buf.st_nlink);
			printf("%6d\t",buf.st_uid);
			printf("%6d\t",buf.st_gid);
			if ((buf.st_mode & 0170000) == 0020000)
			{
				printf("%6u, %6u\t",major(buf.st_rdev), minor(buf.st_rdev));
			}
			else
			{
				printf("%12ld\t",buf.st_size);
			}
			printf("%-15s\t\n",entry->d_name);
		}
	}
	closedir(dirp);
	chdir(prev_dir);
}

int list_recursive(const char * path, const struct stat *buf, int type) {
	if (type == FTW_D) {
		printf("%s:\n",path);
		if (flag_l) list_long(path);
		else list(path);
		printf("\n");
	}
	return 0;
}
int main(int argc,char * argv[]){
	int opt;
	while ((opt = getopt(argc,argv,"alR"))!= -1) {
		switch(opt) {
			case 'a':
				flag_a = 1;
				break;
			case 'l':
				flag_l = 1;
				break;
			case 'R':
				flag_R = 1;
				break;
			default:
				printf("Wrong usage\n");
				return -1;
		}
	}

	if(argc-optind == 0){ 
		if (flag_R) ftw("./",list_recursive,10);
		else if (flag_l) list_long("./");
		else list("./");}
	else if (argc-optind == 1){
		if (flag_R) ftw(argv[optind],list_recursive,10);
		else if (flag_l) list_long(argv[optind]);
		else list(argv[optind]);
	}
	else{
		for(int i=optind; i<argc; i++){
			printf("%s:\n",argv[i]);
			if (flag_R) ftw(argv[i],list_recursive,10);
			else if (flag_l) list_long(argv[i]);
			else list(argv[i]);
			printf("\n");
		}
	}
	
}
