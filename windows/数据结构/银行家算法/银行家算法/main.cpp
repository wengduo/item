#include <iostream> 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

const int x = 10;
const int y = 10;
int Av[x];
int Al[y][y];
int max[y][y];
int need[y][y];
int re[x];
int work[x];
int finish[y];
int p[y];
int i;
int j;
int n;
int m;
int l = 0;
int counter = 0;

void chushihua();
void safe();
void show();
void bank();
void jieshu();

void chushihua()
{
	int ALL[y];
	std::cout << "输入进程数量:";
	std::cin >> n;
	std::cout << "输入资源种类数:";
	std::cin >> m;
	std::cout << std::endl << "输入各进程已分配的资源的数量Al[" << n << "][" << m << "]:" << std::endl;
	for (i = 0; i < n; i++)
	{
		std::cout << "输入进程p[" << i << "]当前以分配的各个资源数量:";
		finish[i] = 0;
		for (j = 0; j < m; j++)
		{
			std::cin >> Al[i][j];
		}
	}
	std::cout << std::endl << "输入个进程对各类资源的最大需求max[" << n << "][" << m << "]:" << std::endl;
	for (i = 0; i < n; i++)
	{
		std::cout << "输入进程怕[" << i << "]对各个资源的最大需求数:";
		for (j = 0; j < m; j++)
		{
			std::cin>>max[i][j];
			if (max[i][j] >= Al[i][j])
			{
				need[i][j] = max[i][j] - Al[i][j];
			}
			else
			{
				need[i][j] = 0;
			}
		}
	}
	std::cout << "输入" << m << "种资源的总数量ALL[]:";
	for (j = 0; j < m; j++)
	{
		std::cin >> ALL[j];
		Av[j] = ALL[j];
		for (i = 0; i < n; i++)
		{
			Av[j] -= Al[i][j];
		}
		work[j] = Av[j];
	}
	std::cout << std::endl << "初始化完成" << std::endl;
}

void safe()
{
	l = 0;
	for (i = 0; i < n; i++)
	{
		if (finish[i] == 0)
		{
			counter = 0;
			for (j = 0; j < m; j++)
			{
				if (work[j] >= need[i][j])
				{
					counter = counter + 1;
				}
			}
			if (counter == m)//
			{
				p[l] = i;//
				finish[i] = 1;
				for (j = 0; j < m; j++)
				{
					work[j] = work[j] + Al[i][j];	
				}
				l = l + 1;
				i = -1;
			}
		}
	}
}

void show()
{
	int i;
	int j;
	int L1;
	std::cout << "当前的状态为:" << std::endl;
	std::cout << "\n各种资源的可用数量(Av):" << std::endl;
	for (j = 0; j < m; j++)
	{
		std::cout << "资源" << j << ":";
		std::cout << Av[j] << " ";
	}
	std::cout << std::endl << "显示当前状态:" << std::endl;
	for (i = 0; i <= 0; i++)
	{
		std::cout << " max   al   need";
		std::cout<<std::endl;
		for (L1 = 0; L1 < n; L1++)
		{
			std::cout << "进程p[" << L1 << "]:";
			for (j = i; j < m; j++)
			{
				std::cout << max[L1][j] << " ";
			}
			std::cout << " ";
			for (j = i; j < m; j++)
			{
				std::cout << Al[L1][j] << " ";
			}
			std::cout << " ";
			for (j = i; j < m; j++)
			{
				std::cout << need[L1][j] << " ";
			}
			std::cout << std::endl;
		}

	}
}

void bank()
{
	std::cout << std::endl << "进程申请分配资源:" << std::endl;
	int k = 0;
	bool r = false;
	do 
	{
		std::cout << "输入申请资源进程（0-" << n - 1 << "):";
		std::cin >> k;
		std::cout << std::endl;
		while (k > n - 1)
		{
			std::cout << std::endl << "输入错误，请重新输入:" << std::endl;
			std::cout << "输入申请资源进程(0--" << n - 1 << "):";
			std::cin >> k;
			std::cout << std::endl;
		}
		std::cout << std::endl << "输入该进程申请各类资源的数量:" << std::endl;
		for (j = 0; j < m; j++)
		{
			do 
			{
				std::cout << "进程" << k << "申请资源[" << j << "]的数量:";
				std::cin >> re[j];
				std::cout << std::endl;
				if (re[j] > need[k][j])
				{
					std::cout << "申请大于需求量" << std::endl;
					std::cout << "申请的资源" << j << "的数量为" << re[j] << ",大于进程" << k << "对于该资源需求量" << need[k][j] << "." << std::endl;
					std::cout << "重新输入" << std::endl;
				}
				else
				{
					if (re[j] > Av[j])
					{
						std::cout << "\n没有那么多的资源，目前可利用资源" << j << "数量为" << Av[j] << "本次不成功，进程等待" << std::endl;
						finish[k] = 0;
						goto ppp;
					}
				}
			} while (re[j] > need[k][j]);
		}
		for (j = 0; j < m; j++)
		{
			Av[j] = Av[j] - re[j];
			Al[k][j] = Al[k][j] + re[j];
			need[k][j] = need[k][j] - re[j];
			work[j] = Av[j];
		}
		safe();
		if (l < n)
		{
			l = 0;
			std::cout << "\n试分配后，状态不安全，所以不予分配，恢复状态" << std::endl;
			for (j = 0; j < m; j++)
			{
				Av[j] =Av[j] + re[j];
				Al[k][j] = Al[k][j] - re[j];
				need[k][j] =need[k][j] + re[j];
				work[j] = Av[j];
			}
			for (i = 0; i < n; i++)
			{
				finish[i] = 0;
			}
		}
		else
		{
			l = 0;
			std::cout << "\n申请资源成功" << std::endl;
			for (j = 0; j < m; j++)
			{
				if (need[k][j] != 0)
				{
					l = 1;
					break;
				}
			}
			if (l != 1)
			{
				for (j = 0; j < m; j++)
				{
					Av[j] = Av[j] + Al[k][j];
					Al[k][j] = 0;
				}
				std::cout << "该进程已得到所有资源" << std::endl;
			}
			l = 0;
			std::cout << "\n安全状态" << std::endl;
			std::cout << "安全序列为:";
			std::cout << std::endl << "进程(" << p[0] << ")";
			finish[0] = 0;
			for (i = 1; i < n; i++)
			{
				std::cout << "-->>" << "进程" << "(" << p[i] << ")";
				finish[i] = 0;
			}
			std::cout << std::endl << std::endl;
		}
		show();
	ppp:
		std::cout << std::endl << "是否继续申请资源（y/n)";
		char *b = new char;
		std::cin >> b;
		std::cout << std::endl;
		std::cout << "......................" << std::endl << std::endl;
		std::cout << std::endl;
		if (*b == 'y' || *b == 'Y')
		{
			r = true;
		}
		else
		{
			r = false;
			jieshu();
		}
	}while (r == true);
}

void jieshu()
{
	std::cout << std::endl<<std::endl;
	std::cout << "\t\t演示完毕" << std::endl;
	std::cout << std::endl << std::endl;
}

int main()
{
	std::cout << std::endl << std::endl<< "\t\t\t\t开始银行家算法"<<std::endl;
	chushihua();
	std::cout << std::endl;
	show();
	safe();
	if (l < n)
	{
		std::cout << "\n当前状态不安全，拒绝申请" << std::endl;
		std::cout << std::endl;
		return 0;
	}
	else
	{
		int i;
		l = 0;
		std::cout << std::endl << "\n当前状态是安全的，安全序列为" << std::endl;
		std::cout << "进程" << "(" << p[0] << ")";
	
		for (i = 1; i < n; i++)
		{
			std::cout << "->>" << "进程" << "(" << p[i] << ")";
		}
		for (i = 0; i < n;i++)
		{
			finish[i] = 0;
		}
		std::cout << std::endl;
	}
	bank();
	std::cout << "\t\t演示完毕" << std::endl;
	return 0;
}

//int main()
//{
//	const int x = 5;
//	int a[x];
//	//int i = 0;
//	//a[0] = 9;
//	printf("%d\n", a[0]);
//	return 0;
//}
