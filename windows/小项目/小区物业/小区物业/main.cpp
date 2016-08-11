#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <malloc.h>

/* ҵ���ṹ�� */
struct yezhu {
	char id[100];
	char name[20];
	int age;
	int family_num;
	int floor_num;
	char room_num[100];
	float lost;
	int area;
	char rz_time[20];
	struct yezhu *next;
};

/* ��ҵ��Ϣ�ṹ�� */
struct wuye {
	char ID[100];
	int last_year;
	int last_month;
	float money;
	int to_time;
	struct wuye *link;
};
struct yezhu *phead; //ҵ��ͷ���
struct wuye *pHead; //��ҵͷ���

/* ���˵� */
int mainmenu()
{
	int n;
	printf("**��ӭ����С����ҵ����ϵͳ**\n");
	printf("----------------------------\n");
	printf("* * * ����ѡ�����1��3��* * *\n");
	printf("* *\n");
	printf("* *\n");
	printf("* ����ҵ��Ϣϵͳ�� *\n");
	printf("* *\n");
	printf("* ��ͳ�Ʋ�ѯϵͳ�� *\n");
	printf("* *\n");
	printf("* ���˳����� *\n");
	printf("* *\n");
	printf("----------------------------\n");
	printf("��������ѡ����:");
	scanf("%d", &n);
	return n;
}

/* ���ҵ����Ϣ��� */
struct yezhu *AddYezhuNode(struct yezhu *p)
{
	struct yezhu *t;
	if (phead == NULL)
	{
		phead = p;
		p->next = NULL;
	}
	else
	{
		t = phead;
		while (t->next != NULL)
			t = t->next;
		t->next = p;
		p->next = NULL;
		return phead;
	}
}

/* ������ҵ��Ϣ */
struct wuye *findWyById(char *id)
{
	struct wuye *p;
	p = pHead;
	while (p != NULL)
	{
		if (strcmp(p->ID, id) == 0)
			return p;
		p = p->link;
	}
	return NULL;
}

/* ͨ��ID����ҵ����Ϣ */
struct yezhu *findYzById(char *id)
{
	struct yezhu *p;
	p = phead;
	while (p != NULL)
	{
		if (strcmp(p->id, id) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

void Display(struct wuye *p)
{
	printf("ҵ��ID:%s\n", p->ID);
	printf("���һ�νɷ����ڣ�%d��%d��\n", p->last_year, p->last_month);
	printf("���һ�νɷѽ�%f\n", p->money);
	printf("������Ч�ڣ�%d����\n", p->to_time);
}

/* Ƿ������ */
void mychaozhao()// 
{
	int year, month;
	struct wuye *k;
	struct yezhu *l;
	k = pHead;
	l = phead;
	printf("�����뵱ǰ��ݣ�");
	scanf("%d", &year);
	printf("�����뵱ǰ�·ݣ�");
	scanf("%d", &month);
	while (k != NULL)
	{
		if (year>k->last_year)
		{
			l = findYzById(k->ID);
			l->lost = (float)(month + 12 - k->to_time - k->last_month)*(0.4*l->area);
			if (l->lost>0)
			{
				printf("ҵ��ID*:%s\n", l->id);
				printf("ҵ������*��%s\n", l->name);
				printf("���һ�νɷ����ڣ�%d��%d��\n", k->last_year, k->last_month);
				printf("Ƿ�ѽ��*��%f\n", l->lost);
				printf("\n\n");
			}
		}
		if (year == k->last_year)
		{
			l = findYzById(k->ID);
			l->lost = (float)(month - k->to_time - k->last_month)*(0.4*l->area);
			if (l->lost>0)
			{
				printf("ҵ��ID:%s\n", l->id);
				printf("ҵ��������%s\n", l->name);
				printf("���һ�νɷ����ڣ�%d��%d��\n", k->last_year, k->last_month);
				printf("Ƿ�ѽ�%f\n", l->lost); printf("\n\n");
			}
		}
		k = k->link;
	}
}

/* ��ѯ�ɷ� */
void myfind()
{
	struct wuye *p;
	char a[100];
	printf("������Ҫ���ҵ�ҵ��id��");
	scanf("%s", a);
	p = findWyById(a);
	if (p != NULL)
	{
		printf("ҵ���Ѿ����!\n");
	}
	else
	{
		printf("ҵ����û�����Ϣ!\n");
		return;
	}
	Display(p);
}

/* ͳ�Ʋ�ѯ�˵���ʾ */
void tongjimenu()
{
	int choose;
	do {
		printf("********ͳ�Ʋ�ѯϵͳ********\n");
		printf("----------------------------\n");
		printf("* * * ����ѡ�����1��3��* * *\n");
		printf("* *\n");
		printf("* *\n");
		printf("* ����ѯ�ɷ���Ϣ�� *\n");
		printf("* *\n");
		printf("* ��Ƿ������һ���� *\n");
		printf("* *\n");
		printf("* ���������˵��� *\n");
		printf("* * * * * * * * * * * * * * *\n");
		printf("��������ѡ����:");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1: myfind();
			break;
		case 2: mychaozhao();
			break;
		case 3: return;
		default: printf("�����������������!\n\n");
		}
	} while (1);
}

/* ����ҵ����Ϣ���ļ� */
void SaveYezhu(struct yezhu *p)
{
	FILE *fp;
	fp = fopen("/storage/emulated/0/cyuyan/profiles/yezhu.dat", "wb");
	p = phead;
	while (p != NULL)
	{
		fwrite(p, sizeof(struct yezhu), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

/* ¼��ҵ����Ϣ */
void AddYezhu()
{
	struct yezhu *p;
	p = (struct yezhu *)malloc(sizeof(struct yezhu));
	printf("��¼��ҵ����Ϣ��\n");
	printf("ID:");
	scanf("%s", p->id);
	printf("����:");
	scanf("%s", p->name);
	printf("���䣺");
	scanf("%d", &p->age);
	printf("��ͥ��Ա����");
	scanf("%d", &p->family_num);
	printf("����¥�ţ�");
	scanf("%d", &p->floor_num);
	printf("��Ԫ�����:");
	scanf("%s", p->room_num);
	printf("סլ���:");
	scanf("%d", &p->area);
	printf("��סʱ�䣺");
	scanf("%s", p->rz_time);
	AddYezhuNode(p);
	SaveYezhu(p);
	printf("¼��ɹ�!\n");
}


/* �޸�ҵ����Ϣ */
void UpdateYezhu()
{
	struct yezhu *k;
	char id[100];
	printf("������Ҫ�޸ĵ�ҵ��ID:");
	scanf("%s", id);
	k = findYzById(id);
	if (k != NULL)
	{
		printf("������Ҫ�޸ĵ�ҵ����Ϣ��\n");
		printf("ID:");
		scanf("%s", k->id);
		printf("����:");
		scanf("%s", k->name);
		printf("���䣺");
		scanf("%d", &k->age);
		printf("��ͥ��Ա����");
		scanf("%d", &k->family_num);
		printf("����¥�ţ�");
		scanf("%d", &k->floor_num);
		printf("��Ԫ�����:");
		scanf("%s", k->room_num);
		printf("סլ���:");
		scanf("%d", &k->area);
		printf("��סʱ�䣺");
		scanf("%s", k->rz_time);
		SaveYezhu(k);
		printf("�޸ĳɹ�!\n");
	}
	else
	{
		printf("�޴�ҵ��ID!\n");
		return;
	}
}

/* ������ҵ��Ϣ���ļ� */
void SaveWuye(struct wuye *p)
{
	FILE *fp;
	fp = fopen("/storage/emulated/0/cyuyan/profiles/wuye.dat", "wb");
	p = pHead;
	while (p != NULL)
	{
		fwrite(p, sizeof(struct wuye), 1, fp);
		p = p->link;
	}
	fclose(fp);
}

/* ɾ��ҵ����Ϣ */
void DelYezhu()
{
	struct yezhu *p, *pp;
	struct wuye *k, *kk;
	char id[100];
	pp = phead;
	kk = pHead;
	printf("������Ҫɾ���˵�ID:");
	scanf("%s", id);
	p = findYzById(id);
	k = findWyById(id);
	if (p != NULL)
	{
		if (p == phead)
		{
			phead = p->next;
			free(p);
		}
		else
		{
			while (pp->next != p)
				pp = pp->next;
			pp->next = p->next;
			free(p);
		}
	}
	else
	{
		printf("�޴�ҵ��ID!\n");
		return;
	}
	printf("ɾ��ҵ����Ϣ�ɹ�!\n");
	SaveYezhu(p);
	if (k != NULL)
	{
		if (k == pHead)
		{
			pHead = k->link;
			free(k);
		}
		else
		{
			while (kk->link != k)
				kk = kk->link;
			kk->link = k->link;
			free(k);
		}
	}
	else
	{
		printf("�޴�ҵ��ID!\n");
		return;
	}
	printf("ɾ����ҵ��Ϣ�ɹ�!\n");
	SaveWuye(k);
}


/* ���ҵ����Ϣ */
void DisplayYezhu()
{
	struct yezhu *p;
	p = phead;
	while (p != NULL)
	{
		printf("\n\n");
		printf("ID:%s\n", p->id);
		printf("����:%s\n", p->name);
		printf("���䣺%d\n", p->age);
		printf("��ͥ��Ա����%d\n", p->family_num);
		printf("����¥�ţ�%d\n", p->floor_num);
		printf("��Ԫ�����:%s\n", p->room_num);
		printf("סլ���:%d\n", p->area);
		printf("��סʱ�䣺%s\n", p->rz_time);
		printf("\n\n");
		p = p->next;
	}
}

/* ҵ���˵����� */
void yezhumenu()
{
	int choose;
	do {
		printf("******ҵ����Ϣ�༭ϵͳ******\n");
		printf("----------------------------\n");
		printf("* * * ����ѡ�����1��5��* * *\n");
		printf("* *\n");
		printf("* *\n");
		printf("* ��ҵ����Ϣ¼�룻 *\n");
		printf("* *\n");
		printf("* ��ҵ����Ϣ�޸ģ� *\n");
		printf("* *\n");
		printf("* ��ҵ����Ϣɾ���� *\n");
		printf("* *\n");
		printf("* ��ҵ����Ϣ����� *\n");
		printf("* *\n");
		printf("* �������ϼ��˵��� *\n");
		printf("* * * * * * * * * * * * * * *\n");
		printf("������ѡ����");
		scanf("%d", &choose);
		//getchar(); 
		switch (choose)
		{
		case 1:AddYezhu();
			break;
		case 2:UpdateYezhu();
			break;
		case 3:DelYezhu();
			break;
		case 4:DisplayYezhu();
			break;
		case 5: return;
		default: printf("����������������룺\n");
		}
	} while (1);
}

/* �����ҵ��Ϣ��� */
struct wuye *AddWyNode(struct wuye *p)
{
	struct wuye *t;
	if (pHead == NULL)
	{
		pHead = p;
		p->link = NULL;
	}
	else
	{
		t = pHead;
		while (t->link != NULL)
			t = t->link;
		t->link = p;
		p->link = NULL;
	}
	return pHead;
}


/* ¼����ҵ��Ϣ */
void AddWuye()
{
	struct wuye *p;
	struct yezhu *t;
	int x;
	p = (struct wuye *)malloc(sizeof(struct wuye));
	printf("��¼����ҵ��Ϣ��\n");
	printf("ID:");
	scanf("%s", p->ID);
	t = findYzById(p->ID);
	if (t != NULL)
	{
		printf("��һ�νɷ���ݣ�");
		scanf("%d", &p->last_year);
		printf("�·ݣ�");
		scanf("%d", &p->last_month);
		printf("�ɷѽ�");
		scanf("%f", &p->money);
		x = p->money / (0.4*t->area);
		p->to_time = (int)x;
		AddWyNode(p);
		SaveWuye(p);
		printf("¼��ɹ�!\n");
	}
	else
	{
		printf("�޴�ҵ��ID!\n");
		return;
	}
}




/* �޸���ҵ��Ϣ */
void UpdateWuye()//
{
	char id[20];
	int x;
	struct wuye *k;
	struct yezhu *t;
	printf("������Ҫ�޸ĵ�ҵ��ID:");
	scanf("%s", id);
	if (k != NULL)
	{
		printf("��Ҫ�޸ĵ���ϢΪ��\n");
		printf("�������µ���Ϣ��\n");
		printf("ID:");
		scanf("%s", k->ID);
		printf("��һ�νɷ���ݣ�");
		scanf("%d", &k->last_year);
		printf("�·ݣ�");
		scanf("%d", &k->last_month);
		printf("�ɷѽ�");
		scanf("%f", &k->money);
		t = findYzById(k->ID);
		x = (int)k->money / (0.4*t->area);
		k->to_time = (int)x;
		AddWyNode(k);
		SaveWuye(k);
		printf("�޸ĳɹ�!\n");
	}
	else
	{
		printf("�޴�ҵ��ID!\n");
		return;
	}
}

/* ɾ����ҵ��Ϣ */
void DelWuye()// 
{
	struct wuye *p, *pp;
	char id[100];
	pp = pHead;
	printf("������Ҫɾ���˵�ID:");
	scanf("%s", id);
	p = findWyById(id);
	if (p != NULL)
	{
		if (p == pHead)
		{
			pHead = p->link;
			free(p);
		}
		else
		{
			while (pp->link != p)
				pp = pp->link;
			pp->link = p->link;
			free(p);
		}
	}
	else
	{
		printf("�޴�ҵ��ID!\n");
		return;
	}
	SaveWuye(p);
	printf("ɾ���ɹ�!\n");
}

/* �����ҵ��Ϣ */
void DisplayWuye()
{
	struct wuye *p;
	p = pHead;
	while (p != NULL)
	{
		printf("ID:%s\n", p->ID);
		printf("���һ�νɷ����ڣ�%d��%d��\n", p->last_year, p->last_month);
		printf("�ɷѽ��:%fԪ\n", p->money);
		printf("������Ч�ڣ�%d����\n", p->to_time);
		printf("\n\n\n");
		p = p->link;
	}
}


/* ���ļ��л�ȡ��ҵ��Ϣ */
void ReadWuye()
{
	FILE *fp;
	struct wuye *p;
	fp = fopen("/storage/emulated/0/cyuyan/profiles/wuye.dat", "rb");
	while (1)
	{
		p = (struct wuye *)malloc(sizeof(struct wuye));
		if (feof(fp))
			break;
		if (fread(p, sizeof(struct wuye), 1, fp))
			AddWyNode(p);
	}
	fclose(fp);
}

/* ��ҵ�˵� */
void wuyemenu()
{
	int choose = 0;
	do {
		printf("******��ҵ���ù���ϵͳ******\n");
		printf("----------------------------\n");
		printf("* * * ����ѡ�����1��5��* * *\n");
		printf("* * \n");
		printf("* *\n");
		printf("* ����ҵ��Ϣ¼�룻 *\n");
		printf("* *\n");
		printf("* ����ҵ��Ϣ�޸ģ� *\n");
		printf("* *\n");
		printf("* ����ҵ��Ϣɾ���� *\n");
		printf("* *\n");
		printf("* ����ҵ��Ϣ����� *\n");
		printf("* *\n");
		printf("* �������ϼ��˵��� *\n");
		printf("* * * * * * * * * * * * * * *\n");
		printf("������ѡ�");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1: AddWuye();
			break;
		case 2: UpdateWuye();
			break;
		case 3: DelWuye();
			break;
		case 4: DisplayWuye();
			break;
		case 5: return;
		default:printf("����������������룺\n");
		}
	} while (1);
}


/* ��ҵ��Ϣ�˵���ʾ */
void xinximenu()
{
	int choose;
	do {
		printf("********��ҵ��Ϣϵͳ********\n");
		printf("----------------------------\n");
		printf("* * * ����ѡ�����1��3��* * *\n");
		printf("* *\n");
		printf("* *\n");
		printf("* ��С��ҵ����Ϣ���� *\n");
		printf("* *\n");
		printf("* ����ҵ������Ϣ���� *\n");
		printf("* *\n");
		printf("* ���������˵��� *\n");
		printf("* * * * * * * * * * * * * * *\n");
		printf("��������ѡ����:");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:yezhumenu();
			break;
		case 2:wuyemenu();
			break;
		case 3:return;
		default:printf("����������������룺\n");
		}
	} while (1);
}

/* ���ļ��л�ȡҵ����Ϣ */
void ReadYezhu()
{
	FILE *fp;
	struct yezhu *p;
	fp = fopen("/storage/emulated/0/cyuyan/profiles/yezhu.dat", "rb");
	while (1)
	{
		p = (struct yezhu *)malloc(sizeof(struct yezhu));
		if (feof(fp))
		{
			break;
		}
		if (fread(p, sizeof(struct yezhu), 1, fp))
		{
			AddYezhuNode(p);
		}
	}
	fclose(fp);
}

void main()//
{
	int m;
	ReadYezhu();
	ReadWuye();//��һ��û����Ϣ�������ã�����
	do {
		m = mainmenu();
		switch (m)
		{
		case 1:
			xinximenu();
			break;
		case 2:
			tongjimenu();
			break;
		case 3:
			printf("******ллʹ�ã��ټ�!*******\n");
			exit(0);
		}
	} while (1);
}