


void exchange_sort(int array[], int n)
{
	int tmp;

	for (int i = 0; i<n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (array[i] > array[j])
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
		}
	}
}
