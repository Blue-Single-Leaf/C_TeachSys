#include<stdio.h>
#include<string.h>
#include<direct.h>	//����ʱ����
#include<stdlib.h>
#include<malloc.h>	//���嶯̬����
#include"time.h"	//����ʱ������
#include"myinput.c"	//����ϰ���õ��������
#include"myfile.c"	//����ϰ���õ��ļ�����
struct date
 { 
	int year;
	int month;
	int day ;
 };
 struct student
 {
	 char ID_Number[16];
	 char familyname[16];
	 char givenname[16];
	 int sex;
	 struct date birthday;
	 float score[4];
	 float sum;
	 float average;
}student[99];
int sn = 0;				//sn������¼ѧ����
int main()
{ 
	int i,j,come;
	FILE *myf;
	void load_file(char *s);		//��ʼ��ѧ����Ϣ
	void load_manual();
	void print();			//��ӡѧ����Ϣ
	void del();			//ɾ��ѧ����Ϣ
	void search();		//��ѯѧ����Ϣ
	void insert();		//�����¼
	void compute();		//ͳ������
	void start();
	printf("\n************************************************�������ϵͳ**********************************************\n");
	printf("\n˵��:\n\t�˽���ϵͳ��ģ��ʹ�ã����ѧ�������Ϊ����99�ˣ��Ҵ�ϵͳ������಻��֮����\n\t��ϵͳ����ʱ��D���½����ļ��У�tech_sys��Ϊ�洢λ�á�\n");
	printf("\n****** D:\\tech_sys\\student_info.txt ��ΪԤ���ļ���������ű����Ϣ;\n****** D:\\tech_sys\\load.txt ��Ϊ�����ļ�����¼�����á�\n");
	printf("\n--------------------------------------------------\n\n");
	if((myf = fopen("D:\\tech_sys\\student_info.txt","r")) == NULL)
	{
		printf("\t->�������ǵ�һ��ʹ�ñ�ϵͳ����ָ�������г�ʼ����\n\n");
		if(_mkdir("D:\\tech_sys") == 0)
		{
			printf("\t->�ļ��У�D:\\tech_sys �ѽ���\n\n");
		}
		if((myf = fopen("D:\\tech_sys\\student_info.txt","w")) != NULL)
		{
			printf("\t->�ļ� D:\\tech_sys\\student_info.txt �ѽ���\n\n");
		}
		printf("\t->�������ݳ�ʼ����\n\n\t\t����¼�뷽ʽ��1.�ļ�¼��\t2.�ֶ�¼��\n\n");
		come = getsInt("��ѡ��:");
		if(come == 1)
		{
			printf("�뽫Ҫ¼����ļ����� D:\\tech_sys �ļ����£�������Ϊload.txt(�����������)");
			getchar();
			getchar();
			load_file("D:\\tech_sys\\load.txt");
		}
		else
		{
			load_manual();
		}
	}
	else
	{
		printf("-----------��ӭ�ٴν������ϵͳ��----------\n\n\n");
		printf("\t->ϵͳΪ������Ԥ���أ������ϴα����ļ�¼.");
		load_file("D:\\tech_sys\\student_info.txt");
	}
	start();
	return 0;
}
void start()			//ϵͳ���
{
	int i,j = -1;
	char c;
	void load_file(char *s);		//��ʼ��ѧ����Ϣ
	void load_manual();
	void print();			//��ӡѧ����Ϣ
	void del();			//ɾ��ѧ����Ϣ
	void search();		//��ѯѧ����Ϣ
	void insert();		//�����¼
	void compute();		//ͳ������
	void save();		//��������Ϣ
	printf("\n\n************************�˵���************************\n\n");
	printf("\n\t1.��ʾ�����Ϣ\t\t2.�����¼������\n\n");
	printf("\t3.ɾ�����м�¼\t\t4.���Ҽ�¼\n\n");
	printf("\t5.��ѯ����ͳ����Ϣ\t6.�������Ϣ���浽�ļ���\n\n");
	printf("\t7.�����ļ���¼�����\t8.�˳�\n\n");
	i = getsInt("��ѡ��ָ�");
	if(i == 1)
	{
		print();
		start();
	}
	else if(i == 2)
	{
		while(j == -1)
		{
			insert();
			c = getsChar("�Ƿ�������룿������y,������n\n\t[y/n]:");
			if(c == 'y')
				j = -1;
			else if(c == 'n')
				j = 1;
			else 
			{
				if(getsChar("������[y/n]:") == 'y')
					j = -1;
				else
					j = 1;
			}
		}
		start();
	}
	else if(i == 3)
	{
		del();
		start();
	}
	else if(i == 4)
	{
		search();
		start();
	}
	else if(i == 5)
	{
		compute();
		start();
	}
	else if(i == 6)
	{
		save();
		start();
	}
	else if(i == 7)
	{
		printf("\n\t1.����Ԥ���ļ� D:\\tech_sys\\student_info.txt\t2.���������ļ�\n\n");
		j = getsInt("��ѡ�����뷽ʽ��");
		if(j == 2)
		{
			printf("�뽫Ҫ¼����ļ����� D:\\tech_sys �ļ����£�������Ϊload.txt(�����������)");
			getchar();
			getchar();
			load_file("D:\\tech_sys\\load.txt");
		}
		else
			load_file("D:\\tech_sys\\student_info.txt");
		start();
	}
	else if(i == 8)
	{
		printf("�˳�\n");
	}
	else if(i == 9)
	{
		printf("\t->�����ߣ�franceyang.jlu.edu.cn\n");
		start();
	}
	else 
	{
		printf("ָ������޴�ָ��\n");
		start();
	}

}

void load_file(char *s)			//�����ļ������
{
	int i = 0,j = 2;
	char tmp[16] = {'\0'};
	FILE *fp;
	if((fp = fopen(s,"r")) == NULL){
		printf("�����ļ�ʧ��\n");
		return;
	}
	while(1)
	{
		if(fgotoline(fp,j) == -1) break;
		strcpy(tmp,fgetstr(fp).c);
		if(tmp[0] == '\n') break;
		strcpy(student[i].ID_Number,tmp);
		strcpy(student[i].familyname,fgetstr(fp).c);
		strcpy(student[i].givenname,fgetstr(fp).c);
		student[i].sex = fgetnum(fp);
		student[i].birthday.year = fgetnum(fp);
		student[i].birthday.month = fgetnum(fp);
		student[i].birthday.day = fgetnum(fp);
		student[i].score[0] = fgetnum(fp);
		student[i].score[1] = fgetnum(fp);
		student[i].score[2] = fgetnum(fp);
		//printf("%5.2f*****\n",student[i].score[2]);
		student[i].score[3] = fgetnum(fp);
		student[i].sum = student[i].score[0]+student[i].score[1]+student[i].score[2]+student[i].score[3];
		student[i].average = student[i].sum/4;
		i++;
		j++;
	}
	printf("\n\t->�����ļ���ɣ��������¼ %d ��\n",i);
	sn = i;
	fclose(fp);
}
void load_manual(){				//�ֶ�¼����Ϣ����ʼʱ��
	int i,j,is_ok = 0;
	struct   tm* ptm;
	long     ts;
	int      y,m,d,h,n,s;
	ts  =   time(NULL); 
	ptm =   localtime(&ts); 
	y   =   ptm-> tm_year+1900;     //�� 
	m   =   ptm-> tm_mon+1;         //��
	d   =   ptm-> tm_mday;          //��
	h   =   ptm-> tm_hour;          //ʱ
	n   =   ptm-> tm_min;           //��
	s   =   ptm-> tm_sec;           //��
	if(sn == 0) 
	{
		printf("\n\n��ʼ��ѧ����Ϣ��\n");
		
		printf("������ѧ����Ϣ:(�� quit ����¼��)\n");
		for(i=0;i<99;i++)
		{	
			printf("\n�� %d λѧ����Ϣ��\n\n",(i+1));
			printf("������ѧ����ѧ��:");
			scanf("%s",student[sn].ID_Number);
			if(strcmp(student[i].ID_Number,"quit") == 0) break;
			printf("������ѧ��������:");
			scanf("%s",student[sn].familyname);
			printf("������ѧ��������:");
			scanf("%s",student[sn].givenname);
			printf("������ѧ���Ա�0����������1����Ů��:");
			scanf("%d",&student[i].sex);
			while(student[i].sex != 0 && student[i].sex != 1)
			{
				printf("��������Ա𲻺����Ա�ֻ������ 0 ��������������1 ������Ů�������������룺");
				scanf("%d",&student[i].sex);
				printf("\n");
			}
			
			while(is_ok != 1)
			{
				if(is_ok == 0)
				printf("������ѧ����������(�������Կո����,�� 1997 8 4,����С��10��һλ������):");
				else
					printf("������ĳ��������������������룺");
				scanf("%d %d %d",&student[i].birthday.year,&student[i].birthday.month,&student[i].birthday.day);
				while(student[i].birthday.month < 1 || student[i].birthday.month >12)
				{
					printf("��������·ݲ������·�ֻ�ܽ��� 1 - 12 ֮�䣬����������:");
					scanf("%d",&student[i].birthday.month);
				}
				while(student[i].birthday.day < 1 || student[i].birthday.day >31)
				{
					printf("����������ڲ���������ֻ�ܽ��� 1 - 31 ֮�䣬����������:");
					scanf("%d",&student[i].birthday.day);
				}
				if((student[i].birthday.year - y) <0)
				{
					is_ok = 1;
				}
				else if((student[i].birthday.year - y) == 0)
				{
					if((student[i].birthday.month - m) < 0)
					{
						is_ok = 1;
					}
					else if((student[i].birthday.month - m) == 0)
					{
						if((student[i].birthday.day - d) <= 0)
						{
							is_ok = 1;
						}
						else
						{
							is_ok = -1;
						}
					}
					else
					{
						is_ok = -1;
					}
				}
			    else
				{
					is_ok = -1;
				}
			}
			student[i].sum = 0;
			printf("������ѧ���ĿƳɼ����������c���ԣ����� :");
			for(j=0;j<4;j++)
			{
				scanf("%f",&student[i].score[j]);
				student[i].sum+=student[i].score[j];
			}
			student[i].average=student[i].sum/4;
			sn++;
		}
	}
}

void del()			//	ɾ������е���Ϣ
{
	char a[16];
	int i,j,k = -1;
	printf("�����뽫Ҫɾ����ѧ��ѧ��:");
	scanf("%s",a);
	for(i = 0;i < sn;i++)
	{
		if(strcmp(student[i].ID_Number,a) == 0)
		{
			k = i;
			break;
		}
	}
	while(k == -1)
	{
		printf("�������ѧ�ţ�%s �����ڣ�����������(����quitȡ��)��",a);
		scanf("%s",a);
		if(strcmp(a,"quit") == 0) return;
		for(i = 0;i < sn;i++)
		{
			if(strcmp(student[i].ID_Number,a) == 0)
			{
				k = i;
				break;
			}
		}
	}

	for(j = k;j<sn;j++)
	{
		strcpy(student[j].ID_Number,student[j+1].ID_Number);
		strcpy(student[j].familyname,student[j+1].familyname);
		strcpy(student[j].givenname,student[j+1].givenname);
		student[j].sex = student[j+1].sex;
		student[j].birthday.year = student[j+1].birthday.year;
		student[j].birthday.month = student[j+1].birthday.month;
		student[j].birthday.day = student[j+1].birthday.day;
		student[j].score[0] = student[j+1].score[0];
		student[j].score[1] = student[j+1].score[1];
		student[j].score[2] = student[j+1].score[2];
		student[j].score[3] = student[j+1].score[3];
		student[j].sum = student[j+1].sum;
		student[j].average = student[j+1].average;
	}
	sn -= 1;
	printf("\nɾ����¼�ɹ�.\n");
}

void print()				//��ӡ�����Ϣ
{
	int i;
	printf("\n\t\t\t\t\t����ѧ������%d���������:\t\t\t\n\n",sn);
	printf("ѧ��\t\t����\t�Ա�\t��������\t����\t����\tc����\t����\t�ܷ�\tƽ����\n");
	for(i=0;i<sn;i++)
	{
		printf("%s\t",student[i].ID_Number);
		printf("%s%s\t",student[i].familyname,student[i].givenname);
		if(student[i].sex == 0)
			printf("��\t");
		else 
			printf("Ů\t");
		printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
        printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
        printf("%5.2f\t",student[i].sum);
        printf("%5.2f\n",student[i].average);
	}
}
void sum_ave(char *s)				//���ƽ���ֺ��ܷ֣�*s�����ǰ�ȫ�����ǰ��༶
{
	int i,j;
	char tmp_cla[8] = {'\0'};
	printf("\tѧ��\t\t����\t�ܷ�\tƽ����\n");
	if(strcmp(s,"all") == 0)
	{
		for(i = 0;i < sn;i++)
			printf("\t%s\t",student[i].ID_Number);
			printf("%s%s\t",student[i].familyname,student[i].givenname);
			printf("%5.2f\t",student[i].sum);
			printf("%5.2f\n",student[i].average);
	}
	else
	{
		for(i = 0;i < sn;i++)
		{
			for(j = 0;j < 6;j++)
				tmp_cla[j] = student[i].ID_Number[j];
			if(strcmp(s,tmp_cla) == 0)
			{
				printf("\t%s\t",student[i].ID_Number);
				printf("%s%s\t",student[i].familyname,student[i].givenname);
				printf("%5.2f\t",student[i].sum);
				printf("%5.2f\n",student[i].average);
			}
		}

	}
}
void search()		//���ұ���¼
{	
	char a[16];
	int b;
	char c[16];
	int i,j,k = -1,m;
	printf("���ҷ�ʽ��\n\t\t1.��ѧ��\n\n\t\t2.������\n\n\t\t3.������\n\n");
	b = getsInt("��������ҷ�ʽ��");
	if(b == 1)
	{
		printf("�����뽫Ҫ���ҵ�ѧ����ѧ��:");
		scanf("%s",a);
		for(i = 0;i < sn;i++)
		{
			if(strcmp(student[i].ID_Number,a) == 0)
			{
				k = i;
				break;
			}
		}
		while(k == -1)
		{
			printf("�������ѧ�ţ�%s �����ڣ�����������(����quitȡ��)��",a);
			scanf("%s",a);
			if(strcmp(a,"quit") == 0) return;
			for(i = 0;i < sn;i++)
			{
				if(strcmp(student[i].ID_Number,a) == 0)
				{
					k = i;
					break;
				}
			}
		}
		printf("ѧ��\t\t����\t�Ա�\t��������\t����\t����\tc����\t����\t�ܷ�\tƽ����\n");
		printf("%s\t",student[i].ID_Number);
		printf("%s%s\t",student[i].familyname,student[i].givenname);
		if(student[i].sex == 0)
			printf("��\t");
		else 
			printf("Ů\t");
		printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
        printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
        printf("%5.2f\t",student[i].sum);
        printf("%5.2f\n",student[i].average);
	}
	else if(b == 2)
	{
		printf("�����뽫Ҫ���ҵ�ѧ��������:");
		scanf("%s",a);
		printf("ѧ��\t\t����\t�Ա�\t��������\t����\t����\tc����\t����\t�ܷ�\tƽ����\n");
		for(i = 0,m = 0;i < sn;i++)
		{
			if(strcmp(student[i].familyname,a) == 0)
			{
				k = i;
				printf("%s\t",student[i].ID_Number);
				printf("%s%s\t",student[i].familyname,student[i].givenname);
				if(student[i].sex == 0)
					printf("��\t");
				else 
					printf("Ů\t");
				printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
				 printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
				 printf("%5.2f\t",student[i].sum);
				 printf("%5.2f\n",student[i].average);
				 m++;
			}
		}
		if(k == -1)
			printf("\n����������ϣ�%s �����ڡ�\n",a);
		else 
			printf("\n��Ѱ����� %d ����\n",m);
	}
	else if(b == 3)
	{
		printf("�����뽫Ҫ���ҵ�ѧ��������:");
		scanf("%s",a);
		printf("ѧ��\t\t����\t�Ա�\t��������\t����\t����\tc����\t����\t�ܷ�\tƽ����\n");
		for(i = 0,m = 0; i < sn; i++)
		{
			sprintf(c,"%s%s",student[i].familyname,student[i].givenname);
			if(strcmp(c,a) == 0)
			{
				k = i;
				printf("%s\t",student[i].ID_Number);
				printf("%s%s\t",student[i].familyname,student[i].givenname);
				if(student[i].sex == 0)
					printf("��\t");
				else 
					printf("Ů\t");
				printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
				 printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
				 printf("%5.2f\t",student[i].sum);
				 printf("%5.2f\n",student[i].average);
				 m++;
			}
		}
		if(k ==  -1) 
			printf("\n�����ҵ�������%s �����ڡ�\n",a);
		else 
			printf("\n��Ѱ����� %d ����\n",m);
	}
	else printf("\n�޴�����\n");
}

void insert()			// �����в�������
{ 
			int i,j,is_ok = 0;
			struct   tm* ptm;
	long     ts;
	int      y,m,d,h,n,s;
	ts  =   time(NULL); 
	ptm =   localtime(&ts); 
	y   =   ptm-> tm_year+1900;     //�� 
	m   =   ptm-> tm_mon+1;         //��
	d   =   ptm-> tm_mday;          //��
	h   =   ptm-> tm_hour;          //ʱ
	n   =   ptm-> tm_min;           //��
	s   =   ptm-> tm_sec;           //��
			printf("����ִ�в������������� %d ��ѧ������Ϣ��\n",(sn+1));
			printf("������ѧ����ѧ��:");
			scanf("%s",student[sn].ID_Number);
			printf("������ѧ��������:");
			scanf("%s",student[sn].familyname);
			printf("������ѧ��������:");
			scanf("%s",student[sn].givenname);
			for(i = 0;i < sn;i++)
			{
				if(strcmp(student[sn].ID_Number,student[i].ID_Number) == 0)
				{
					printf("ѧ���Ѿ����ڣ�����");
					return;
				}
			}
			printf("������ѧ���Ա�0����������1����Ů��:");
			scanf("%d",&student[sn].sex);
			while(student[sn].sex != 0 && student[sn].sex != 1)
			{
				printf("��������Ա𲻺����Ա�ֻ������ 0 ��������������1 ������Ů�������������룺");
				scanf("%d",&student[sn].sex);
				printf("\n");
			}
			while(is_ok != 1)
			{
				if(is_ok == 0)
				printf("������ѧ����������(�������Կո����,�� 1997 8 4,����С��10��һλ������):");
				else
					printf("������ĳ��������������������룺");
				scanf("%d %d %d",&student[i].birthday.year,&student[i].birthday.month,&student[i].birthday.day);
				while(student[i].birthday.month < 1 || student[i].birthday.month >12)
				{
					printf("��������·ݲ������·�ֻ�ܽ��� 1 - 12 ֮�䣬����������:");
					scanf("%d",&student[i].birthday.month);
				}
				while(student[i].birthday.day < 1 || student[i].birthday.day >31)
				{
					printf("����������ڲ���������ֻ�ܽ��� 1 - 31 ֮�䣬����������:");
					scanf("%d",&student[i].birthday.day);
				}
				if((student[i].birthday.year - y) <0)
				{
					is_ok = 1;
				}
				else if((student[i].birthday.year - y) == 0)
				{
					if((student[i].birthday.month - m) < 0)
					{
						is_ok = 1;
					}
					else if((student[i].birthday.month - m) == 0)
					{
						if((student[i].birthday.day - d) <= 0)
						{
							is_ok = 1;
						}
						else
						{
							is_ok = -1;
						}
					}
					else
					{
						is_ok = -1;
					}
				}
			    else
				{
					is_ok = -1;
				}
			}
			student[sn].sum = 0;
			printf("������ѧ���ĿƳɼ����������c���ԣ����� :");
			for(j=0;j<4;j++)
			{
				scanf("%f",&student[sn].score[j]);
				student[sn].sum+=student[sn].score[j];
			}
			student[sn].average=student[sn].sum/4;
			sn++;
}
void compute()					//����ͳ������
{
	int l,m,i,j,n;
	int class_num = 0;
	char cla[50][8];
	char cla_query[8];
	char tmp_cla[8] = {'\0'};
	void rank_by_average(char *s);		//��ƽ���ɼ�����
	void course_count(char *s);		//����Ŀͳ��ѧ���÷����
	void course_ave(char *s);			//����ƽ���ּ���ƽ����
	printf("\nͳ�Ʒ�ʽ��1.ȫ��ͳ��\t2.����ͳ��\n\n");
	m = getsInt("��ѡ��ͳ�Ʒ�ʽ��");
	if(m == 2)
	{
		printf("\n\t1.�ֶ�����༶�����ѯ���磺201701)\t2.�Զ�������а༶���\n");
		n = getsInt("����ѡ��");
		if(n == 1)
		{
			printf("������༶���룺");
			getchar();
			gets(cla_query);
			cla_query[6] = '\0';
		}
	}

	printf("\tͳ����Ϣָ�  1\t->��ƽ���ɼ�����;\n\t\t\t2\t->ͳ�Ƹ���ѧ���÷����;\n\t\t\t3\t->����ƽ���ּ���ƽ����;\n\t\t\t4\t->ѧ�����ּܷ�ƽ����\n");
	l = getsInt("\n������ָ��ǰ����ţ�");
	if(m == 1)
	{
		if(l == 1)
			rank_by_average("all");
		else if(l == 2)
			course_count("all");
		else if(l == 3)
			course_ave("all");
		else if(l == 4)
			sum_ave("all");
		else printf("ָ�����.\n");
	}
	if(m == 2)
	{
		if(n ==2)
		{
		for(i = 0; i < sn;i++)
		{
			for(j = 0;j < 6;j++)
				tmp_cla[j] = student[i].ID_Number[j];
			if(class_num == 0)
			{
				strcpy(cla[0],tmp_cla);	
				class_num++;
				continue;
			}
			for(j = 0;j < class_num;j++)
				if(strcmp(cla[j],tmp_cla) == 0)
					break;
			if(j == class_num)
			{
				strcpy(cla[class_num],tmp_cla);
				class_num++;
			}
		}
		if(l == 1)
		{
			for(i = 0;i < class_num;i++)
			{
				printf("\n�༶��%s �������\n\n",cla[i]);
				rank_by_average(cla[i]);
			}
		}
		if(l == 2)
		{
			for(i = 0;i < class_num;i++)
			{
				printf("\n�༶��%s �������\n\n",cla[i]);
				course_count(cla[i]);
			}
		}
		if(l == 3)
		{
			for(i = 0;i < class_num;i++)
			{
				printf("\n\n�༶��%s �������\n\n",cla[i]);
				course_ave(cla[i]);
			}
		}
		if(l == 4)
		{
			for(i = 0;i < class_num;i++)
			{
				printf("\n\n�༶��%s �������\n\n",cla[i]);
				sum_ave(cla[i]);
			}
		}
		}
		if(n == 1){
			printf("�༶��%s �������\n\n",cla_query);
			if(l == 1)
				rank_by_average(cla_query);
			else if(l == 2)
				course_count(cla_query);
			else if(l == 3)
				course_ave(cla_query);
			else if(l == 4)
				sum_ave(cla_query);

			else printf("ָ�����.\n");
		}
	}				
}
void rank_by_average(char *s)		//��ƽ���ɼ�����
{
	int i,j,k,m,n = 0;
	int *rank;
	char tmp_cla[8] = {'\0'};
	float max ;
	float *bp_average;
	bp_average = (float *)malloc(sn*sizeof(float));
	rank = (int *)malloc(sn*sizeof(int));
	for(i = 0;i < sn;i++)
		bp_average[i] = student[i].average;
	for(i = 0;i < sn;i++)
	{
		max = 0;
		j = 0;
		for(j = 0;j < sn;j++)
			if(bp_average[j] > max)
			{
				max = bp_average[j];
				k = j;
			}
		bp_average[k] = -(i+1);
		rank[i] = k;
	}
	printf("\n\n\t��ƽ���ɼ��������£�\n\n");
	printf("\t����\t\tѧ��\t����\t����\t����\tc����\t����\t�ܷ�\tƽ����\n");
	for(j = 0;j < sn;j++)
	{
		if(strcmp(s,"all") == 0)
		{
			i = rank[j];
			printf("\t%d\t",j+1);
				printf("      %s\t",student[i].ID_Number);
				printf("%s%s\t",student[i].familyname,student[i].givenname); 
				 printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
				 printf("%5.2f\t",student[i].sum);
				 printf("%5.2f\n",student[i].average);
		}
		else
		{
			i = rank[j];
			for(m = 0;m < 6;m++)
				tmp_cla[m] = student[i].ID_Number[m];
			if(strcmp(s,tmp_cla) == 0){
				printf("\t%d\t",n+1);
				printf("      %s\t",student[i].ID_Number);
				printf("%s%s\t",student[i].familyname,student[i].givenname); 
				 printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
				 printf("%5.2f\t",student[i].sum);
				 printf("%5.2f\n",student[i].average);
				 n++;
			}
		}
	}
	free(bp_average);
	free(rank);
}
void course_count(char *s){			//���������c���� �����ܺ͸�����Ϣ
	int i,j,m;
	char tmp_cla[8] = {'\0'};
	char course[20];
	for(m = 0; m < 4;m++)
	{
		if(m ==0)
			sprintf(course,"����");
		else if(m == 1)
			sprintf(course,"����");
		else if(m == 2)
			sprintf(course,"c����");
		else 
			sprintf(course,"����");
		printf("\n��**%s**ͳ����Ϣ���£�\n\n",course);
		printf("\t90�����ϵ�ѧ����\n\n");
		printf("\t\t\tѧ��\t\t����\t%s�ɼ�\n",course);
		for(i = 0; i < sn;i++)
		{	
			if(strcmp(s,"all") == 0){
				if(student[i].score[m] >= 90){
					printf("\t\t\t%s\t",student[i].ID_Number);
					printf("%s%s\t",student[i].familyname,student[i].givenname);
					printf("%5.2f\n",student[i].score[m]);
				}
			}
			else
			{
				for(j = 0;j < 6;j++)
					tmp_cla[j] = student[i].ID_Number[j];
				if(strcmp(s,tmp_cla) == 0)
				{
					if(student[i].score[m] >= 90)
					{
						printf("\t\t\t%s\t",student[i].ID_Number);
						printf("%s%s\t",student[i].familyname,student[i].givenname);
						printf("%5.2f\n",student[i].score[m]);
					}
				}
			}
		}
		printf("\n\t80��-90��ѧ����\n\n");
		printf("\t\t\tѧ��\t\t����\t%s�ɼ�\n",course);
		for(i = 0; i < sn;i++)
		{
			if(strcmp(s,"all") == 0)
			{
				if(student[i].score[m] >= 80 && student[i].score[m] < 90){
					printf("\t\t\t%s\t",student[i].ID_Number);
					printf("%s%s\t",student[i].familyname,student[i].givenname);
					printf("%5.2f\n",student[i].score[m]);
				}
			}
			else
			{
				for(j = 0;j < 6;j++)
					tmp_cla[j] = student[i].ID_Number[j];
				if(strcmp(s,tmp_cla) == 0)
				{
					if(student[i].score[m] >= 80 && student[i].score[m] < 90)
					{
						printf("\t\t\t%s\t",student[i].ID_Number);
						printf("%s%s\t",student[i].familyname,student[i].givenname);
						printf("%5.2f\n",student[i].score[m]);
					}
				}
			}
		}
		
		printf("\n\t70��-80�ֵ�ѧ����\n\n");
		printf("\t\t\tѧ��\t\t����\t%s�ɼ�\n",course);
		for(i = 0; i < sn;i++)
		{
			if(strcmp(s,"all") == 0)
			{
				if(student[i].score[m] >= 70 && student[i].score[m] < 80){
					printf("\t\t\t%s\t",student[i].ID_Number);
					printf("%s%s\t",student[i].familyname,student[i].givenname);
					printf("%5.2f\n",student[i].score[m]);
				}
			}
			else
			{
				for(j = 0;j < 6;j++)
					tmp_cla[j] = student[i].ID_Number[j];
				if(strcmp(s,tmp_cla) == 0)
				{
					if(student[i].score[m] >= 70 && student[i].score[m] < 80)
					{
						printf("\t\t\t%s\t",student[i].ID_Number);
						printf("%s%s\t",student[i].familyname,student[i].givenname);
						printf("%5.2f\n",student[i].score[m]);
					}
				}
			}
		}
		printf("\n\t60��-70�ֵ�ѧ����\n\n");
		printf("\t\t\tѧ��\t\t����\t%s�ɼ�\n",course);
		for(i = 0; i < sn;i++)
		{
			if(strcmp(s,"all") == 0)
			{
				if(student[i].score[m] >= 60 && student[i].score[m] < 70){
					printf("\t\t\t%s\t",student[i].ID_Number);
					printf("%s%s\t",student[i].familyname,student[i].givenname);
					printf("%5.2f\n",student[i].score[m]);
				}
			}
			else
			{
				for(j = 0;j < 6;j++)
					tmp_cla[j] = student[i].ID_Number[j];
				if(strcmp(s,tmp_cla) == 0)
				{
					if(student[i].score[m] >= 60 && student[i].score[m] < 70)
					{
						printf("\t\t\t%s\t",student[i].ID_Number);
						printf("%s%s\t",student[i].familyname,student[i].givenname);
						printf("%5.2f\n",student[i].score[m]);
					}
				}
			}
		}
		printf("\n\t60�����µ�ѧ����\n\n");
		printf("\t\t\tѧ��\t\t����\t%s�ɼ�\n",course);
		for(i = 0; i < sn;i++)
		{
			if(strcmp(s,"all") == 0)
			{
				if(student[i].score[m] <= 60){
					printf("\t\t\t%s\t",student[i].ID_Number);
					printf("%s%s\t",student[i].familyname,student[i].givenname);
					printf("%5.2f\n",student[i].score[m]);
				}
			}
			else
			{
				for(j = 0;j < 6;j++)
					tmp_cla[j] = student[i].ID_Number[j];
				if(strcmp(s,tmp_cla) == 0)
				{
					if(student[i].score[m] <= 60)
					{
						printf("\t\t\t%s\t",student[i].ID_Number);
						printf("%s%s\t",student[i].familyname,student[i].givenname);
						printf("%5.2f\n",student[i].score[m]);
					}
				}
			}
		}
	}
}
void course_ave(char *s){			//����ƽ���ɼ�����ƽ���ɼ�
	int i,j,m = 0;
	char tmp_cla[8] = {'\0'};
	float grade[5] = {0.0};
	if(strcmp(s,"all") == 0)
	{
		for(i = 0;i < sn; i ++)
		{
			for(j = 0;j < 4;j++)
				grade[j] += student[i].score[j];
			grade[4] += student[i].average;
		}
		printf("\n���Ƽ��ֵܷ�ƽ���ɼ����£�\n\n");
	printf("\t\t\t����\t����\tc����\t����\t��ƽ���ɼ�\n");
	printf("\t\t\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%6.2f\n",grade[0]/sn,grade[1]/sn,grade[2]/sn,grade[3]/sn,grade[4]/sn);
	}
	else
	{
		for(i = 0;i < sn; i ++)
		{
			for(j = 0;j < 6;j++)
				tmp_cla[j] = student[i].ID_Number[j];
			if(strcmp(s,tmp_cla) == 0){
				for(j = 0;j < 4;j++)
					grade[j] += student[i].score[j];
			grade[4] += student[i].average;
			m++;
			}
		}
	printf("\n���Ƽ��ֵܷ�ƽ���ɼ����£�\n\n");
	printf("\t\t\t����\t����\tc����\t����\t��ƽ���ɼ�\n");
	printf("\t\t\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%6.2f\n",grade[0]/m,grade[1]/m,grade[2]/m,grade[3]/m,grade[4]/m);
	}
}
void save()				//�������Ϣ�����ĵ���D:\\tech_sys\\student_info.txt
{
	int i,j;
	FILE *fp;
	if((fp = fopen("D:\\tech_sys\\student_info.txt","w")) == NULL)
	{
		printf("���ļ� D:\\tech_sys\\student_info.txt ʧ��\n");
	}
	fprintf(fp,"ѧ��  ��  �� �Ա� �� �� �� ���� ���� C���� ���� ƽ���ɼ� �ܳɼ�\n");
	for(i = 0;i < sn;i++)
	{
		fprintf(fp,"%s %s %s %d %d %d %d %5.2f %5.2f %5.2f %5.2f\n",student[i].ID_Number,student[i].familyname,student[i].givenname,
			student[i].sex,student[i].birthday.year,student[i].birthday.month,student[i].birthday.day,student[i].score[0],
			student[i].score[1],student[i].score[2],student[i].score[3]);
	}
	fprintf(fp,"\n\n");
	fclose(fp);
	printf("\n\t->��������Ϣ�ɹ���\n");
}




