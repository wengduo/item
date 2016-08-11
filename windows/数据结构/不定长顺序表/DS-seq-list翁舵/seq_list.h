
typedef int ELEM_TYPE;


typedef struct _SEQ_LIST// _DSEQ_LIST
{
	ELEM_TYPE *elem;   //�洢�ռ�Ļ�ַ
	int length;       //����ǰ����
	int TotalLength;//��������洢�ռ�ķ�������
	int n;       //��������洢�ռ�Ĵ�С
}SEQ_LIST;

bool InitSeqList(SEQ_LIST *p);

bool DetorySeqList(SEQ_LIST *p);

bool ClearSeqList(SEQ_LIST *p);

bool IsEmpty(SEQ_LIST *p);

int GetLength(SEQ_LIST *p);

bool Insert(SEQ_LIST *p, int pos, ELEM_TYPE val);

bool IsFull(SEQ_LIST *p);

void DisplaySeqList(SEQ_LIST *p);

bool Delete(SEQ_LIST *p, int pos);

int my_Search(SEQ_LIST *p, ELEM_TYPE val);

bool DeleteVal(SEQ_LIST *p, ELEM_TYPE val);