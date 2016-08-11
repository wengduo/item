
typedef int ELEM_TYPE;


typedef struct _SEQ_LIST// _DSEQ_LIST
{
	ELEM_TYPE *elem;   //存储空间的基址
	int length;       //链表当前长度
	int TotalLength;//线性链表存储空间的分配增量
	int n;       //线性链表存储空间的大小
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