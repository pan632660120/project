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
	printf("---------学生成绩管理系统---------\n");
	printf( "1、手动录入\n"
			"2、计算每门课程的总分和平均分\n"
			"3、按学生总分由高到低排出名次表\n"
			"4、按学号由小到大排出成绩表\n"
			"5、按姓名查询学生排名及其考试成绩\n"
			"6、统计\n"
			"7、输出\n"
			"0、退出系统\n"
			"-----请选择并输入对应的菜单项-----\n"); 
	printf("请输入:");
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
				LOOP1:printf("请按格式输入：（人数≤30，科目数≤6）\n总人数 总科目门数:");
					  
				scanf("%d %d",&np,&nb);
				if(np<=MAXNUM&&nb<=MAXSUB){
				printf("**********************************\n");
				for(i=0;i<np;i++)
				{
				LOOP2:printf("学生%d-请输入:\n学号:",i+1);
				 	scanf("%s",inf[i].stunum);
					if(strlen(inf[i].stunum)==8&&checkout(inf[i].stunum,i))
						{
							printf("姓名:");
							scanf("%s",inf[i].name);
							for(j=0;j<nb;j++)
							{
								LOOP3:printf("科目%d成绩:",j+1);
								scanf("%d",&inf[i].score[j]);
								if(inf[i].score[j]>100||inf[i].score[j]<0)
								{
									printf("错误：请输入正确的成绩（0~100）。\n");
									goto LOOP3;
								}
							}
							printf("\n");
						}
				else{
						printf("错误：请输入正确的学号(8位数字)或学号已存在。\n");
						goto LOOP2;
					}
				}
	
				}
	else{
			printf("错误：输入人数或科目门数超出总人数或科目数，请重新输入。\n");
			goto LOOP1;
	}
	if(i==np)
	{
		system("cls");
		printf("****学生成绩已录入完毕，按回车回到初始菜单。****\n\n");
		
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
			printf("学号：%s\n",inf[i].stunum);
			for(j=0;j<nb;j++)
			printf("科目%d：%d\n",j+1,inf[i].score[j]);
			printf("总分：%d	排名：%d\n",inf[i].adds,inf[i].rank);
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
		printf("科目%d优秀人数占:%.1f\n",i+1,(float)mark[i].a/np);
		printf("科目%d良好人数占:%.1f\n",i+1,(float)mark[i].b/np);
		printf("科目%d中等人数占:%.1f\n",i+1,(float)mark[i].c/np);
		printf("科目%d及格人数占:%.1f\n",i+1,(float)mark[i].d/np);
		printf("科目%d不及格人数占:%.1f\n",i+1,(float)mark[i].e/np);
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
				printf("科目%d总分为：%d。\n",i+1,sumsco(i));
				printf("科目%d平均分为:%d。\n",i+1,sumsco(i)/np);
				printf("-------------------\n");
			};
			printf("按回车键返回开始菜单。\n");
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
					printf("姓名：%s  学号：%s  总分：%d  排名：%d\n",inf[j].name,inf[j].stunum,inf[j].adds,inf[j].rank);
				}
			printf("------------------------------\n");
			printf("按回车键返回开始菜单。\n");
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
						printf("学号：%s  姓名：%s  总分：%d  排名：%d\n",inf[j].stunum,inf[j].name,inf[j].adds,inf[j].rank);
						for(k=0;k<nb;k++)
						printf("科目%d：%d\n",k+1,inf[j].score[k]);
						printf("\n");
					}
				}
				printf("------------------------------\n");
			printf("按回车键返回开始菜单。\n");
			getchar();
			getchar();
			system("cls"); break;
		case 5:
			system("cls");
			printf("请输入要查询的学生姓名：");
			scanf("%s",name);
			query(name);
			printf("按回车键返回开始菜单。\n");
			getchar();
			getchar();
			system("cls"); break;
			
		case 6:
			system("cls");
			statistics();
			printf("------------------------------\n");
			printf("按回车键返回开始菜单。\n");
			getchar();
			getchar();
			system("cls"); break;
		case 7:
			system("cls");
			for(i=0;i<np;i++)
			{
				printf("姓名：%s	学号：%s\n",inf[i].name,inf[i].stunum);
				for(j=0;j<nb;j++)
				printf("科目%d：%d\n",j+1,inf[i].score[j]);
				printf("总分：%d	排名：%d\n",inf[i].adds,inf[i].rank);
				printf("------------------------------\n");
			}
			printf("按回车键返回开始菜单。\n");
			getchar();
			getchar();
			system("cls"); break;
			
		case 0: flag=0; break;
		default:break;
	
	}
	}


	return 0;
}
