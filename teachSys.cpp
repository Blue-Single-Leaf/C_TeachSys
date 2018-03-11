#include<stdio.h>
#include<string.h>
#include<direct.h>	//计算时间用
#include<stdlib.h>
#include<malloc.h>	//定义动态数组
#include"time.h"	//计算时间有用
#include"myinput.c"	//个人习惯用的输入操作
#include"myfile.c"	//个人习惯用的文件操作
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
int sn = 0;				//sn用来记录学生数
int main()
{ 
	int i,j,come;
	FILE *myf;
	void load_file(char *s);		//初始化学生信息
	void load_manual();
	void print();			//打印学生信息
	void del();			//删除学生信息
	void search();		//查询学生信息
	void insert();		//插入记录
	void compute();		//统计数据
	void start();
	printf("\n************************************************教务管理系统**********************************************\n");
	printf("\n说明:\n\t此教务系统作模拟使用，因此学生数设计为少于99人，且此系统尚有诸多不足之处。\n\t此系统运行时在D盘下建立文件夹：tech_sys作为存储位置。\n");
	printf("\n****** D:\\tech_sys\\student_info.txt 作为预存文件，用来存放表格信息;\n****** D:\\tech_sys\\load.txt 作为其它文件加载录入表格用。\n");
	printf("\n--------------------------------------------------\n\n");
	if((myf = fopen("D:\\tech_sys\\student_info.txt","r")) == NULL)
	{
		printf("\t->鉴定您是第一次使用本系统，现指引您进行初始化：\n\n");
		if(_mkdir("D:\\tech_sys") == 0)
		{
			printf("\t->文件夹：D:\\tech_sys 已建立\n\n");
		}
		if((myf = fopen("D:\\tech_sys\\student_info.txt","w")) != NULL)
		{
			printf("\t->文件 D:\\tech_sys\\student_info.txt 已建立\n\n");
		}
		printf("\t->进行数据初始化：\n\n\t\t数据录入方式：1.文件录入\t2.手动录入\n\n");
		come = getsInt("请选择:");
		if(come == 1)
		{
			printf("请将要录入的文件放入 D:\\tech_sys 文件夹下，并命名为load.txt(按任意键继续)");
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
		printf("-----------欢迎再次进入教务系统！----------\n\n\n");
		printf("\t->系统为您进行预加载，载入上次保留的记录.");
		load_file("D:\\tech_sys\\student_info.txt");
	}
	start();
	return 0;
}
void start()			//系统入口
{
	int i,j = -1;
	char c;
	void load_file(char *s);		//初始化学生信息
	void load_manual();
	void print();			//打印学生信息
	void del();			//删除学生信息
	void search();		//查询学生信息
	void insert();		//插入记录
	void compute();		//统计数据
	void save();		//保存表格信息
	printf("\n\n************************菜单栏************************\n\n");
	printf("\n\t1.显示表格信息\t\t2.插入记录到表中\n\n");
	printf("\t3.删除表中记录\t\t4.查找记录\n\n");
	printf("\t5.查询各类统计信息\t6.将表格信息保存到文件中\n\n");
	printf("\t7.载入文件记录到表格\t8.退出\n\n");
	i = getsInt("请选择指令：");
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
			c = getsChar("是否继续插入？是输入y,否输入n\n\t[y/n]:");
			if(c == 'y')
				j = -1;
			else if(c == 'n')
				j = 1;
			else 
			{
				if(getsChar("请输入[y/n]:") == 'y')
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
		printf("\n\t1.载入预存文件 D:\\tech_sys\\student_info.txt\t2.载入其它文件\n\n");
		j = getsInt("请选择载入方式：");
		if(j == 2)
		{
			printf("请将要录入的文件放入 D:\\tech_sys 文件夹下，并命名为load.txt(按任意键继续)");
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
		printf("退出\n");
	}
	else if(i == 9)
	{
		printf("\t->制作者：franceyang.jlu.edu.cn\n");
		start();
	}
	else 
	{
		printf("指令错误，无此指令\n");
		start();
	}

}

void load_file(char *s)			//加载文件到表格
{
	int i = 0,j = 2;
	char tmp[16] = {'\0'};
	FILE *fp;
	if((fp = fopen(s,"r")) == NULL){
		printf("载入文件失败\n");
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
	printf("\n\t->载入文件完成，共载入记录 %d 条\n",i);
	sn = i;
	fclose(fp);
}
void load_manual(){				//手动录入信息，开始时候
	int i,j,is_ok = 0;
	struct   tm* ptm;
	long     ts;
	int      y,m,d,h,n,s;
	ts  =   time(NULL); 
	ptm =   localtime(&ts); 
	y   =   ptm-> tm_year+1900;     //年 
	m   =   ptm-> tm_mon+1;         //月
	d   =   ptm-> tm_mday;          //日
	h   =   ptm-> tm_hour;          //时
	n   =   ptm-> tm_min;           //分
	s   =   ptm-> tm_sec;           //秒
	if(sn == 0) 
	{
		printf("\n\n初始化学生信息：\n");
		
		printf("请输入学生信息:(以 quit 结束录入)\n");
		for(i=0;i<99;i++)
		{	
			printf("\n第 %d 位学生信息：\n\n",(i+1));
			printf("请输入学生的学号:");
			scanf("%s",student[sn].ID_Number);
			if(strcmp(student[i].ID_Number,"quit") == 0) break;
			printf("请输入学生的姓氏:");
			scanf("%s",student[sn].familyname);
			printf("请输入学生的名字:");
			scanf("%s",student[sn].givenname);
			printf("请输入学生性别，0代表男生，1代表女生:");
			scanf("%d",&student[i].sex);
			while(student[i].sex != 0 && student[i].sex != 1)
			{
				printf("您输入的性别不合理，性别只能输入 0 （代表男生），1 （代表女生）请重新输入：");
				scanf("%d",&student[i].sex);
				printf("\n");
			}
			
			while(is_ok != 1)
			{
				if(is_ok == 0)
				printf("请输入学生出生日期(年月日以空格隔开,如 1997 8 4,月日小于10第一位不带零):");
				else
					printf("您输入的出生日期有误，请重新输入：");
				scanf("%d %d %d",&student[i].birthday.year,&student[i].birthday.month,&student[i].birthday.day);
				while(student[i].birthday.month < 1 || student[i].birthday.month >12)
				{
					printf("您输入的月份不合理，月份只能介于 1 - 12 之间，请重新输入:");
					scanf("%d",&student[i].birthday.month);
				}
				while(student[i].birthday.day < 1 || student[i].birthday.day >31)
				{
					printf("您输入的日期不合理，日期只能介于 1 - 31 之间，请重新输入:");
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
			printf("请输入学生四科成绩外语，高数，c语言，马哲 :");
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

void del()			//	删除表格中的信息
{
	char a[16];
	int i,j,k = -1;
	printf("请输入将要删除的学生学号:");
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
		printf("您输入的学号：%s 不存在，请重新输入(输入quit取消)：",a);
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
	printf("\n删除记录成功.\n");
}

void print()				//打印表格信息
{
	int i;
	printf("\n\t\t\t\t\t共有学生数：%d，情况如下:\t\t\t\n\n",sn);
	printf("学号\t\t姓名\t性别\t出生日期\t外语\t高数\tc语言\t马哲\t总分\t平均分\n");
	for(i=0;i<sn;i++)
	{
		printf("%s\t",student[i].ID_Number);
		printf("%s%s\t",student[i].familyname,student[i].givenname);
		if(student[i].sex == 0)
			printf("男\t");
		else 
			printf("女\t");
		printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
        printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
        printf("%5.2f\t",student[i].sum);
        printf("%5.2f\n",student[i].average);
	}
}
void sum_ave(char *s)				//输出平均分和总分，*s决定是按全表，还是按班级
{
	int i,j;
	char tmp_cla[8] = {'\0'};
	printf("\t学号\t\t姓名\t总分\t平均分\n");
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
void search()		//查找表格记录
{	
	char a[16];
	int b;
	char c[16];
	int i,j,k = -1,m;
	printf("查找方式：\n\t\t1.按学号\n\n\t\t2.按姓氏\n\n\t\t3.按姓名\n\n");
	b = getsInt("请输入查找方式：");
	if(b == 1)
	{
		printf("请输入将要查找的学生的学号:");
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
			printf("您输入的学号：%s 不存在，请重新输入(输入quit取消)：",a);
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
		printf("学号\t\t姓名\t性别\t出生日期\t外语\t高数\tc语言\t马哲\t总分\t平均分\n");
		printf("%s\t",student[i].ID_Number);
		printf("%s%s\t",student[i].familyname,student[i].givenname);
		if(student[i].sex == 0)
			printf("男\t");
		else 
			printf("女\t");
		printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
        printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
        printf("%5.2f\t",student[i].sum);
        printf("%5.2f\n",student[i].average);
	}
	else if(b == 2)
	{
		printf("请输入将要查找的学生的姓氏:");
		scanf("%s",a);
		printf("学号\t\t姓名\t性别\t出生日期\t外语\t高数\tc语言\t马哲\t总分\t平均分\n");
		for(i = 0,m = 0;i < sn;i++)
		{
			if(strcmp(student[i].familyname,a) == 0)
			{
				k = i;
				printf("%s\t",student[i].ID_Number);
				printf("%s%s\t",student[i].familyname,student[i].givenname);
				if(student[i].sex == 0)
					printf("男\t");
				else 
					printf("女\t");
				printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
				 printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
				 printf("%5.2f\t",student[i].sum);
				 printf("%5.2f\n",student[i].average);
				 m++;
			}
		}
		if(k == -1)
			printf("\n您输入的姓氏：%s 不存在。\n",a);
		else 
			printf("\n查寻结果： %d 条。\n",m);
	}
	else if(b == 3)
	{
		printf("请输入将要查找的学生的姓名:");
		scanf("%s",a);
		printf("学号\t\t姓名\t性别\t出生日期\t外语\t高数\tc语言\t马哲\t总分\t平均分\n");
		for(i = 0,m = 0; i < sn; i++)
		{
			sprintf(c,"%s%s",student[i].familyname,student[i].givenname);
			if(strcmp(c,a) == 0)
			{
				k = i;
				printf("%s\t",student[i].ID_Number);
				printf("%s%s\t",student[i].familyname,student[i].givenname);
				if(student[i].sex == 0)
					printf("男\t");
				else 
					printf("女\t");
				printf("%d %d %d\t",student[i].birthday.year,student[i].birthday.month,student[i].birthday.day); 
				 printf("%5.2f\t%5.2f\t%5.2f\t%5.2f\t",student[i].score[0],student[i].score[1],student[i].score[2],student[i].score[3]);
				 printf("%5.2f\t",student[i].sum);
				 printf("%5.2f\n",student[i].average);
				 m++;
			}
		}
		if(k ==  -1) 
			printf("\n您查找的姓名：%s 不存在。\n",a);
		else 
			printf("\n查寻结果： %d 条。\n",m);
	}
	else printf("\n无此命令\n");
}

void insert()			// 向表格中插入数据
{ 
			int i,j,is_ok = 0;
			struct   tm* ptm;
	long     ts;
	int      y,m,d,h,n,s;
	ts  =   time(NULL); 
	ptm =   localtime(&ts); 
	y   =   ptm-> tm_year+1900;     //年 
	m   =   ptm-> tm_mon+1;         //月
	d   =   ptm-> tm_mday;          //日
	h   =   ptm-> tm_hour;          //时
	n   =   ptm-> tm_min;           //分
	s   =   ptm-> tm_sec;           //秒
			printf("正在执行插入操作，插入第 %d 个学生的信息：\n",(sn+1));
			printf("请输入学生的学号:");
			scanf("%s",student[sn].ID_Number);
			printf("请输入学生的姓氏:");
			scanf("%s",student[sn].familyname);
			printf("请输入学生的名字:");
			scanf("%s",student[sn].givenname);
			for(i = 0;i < sn;i++)
			{
				if(strcmp(student[sn].ID_Number,student[i].ID_Number) == 0)
				{
					printf("学号已经存在！！！");
					return;
				}
			}
			printf("请输入学生性别，0代表男生，1代表女生:");
			scanf("%d",&student[sn].sex);
			while(student[sn].sex != 0 && student[sn].sex != 1)
			{
				printf("您输入的性别不合理，性别只能输入 0 （代表男生），1 （代表女生）请重新输入：");
				scanf("%d",&student[sn].sex);
				printf("\n");
			}
			while(is_ok != 1)
			{
				if(is_ok == 0)
				printf("请输入学生出生日期(年月日以空格隔开,如 1997 8 4,月日小于10第一位不带零):");
				else
					printf("您输入的出生日期有误，请重新输入：");
				scanf("%d %d %d",&student[i].birthday.year,&student[i].birthday.month,&student[i].birthday.day);
				while(student[i].birthday.month < 1 || student[i].birthday.month >12)
				{
					printf("您输入的月份不合理，月份只能介于 1 - 12 之间，请重新输入:");
					scanf("%d",&student[i].birthday.month);
				}
				while(student[i].birthday.day < 1 || student[i].birthday.day >31)
				{
					printf("您输入的日期不合理，日期只能介于 1 - 31 之间，请重新输入:");
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
			printf("请输入学生四科成绩外语，高数，c语言，马哲 :");
			for(j=0;j<4;j++)
			{
				scanf("%f",&student[sn].score[j]);
				student[sn].sum+=student[sn].score[j];
			}
			student[sn].average=student[sn].sum/4;
			sn++;
}
void compute()					//各类统计数据
{
	int l,m,i,j,n;
	int class_num = 0;
	char cla[50][8];
	char cla_query[8];
	char tmp_cla[8] = {'\0'};
	void rank_by_average(char *s);		//按平均成绩排名
	void course_count(char *s);		//按科目统计学生得分情况
	void course_ave(char *s);			//各科平均分及总平均分
	printf("\n统计方式：1.全表统计\t2.按班统计\n\n");
	m = getsInt("请选择统计方式：");
	if(m == 2)
	{
		printf("\n\t1.手动输入班级号码查询（如：201701)\t2.自动输出所有班级情况\n");
		n = getsInt("输入选择：");
		if(n == 1)
		{
			printf("请输入班级号码：");
			getchar();
			gets(cla_query);
			cla_query[6] = '\0';
		}
	}

	printf("\t统计信息指令：  1\t->按平均成绩排名;\n\t\t\t2\t->统计各科学生得分情况;\n\t\t\t3\t->各科平均分及总平均分;\n\t\t\t4\t->学生的总分及平均分\n");
	l = getsInt("\n请输入指令前的序号：");
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
		else printf("指令错误.\n");
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
				printf("\n班级：%s 的情况：\n\n",cla[i]);
				rank_by_average(cla[i]);
			}
		}
		if(l == 2)
		{
			for(i = 0;i < class_num;i++)
			{
				printf("\n班级：%s 的情况：\n\n",cla[i]);
				course_count(cla[i]);
			}
		}
		if(l == 3)
		{
			for(i = 0;i < class_num;i++)
			{
				printf("\n\n班级：%s 的情况：\n\n",cla[i]);
				course_ave(cla[i]);
			}
		}
		if(l == 4)
		{
			for(i = 0;i < class_num;i++)
			{
				printf("\n\n班级：%s 的情况：\n\n",cla[i]);
				sum_ave(cla[i]);
			}
		}
		}
		if(n == 1){
			printf("班级：%s 的情况：\n\n",cla_query);
			if(l == 1)
				rank_by_average(cla_query);
			else if(l == 2)
				course_count(cla_query);
			else if(l == 3)
				course_ave(cla_query);
			else if(l == 4)
				sum_ave(cla_query);

			else printf("指令错误.\n");
		}
	}				
}
void rank_by_average(char *s)		//按平均成绩排名
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
	printf("\n\n\t按平均成绩排名如下：\n\n");
	printf("\t名次\t\t学号\t姓名\t外语\t高数\tc语言\t马哲\t总分\t平均分\n");
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
void course_count(char *s){			//外语，高数，c语言 ，马哲和各科信息
	int i,j,m;
	char tmp_cla[8] = {'\0'};
	char course[20];
	for(m = 0; m < 4;m++)
	{
		if(m ==0)
			sprintf(course,"外语");
		else if(m == 1)
			sprintf(course,"高数");
		else if(m == 2)
			sprintf(course,"c语言");
		else 
			sprintf(course,"马哲");
		printf("\n对**%s**统计信息如下：\n\n",course);
		printf("\t90分以上的学生：\n\n");
		printf("\t\t\t学号\t\t姓名\t%s成绩\n",course);
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
		printf("\n\t80分-90的学生：\n\n");
		printf("\t\t\t学号\t\t姓名\t%s成绩\n",course);
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
		
		printf("\n\t70分-80分的学生：\n\n");
		printf("\t\t\t学号\t\t姓名\t%s成绩\n",course);
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
		printf("\n\t60分-70分的学生：\n\n");
		printf("\t\t\t学号\t\t姓名\t%s成绩\n",course);
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
		printf("\n\t60分以下的学生：\n\n");
		printf("\t\t\t学号\t\t姓名\t%s成绩\n",course);
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
void course_ave(char *s){			//各科平均成绩及总平均成绩
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
		printf("\n各科及总分的平均成绩如下：\n\n");
	printf("\t\t\t外语\t高数\tc语言\t马哲\t总平均成绩\n");
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
	printf("\n各科及总分的平均成绩如下：\n\n");
	printf("\t\t\t外语\t高数\tc语言\t马哲\t总平均成绩\n");
	printf("\t\t\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%6.2f\n",grade[0]/m,grade[1]/m,grade[2]/m,grade[3]/m,grade[4]/m);
	}
}
void save()				//将表格信息存入文档：D:\\tech_sys\\student_info.txt
{
	int i,j;
	FILE *fp;
	if((fp = fopen("D:\\tech_sys\\student_info.txt","w")) == NULL)
	{
		printf("打开文件 D:\\tech_sys\\student_info.txt 失败\n");
	}
	fprintf(fp,"学号  姓  名 性别 年 月 日 外语 高数 C语言 马哲 平均成绩 总成绩\n");
	for(i = 0;i < sn;i++)
	{
		fprintf(fp,"%s %s %s %d %d %d %d %5.2f %5.2f %5.2f %5.2f\n",student[i].ID_Number,student[i].familyname,student[i].givenname,
			student[i].sex,student[i].birthday.year,student[i].birthday.month,student[i].birthday.day,student[i].score[0],
			student[i].score[1],student[i].score[2],student[i].score[3]);
	}
	fprintf(fp,"\n\n");
	fclose(fp);
	printf("\n\t->保存表格信息成功。\n");
}




