#include <stdio.h>
#include "POLY.h"
#include <vld.h>


int main()
{
	NODE headA;
	CreatePloy(&headA);
	DisplayPoly(&headA);

	NODE headB;
	CreatePloy(&headB);
	DisplayPoly(&headB);

	//AddPoly(&headA, &headB);
	//DisplayPoly(&headA);

	//SubPoly(&headA, &headB);
	//DisplayPoly(&headA);

	MulPoly(&headA, &headB);
	DisplayPoly(&headA);
	DestoryList(&headA);
	DestoryList(&headB);
	return 0;
}