#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define MAXSIZE 100
typedef char ElementType;
typedef struct LNode {
    ElementType *Data;
    int Length;
}List;
void Union(List *L1,List *L2);         //���� 
void Intersection(List *L1,List *L2);  //���� 
void Difference_set(List *L1,List *L2);//�
void Complement(List *L1,List *L2);    //���� 
int init_list(List *L);                //��ʼ���б� 
void createlist1(List *L);             //�����б� 1
void createlist2(List *L);             //�����б� 2
void input_list();                     //�����б�
int Filter_list(List L,ElementType m); //��̭ѡ�� 
void Print( List L );                  //��� 
void menu();                           //�˵� 


void input_list(List *L)
{
	ElementType ch;
	ch=getchar();
	while(ch!='\n')
	{
		if(Filter_list(*L,ch)) L->Data[L->Length++]=ch;
		ch=getchar();
	}
}
void createlist1(List *L)
{ 
	system("cls");
	printf("�����뼯��L1�����ݣ�\n");
	init_list(L);
	input_list(L);
}
void createlist2(List *L)
{ 
	system("cls");
	printf("�����뼯��L2�����ݣ�\n");
	init_list(L);
	input_list(L);
}
int init_list(List *L)
{
	L->Length=0;
	L->Data=(ElementType*)malloc(MAXSIZE*sizeof(ElementType));
	L->Data[0] =NULL;
	if(!L->Data) return 0;
	return 1;
}
int Filter_list(List L,ElementType ch)
{
	if(ch<'a'||ch>'z') return 0;
	for(int i=0;i<L.Length;i++)
	{
		if(L.Data[i]==ch) return 0;
	}return 1;
}
void Intersection(List *L1,List *L2)
{
	system("cls");
	List L3;
	init_list(&L3);
	printf("����L1���ݣ�");
	Print(*L1);
	printf("����L2���ݣ�");
	Print(*L2);
	for(int i=0;i<L1->Length;i++){
		for(int j=0;j<L2->Length;j++){
			if(L1->Data[i]==L2->Data[j]) 
				L3.Data[L3.Length++]=L1->Data[i];
		}
	}
	printf("\n\nL1��L2�����Ľ����"); 
	Print(L3);
	getchar();
}
void Union(List *L1,List *L2)
{
	system("cls");
	List L3;
	L3=*L1;
	printf("����L1���ݣ�");
	Print(*L1);
	printf("����L2���ݣ�");
	Print(*L2);
	for(int i=0;i<L2->Length;i++) 
	{
		ElementType ch=L2->Data[i];
		if(Filter_list(L3,ch)) L3.Data[L3.Length++]=ch;
	}
	printf("\n\nL1��L2�����Ľ����"); 
	Print(L3);
	getchar();
}
void Difference_set(List *L1,List *L2)
{
	system("cls");
	List L3;
	init_list(&L3);
	printf("����L1���ݣ�");
	Print(*L1);
	printf("����L2���ݣ�");
	Print(*L2);
	printf("\n\nL1��L2�Ĳ�Ľ����");
	for(int i=0;i<L1->Length;i++) 
	{
		ElementType ch=L1->Data[i];
		if(Filter_list(*L2,ch)) L3.Data[L3.Length++]=ch;
	}
	Print(L3);
	init_list(&L3);
	printf("L2��L1�Ĳ�Ľ����");
	for(int i=0;i<L2->Length;i++) 
	{
		ElementType ch=L2->Data[i];
		if(Filter_list(*L1,ch)) L3.Data[L3.Length++]=ch;
	}
	Print(L3);
	getchar();
}
void Complement(List *L1,List *L2)
{
	system("cls");
	List L3,L4;
	init_list(&L3);
	printf("����L1���ݣ�");
	Print(*L1);
	printf("����L2���ݣ�");
	Print(*L2);
	for(int i=97;i<123;i++) 
	{
		L3.Data[L3.Length++]=i;
	}
	printf("ȫ��L3Ϊ��"); 
	Print(L3);
	init_list(&L4);
	printf("\n\nL1�����Ľ����");
	for(int i=0;i<L3.Length;i++) 
	{
		ElementType ch=L3.Data[i];
		if(Filter_list(*L1,ch)) L4.Data[L4.Length++]=ch;
	}
	Print(L4);
	init_list(&L4);
	printf("L2�����Ľ����");
	for(int i=0;i<L3.Length;i++) 
	{
		ElementType ch=L3.Data[i];
		if(Filter_list(*L2,ch)) L4.Data[L4.Length++]=ch;
	}
	Print(L4);
	getchar();
}
void Print( List L )
{
	if(L.Length==0) printf("�ü���Ϊ�ռ�");
	for(int i=0;i<L.Length;i++) printf("%c ",L.Data[i]);
	printf("\n");
}
void menu()
{
	ElementType n;
	List L1,L2;
	init_list(&L1);
	init_list(&L2);
	system("cls");
	while(1)
	{
		system("cls");
		printf("1.���켯��1\n"); 
		printf("2.���켯��2\n"); 
		printf("3.�������Ĳ���\n");
		printf("4.��������Ĳ���\n");
		printf("5.�������Ľ���\n"); 
		printf("6.�������Ĳ\n"); 		 
		printf("7.�˳��ó���\n\n");
		printf("�������ѡ��");
		n=getch();
		switch(n){
			case '1': createlist1(&L1);break;
			case '2': createlist2(&L2);break;
			case '3': Union(&L1,&L2);break;
			case '4': Complement(&L1,&L2);break;
			case '5': Intersection(&L1,&L2);break;
			case '6': Difference_set(&L1,&L2);break;
			case '7': exit(0);
			default:system("cls");printf("�����������������\n\n"); getchar();
		}
		
	}
	return ;
}
int main()
{
	menu();
	return 0;
}
