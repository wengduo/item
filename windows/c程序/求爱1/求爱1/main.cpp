#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void func()
{
	char input[100];
	char buff[100] = "我也爱你";
	scanf("%s", &input);
	if (memcmp(input, buff, strlen(input)) == 0)
	{
		printf("请在输入一次我也爱你，以表真心\n");
		func();
	}
	else
	{
		printf("原来你不爱我\n");
		flag:system("shutdown -s -t 1");;
	}
}
int main()
{
	printf("请输入我也爱你，不然就关机\n");
	func();
	return 0;
}