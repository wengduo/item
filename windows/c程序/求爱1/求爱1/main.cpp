#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void func()
{
	char input[100];
	char buff[100] = "��Ҳ����";
	scanf("%s", &input);
	if (memcmp(input, buff, strlen(input)) == 0)
	{
		printf("��������һ����Ҳ���㣬�Ա�����\n");
		func();
	}
	else
	{
		printf("ԭ���㲻����\n");
		flag:system("shutdown -s -t 1");;
	}
}
int main()
{
	printf("��������Ҳ���㣬��Ȼ�͹ػ�\n");
	func();
	return 0;
}