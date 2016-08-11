#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp = NULL, *fpj = NULL, *fps = NULL;
int i, choice;
typedef struct book{
	char name[8];
	char num[8];
	int kucun;
	int jiechu;
}bo;
typedef struct student{
	char name[8];
	char num[8];
	int jie;
}st;
typedef struct jieyue{
	char snum[8];
	char bnum[8];
}ji;

/* �˵� */
void menu()
{
	printf("\n");
	printf("**********���˵�*********\n");
	printf("    1-----ͼ��¼��\n");
	printf("    2-----ͼ�����\n");
	printf("    3-----ͼ���ѯ\n");
	printf("    4-----�޸�ɾ��ͼ��\n");
	printf("    5-----����ͼ��\n");
	printf("    6-----�黹ͼ��\n");
	printf("    7-----���Ĳ�ѯ\n");
	printf("*************************\n");
}

/* ¼��ͼ�� */
void end()
{
	bo boo, booq;
	printf("������ͼ����(���6���ַ�)��\n");
	scanf("%s", boo.name);
	do{
		i = 1;
		printf("������ͼ����(���6���ַ�)��\n");
		scanf("%s", boo.num);
		fread(&booq, sizeof(bo), 1, fp);
		while (!feof(fp)){
			if (strcmp(booq.num, boo.num) == 0){
				printf("\n�ñ���Ѵ�������������\n\n");
				i = 0;
				break;
			}
			fread(&booq, sizeof(bo), 1, fp);
		}
		rewind(fp);
	} while (i == 0);

	printf("������ͼ���������\n");
	scanf("%d", &boo.kucun);
	boo.jiechu = 0;
	getchar();
	fseek(fp, 0, 2);
	fwrite(&boo, sizeof(bo), 1, fp);

	printf("\n¼��ɹ�����������������˵�");
	__fpurge(stdin);
	getchar();
	system("clear");
}

/* ���ͼ�� */
void print()
{
	bo boo;
	printf("  ����  ���  ԭ���  ���\n");
	fread(&boo, sizeof(bo), 1, fp);
	while (feof(fp) == 0){
		printf("%6s%6s%8d%6d\n", boo.name, boo.num, boo.kucun, boo.jiechu);
		fread(&boo, sizeof(bo), 1, fp);
	}
	printf("\n�����ϣ���������������˵�");
	__fpurge(stdin);
	getchar();
	system("clear");
}

/* �Ա������ַ�������ضȣ����ھ�ȷ������ */
int dui(char *p, char *p1)
{
	int bao = 0, fan = 1;
	for (i = 0; i<(int)strlen(p1); i++){
		if (p[0] == p1[i]){
			bao = i;
			break;
		}
	}

	if ((int)strlen(p)>(int)strlen(p1) - bao + 1)
		return 0;
	else
	for (i = 0; i<(int)strlen(p); i++){
		if (p[i] != p1[bao + i])
			fan = 0;
	}
	return fan;
}

/* ��ѯͼ�� */
void find()
{
	char hao[10];
	int fan = 1;
	int bian = 1;
	bo boo;
	printf("��ѡ���ѯ���ͣ�\n    1-��ͼ����ģ����ѯ\n    2-��ͼ�����ؼ��ֲ�ѯ\n    3-��ͼ���ž�ȷ��ѯ\n    4-��ͼ������ȷ��ѯ\n  ��ѡ��");
	scanf("%d", &choice);
	if (choice == 1){
		printf("��������(���6���ַ�)��");
		scanf("%s", hao);
		printf("���  ����  ���  ԭ���  ���\n");
		fread(&boo, sizeof(bo), 1, fp);
		while (!feof(fp)){
			fan = dui(hao, boo.num);
			if (fan == 1){
				printf("%4d%6s%6s%8d%6d\n", bian, boo.name, boo.num, boo.kucun, boo.jiechu);
				bian++;
			}
			fread(&boo, sizeof(bo), 1, fp);
		}
	}
	else if (choice == 2){
		printf("������ͼ�����ؼ���(���6���ַ�)��");
		scanf("%s", hao);
		printf("���  ����  ���  ԭ���  ���\n");
		fread(&boo, sizeof(bo), 1, fp);
		while (!feof(fp)){
			fan = dui(hao, boo.name);
			if (fan == 1)
				printf("%4d%6s%6s%8d%6d\n", bian, boo.name, boo.num, boo.kucun, boo.jiechu);
			fread(&boo, sizeof(bo), 1, fp);
		}
	}
	else if (choice == 4){
		printf("������ͼ����(���6���ַ�)��");
		scanf("%s", hao);
		printf("���  ����  ���  ԭ���  ���\n");
		while (!feof(fp)){
			if (strcmp(hao, boo.name) == 0)
				printf("%4d%6s%6s%8d%6d\n", bian, boo.name, boo.num, boo.kucun, boo.jiechu);
			fread(&boo, sizeof(bo), 1, fp);
		}

	}
	else if (choice == 3){
		printf("������ͼ����(���6���ַ�)��");
		scanf("%s", hao);
		printf("���  ����  ���  ԭ���  ���\n");
		while (!feof(fp)){
			if (strcmp(hao, boo.num) == 0)
				printf("%4d%6s%6s%8d%6d\n", bian, boo.name, boo.num, boo.kucun, boo.jiechu);
			fread(&boo, sizeof(bo), 1, fp);
		}

	}
	else{
		printf("������������˳���");
		return;
	}

	printf("\n��ѯ��ϣ���������������˵�");
	__fpurge(stdin);
	getchar();
	system("clear");
}

/* �޸�ɾ��ͼ�� */
void del()
{
	FILE *p;
	ji jie;
	int j = 0;
	char num[10];
	bo boo, booq;
	int xu;
	char or;
	char cha[10];
	printf("\nɾ���޸�ͼ��ֻ��ͨ��ͼ��������ɣ�\n�Ƿ����ͼ���ѯ����ѯ��Ҫ������ͼ���ţ�Y/N��\n");
	getchar();
	scanf("%c", &or);
	if (or == 'Y' || or == 'y'){
		find();
		rewind(fp);
	}
	printf("\n��������Ҫ������ͼ��ı�ţ�����������ı�ţ��������κβ�������");
	scanf("%s", cha);
	fread(&jie, sizeof(ji), 1, fpj);
	while (!feof(fpj)){
		if (strcmp(jie.bnum, cha) == 0){
			printf("\n�Ȿ�������˽��ģ����ܲ�����\n�����˳� ");
			return;
		}
		fread(&jie, sizeof(ji), 1, fpj);
	}
	printf("\n\n1-ɾ��ͼ��   2-�޸�ͼ��\n\n");
	printf("��ѡ��������ͣ�");
	scanf("%d", &choice);
	fread(&boo, sizeof(bo), 1, fp);
	p = fopen("/storage/emulated/0/cyuyan/profiles/books1.txt", "wb+");
	while (!feof(fp)){
		j++;
		if (strcmp(boo.num, cha) == 0){
			if (choice == 2){
				printf("\n\n1-����    2-���    3-���\n\n");
				printf("��ѡ��Ҫ�޸ĵ���Ŀ:");
				scanf("%d", &xu);
				if (xu == 1){
					printf("��Ҫ��%s��Ϊ��", boo.name);
					scanf("%s", boo.name);
				}
				else if (xu == 2){
					do{
						i = 1;
						printf("��Ҫ��%s��Ϊ��", boo.num);
						scanf("%s", num);
						rewind(fp);
						fread(&booq, sizeof(bo), 1, fp);
						while (!feof(fp)){
							if (strcmp(booq.num, num) == 0){
								printf("\n�ñ���Ѵ�������������\n\n");
								i = 0;
								break;
							}
							fread(&booq, sizeof(bo), 1, fp);
						}
					} while (i == 0);
					rewind(fp);
					for (i = 0; i<j; i++){
						fread(&boo, sizeof(bo), 1, fp);
						strcpy(boo.num, num);
					}
				}
				else if (xu == 3){
					printf("��Ҫ��%d��Ϊ��", &boo.kucun);
					scanf("%d", &boo.kucun);
				}
				fwrite(&boo, sizeof(bo), 1, p);
			}
		}
		else
			fwrite(&boo, sizeof(bo), 1, p);
		fread(&boo, sizeof(bo), 1, fp);
	}
	fclose(p);
	p = fopen("/storage/emulated/0/cyuyan/profiles/books1.txt", "rb+");
	fclose(fp);
	fp = fopen("/storage/emulated/0/cyuyan/profiles/book.txt", "wb+");
	fread(&boo, sizeof(bo), 1, p);
	while (!feof(p)){
		fwrite(&boo, sizeof(bo), 1, fp);
		fread(&boo, sizeof(bo), 1, p);
	}
	fclose(fp);

	printf("\n�����ɹ�����������������˵�");
	__fpurge(stdin);
	getchar();
	system("clear");
}

/* ����ͼ�� */
void lend()
{
	bo boo;
	FILE *p;
	st stu;
	ji jie;
	int j = 0;
	char or, num[10], xnum[10];
	printf("\n����ͼ��ֻ��ͨ��ͼ������ɣ�\n�Ƿ����ͼ���ѯ����ѯ��Ҫ������ͼ���ţ�Y/N��\n");
	getchar();
	scanf("%c", &or);
	if (or == 'Y' || or == 'y')
		find();
	printf("\n��������Ҫ���ĵ�ͼ��ı�ţ�");
	scanf("%s", num);
	fread(&boo, sizeof(bo), 1, fp);
	while (!feof(fp)){
		if (strcmp(num, boo.num) == 0){
			j = 1;
			break;
		}
		fread(&boo, sizeof(bo), 1, fp);
	}
	if (j == 0){
		printf("\n���û�и�ͼ�� �����˳�\n");
		return;
	}
	printf("\n����Ҫ���ĵ�ͼ���ǣ�\n");
	printf("  ����  ���  ԭ���  ���\n");
	printf("%6s%6s%8d%6d\n", boo.name, boo.num, boo.kucun, boo.jiechu);
	if (boo.kucun == boo.jiechu){
		printf("\n�ò�ͼ����ȫ������������˳�\n");
		return;
	}
	printf("\n���������ѧ�ţ�");
	scanf("%s", xnum);
	j = 0;
	fread(&jie, sizeof(ji), 1, fpj);
	while (!feof(fpj)){
		if ((strcmp(jie.bnum, num) == 0) && (strcmp(jie.snum, xnum) == 0)){
			j = 1;
			break;
		}
		fread(&jie, sizeof(ji), 1, fpj);
	}
	if (j == 1){
		printf("\n���Ѿ����Ĺ�����  �����˳�\n");
		return;
	}
	fread(&stu, sizeof(st), 1, fps);
	j = 0;
	while (!feof(fps)){
		if (strcmp(xnum, stu.num) == 0){
			j = 1;
			break;
		}
		fread(&stu, sizeof(st), 1, fps);
	}
	if (j == 0){
		printf("\n���ǵ�һ�ν���ͼ�飬Ϊ�˷���������������������");
		scanf("%s", stu.name);
		strcpy(stu.num, xnum);
		stu.jie = 1;
		fseek(fps, 0, 2);
		fwrite(&stu, sizeof(st), 1, fps);
	}
	else{
		if (stu.jie == 5){//������Կ���ÿ��ѧ�����輸����
			printf("\n���Ѿ�����5���飬�����ٽ�\n");
			return;
		}
		p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "wb+");
		rewind(fps);
		fread(&stu, sizeof(st), 1, fps);
		while (!feof(fps)){
			if (strcmp(xnum, stu.num) == 0)
				stu.jie++;
			fwrite(&stu, sizeof(st), 1, p);
			fread(&stu, sizeof(st), 1, fps);
		}
		fclose(p);
		fclose(fps);
		p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "rb+");
		fps = fopen("/storage/emulated/0/cyuyan/profiles/student.txt", "wb+");
		fread(&stu, sizeof(st), 1, p);
		while (!feof(p)){
			fwrite(&stu, sizeof(st), 1, fps);
			fread(&stu, sizeof(st), 1, p);
		}
	}
	strcpy(jie.bnum, num);
	strcpy(jie.snum, xnum);
	fseek(fpj, 0, 2);
	fwrite(&jie, sizeof(ji), 1, fpj);
	rewind(fp);
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "wb+");
	fread(&boo, sizeof(bo), 1, fp);
	while (!feof(fp)){
		if (strcmp(num, boo.num) == 0)
			boo.jiechu++;
		fwrite(&boo, sizeof(bo), 1, p);
		fread(&boo, sizeof(bo), 1, fp);
	}
	fclose(p);
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "rb+");
	fclose(fp);
	fp = fopen("/storage/emulated/0/cyuyan/profiles/book.txt", "wb+");
	fread(&boo, sizeof(bo), 1, p);
	while (!feof(p)){
		fwrite(&boo, sizeof(bo), 1, fp);
		fread(&boo, sizeof(bo), 1, p);
	}

	printf("\n���ĳɹ�����������������˵�");
	__fpurge(stdin);
	getchar();
	system("clear");
}

/* �黹ͼ�� */
void huan(){
	FILE *p;
	bo boo;
	ji jie;
	st stu;
	int j = 0;
	char snum[10], bnum[10];
	i = 0;
	printf("\n���������ѧ�ţ�");
	scanf("%s", snum);
	printf("\n�����������ͼ��\n");
	fread(&jie, sizeof(ji), 1, fpj);
	printf("  ����  ���  ԭ���  ���\n");
	while (!feof(fpj)){
		if (strcmp(jie.snum, snum) == 0){
			fread(&boo, sizeof(bo), 1, fp);
			while (!feof(fp)){
				if (strcmp(jie.bnum, boo.num) == 0){
					printf("%6s%6s%8d%6d\n", boo.name, boo.num, boo.kucun, boo.jiechu);
					j = 1;
				}
				fread(&boo, sizeof(bo), 1, fp);
			}
		}
		fread(&jie, sizeof(ji), 1, fpj);
	}
	if (j == 0){
		printf("\n��û�н����κ�ͼ�飡\n\n�����˳�");
		return;
	}
	rewind(fp);
	rewind(fpj);
	printf("\n��������黹��ͼ��ı�ţ�");
	scanf("%s", bnum);
	fread(&jie, sizeof(jie), 1, fpj);//�ı�jieyue.txt�������
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "wb+");
	while (!feof(fpj)){
		if ((strcmp(jie.bnum, bnum) == 0) && (strcmp(jie.snum, snum) == 0))
			i = 1;
		else
			fwrite(&jie, sizeof(jie), 1, p);
		fread(&jie, sizeof(jie), 1, fpj);
	}
	if (i == 0){
		printf("\n��û�н����ͼ��\n�����˳�");
		return;
	}
	fclose(p);
	fclose(fpj);
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "rb+");
	fpj = fopen("/storage/emulated/0/cyuyan/profiles/jieyue.txt", "wb+");
	fread(&jie, sizeof(ji), 1, p);
	while (!feof(p)){
		fwrite(&jie, sizeof(ji), 1, fpj);
		fread(&jie, sizeof(ji), 1, p);
	}
	fclose(p);//�ı�book.txt�������
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "wb+");
	fread(&boo, sizeof(bo), 1, fp);
	while (!feof(fp)){
		if (strcmp(bnum, boo.num) == 0)
			boo.jiechu--;
		fwrite(&boo, sizeof(bo), 1, p);
		fread(&boo, sizeof(bo), 1, fp);
	}
	fclose(p);
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "rb+");
	fclose(fp);
	fp = fopen("/storage/emulated/0/cyuyan/profiles/book.txt", "wb+");
	fread(&boo, sizeof(bo), 1, p);
	while (!feof(p)){
		fwrite(&boo, sizeof(bo), 1, fp);
		fread(&boo, sizeof(bo), 1, p);
	}
	fclose(p);//�ı�student.txt�������
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "wb+");
	rewind(fps);
	fread(&stu, sizeof(st), 1, fps);
	while (!feof(fps)){
		if (strcmp(snum, stu.num) == 0)
			stu.jie--;
		fwrite(&stu, sizeof(st), 1, p);
		fread(&stu, sizeof(st), 1, fps);
	}
	fclose(p);
	fclose(fps);
	p = fopen("/storage/emulated/0/cyuyan/profiles/jie.txt", "rb+");
	fps = fopen("/storage/emulated/0/cyuyan/profiles/student.txt", "wb+");
	fread(&stu, sizeof(st), 1, p);
	while (!feof(p)){
		fwrite(&stu, sizeof(st), 1, fps);
		fread(&stu, sizeof(st), 1, p);
	}

	printf("\n�黹�ɹ�����������������˵�");
	__fpurge(stdin);
	getchar();
	system("clear");
}

/* ���Ĳ�ѯ */
void cha(){
	char num[10];
	bo boo;
	ji jie;
	printf("\n���������ѧ�ţ�");
	scanf("%s", num);
	fread(&jie, sizeof(ji), 1, fpj);
	printf("  ����  ���  ԭ���  ���\n");

	while (!feof(fpj)){
		if (strcmp(jie.snum, num) == 0){
			fread(&boo, sizeof(bo), 1, fp);
			while (!feof(fp)){
				if (strcmp(jie.bnum, boo.num) == 0)
					printf("%6s%6s%8d%6d\n", boo.name, boo.num, boo.kucun, boo.jiechu);
				fread(&boo, sizeof(bo), 1, fp);
			}
		}
		fread(&jie, sizeof(ji), 1, fpj);
	}


	printf("\n��ѯ��ϣ���������������˵�");
	__fpurge(stdin);
	getchar();
	system("clear");
}
void main(){
	menu();
	printf("  ��ѡ��:");
	scanf("%d", &choice);

	while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7){
		fp = fopen("/storage/emulated/0/cyuyan/profiles/book.txt", "rb+");
		if (fp == NULL){
			printf("book.txt open error\n");
			return;
		}
		fps = fopen("/storage/emulated/0/cyuyan/profiles/student.txt", "rb+");
		if (fps == NULL){
			printf("student.txt open error\n");
			return;
		}
		fpj = fopen("/storage/emulated/0/cyuyan/profiles/jieyue.txt", "rb+");
		if (fpj == NULL){
			printf("jieyue.txt open error\n");
			return;
		}
		switch (choice){
		case 0:
			break;
		case 1:
			end();
			break;
		case 2:
			print();
			break;
		case 3:
			find();
			break;
		case 4:
			del();
			break;
		case 5:
			lend();
			break;
		case 6:
			huan();
			break;
		case 7:
			cha();
			break;
		}
		fclose(fp);
		fclose(fpj);
		fclose(fps);
		menu();
		printf("\n  ��ѡ��:");
		scanf("%d", &choice);
	}
}