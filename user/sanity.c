#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void
task2_test(void){
    int fd;
    char data[1024];

    // fills the data array with 7s
    memset(data, 7, 1024);
    fd = open("sanity_check_file", O_CREATE | O_RDWR);
    for(int i = 0; i < 1024*10; i++){
        write(fd, data, sizeof(data));
        if (i == 11)
            printf("Finished writing 12KB (direct)\n");
        if (i == 267)
            printf("Finished writing 268KB (single direct)\n");
    }
    printf("Finished writing 10MB\ntest finished\n");
}

void sanityCheck(void)
{
  char *direct = malloc(12 * 1024);
  char *single_indirect = malloc(268 * 1024);
  char *double_indirect = malloc(10 * 1024 * 1024);

  for (int i = 0; i < 1024 * 12; i++)
  {
    direct[i] = 'a';
  }
  for (int i = 0; i < 1024 * 268; i++)
  {
    single_indirect[i] = 'a';
  }
  for (int i = 0; i < 10 * 1024 * 1024; i++)
  {
    double_indirect[i] = 'a';
  }

  int fd = open("test", O_CREATE | O_RDWR);

  if (write(fd, direct, 12 * 1024) != 12 * 1024)
  {
    printf("error: write to backup file failed\n");
    exit(0);
  }
  else
  {
    printf("Finished writing 12KB (direct)\n");
  }

  if (write(fd, single_indirect, 268 * 1024) != 268 * 1024)
  {
    printf("error: write to backup file failed\n");
    exit(0);
  }
  else
  {
    printf("Finished writing 268KB (single indirect)\n");
  }

  if (write(fd, double_indirect, 10 * 1024 * 1024) != 10 * 1024 * 1024)
  {
    printf("error: write to backup file failed\n");
    exit(0);
  }
  else
  {
    printf("Finished writing 10MB (double indirect)\n");
  }
}
int main(){
  // task2_test();
  sanityCheck();
  exit(0);
}
