#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<io.h>
#include<vld.h>
#include <sys/stat.h>
//#include <unistd.h>

/*int main()
{
	FILE *fr = fopen("g:\\12306.txt", "r");
	assert(fr != NULL);
	size_t line = 0;
	char buff[200];
	while (fgets(buff, 200, fr) != NULL)
	{
		line++;
	}
	printf("%u\n", line);
	char *p = (char *)malloc(sizeof(char)* 200 * line);//12W BYTE
	assert(p != NULL);
	fseek(fr, 0, SEEK_SET);
	int tmp = line;
	char *s = p;
	while (tmp--)
	{
		fgets(p, 200, fr);
		p = p + 200;
	}
	printf("请输出待查询内容:");
	scanf("%s", buff);
	for (int i = 0; i < line; i++)
	{
		if (strstr(s, buff) != NULL)
		{
			printf("%s\n", s);
		}
		s += 200;
	}
	return 0;
}
//12306查询
struct find
{
	char *mail;
	char *username;
	char *name;
	char *id;
	char *password;
	char *telephone;
}*p ,*f;
int main()
{
	FILE *fr = fopen("g:\\12306.txt", "r");
	assert(fr != NULL);
	char buff[200];
	char buff1[40];
	int  select;
	int k = 0;
	int line = 0;
	(struct find *)p = (struct find *)malloc(sizeof(struct find) * 131654);
	assert(p != NULL);
	f = p;
	while (fgets(buff, 200, fr) != NULL)
	{
		char **s= (char **)malloc(sizeof(char *)* 30);
		*(s + 0) = strtok(buff, "-\n");
		*(s + 1) = strtok(NULL, "-\n");
		*(s + 2) = strtok(NULL, "-\n");
		*(s + 3) = strtok(NULL, "-\n");
		*(s + 4) = strtok(NULL, "-\n");
		*(s + 5) = strtok(NULL, "-\n");
		(char *)p->mail = (char *)malloc(sizeof(char)*(strlen(*s)+1));
		memcpy(p->mail, *s, strlen(*s) + 1);
		(char *)p->username = (char *)malloc(sizeof(char)*(strlen(*(s+1))+1));
		memcpy(p->username, *(s + 1), strlen((*(s + 1))) + 1);
		(char *)p->name = (char *)malloc(sizeof(char)*(strlen(*(s + 2))+1));
		memcpy(p->name, *(s + 2), strlen(*(s + 2)) + 1);
		(char *)p->id = (char *)malloc(sizeof(char)*(strlen(*(s + 3))+1));
		memcpy(p->id, *(s + 3), strlen(*(s + 3)) + 1);
		(char *)p->password = (char *)malloc(sizeof(char)*(strlen(*(s + 4))+1));
		memcpy(p->password, *(s + 4), strlen(*(s + 4)) + 1);
		(char *)p->telephone = (char *)malloc(sizeof(char)*(strlen(*(s + 5))+1));
		memcpy(p->telephone, *(s + 5), strlen(*(s + 5)) + 1);
		free(s);
		p++;
		line++;
	}
	fclose(fr);
	p = f;
	scanf("%d", &select);
	switch (select)
	{
		case 1:scanf("%s", &buff1);
			for (int i = 0; i < line; i++)
			{
				if (memcmp(p->mail, buff1, strlen(buff1)) == 0)
				{
					printf("%s----%s----%s----%s----%s----%s\n", p->mail, p->username,
					p->name, p->id, p->password, p->telephone);
					k++;
				}
				p++;
			}
			break;
		case 2:scanf("%s", &buff1);
			for (int i = 0; i < line; i++)
			{
				if (memcmp(p->username, buff1, strlen(buff1)) == 0)
				{
					printf("%s----%s----%s----%s----%s----%s\n", p->mail, p->username,
					p->name, p->id, p->password, p->telephone);
					k++;
				}
				p++;
			}
			break;
		case 3:scanf("%s", &buff1);
			for (int i = 0; i < line; i++)
			{
				if (0 == memcmp(p->name, buff1, strlen(buff1)))
				{
					printf("%s----%s----%s----%s----%s----%s\n", p->mail, p->username,
					p->name, p->id, p->password, p->telephone);
					k++;
				}
				p++;
				}
			break;
		case 4:scanf("%s", &buff1);
			for (int i = 0; i < line; i++)
			{
				if (memcmp(p->id, buff1, strlen(buff1)) == 0)
				{
					printf("%s----%s----%s----%s----%s----%s\n", p->mail, p->username,
					p->name, p->id, p->password, p->telephone);
					k++;
				}
				p++;
			}
			break;
		case 5:scanf("%s", &buff1);
			for (int i = 0; i < line; i++)
			{
				if (memcmp(p->password, buff1, strlen(buff1)) == 0)
				{
					printf("%s----%s----%s----%s----%s----%s\n", p->mail, p->username,
					p->name, p->id, p->password, p->telephone);
					k++;
				}
				p++;
			}
			break;
		case 6:scanf("%s", &buff1);
			for (int i = 0; i < line; i++)
			{
				if (memcmp(p->telephone, buff1, strlen(buff1)) == 0)
				{
					printf("%s----%s----%s----%s----%s----%s\n", p->mail, p->username,
					p->name, p->id, p->password, p->telephone);
					k++;
				}
				p++;
			}
			break;
	default:printf("输入错误\n");
	}
	if (k == 0)
	{
		printf("无此人信息\n");
	}
	p = f;
	for (int i = 0; i < line; i++)
	{
		free(p->mail);
		free(p->username);
		free(p->name);
		free(p->id);
		free(p->password);
		free(p->telephone);
		p++;
	}
	free(f);
	return 0;
}
int main()
{
	int i;
	char c;
	for (i = 0; i < 5; i++)
	{
		scanf("%d", &c);
		printf("%d   ", i);
	}
	return 0;
}
int main()
{
	printf("%g\n",sqrt(2.0));
	return 0;
}

int main()
{
	char c;
	static char buf(BUFSIZ);
	char *malloc();
	setbuf(stdout, malloc(BUFSIZ));
	register int c;
	while ((c = getchar()) != EOF)
	putchar(c);
	return 0;
}
//清零占结构体
int main()
{
	char *p = (char *)malloc(sizeof(char)* 10);
	char *s = (char *)malloc(sizeof(char)* 0);
	p = (char *)realloc(p,0);
	return 0;
}
int main()
{
	int a[20] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
	110, 120, 130, 140, 150, 160, 170, 180, 190, 200 };
	int *p = a + 3;
	printf("%d\n", a);
	printf("%d\n", a[4]);
	printf("%d\n", a+4);
	printf("%d\n", *a+4);
	printf("%d\n", *(a+4));
	printf("%d\n", a[-2]);
	printf("%d\n", &a);
	printf("%d\n", &a[4]);
	printf("%d\n", &a + 4);
	printf("%d\n", &a[-2]);
	printf("%d\n", *p);
	printf("%d\n", p[4]);
	printf("%d\n", p+4);
	printf("%d\n", *p+4);
	printf("%d\n", *(p+4));
	printf("%d\n", p[-2]);
	printf("%d\n", &p);
	printf("%d\n", &p[4]);
	printf("%d\n", &p + 4);
	printf("%d\n", &p[-2]);
	return 0;
}
int my_huiwen(char *p)
{
	char *s = p+strlen(p)-1;
	while (p < s)
	{
		if (*p != *s)
		{
			return 0;
		}
	p++;
	s--;
	}
	if (p >= s)
	{
		return 1;
	}
}
int main()
{
	char a[] = "he2llol2l2eh";
	printf("%d\n", my_huiwen(a));
	return 0;
}
//矩阵乘法
void matrix_multiply(int *m1, int *m2, register int *r, int x, int y, int z)
{
	register int *m1p;
	register int *m2p;
	register int k;
	int row;
	int column;
	for (row = 0; row < x; row++)
	{
		for (column = 0; column < z; column++)
		{
			m1p = m1 + row*y;
			m2p = m2 + column;
			*r = 0;
			for (k = 0; k < y; k++)
			{
				*r += *m1p * *m2p;
				m1p++;
				m2p += z;
			}
			r++;
		}
	}
}
int main()
{
	int m1[3][2] = { { 2, -6 }, { 3, 5 }, { 1, -1 } };
	int m2[2][4] = { { 4, -2, -4, -5 }, { -7, -3, 6, 7 } };
	int r[3][4] = { 0 };
	matrix_multiply(*m1, *m2, *r, 3, 2, 4);

	return 0;
}
//无限制接受输入
int main()
{
	char ch;
	while ((ch = getchar()) != EOF)
	{
		putchar(ch);
	}
	return 0;
}
void sort(char **name,int lengh)
{
	char *p;
	char **start = name;
	for (int i = 0; i < lengh-1; i++)
	{
		for (int j = 0; j<lengh - i; j++)
		{
			if (strcmp(*name,*(name+1))>0)
			{
				p = *name;
				*name = *(name+1);
				*(name + 1) = p;
			}
			name++;
		}
		name = start;
	}
}
int main()
{
	char *arr[] = {
		"hello",
		"break",
		"double"
	};
	sort(arr, sizeof(arr) / sizeof(arr[0]));
	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
	{
		printf("%s\n", arr+i);
	}
	return 0;
}
//寻找关键字
int count = 0;
void func(char **p, int *r,int m )
{
	FILE *fr = fopen("f:\\c程序\\各种作业\\各种作业\\main.cpp", "r");
	assert(fr != NULL);
	char buff[60];
	while (fgets(buff, 60, fr) != NULL)
	{
		count++;
		char **s = (char **)malloc(sizeof(char *)* 60);
		if ((*(s + 0) = strtok(buff, " \n\t/*")) != NULL)
		{
			int i = 1;
			while ((*(s + i) = strtok(NULL, " \n\t/*")) != NULL)
			{
				i++;
			}
			for (int j = 0; j < i; j++)
			{
				for (int k = 0; k < m; k++)
				{
					if (strcmp(*(p + k), *(s + j)) == 0)
					{
						r[k]++;
					}
				}

			}
		}
		free(s);
	}
	fclose(fr);
}
int main()
{
	char *arr[] = {
		"int",
		"if",
		"else",
		"case",
		"float",
		"double",
		"char",
		"for",
		"while",
		"switch",
		"do",
		"long",
		"short"
	};
	int h = sizeof(arr) / sizeof(arr[0]);
	int brr[13] = { 0 };
	func(arr, brr, h);
	for (int i = 0; i < h; i++)
	{
		printf("%d\n", brr[i]);
	}
	printf("%d\n", count);
	return 0;
}
void my_sort(int *array, int n)
{
	int tmp;
	for (int i = 0; i<n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (*(array+i) > *(array+j))
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
		}
	}
}
int my_find(int *p, int k)
{
	int j = 1;
	for (int i = 0; i < k-1; i++)
	{
		if (*(p+i) == *(p+j))
		{
			return *(p+i);
		}
		j++;
	}
	return 0;
}
int main()
{
	int arr[11] = { 1, 2, 6, 3, 4, 5, 6, 7, 8, 9, 10 };
	my_sort(arr, sizeof(arr) / sizeof(arr[0]));
	printf("%d\n", my_find(arr, sizeof(arr) / sizeof(arr[0])));
	return 0;
}
int main()
{
	struct _finddata_t finddata;

	int handle;

	handle = _findfirst("f:\\c程序\\*\\*\\main.cpp", &finddata);
	if (-1 == handle)
	{
		return -1;
	}

	while (!_findnext(handle, &finddata))
	{
		printf("%s\n", finddata.name);
	}
	_findclose(handle);

	return 0;
}
void dfsFolder(string folderPath, ofstream &fout)  
{  
    _finddata_t FileInfo;  
    string strfind = folderPath + "\\*";  
    long Handle = _findfirst(strfind.c_str(), &FileInfo);  
      
    if (Handle == -1L)  
    {  
        printf("can not match the folder path\n");  
        exit(-1);  
    }  
    do{  
        //判断是否有子目录  
        if (FileInfo.attrib & _A_SUBDIR)      
        {  
            //这个语句很重要  
            if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))     
            {  
                string newPath = folderPath + "\\" + FileInfo.name;  
                dfsFolder(newPath, fout);  
            }  
        }  
        else    
        {  
			printf("%s%s\\%s" "", &fout, &folderPath, &FileInfo.name);
           // fout << folderPath << "\\" << FileInfo.name  << " ";  
        }  
    }while (_findnext(Handle, &FileInfo) == 0);  
  
    _findclose(Handle);  
    fout.close();  
} 

char *my_find(char *p)
{
	int handle;
	struct _finddata_t finddata;
	handle = _findfirst(p, &finddata);
	if (-1 == handle)
	{
		;
	}
	while (!_findnext(handle, &finddata))
	{
		return ;
	_findclose(handle);
}
int main()
{

	int handle;
    char to_search[50] = "f:\\c程序\\*.cpp";
	

	return 0;
}
// 目录
int isdir(char *path)
{
	struct stat buf;
	int cc;
	cc = stat(path, &buf);
	if (!cc && (buf.st_mode & S_IFDIR)) return(1);
	return(cc);
}
// 可读普通文件
int isrfile(char *path)
{
	struct stat buf;
	int cc;
	int euid, egid;
	cc = stat(path, &buf);
	if (!cc) {
		if ((buf.st_mode & S_IFMT) != S_IFREG) return 0;
		euid = geteuid();
		egid = getegid();
		if (euid == 0) {
			if (buf.st_mode & S_IRUSR || buf.st_mode & S_IRGRP ||
				buf.st_mode & S_IROTH)
				return 1;
			else return 0;
		}
		if ((buf.st_mode & S_IROTH) != 0) return 1;
		if ((buf.st_gid == egid) && ((buf.st_mode & S_IRGRP) != 0))
			return 1;
		if ((buf.st_uid == euid) && ((buf.st_mode & S_IRUSR) != 0))
			return 1;

	}
	return cc;
}

#define _WIN32_WINNT 0x0501
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#include <tchar.h> 
#include <wchar.h> 
#include <strsafe.h>

#define BUFSIZE MAX_PATH

int _tmain(int argc, TCHAR *argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError;
	LPTSTR DirSpec;
	size_t length_of_arg;
	INT retval;

	DirSpec = (LPTSTR)malloc(BUFSIZE);

	if (DirSpec == NULL)
	{
		printf("Insufficient memory available\n");
		retval = 1;
		goto Cleanup;
	}


	// Check for the directory to query, specified as 
	// a command-line parameter; otherwise, print usage.
	if (argc != 2)
	{
		_tprintf(TEXT("Usage: Test <dir>\n"));
		retval = 2;
		goto Cleanup;
	}

	// Check that the input is not larger than allowed.
	StringCbLength(argv[1], BUFSIZE, &length_of_arg);

	if (length_of_arg > (BUFSIZE - 2))
	{
		_tprintf(TEXT("Input directory is too large.\n"));
		retval = 3;
		goto Cleanup;
	}

	_tprintf(TEXT("Target directory is %s.\n"), argv[1]);

	// Prepare string for use with FindFile functions.  First, 
	// copy the string to a buffer, then append '\*' to the 
	// directory name.
	StringCbCopyN(DirSpec, BUFSIZE, argv[1], length_of_arg + 1);
	StringCbCatN(DirSpec, BUFSIZE, TEXT("\\*"), 2 * sizeof(TCHAR));

	// Find the first file in the directory.
	hFind = FindFirstFile(DirSpec, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("Invalid file handle. Error is %u.\n"),
			GetLastError());
		retval = (-1);
	}
	else
	{
		_tprintf(TEXT("First file name is: %s\n"),
			FindFileData.cFileName);

		// List all the other files in the directory.
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			_tprintf(TEXT("Next file name is: %s\n"),
				FindFileData.cFileName);
		}

		dwError = GetLastError();
		FindClose(hFind);
		if (dwError != ERROR_NO_MORE_FILES)
		{
			_tprintf(TEXT("FindNextFile error. Error is %u.\n"),
				dwError);
			retval = (-1);
			goto Cleanup;
		}
	}
	retval = 0;

Cleanup:
	free(DirSpec);
	return retval;

}
int main()
{

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <windows.h>  
using namespace std;
void show_file(char path[], int level = 0)
{
	char find_path[128];
	char *s = find_path;
	sprintf(find_path, "%s*", path);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	bool bContinue = true;
	hFind = FindFirstFile((LPCWSTR)find_path, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	while (bContinue)
	{
		if (strcmp((char*)FindFileData.cFileName, "..") && strcmp((char*)FindFileData.cFileName, "."))
		{
			for (int i = 0; i < level; ++i)
				cout << "  ";
			cout << FindFileData.cFileName << endl;
			if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				sprintf(find_path, "%s%s\\", path, FindFileData.cFileName);
				show_file(find_path, level + 1);
			}
		}
		bContinue = FindNextFile(hFind, &FindFileData);
	}
}
int main()
{
	char szPath[] = "f:\\c程序\\";
	show_file(szPath);
	return 0;
}
*/
void my_fenge(char *p,char *s,int i)
{
	FILE *fr = fopen(p, "rb");
	assert(fr != NULL);
	char *buff = (char*)malloc(1024 * 1024 * 5 * sizeof(char));
	assert(buff != NULL);
	int h = fseek(fr, 0, SEEK_END);
	if (h != 0)
	{
		exit(-1);
	}
	long pos = ftell(fr)/(1024 * 1024 * 5 * i) + 1;
	fseek(fr, 0, SEEK_SET);
	int rs;
	for (int j = 0; j<pos; j++)
	{
		FILE *fw = fopen(s, "wb");
		assert(fw != NULL);
		while ((i--)&&((rs = fread(buff, sizeof(char), 1024 * 1024 * 5, fr)) > 0))
		{
			fwrite(buff, sizeof(char), rs, fw);
		}
		i = 10;
		fclose(fw);
		s[3]++;
	}
	s[3] = '1';
	fclose(fr);
	free(buff);
}
void my_hebing(char *p, char *s, int i)
{
	FILE *fw = fopen(s, "wb");
	assert( fw != NULL);
	char *buff = (char*)malloc(1024 * 1024 * 5 * sizeof(char));
	assert(buff != NULL);
	int rs;
	for (int j = 0; j < i; j++)
	{
		FILE *fr = fopen(p, "rb");
		assert(fr != NULL);
		while ((rs = fread(buff, sizeof(char), 1024 * 1024 * 5, fr)) >  0)
		{
			fwrite(buff, sizeof(char), rs, fw);
		}
		fclose(fr);
		p[3]++;
	}
	fclose(fw);
	free(buff);
}
int main()
{
	int i = 10;
	char src_path[] = "g:\\视频\\录像1.exe";
	char dst_path[] = "f:\\1.txt";
	char arr[] = "e:\\录像1.exe";
	my_fenge(src_path, dst_path,i);
	my_hebing(dst_path, arr, 5);
	return 0;
}
