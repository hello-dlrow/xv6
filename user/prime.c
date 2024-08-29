#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int* filter(int* inputarray){

	int i = 0;
	int j = 0;
	int PRIME;
	static int outputarray[40];

	PRIME = inputarray[i];
	i++;
	printf("PRIME:%d\n", PRIME);

	while(i < 40){
		if(inputarray[i] % PRIME != 0){
			outputarray[j] = inputarray[i];
			j++;
		}
		i++;
	}

	return outputarray;
}

int main(int argc, char *argv[]){
	// 父进程
	int p[2];

	pipe(p);

	// 创建子进程
	if(fork() == 0){
		int upstream[40];
		int* downstream;

		close(p[1]); // 关闭写端

		// 读取完整的数组
		read(p[0], upstream, sizeof(upstream));

		close(p[0]); // 关闭读端


		downstream = filter(upstream);

		int p1[2];
		pipe(p1);	//创建与孙子进程的管道

		//创建孙子进程
		if(fork() == 0){


			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			downstream = filter(downstream);
			exit(0);

		}
		else{
			close(p1[0]);

			write(p1[1], downstream, sizeof(downstream));

			close(p1[1]);

			wait(0);
			exit(0);
		}




	}
	else{
		int i;
		int j = 0;
		int downstream[40]; // 将数组大小调整为合适的大小

		close(p[0]); // 关闭读端

		// 初始化数组
		for(i = 2; i <= 35; i++){
			downstream[j] = i;
			j++;
		}

		// 向管道写入整个数组
		write(p[1], downstream, sizeof(downstream));

		close(p[1]); // 关闭写端

		wait(0); // 等待子进程完成
	}
	printf("main exit sucess");
	exit(0);
}
