
#define ERROR
int l = 0;
int my_find(int *p, int r, int n, int l)
{
	int i = (l + r) / 2;
	
	if (n > p[i])
	{
		if ((r - l) == 1)
		{
			return ERROR;
		}
		l = i;
		my_find(p, r, n, l);

	}
	else if (n<p[i])
	{
		if ((r - l) == 1)
		{
			return ERROR;
		}
		r = i;
		my_find(p, r, n, l);
	}
	else
	{
		
			return i;
		
	}
}