#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <asm/vsyscall.h>
void wu(unsigned long addr)
{

	unsigned long real_addr = 0x00;//要输出的地址

	struct task_struct *cur_task = get_current();//获取当前进程控制块

	struct mm_struct *mm = cur_task ->  mm;//进程虚拟空间

	pgd_t *pgd;//描述页全局目录项

	pmd_t *pmd;//描述页中间项

	pte_t *pte;//页表项



	pgd = pgd_offset(mm, addr);//找出所在目录

	if (pgd_none(*pgd)){

        goto out;
	}

	pmd = pmd_offset(pgd, addr);//找出所在中间项



	if (pmd_none(*pmd)){

    goto out;
	}

	pte = pte_offset(pmd, addr);//找出所在页面

	if (pte_none(*pte)) {

    goto out;
	}



	//假设每页4KB

	real_addr = addr & 0x00003fff; //取出页面偏移量

	real_addr += pte;//内核空间访问的地址

	real_addr -= PAGE_OFFSET;//真正物理地址()

	printk("物理地址是 %x\n",real_addr);

	return;
out:
	printk("没有内存映射",real_addr);
}


int main ( int argc, char *argv[] )
{
	int a = 20;
	pid_t id;
	if(id = fork())
	{
		wu((long)&a);
	}
	else
	{
		wu((long)&a);
	}
	return 0;
}
