#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3 && (argc != 4)){
    fprintf(2, "Usage: ln [command] old new\n");
    exit(1);
  }
  if(strcmp(argv[1],"-s") && link(argv[2], argv[3]) < 0){
     fprintf(2, "link %s %s: failed\n", argv[1], argv[2]);
    exit(1);
  }
  if(argc == 4 && !strcmp(argv[1],"-s")){
    char* old = argv[2];
    char* new = argv[3];
    if(symlink(old, new) != 0){
      fprintf(2, "symlink %s %s: failed\n", old, new);
    }
  }
  exit(0);
}
