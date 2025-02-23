#include <HByte/Pool.h>
#include <stdio.h>

int main(void)
{
  ByPool mem;
  allocPool(&mem, 256);

  dySegmetation(32, &mem);
  printf("Pool Size -> %d \nBlock Max Size -> %d \n\n",
         calPool(&mem), calBlock(0, &mem));

  float *v = allocBlockdy(sizeof(float) * 3, &mem);
  v[0] = 11.6;
  v[1] = 33.89;
  v[2] = 1.50;
  allocBlockdy(sizeof(int) * 300, &mem);
  Byte4 *vS = (Byte4*)mem.iEnd[calIndex(v, &mem) + 1];

  printf("{ ");
  for (uint32_t i = 0 ;i < 256; i++ ) {
    printf("%d ", mem.iMem[i]);
  }
  printf("} \n\n");


  printf("v All Elements -> %.2f, %.2f, %.2f\n", v[0], v[1], v[2]);
  printf("First Element size -> %d", 
         calSegSize(v, &mem));


  desallocPool(&mem);

  return 0;
}
