#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNUM 30
#define MAXSUB 6
static struct stu
{
	char stunum[9];
	char name[20];
	int score[MAXSUB];
	int adds;
	int rank;
	int flag;
}inf[MAXNUM];

static int np,nb;

int menu(){
	int i;
	printf("---------ѧ���ɼ�����ϵͳ---------\n");
	printf( "1���ֶ�¼��\n"
			"2������ÿ�ſγ̵��ֺܷ�ƽ����\n"
			"3����ѧ���ܷ��ɸߵ����ų����α�\n"
			"4����ѧ����С�����ų��ɼ���\n"
			"5����������ѯѧ���������俼�Գɼ�\n"
			"6��ͳ��\n"
			"7�����\n"
			"0���˳�ϵͳ\n"
			"-----��ѡ�������Ӧ�Ĳ˵���-----\n"); 
	printf("������:");
	scanf("%d",&i);
	return i;
}

int checkout(char num[],int j)
{
	int k;
	for(k=0;k<j;k++)
		if(strcmp(inf[k].stunum,num)==0)
			return 0;
	
	return 1;
}

void enter(){
				int i,j,k;
				LOOP1:printf("�밴��ʽ���룺��������30����Ŀ����6��\n������ �ܿ�Ŀ����:");
					  
				scanf("%d %d",&np,&nb);
				if(np<=MAXNUM&&nb<=MAXSUB){
				printf("**********************************\n");
				for(i=0;i<np;i++)
				{
				LOOP2:printf("ѧ��%d-������:\nѧ��:",i+1);
				 	scanf("%s",inf[i].stunum);
					if(strlen(inf[i].stunum)==8&&checkout(inf[i].stunum,i))
						{
							printf("����:");
							scanf("%s",inf[i].name);
							for(j=0;j<nb;j++)
							{
								LOOP3:printf("��Ŀ%d�ɼ�:",j+1);
								scanf("%d",&inf[i].score[j]);
								if(inf[i].score[j]>100||inf[i].score[j]<0)
								{
									printf("������������ȷ�ĳɼ���0~100����\n");
									goto LOOP3;
								}
							}
							printf("\n");
						}
				else{
						printf("������������ȷ��ѧ��(8λ����)��ѧ���Ѵ��ڡ�\n");
						goto LOOP2;
					}
				}
	
				}
	else{
			printf("���������������Ŀ�����������������Ŀ�������������롣\n");
			goto LOOP1;
	}
	if(i==np)
	{
		system("cls");
		printf("****ѧ���ɼ���¼����ϣ����س��ص���ʼ�˵���****\n\n");
		
	}
}

int sumsco(int j)
{
	int i,sum;
	sum=0;
	for(i=0;i<np;i++)
		sum+=inf[i].score[j];
	return sum;
	
}

void addsco()
{
	int i,j;
	for(i=0;i<np;i++)
		for(j=0;j<nb;j++)
			inf[i].adds+=inf[i].score[j];
}

void rank()
{
	int i,j,k,m,flag;
	int gt[np];
	for(m=0;m<np;m++)
		gt[m]=inf[m].adds;
		
	k=np;
	for(i=1;i<np;i++)
	{
		k-=1;
		for(j=0;j<k;j++)
		{
			if(gt[j]<gt[j+1])
				{
					flag=gt[j];
					gt[j]=gt[j+1];
					gt[j+1]=flag;
				}
		}
	}

	for(i=0;i<np;i++)
		for(j=0;j<np;j++)
			{
				if(inf[i].adds==gt[j])
				{
					inf[i].rank=j+1; 
					break;
				}
					
			}
			

		
}

void stuflag()
{
	int i,j,k,m,flag;
	int gt[np];
	for(m=0;m<np;m++)
		gt[m]= atoi(inf[m].stunum);

	k=np;
	for(i=1;i<np;i++)
	{
		k-=1;
		for(j=0;j<k;j++)
		{
			if(gt[j]>gt[j+1])
				{
					flag=gt[j];
					gt[j]=gt[j+1];
					gt[j+1]=flag;
				}
		}
	}

	for(i=0;i<np;i++)
		for(j=0;j<np;j++)
			{
				if(atoi(inf[i].stunum)==gt[j])
					inf[i].flag=j;
			}	
}

void query(char name[]){
	int i,j;
	for(i=0;i<np;i++)
		if(strcmp(name,inf[i].name)==0)
		{
			printf("ѧ�ţ�%s\n",inf[i].stunum);
			for(j=0;j<nb;j++)
			printf("��Ŀ%d��%d\n",j+1,inf[i].score[j]);
			printf("�ܷ֣�%d	������%d\n",inf[i].adds,inf[i].rank);
			printf("------------------------------\n");
		}
}

void statistics(){
	int i,j;
	float f;
	struct flag{
		int a,b,c,d,e;
	}mark[nb];
	for(i=0;i<nb;i++)
	{
		mark[i].a=0;
		mark[i].b=0;
		mark[i].c=0;
		mark[i].d=0;
		mark[i].e=0;
	}
	
	for(i=0;i<np;i++)
		for(j=0;j<nb;j++)
		{
			if(inf[i].score[j]<100&&inf[i].score[j]>=90)
				mark[j].a++;
			if(inf[i].score[j]<90&&inf[i].score[j]>=80)
				mark[j].b++;
			if(inf[i].score[j]<80&&inf[i].score[j]>=70)
				mark[j].c++;
			if(inf[i].score[j]<70&&inf[i].score[j]>=60)
				mark[j].d++;
			if(inf[i].score[j]<60)
				mark[j].e++;
		}
		
	for(i=0;i<nb;i++)
	{
		printf("��Ŀ%d��������ռ:%.1f\n",i+1,(float)mark[i].a/np);
		printf("��Ŀ%d��������ռ:%.1f\n",i+1,(float)mark[i].b/np);
		printf("��Ŀ%d�е�����ռ:%.1f\n",i+1,(float)mark[i].c/np);
		printf("��Ŀ%d��������ռ:%.1f\n",i+1,(float)mark[i].d/np);
		printf("��Ŀ%d����������ռ:%.1f\n",i+1,(float)mark[i].e/np);
		printf("------------------------------\n");
	}
		
		
				
	
}

int main(int argc, char *argv[]) {
	int i,j,k,flag;
	char name[20];
	flag=1;
	while(flag)
	{
	 switch(menu()){
		case 1:
			system("cls");
			enter(); 
			addsco();
			rank();
			getchar();
			getchar();
			break;
		case 2:
			system("cls");
			for(i=0;i<nb;i++)
			{
				printf("��Ŀ%d�ܷ�Ϊ��%d��\n",i+1,sumsco(i));
				printf("��Ŀ%dƽ����Ϊ:%d��\n",i+1,sumsco(i)/np);
				printf("-------------------\n");
			};
			printf("���س������ؿ�ʼ�˵���\n");
				getchar();
				getchar();
				system("cls");
				break;
				
		case 3:
			system("cls");
			for(i=1;i<=np;i++)
				for(j=0;j<np;j++)
				{
					if(inf[j].rank==i)
					printf("������%s  ѧ�ţ�%s  �ܷ֣�%d  ������%d\n",inf[j].name,inf[j].stunum,inf[j].adds,inf[j].rank);
				}
			printf("------------------------------\n");
			printf("���س������ؿ�ʼ�˵���\n");
			getchar();
			getchar();
			system("cls"); break;
		case 4:
			system("cls");
			stuflag();
			for(i=0;i<np;i++)
				for(j=0;j<np;j++)
				{
					if(inf[j].flag==i)
					{
						printf("ѧ�ţ�%s  ������%s  �ܷ֣�%d  ������%d\n",inf[j].stunum,inf[j].name,inf[j].adds,inf[j].rank);
						for(k=0;k<nb;k++)
						printf("��Ŀ%d��%d\n",k+1,inf[j].score[k]);
						printf("\n");
					}
				}
				printf("------------------------------\n");
			printf("���س������ؿ�ʼ�˵���\n");
			getchar();
			getchar();
			system("cls"); break;
		case 5:
			system("cls");
			printf("������Ҫ��ѯ��ѧ��������");
			scanf("%s",name);
			query(name);
			printf("���س������ؿ�ʼ�˵���\n");
			getchar();
			getchar();
			system("cls"); break;
			
		case 6:
			system("cls");
			statistics();
			printf("------------------------------\n");
			printf("���س������ؿ�ʼ�˵���\n");
			getchar();
			getchar();
			system("cls"); break;
		case 7:
			system("cls");
			for(i=0;i<np;i++)
			{
				printf("������%s	ѧ�ţ�%s\n",inf[i].name,inf[i].stunum);
				for(j=0;j<nb;j++)
				printf("��Ŀ%d��%d\n",j+1,inf[i].score[j]);
				printf("�ܷ֣�%d	������%d\n",inf[i].adds,inf[i].rank);
				printf("------------------------------\n");
			}
			printf("���س������ؿ�ʼ�˵���\n");
			getchar();
			getchar();
			system("cls"); break;
			
		case 0: flag=0; break;
		default:break;
	
	}
	}


	return 0;
}
