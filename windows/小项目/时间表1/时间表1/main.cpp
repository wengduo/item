#include "����ʱ�������.h"
int main()
{
	char *in = "input.txt";       //�����ļ�
	char *out = "output.txt";      //����ļ� 
	TaskTable table(in, out);       //�ļ���ʼ������˳��ʱ��
	table.Solve();         //�������ʱ���
	return 0;
}