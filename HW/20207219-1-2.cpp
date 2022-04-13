#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAXSIZE 100
typedef int ElementType;
typedef struct LNode {
    ElementType *Data;
    ElementType Length;
}List;

void Print( List L )
{
	if(L.Length==0) printf("�ü���Ϊ�ռ�");
	for(int i=0;i<L.Length;i++) printf("%d ",L.Data[i]);
	printf("\n");
}
void input_list(List *L)
{
	ElementType ch;
	scanf("%d",&ch);
	while(ch!=-1)
	{
		L->Data[L->Length++]=ch;
		scanf("%d",&ch);
	}
}
int init_list(List *L)
{
	L->Length=0;
	L->Data=(ElementType*)malloc(MAXSIZE*sizeof(ElementType));
	if(!L->Data) return 0;
	return 1;
}
void Union(List *L1,List *L2,List *L3)
{
	ElementType i=0,j=0;
	while((i<L1->Length)&&(j<L2->Length))
	{
		if(L1->Data[i]<L2->Data[j])
		{
			L3->Data[L3->Length++]=L1->Data[i];
			i++;
		}else{
			L3->Data[L3->Length++]=L2->Data[j];
			j++;
		}
	}
	while(i<L1->Length)
	{
		L3->Data[L3->Length++]=L1->Data[i];
		i++;
	}
	while(j<L2->Length)
	{
		L3->Data[L3->Length++]=L2->Data[j];
		j++;
	}
	printf("�ϲ���L3�����");
	Print(*L3);
}
void Delete(List *L)
{
	ElementType i,mp=-1;
	List Lt;
	Lt=*L;
	init_list(L);
	for(i=0;i<Lt.Length;i++)
	{
		if(Lt.Data[i]!=mp) L->Data[L->Length++]=Lt.Data[i];
		mp=Lt.Data[i];
	}
	printf("ȥ�غ�L3�����");
	Print(*L);
}
void Inversion(List *L)
{
	ElementType i,mp=-1;
	List Lt;
	Lt=*L;
	init_list(L);
	for(i=Lt.Length-1;i>=0;i--)
	{
		if(Lt.Data[i]!=mp) L->Data[L->Length++]=Lt.Data[i];
		mp=Lt.Data[i];
	}
	printf("L3���ý����");
	Print(*L);
}
int main()
{
	List L1,L2,L3;
	printf("����ǵݼ������ѭ���L1,������-1����:");
	init_list(&L1);
	input_list(&L1);
	printf("����ǵݼ������ѭ���L2,������-1����:");
	init_list(&L2);
	input_list(&L2);
	printf("\n\n˳���L1Ϊ����ǣ�") ;
	Print(L1);
	printf("˳���L2Ϊ����ǣ�") ;
	Print(L2);
	init_list(&L3);
	Union(&L1,&L2,&L3);
	Delete(&L3);
	Inversion(&L3);

	//system("pause");
	getch();
	return 0;
}
