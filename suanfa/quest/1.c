#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define    page_map_file     "/proc/self/pagemap"
#define    PFN_MASK          ((((uint64_t)1)<<55)-1)
#define    PFN_PRESENT_FLAG  (((uint64_t)1)<<63)


int mem_addr_vir2phy(unsigned long vir, unsigned long *phy)
{
  int fd;
  int page_size=getpagesize();
  unsigned long vir_page_idx = vir/page_size;
  unsigned long pfn_item_offset = vir_page_idx*sizeof(uint64_t);
  uint64_t pfn_item;
  int a = *(int *)(void *)vir;
	printf("%d\n",a);
  fd = open(page_map_file, O_RDONLY);
  if (fd<0)
  {
    printf("open %s failed", page_map_file);
    return -1;
  }
  if ((off_t)-1 == lseek(fd, pfn_item_offset, SEEK_SET))
  {
    printf("lseek %s failed", page_map_file);
    return -1;
  }
  if (sizeof(uint64_t) != read(fd, &pfn_item, sizeof(uint64_t)))
  {
    printf("read %s failed", page_map_file);
    return -1;
  }
  if (0==(pfn_item & PFN_PRESENT_FLAG))
  {
    printf("page is not present");
    return -1;
  }
  *phy = (pfn_item & PFN_MASK)*page_size + vir % page_size;
  return 0;
}

	
int a = 10;
int main()
{
	int b = 11;
	int c = 12;
	long d;
	pid_t id;
	if(id = fork())
	{
		mem_addr_vir2phy((long)&a,&d);
		printf("pid%p-%p-%p-%ld\n",&a,&b,&c,d);
	}
	else
	{
		long dd;
		mem_addr_vir2phy((long)&a,&dd);
		printf("ppid%p-%p-%p-%ld\n",&a,&b,&c,dd);
	}
}

