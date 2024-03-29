#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WR 1

int 
main(int argc, const char *argv[])
{
  char buf = 'P';

  int fd_c2p[2];
  int fd_p2c[2];
  pipe(fd_c2p);
  pipe(fd_p2c);

  int pid = fork();
  
  if (pid < 0) {
    fprintf(2, "fork() error\n");
    close(fd_c2p[RD]);
    close(fd_c2p[WR]);
    close(fd_p2c[RD]);
    close(fd_p2c[WR]);
    exit(1);
  } else if (pid == 0) { //children
    close(fd_p2c[WR]);
    close(fd_c2p[RD]);

    if (read(fd_p2c[RD], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "Child read() error!\n");
      exit(1);
    } else {
      fprintf(1, "%d: received ping\n", getpid());
    }
    
    if (write(fd_c2p[WR], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "child write() error\n");
      exit(1);
    }

    close(fd_p2c[RD]);
    close(fd_c2p[WR]);

    exit(0);
  } else { // parent
    close(fd_p2c[RD]);
    close(fd_c2p[WR]);

    if (write(fd_p2c[WR], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "parent write() error!\n");
      exit(1);
    } 
    if (read(fd_c2p[RD], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "parent read() error\n");
      exit(1);
    } else {
      fprintf(1, "%d: received pong\n", getpid());
    }

    close(fd_p2c[WR]);
    close(fd_c2p[RD]);

    exit(0);
  }

}
