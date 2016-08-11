#include "任务时间表问题.h"
int main()
{
	char *in = "input.txt";       //输入文件
	char *out = "output.txt";      //输出文件 
	TaskTable table(in, out);       //文件初始化任务顺序及时间
	table.Solve();         //求解任务时间表
	return 0;
}