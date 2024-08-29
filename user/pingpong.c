


int main(int argc, char *argv[])
{
int p1[2];                     // 创建一个整型数组用于存储管道的文件描述符
int p2[2];


pipe(p1);                      // 创建一个管道
pipe(p2);

if (fork() == 0) {            // 创建子进程
	char buf1[512];
	close(0);
	dup(p1[0]);				//将标准输入对接到管道读端
	close(p1[0]);			//关闭管道1的文件描述符，使其唯一对接标准输入
	read(0, buf1, sizeof buf1);

	printf("child: (%d) recived: %s\n", getpid(), buf1);

    strcpy(buf1, "pong");
    write(p2[1], buf1, sizeof buf1);
    close(p2[1]);

    
} else {				// 父进程
	char buf2[512];
	strcpy(buf2, "ping");                      
	close(p1[0]);		// 关闭管道读端
	write(p1[1], buf2, sizeof buf2);
	close(p1[1]);		// 关闭写端
	wait((int *) 0);	//等待子进程结束

	close(0);
	dup(p2[0]);
	close(p2[0]);
	read(0, buf2, sizeof buf2);

	printf("(father: %d) recived: %s\n", getpid(), buf2);


}
}