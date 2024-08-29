#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]){

	char line[MAX_LINE_LENGTH];
	char *new_argv[MAXARG];
	int i, n;

	for(i = 1; i < argc; i++){
		new_argv[i-1] = argv[i];
	}

	if((n = read(0, &line, sizeof(line))) > 0){

		//remove Newline
		if(line[n-1] == '/'){
			line[n-1] = 0;
		}
		else{
			line[n] = 0;
		}


		//link line to new_argv
		new_argv[argc-1] = line;
		new_argv[argc] = 0;
	}
	else{
		printf("xargs: read error");
	}

	if(fork() == 0){
		exec(new_argv[0], new_argv);
		exit(0);
	}
	else{
		wait(0);
	}
	exit(0);
}