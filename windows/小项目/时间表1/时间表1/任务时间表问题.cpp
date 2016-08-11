#include "����ʱ�������.h" 
TaskTable::TaskTable(char *in, char *out) : fout(out)
{
	ifstream fin(in);
	if (!fin)
	{
		cerr << "�ļ�" << in << "�޷���!" << endl;
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
		cerr << "�ļ�" << out << "�޷���!" << endl;
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
	DecreaseSort();        //�ǵ�����������
	int *order;
	order = new int[task_num];      //ʱ��������Ŵ�������
	for (int i = 0; i < task_num; i++)
		order[i] = 0;       //��ʼ��Ϊ0������û����ʱ��
	for (int i = 0; i < task_num; i++)
	{
		int j;
		for (j = tasks[i].deadline - 1; j >= 0; j--)
		{
			if (order[j] == 0)  //�����λ�û�û��������

			{
				order[j] = tasks[i].number;   //��λ���Ÿ�������
				break;
			}
		}
		if (j < 0)         //�޷���֤����ʱ
		{
			min_fine += tasks[i].fine;     //���񷣿��������С��ʱ����
			for (j = task_num - 1; j >= tasks[i].deadline - 1; j--)
			{
				if (order[j] == 0)     //�����λ�û�û��������
				{
					order[j] = tasks[i].number;  //��λ���Ÿ�������
					break;
				}
			}
		}
	}
	OrderSort(order);      //��ʱ�������������
}
void TaskTable::Output()
{
	fout << min_fine << endl;
	for (int i = 0; i < task_num; i++)
		fout << tasks[i].number << ' ';
}






			


























































				