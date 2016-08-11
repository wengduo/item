#include<stdio.h>
void swap(int *m, int *n)
{
	int *tmp;
	tmp =m;
	m = n;
	n = tmp;

}
int main()
{
	int x = 10;
	int y = 20;
	swap(&x, &y);
	printf("%d-%d\n", x,y);

	return 0;
}