#include<stdio.h>
#include<string.h>


/*int main()
{
	char string1[] = "h,,,e¡­¡­6e,&,,l,,e**e*9u0h";
	char string2[100] = "";
	char string3[100] = "";
	int h = strlen(string1);
	int n = 0;
	int k = 0;
	for (int i = 0; i <= h - 1; i++)
	{
		if (((string1[i] >= 'a') && (string1[i] <= 'z')) || ((string1[i] >= 'A') && (string1[i] <= 'Z')))
		{
			string2[n] = string1[i];
			n++;
		}
	}
	for (int j =h-1; j>=0; j--)
	{
		
		if (((string1[j] >= 'a') && (string1[j] <= 'z')) || ((string1[j] >= 'A') && (string1[j] <= 'Z')))
		{
			string3[k] = string1[j];
			k++;
		}
	}
	printf("%d ", strcmp(string2, string3));
	return 0;
}*/

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int *p = arr;
	int *s = arr;
	int k = sizeof(arr) / sizeof(arr[0]);
	/*for (int i = 0; i <= k-1; i++)
	{
		printf("%d ", *(p + i));
	}*/
	int j = k - 1;
	for (int i = 0; i <= j;i++)
	{
		int tmp;
		tmp = *(p + i);
		*(p + i) = *(p + j);
		*(p + j) = tmp;
		j--;
	}

	printf("%d ", *p);


	return 0;
}


/*void my_huisu(int p ,int m)
{

}


int main()
{

	char string[] = "h,,,e¡­¡­6e,&,,l,,e**e*9u0h";
	int h = strlen(string);
	my_huisu(*string, h);

	return 0;
}*/



