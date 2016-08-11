#ifndef KNAP_H 
#define KNAP_H 
#include <iostream> 
#include <fstream> 
#include <string>
using namespace std;
struct task
{
	int number;
	int deadline;
	int fine;
};
class TaskTable
{
public:
	TaskTable(char *in, char *out);
	~TaskTable();
	void Solve();
protected:
	void DecreaseSort();
	void OrderSort(int *order);
	void SwapTask(int i, int j);
	void Schedule();
	void Output();
private:
	int task_num;
	task *tasks;
	int min_fine;
	ofstream fout;
};
#endif 