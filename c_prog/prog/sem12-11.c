int dup(int fd);
int dup2(int fd, int fd1);

int fd=open("file", O_RDONLY);
int fd1=dup(fd);
read(fd, s, 4);
read(fd1, s, 4);

close(0);
int fin=dup(fd);

int f2=open("file", O_WRONLY);
int fout=dup2(f2, 1);
close(f2);

int pipe(int fd[2]);
    int fd[2]; // fd[0] - чтение  fd[1] - запись
    pipe(fd); 
    