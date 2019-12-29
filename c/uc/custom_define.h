#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/mman.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <fcntl.h>
#define E_MSG(string,val) do{perror(string);return (val);}while(0)
