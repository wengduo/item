



typedef int ELEM_TYPE;


struct _TRIP
{
	ELEM_TYPE e1;
	ELEM_TYPE e2;
	ELEM_TYPE e3;
};

typedef struct _TRIP TRIP;


bool InitTrip(TRIP *p,ELEM_TYPE v1, ELEM_TYPE v2, ELEM_TYPE v3);
bool DestoryTrip(TRIP *p);


//ELEM_TYPE get(TRIP *p, int pos);

bool Get(TRIP *p, int pos, ELEM_TYPE *e);
bool Put(TRIP *p, int pos, ELEM_TYPE e);

bool IsAscending(TRIP *p);
bool IsDescending(TRIP *p);

void Max(TRIP *p, ELEM_TYPE *e);
void Min(TRIP *p, ELEM_TYPE *e);