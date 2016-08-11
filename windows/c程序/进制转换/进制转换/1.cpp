#include<stdio.h>
#include<string.h>


/*int my_atoi(char str[])
	{
		int i = 0;
		int sum = 0;
		int item = 0;

		while (str[i] != 0)
		{
			item = str[i] - '0';
			sum = sum * 10 + item;
			i++;
		}

		return sum;
	}

int main()
   {
		char str[] = "123956789";
		int i = my_atoi(str);    
		printf("%d\n", i);


		return 0;

	}



void my_itoa(int num, char buff[], int radix)
{
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int i = 0;
	while (num != 0)
	{
		buff[i] = index[num%radix];
		num = num / radix;
		i++;
	}
	buff[i] = 0;
	_strrev(buff);

}

int main()
{

	char buff[200];
	int i = 11;
	my_itoa(i, buff, 8);
	printf("%s\n", buff);
	return 0;
}
*/
//int my_atoi(char buff[], int num, int radix)
//{
//
//
//
//
//}
//int main()
//{
//	int arr[100];
//	char i = "gdsgf";
//
//	return 0;
//}
