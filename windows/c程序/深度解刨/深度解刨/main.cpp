#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
//#include<stdarg.h>
//#include<vld.h>


//��ṹ���С
//#pragma pack������ĳ���ֽڶ���
/*struct TestStruct1
{
	char c1;  //1->2
	short s;  //2+2->4
	char c2;  //2->4
	int i;    //4+4+4->12
};
int main()
{
	printf("%d\n", sizeof(TestStruct1));
	return 0;
}
// v6��bug
int main()
{
	//char i = 10;
	//int j = 100;
	//int *p = (int *)(&i);
	char *p = (char *)0x12ff7c;
	*p = NULL;
	p = NULL;
	return 0;
}

//�ڴ�����ӵĶԱ�
int main()
{
	int a[5][5];
	int(*p)[4];
	p = a;
	printf("a_ptr=%#p,p_ptr=%#p\n", &a[4][2], &p[4][2]);
	printf("%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]);//-4
	return 0;
}

//������Ԫ�غ�
int main()
{
	int a[4] = { 1, 2, 3, 4 };
	int *ptr1 = (int *)(&a + 1);
	int *ptr2 = (int *)((int)a + 1);
	printf("%x,%x", ptr1[-1], *ptr2);
	return 0;
}
//malloc��free�е�����
int main()
{
	char *p = (char *)malloc(10);
	strcpy(p, "hello");
	free(p);      //free��Ҫ��p�ÿ�
	free(p);
	if (NULL != p)//�������0���ֽڣ�if��ʧȥЧӦ
	{
		strcpy(p, "world");
	}
	return 0;
}
//�ݹ��еĿ�
void fun(int i)
{
	if (i>0)
	{
		fun(i / 2);
	}
	printf("%d\n", 20);
	printf("%d\n", i);
}
int main()
{
	fun(10);
	return 0;
}
//�ݹ����ַ�������
int my_strlen(const char* strDest)
{
	assert(NULL != strDest);
	if ('\0' == *strDest)
	{
		return 0;
	}
	else
	{
		return (1 + my_strlen(++strDest));
	}
}
int my_strlen(const char* strDest)
{
	assert(NULL != strDest);
	return ('\0' != *strDest) ? (1 + my_strlen(strDest + 1)) : 0;
}
int main()
{
	char s[] = "hello";
	printf("%d\n",my_strlen(s));
	return 0;
}
struct student
{
	char *name;
	int score;
}stu, *pstu;
int main()
{
	struct student *pstu1;
	//pstu = (struct student*)malloc(sizeof(struct student)*2);
	printf("%d\n", sizeof(struct student));
	strcpy(pstu1->name, "Jimy");//nameû�з���Ϸ��ĵ�ַ
	pstu1->score = 99;
	free(pstu);
	return 0;
}
//����ָ�������ָ��
char * fun1(char * p)
{
	printf("%s\n", p);
	return p;
}
char * fun2(char * p)
{
	printf("%s\n", p);
	return p;
}
char * fun3(char * p)
{
	printf("%s\n", p);
	return p;
}
int main()
{
	char * (*a[3])(char * p);
	char * (*(*pf)[3])(char * p);
	pf = &a;
	a[0] = fun1;       // ����ֱ���ú�����
	a[1] = &fun2;      //Ҳ������ȡ��ַ�Ӻ�����
	a[2] = &fun3;
	pf[0][0]("fun1");
	pf[0][1]("fun2");
	pf[0][2]("fun3");
	return 0;
}*/
/////////////////////////////////////////////////////////////////////////////////////////
//(*(void(*) ())0)();
//��һ����void(*) ()��������������һ������ָ�����͡��������û�в�����û�з���ֵ��
//�ڶ�����(void(*) ())0�����ǽ�0 ǿ��ת��Ϊ����ָ�����ͣ�0 ��һ����ַ��Ҳ����˵һ
//        �����������׵�ַΪ0 ��һ�������ڡ�
//��������(*(void(*) ())0)������ȡ0 ��ַ��ʼ��һ���ڴ���������ݣ������ݾ��Ǳ���
//        ���׵�ַΪ0 ��һ�������ڵĺ�����
//���Ĳ���(*(void(*) ())0)()�����Ǻ������á�
/////////////////////////////////////////////////////////////////////////////////////////////
//(*(char**(*) (char **,char **))0) ( char **,char **);
//��һ����char** (*) (char **,char **)��������������һ������ָ�����ͣ���������Ĳ�
//        ��Ϊ����ָ��char������ֵҲΪ����ָ��char��
//�ڶ�����(char** (*) (char **,char **))0,���ǽ�0 ǿ��ת��Ϊ����ָ�����ͣ�0 ��һ��
//        ��ַ��Ҳ����˵һ�����������׵�ַΪ0 ��һ�������ڡ�
//��������(*(char** (*) (char **,char **))0),����ȡ0 ��ַ��ʼ��һ���ڴ���������ݣ�
//        �����ݾ��Ǳ������׵�ַΪ0 ��һ�������ڵĺ�����
//���Ĳ���(*(char**(*) (char **,char **))0) ( char **,char **)�����Ǻ�������,�����
//        Ϊ��������ָ��char��
////////////////////////////////////////////////////////////////////////////////////////////////
/*int main()
{ 
	(*(char**(*) (char **, char **))0)          ((char **)1,(char**)2);

	return 0;

}
//ȥ���ַ������ظ����ַ�
char *prepare_key(char *key)
{
	char *buff = (char*)calloc(sizeof(char),strlen(key)+1+26);
	assert(buff != NULL);
	key = strupr(key);
	strcpy(buff,key);
	strcat(buff,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	memset(key,0,27);
	char *tmp1 = key;
	char *tmp2 = buff;
	while(*buff)
	{
		if(strchr(tmp1,*buff) == NULL)
		{
			*key = *buff;
			key++;
		}
	buff++;
	}
	free(tmp2);
	return tmp1;
}
//λ���е�֪ʶ��
struct _CPU
{
	unsigned int CF : 5;//���ܳ���32��Ҳ����С��0
	unsigned int BF : 5;
	unsigned int AF : 5;
	unsigned int    : 5;//ռ��
	unsigned int EF : 5;
	unsigned int    : 0;//����һ��λʹ���µ�intλ
	unsigned int DF : 5;
	unsigned int IF : 5;
}a;
int main()
{
	printf("%d\n", sizeof(struct _CPU ));
	return 0;
}*/
//float->int
/*union H
{
	int i;
	float f;
};
int main()
{
	union H h;
	h.f = 12.125;
	return 0;
}
void *my_calloc(size_t n, size_t elem_size)
{
	void *p =malloc(elem_size* n);
	memset(p, 0, elem_size);
	//free(p);
	return p;
}
int main()
{
	my_calloc(10, sizeof(int));
	return 0;
}
//�ַ�ת����
int ascil_to_integer(char *string)
{
	int value = 0;
	while (*string >= '0' && *string <= '9')
	{
		value *= 10;
		value += *string - '0';
		string++;
	}
	if (*string != '\0')
	{
		value = 0;
	}
	return value;
}
int main()
{
	char s[] = "12";
	printf("%d\n", ascil_to_integer(s));
	return 0;
}
float aver(int n, ...)
{
	float sum = 0.0f;
	va_list argument;
	va_start(argument, n);
	int rs = 0;
	for (int i = 0; i<n; i++)
	{
		rs = va_arg(argument, int);
		sum += rs;
	}
	va_end(argument);
	return sum / n;
}

int max_value(int v1, ...)
{
	va_list argument;
	va_start(argument, v1);

	int max = v1;

	int rs = v1;
	while (rs >= 0)
	{
		if (max < rs)
		{
			max = rs;
		}
		rs = va_arg(argument, int);
	}
	va_end(argument);
	return max;
}


int main()
{
	printf("%f\n",aver(10,10,20,30,40,50,60,70,80,90,100));
	printf("%d\n", max_value(2, 4, 6, 1, 3, 5, -99));
	return 0;
}
//������������ֵ�����ֵ
int max_list(int n, ...)
{
	va_list argument;
	va_start(argument, n);
	int max = INT_MIN;
	while (n--)
	{
		int k = va_arg(argument, int);
		if (max < k)
		{
			max = k;
		}
	}
	va_end(argument);
	return max;
}
int main()
{
	printf("%d\n", max_list(6, 4,-99,1,2,99,0));
	return 0;
}

double double_sum(double v1, ...)
{
	char *argument = (char *)&v1;
	argument = argument + sizeof(v1);
	double rs = 0.0;
	double sum = v1;
	do
	{
		rs = *(double*)&argument;
		sum += rs;
		argument = argument + sizeof(double);
	} while (rs != 0);
	argument = NULL;
	return sum;
}
int main()
{
	printf("%lf\n", double_sum(1.0, 2.0, 3.0, 4.0, 0));
	return 0;
}
//�ݹ�
int func(int n)
{
	if (n == 0||n == 1)
	{
		return 1;
	}
	else
	{
		return n*func(n - 1);
	}
}
int main()
{
	printf("%d\n", func(-1));
	return 0;
}
int func(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	else
	{
		return func(n - 1) + func(n - 2);
	}
}
int main()
{
	printf("%d\n", func(7));
	return 0;
}
//�����ӡ
int func(int n)
{
	if (n == 0)
	{
		return 0;
	}
	else
	{
		printf("%c", n % 10+'0');
		func(n / 10);
	}
}
int main()
{
	func(12345);
	return 0;
}
//���ܶ���ʽ
int hermite(int n, int x)
{
	if (n <= 0)
	{
		return 1;
	}
	else if (n == 1)
	{
		return 2*x;
	}
	else
	{
		return 2 * x*hermite(n - 1, x) - 2 * (n - 1)*hermite(n - 2, x);
	}
}
int main()
{
	printf("%d\n", hermite(3, 2));
	return 0;
}*/
//���Լ��
int count = 0;
int gcd(int m,int n)
{
	count++;
	if (m <= 0 || n <= 0)
	{
		return 0;
	}
	int r = m%n;
	if (r > 0)
	{
		gcd(n, r);
	}
	else
	{
		return n;
	}
}
int main()
{
	printf("%d\n", gcd(9, 12));
	printf("%d\n", count);
	return 0;
}
