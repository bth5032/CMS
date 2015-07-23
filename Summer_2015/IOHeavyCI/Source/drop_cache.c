#include <stdio.h>

int main()
{
  FILE *f = fopen("/proc/sys/vm/drop_caches", "w");

  if (!f)
  {
    perror("Opening of /proc/sys/vm/drop_caches failed");
    return 1;
  }
  
  fprintf(f, "3");

  fclose(f);
  
  return 0;
}
