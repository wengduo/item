#include "任务时间表问题.h" 
TaskTable::TaskTable(char *in, char *out) : fout(out)
{
	ifstream fin(in);
	if (!fin)
	{
		cerr << "文件" << in << "无法打开!" << endl;
		exit(1);
	}
	fin >> task_num;
	tasks = new task[task_num];
	for (int i = 0; i < task_num; i++)
		tasks[i].number = i + 1;
	for (int i = 0; i < task_num; i++)
		fin >> tasks[i].deadline;
	for (int i = 0; i < task_num; i++)
		fin >> tasks[i].fine;
	fin.close();
	min_fine = 0;
	if (!fout)
	{
		cerr << "文件" << out << "无法打开!" << endl;
		exit(1);
	}
}
TaskTable::~TaskTable()
{
	if (fout)
	fout.close();
	if (tasks)
	delete[] tasks;
}
void TaskTable::Solve()
{
	Schedule();
	Output();
}
void TaskTable::DecreaseSort()
{
	for (int i = 0; i < task_num - 1; i++)
	{
		int max = i;
		for (int j = i + 1; j < task_num; j++)
		{
			if (tasks[j].fine > tasks[max].fine)
			{
                max = j;
			}	
			else
			{
				if (tasks[j].fine == tasks[max].fine)
				{
					if (tasks[j].deadline < tasks[max].deadline)
					{
						max = j;
					}
					
				}
			}
		}
		if (max != i)
		{
          SwapTask(max, i);
		}	
	}
}
void TaskTable::OrderSort(int *order)
{
	for (int i = 0; i < task_num; i++)
	{
		int j;
		for (j = i; order[i] != tasks[j].number; j++);
		SwapTask(i, j);
	}
}
void TaskTable::SwapTask(int i, int j)
{
	task temp;
	temp = tasks[i];
	tasks[i] = tasks[j];
	tasks[j] = temp;
}
void TaskTable::Schedule()
{
	DecreaseSort();        //非递增排序任务
	int *order;
	order = new int[task_num];      //时间表任务编号次序数组
	for (int i = 0; i < task_num; i++)
		order[i] = 0;       //初始化为0，任务还没有排时间
	for (int i = 0; i < task_num; i++)
	{
		int j;
		for (j = tasks[i].deadline - 1; j >= 0; j--)
		{
			if (order[j] == 0)  //如果该位置还没有排任务

			{
				order[j] = tasks[i].number;   //该位置排该任务编号
				break;
			}
		}
		if (j < 0)         //无法保证不误时
		{
			min_fine += tasks[i].fine;     //任务罚款加入总最小误时罚款
			for (j = task_num - 1; j >= tasks[i].deadline - 1; j--)
			{
				if (order[j] == 0)     //如果该位置还没有排任务
				{
					order[j] = tasks[i].number;  //该位置排该任务编号
					break;
				}
			}
		}
	}
	OrderSort(order);      //按时间任务表排任务
}
void TaskTable::Output()
{
	fout << min_fine << endl;
	for (int i = 0; i < task_num; i++)
		fout << tasks[i].number << ' ';
}






			


























































				