#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdio.h>
#include<string.h>
/*int main()

{

	char c;

	while (scanf("%c", &c))

	{

		if ('a' <= c&&c <= 'z')

		{

			printf("y");

		}
		else if(c == '\n')
		{
			break;
		}
		else

		{

			printf("n");

		}

	}

	return 0;
}
int main()

{

	int d;

	while (scanf("%d", &d) != EOF)

	{
		int r = d % 2;

		if (r != 0)

		{

			printf("%d是奇数\n",d);

		}

		else

		{

			printf("%d是偶数\n",d);

		}

	}

	return 0;

}

/*int find_in_string(const char* s, char c)
{

	size_t i;

	for (i = 0; i<strlen(s); i++) {

		if (s[i] == c)

			return i;

	}

	return -1;

}

int main() {

	char c, s[11];

	while (scanf("%c%s", &c, s) != EOF)
	{

		printf("%d\n", find_in_string(s, c));

	}

	return 0;
}*/
int main()
{
	int arr[10];
	int i = 0;
	int j = sizeof(arr) / sizeof(arr[0]);
	for (; i <= j; )
	{
		int tmp1 = arr[i];
		if (arr[j] < tmp1)
		{
			arr[i] = arr[j];
			i++;
		}
		else
		{
			j--;
		}
	}
	return 0;
}