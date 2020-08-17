#include "types.h"
#include "user.h"

// Prevent this function from being optimized, which might give it closed form
#pragma GCC push_options
#pragma GCC optimize ("O0")
static int
recurse(int n, int temp)
{
  if(temp == n)
    return temp;
  else {
	temp++;
  }
  return recurse(n, temp);
}
#pragma GCC pop_options

int
main(int argc, char *argv[])
{
  int n, m;

  if(argc != 2){
    printf(1, "Usage: %s levels\n", argv[0]);
    exit(0);
  }

  n = atoi(argv[1]);
  printf(1, "Lab 3: Recursing %d levels\n", n);
  m = recurse(n, 0);
  printf(1, "Lab 3: Yielded a value of %d\n", m);
  exit(0);
}
