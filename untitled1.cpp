
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Staff{
	int id;
	char name[50];
	char bank[20];
	int dx;
	int jc[13];
	int sd;
	int total_sj;
	int total;
	struct Staff* next;
};

struct Register{ 
	int username;
	char password[50];
	char level;
	struct Register* next;
};



struct Staff* loadCSV_staff(struct Staff *head_staff);
struct Register* loadCSV_register(struct Register *head_reg);
struct Register* listcompare(struct Register*head_reg);
void menu_choice(struct Register* p,struct Staff* head_staff);
void main_menu(struct Staff *head_staff);
void clearScreen();
struct Staff* create(struct Staff *head_staff);
void writeCSV(struct Staff *head_staff);
void count(struct Staff *head_staff);
void delt(struct Staff* head_staff);
struct Staff* addnum(struct Staff* head_staff);
void change(struct Staff* head_staff);
void ask(struct Staff* head_staff);
void sort_choice(struct Staff* heaf_staff);
void sortstaff_id(struct Staff* head_staff);
void sortstaff_total(struct Staff* head_staff);
void sortstaff_name(struct Staff* head_staff);
void check(struct Staff* head_staff);
void ask_choice(struct Staff* head_staff);
void ask_name(struct Staff* head_staff);
void ask_id(struct Staff* head_staff);
void ask_total(struct Staff* head_staff);
void count_choice(struct Staff* head_staff);
void count_all(struct Staff *head_staff);
void count_signal(struct Staff* head_staff);
void Print(struct Staff* p);
void Print_personal(int username,struct Staff* head_staff);
int tax_month(int gz);


//主函数
int main() {
	struct Staff* head_staff = NULL;
	struct Register* head_reg = NULL,*p=NULL;
	head_staff=loadCSV_staff(head_staff);
	head_reg=loadCSV_register(head_reg);
	p=listcompare(head_reg);
	menu_choice(p,head_staff);
	return 0;
}


//将文件中的信息载入
struct Staff* loadCSV_staff(struct Staff *head_staff) {
	FILE* file = fopen("staff.csv", "r");
	if (file == NULL) {
		printf("无法打开文件\n");
		exit(0);
	}
	char line[256];  // 适当调整缓冲区大小
	fgets(line, sizeof(line), file);  // 读取首行
	struct Staff *p1=NULL,*newStaff=NULL;
	head_staff=NULL;
	while (fgets(line, sizeof(line), file) != NULL) 
	{
		int id;
		char name[50];
		int total;
		int dx;
		int jc[13];
		char bank[20];
		int sd;
		int total_sj; 
		sscanf(line, "%d,%49[^,],%49[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &id,name,bank,&dx,
			&jc[1],&jc[2],&jc[3],&jc[4],&jc[5],&jc[6],&jc[7],&jc[8],&jc[9],&jc[10],&jc[11],&jc[12],
			&sd, &total_sj,&total);
		newStaff = (struct Staff*)malloc(sizeof(struct Staff));
		newStaff->next=NULL;
		if (newStaff != NULL) {
			newStaff->id = id;
			strcpy(newStaff->name, name);
			strcpy(newStaff->bank,bank);
			newStaff->dx=dx;
			for(int i=1;i<=12;i++)
			{
				newStaff->jc[i]=jc[i];				
			}
			newStaff->sd=sd;
			newStaff->total_sj=total_sj;
			newStaff->total = total;
			
			if(head_staff==NULL){
				head_staff=p1=newStaff;
			}
			else
			{
				p1->next=newStaff;
				p1=p1->next;
			}
		}
	}
	fclose(file); 
	return head_staff; 
}


//将文件中的信息载入
struct Register* loadCSV_register(struct Register *head_reg){
	FILE* file = fopen("register.csv", "r");
	if (file == NULL) {
		printf("无法打开文件\n");
		exit(0);
	}
	
	fseek(file, 0, SEEK_SET);  // 将文件指针移动到文件开头
	
	char line[256];  // 适当调整缓冲区大小
	fgets(line, sizeof(line), file);  // 读取首行
	struct Register *p1=NULL,*newReg=NULL;
	head_reg=NULL;
	
	while (fgets(line, sizeof(line), file) != NULL) {
		int username;
		char password[50];
		char level;
		sscanf(line, "%d,%49[^,],%c\n", &username, password,&level);
		newReg = (struct Register*)malloc(sizeof(struct Register));
		newReg->next = NULL;
		if (newReg != NULL) {
			newReg->username = username;
			strcpy(newReg->password, password);
			newReg->level = level;
			
			if(head_reg==NULL){
				head_reg=p1=newReg;
			}
			else{
				p1->next=newReg;
				p1=p1->next;
			}
		}
	}
	fclose(file);
	return head_reg;
};


//登录
struct Register* listcompare(struct Register*head_reg){
	int id;
	char password[50];
	while(1){
		printf("请输入用户名：");
		scanf("%d",&id);
		printf("请输入密码：");
		scanf("%s",password);
		struct Register* p1=head_reg;
		while(p1!=NULL && p1->username != id){
			p1 = p1->next;
		}
		if(p1 == NULL){
			clearScreen();
			printf("用户名错误或不存在\n");
		}
		else{
			if(strcmp(password, p1->password)!=0){
				printf("密码错误\n");
			}
			else{
				printf("登录成功\n\n\n");
				return p1;
			}
		}	
	}	
}

//写入员工信息存到文件
void writeCSV(struct Staff *head_staff) {
	FILE* file = fopen("staff.csv", "w");
	
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}
	
	struct Staff* current = head_staff;
	
	fprintf(file, "工号,姓名,银行卡号,月固定底薪,一月加成,二月加成,三月加成,四月加成,五月加成,六月加成,七月加成,八月加成,九月加成,十月加成,十一月加成,十二月加成,月水电费,年总税收,年实发工资\n");
	
	while (current != NULL) {
		fprintf(file, "%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", current->id, current->name,
			current->bank, current->dx, current->jc[1], current->jc[2], current->jc[3], current->jc[4], current->jc[5], current->jc[6], current->jc[7], current->jc[8], current->jc[9], current->jc[10], current->jc[11], current->jc[12],current->sd, current->total_sj,
			current->total);
		current = current->next;
	}
	
	
	fclose(file);  // 关闭文件
	
	printf("员工信息已成功写入CSV文件\n");
}



//写入登录信息存到文件
void write_regCSV(struct Register* head_reg){
	FILE* file = fopen("register.csv", "w");
	
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}
	
	struct Register* current = head_reg;
	
	fprintf(file,"用户名,密码,权限\n");
	while (current != NULL) {
		fprintf(file,"%d,%s,%c\n",current->username,current->password,current->level);
		current=current->next;
	}
	fclose(file);
	printf("注册信息已载入csv文件\n");
}


//权限分配菜单
void menu_choice(struct Register* p,struct Staff* head_staff){
	if(p->level=='A'){
		main_menu(head_staff);
	}
	else{
		Print_personal(p->username,head_staff);
	}
}


//菜单
void main_menu(struct Staff *head_staff) {
	int choice;
	do {
		system("color 1F"); //设置背景色蓝色 文字颜色为白色
		printf("           		       ◆━━━━━━━━━━━━━━━━━━━请选择功能━━━━━━━━━━━━━━━◆\n");
		printf("                      		┃		1. 创建员工信息	           ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                      		┃ 		2. 删除员工信息	           ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                      		┃  		3. 增加员工数量	           ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("       		                ┃		4. 修改员工信息	           ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("       		                ┃		5. 查询员工信息		   ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("       		                ┃		6. 浏览所有员工信息	   ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("            		        ┃		7. 统计员工信息	           ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                 	 	┃		8. 保存信息存入文件的顺序  ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                    		┃		0. 退出		           ┃\n");
		printf("            		       ◆━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◆\n");
		printf("\t\t\t\t请输入您的选择: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			clearScreen();
			head_staff=create(head_staff);
			break;
		case 2:
			clearScreen();
			delt(head_staff);
			break;
		case 3:
			clearScreen();
			head_staff=addnum(head_staff);
			break;
		case 4:
			clearScreen();
			change(head_staff);
			break;
		case 5:
			clearScreen();
			ask_choice(head_staff);
			break;
		case 6:
			clearScreen();
			check(head_staff);
			break;
		case 7:
			clearScreen();
			count_choice(head_staff);
			break;
		case 8:
			clearScreen();
			sort_choice(head_staff);
			writeCSV(head_staff);
			break;
		case 0:
			clearScreen();
			break;
		default:
			printf("无效的选择，请重新输入。\n");
		}
	} while (choice != 0);
	
}



//清屏
void clearScreen() {   
	printf("\x1B[2J\x1B[H");
}

//创建
struct Staff* create(struct Staff *head_staff) {
	struct Register* head_reg=NULL;
	head_reg=loadCSV_register(head_reg);
	char name[50];
	int sj[13];
	struct Staff* newStaff = (struct Staff*)malloc(sizeof(struct Staff));
	struct Register* newReg = (struct Register*)malloc(sizeof(struct Register));
	struct Staff* p;
	p=head_staff;
	
	printf("\t\t请输入要创建的员工信息:\n");
	while(1){
		printf("\t\t工号：");
		scanf("%d", &newStaff->id);
		while(p!=NULL){
			if(p->id==newStaff->id){
				break;	
			}
			p=p->next;
		}
		if(p==NULL) break;
		printf("工号已存在，请重新输入！\n");	
	}
	
	newReg->username=newStaff->id;
	printf("\t\t姓名：");
	scanf("%s",name);
	strcpy(newStaff->name, name);
	printf("\t\t请创建密码:");
	scanf("%s",newReg->password);
	newReg->level='B';
	
	while(1){
		printf("\t\t请输入银行卡号(16位)：");
		scanf("%s",newStaff->bank);
		int i;
		for(i=0;newStaff->bank[i]!='\0';i++){
		}
		if(i==16){
			break;
		}
		printf("输入的银行卡号错误，请重新输入！\n");
	}
	printf("\t\t请输入固定底薪：");
	scanf("%d",&newStaff->dx);
	newStaff->total=0;
	newStaff->total_sj=0;
	for(int i=1;i<=12;i++)
	{
		printf("\t\t输入第%d月的加成：",i);
		scanf("%d",&newStaff->jc[i]);
		sj[i]=tax_month(newStaff->dx+newStaff->jc[i]);
		newStaff->total_sj+=sj[i];
		newStaff->total+=newStaff->jc[i]-sj[i];
	}
	
	printf("\t\t月水电费：");
	scanf("%d",&newStaff->sd);
	newStaff->total=newStaff->total+newStaff->dx*12+newStaff->sd*12;
	newStaff->next = head_staff;
	head_staff = newStaff;
	
	newReg->next = head_reg;
	head_reg = newReg;
	
	writeCSV(head_staff);
	write_regCSV(head_reg);
	return head_staff;
}


//统计选择
void count_choice(struct Staff* head_staff){
	int choice;
	do{
		printf("           		       ◆━━━━━━━━━━━━━━━━━━━请选择功能━━━━━━━━━━━━━━━◆\n");	
		printf("       		                ┃		1. 统计所有员工工资	   ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("       		                ┃		2. 统计某个员工工资	   ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                    		┃		0. 退出		           ┃\n");
		printf("            		       ◆━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◆\n");
		printf("\t\t\t\t请输入你的选择：");
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:
			clearScreen();
			count_all(head_staff);
			break;
		case 2:
			clearScreen();
			count_signal(head_staff);
			break;
		case 0:
			clearScreen();
			break;
		default :
			clearScreen();
			break;
		}
	}while(choice!=0);
}

//统计某个人
void count_signal(struct Staff* head_staff){
	struct Staff* visit;
	int c=1;
	printf("输入要统计的员工的工号：");
	while(1){
		visit=head_staff;
		int charm;
		int sj[13];
		scanf("%d",&charm);
		
		while(visit!=NULL){
			if(visit->id==charm)
			{
				printf("输入统计的工资时间段(*月->*月)：");
				int start,end,total=0;
				scanf("%d %d",&start,&end);
				for(int i=start;i<=end;i++)
				{
					sj[i]=tax_month(visit->dx+visit->jc[i]);
					total+=visit->dx+visit->jc[i]+visit->sd-sj[i];
					printf("%d月实发工资：%d\n",i,visit->jc[i]+visit->sd-sj[i]+visit->dx);
				}
				printf("第%d月到第%d月实发工资：%d\n",start,end,total);
				c=0;
				break;
			}
			visit=visit->next;
		}
		if(c==0) break;
		printf("输入员工号错误或无该员工，请重新输入：");
	}
}


//统计所有人
void count_all(struct Staff *head_staff){
	int sd=0,total_sj=0,total=0;
	struct Staff* visit = head_staff;
	printf("==员工工资表==\n");
	printf(" 工号 姓名  年水电费  年税金 年度实发工资\n");
	while (visit != NULL) {
		printf("%4d%5s%10d%8d%12d\n",visit->id, visit->name, 12*visit->sd, visit->total_sj,visit->total);
		sd+=visit->sd;
		total_sj+=visit->total_sj;
		total+=visit->total;
		visit = visit->next;
	}
	sd*=12;
	printf("                                     所有人年度水电费总资金      总年度税金      所有人总发工资\n");
	printf("                                            %d                %d                   %d\n\n\n",sd,total_sj,total);
	char charm[10];
	int qt[13];
	int sj[13];
	printf("是否继续统计每人每月实际发放工资状态：(yes/no)");
	scanf("%s",charm);
	clearScreen();
	if(strcmp(charm,"yes")==0)
	{
		struct Staff* Visit=head_staff;
		
		printf("==员工工资表==\n");
		printf(" 工号 姓名   一月   二月   三月   四月   五月   六月   七月   八月   九月   十月 十一月 十二月\n");
		while (Visit != NULL) {
			for(int i=1;i<=12;i++){
				sj[i]=tax_month(Visit->dx+Visit->jc[i]);
				qt[i]=Visit->dx+Visit->jc[i]+Visit->sd-sj[i];
				
			}
			printf("%4d%5s%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d\n",Visit->id, Visit->name,qt[1],qt[2],qt[3],qt[4],qt[5],qt[6],qt[7],qt[8],qt[9],qt[10],qt[11],qt[12]);
			Visit = Visit->next;
		}
		printf("\n\n\n\n");	
	}
}



//删除
void delt(struct Staff* head_staff){
	struct Register* head_reg=NULL;
	head_reg=loadCSV_register(head_reg);
	int id = 0;
	printf("请输入你想删除的员工工号\n");
	scanf("%d", &id);
	
	struct Staff* p1, * p2;
	p1 = p2 = head_staff;
	struct Register* q1, * q2;
	q1 = q2 = head_reg;
	
	while (p1 != NULL && p1->id != id) {
		p2 = p1;
		p1 = p1->next;
	}
	while (q1 !=NULL && q1->username != id){
		q2=q1;
		q1=q1->next;
	}
	if (p1 != NULL) {
		if (head_staff->id == id) {
			head_staff = head_staff->next;
		}
		else {
			p2->next = p1->next;
		}
		free(p1);  // 释放被删除的节点的内存
		printf("已删除员工信息\n");
		writeCSV(head_staff);
		if(head_reg->username==id){
			head_reg=head_reg->next;
		}
		else{
			q2->next=q1->next;
		}
		free(q1);
		write_regCSV(head_reg);
	}
	else {
		printf("未找到员工信息\n");
	}
	
}


//增加
struct Staff* addnum(struct Staff* head_staff) {
	int num;
	printf("请输入要增加的员工数量：");
	scanf("%d", &num);
	
	for (int i = 0; i < num; ++i) {
		head_staff=create(head_staff);  // 调用创建学生信息的函数
	}
	
	clearScreen();
	printf("员工数量已增加\n");
	//sortstaff_id();
	//writeCSV(head_staff);  // 将更新后的学生信息写入CSV文件
	return head_staff;
}


//修改
void change(struct Staff* head_staff) {
	int id = 0;
	char charm[50];
	printf("请输入想要修改的员工工号\n");
	scanf("%d", &id);
	
	struct Staff* current = head_staff;
	
	while (current != NULL && current->id != id) {
		current = current->next;
	}
	
	if (current == NULL) {
		printf("未找到学生\n");
	}
	
	else {
		//current->total = 0;
		printf("请输入想修改的项目(银行卡号/月固定工资/月加成/月水电费):");
		scanf("%s",charm);
		
		if(strcmp(charm,"月加成")!=0)
		{
			printf("输入修改后的数据：");
			if(strcmp(charm,"银行卡号")==0){
				char data[20];
				while(1){
					scanf("%s",data);
					int i=0;
					for(i=0;data[1]!='\0';i++){	
					}
					if(i==16){
						strcpy(current->bank,data);
						break;
					}
					printf("输入的银行卡号错误，请重新输入！\n");
				}
				
			} 
			else if(strcmp(charm,"月水电费")==0){
				int data;
				scanf("%d",&data);
				current->sd=data;
			} 
			else if(strcmp(charm,"月固定工资")==0){
				int data;
				scanf("%d",&data);
				current->dx=data;
			}
		}
		
		else{
			int month;
			int data;
			printf("输入要修改的月份：");
			scanf("%d",&month);
			printf("输入修改后的数据：");
			scanf("%d",&data);	
			current->jc[month]=data;
		}
		current->total=0;
		current->total_sj=0;
		int sj[13];
		for(int i=1;i<=12;i++)
		{
			sj[i]=tax_month(current->dx+current->jc[i]);
			current->total_sj+=sj[i];
			current->total=current->total+current->jc[i]+current->dx+current->sd;
		}
		current->total-=current->total_sj;
		writeCSV(head_staff);
		printf("修改成功\n");
	}
}



//排序选择
void sort_choice(struct Staff* head_staff){
	int choice;
	struct Staff* p=head_staff;
	do{
		printf("           		       ◆━━━━━━━━━━━━━━━━━━━请选择功能━━━━━━━━━━━━━━━◆\n");
		printf("            		        ┃		1. 按工号排序进行浏览	   ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("            		        ┃		2. 按姓名排序进行浏览	   ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("            		        ┃		3. 按年总工资进行浏览      ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                    		┃		0. 退出		           ┃\n");
		printf("            		       ◆━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◆\n");
		printf("\t\t\t\t输入你的选择：");
		scanf("%d",&choice);
		switch (choice) {
		case 1:
			clearScreen();
			sortstaff_id(p);
			break;
		case 2:
			clearScreen();
			sortstaff_name(p);
			break;
		case 3:
			clearScreen();
			sortstaff_total(p);
			break;	
		case 0:
			clearScreen();
			break;
		default:
			printf("\n无效输入，请重新输入\n");
			break;	
		}
	}while(choice!=0&&choice!=1&&choice!=2&&choice!=3);
	
	
}


//按工号排序
void sortstaff_id(struct Staff* head_staff){
	struct Staff* pb, * pf, temp;
	pf = head_staff;
	if (head_staff == NULL)
	{
		printf("只有一个结点,不用排序\n");
		return;
	}
	if (head_staff->next == NULL)
	{
		printf("只有一个节点,不用排序\n");
		return;
	}
	while (pf->next != NULL)
	{
		pb = pf->next;//pb从基准元素的下个元素开始
		while (pb != NULL)
		{
			if (pf->id > pb->id)
			{
				temp = *pb;
				*pb = *pf;
				*pf = temp;
				temp.next = pb->next;
				pb->next = pf->next;
				pf->next = temp.next;
			}
			pb = pb->next;
		}
		pf = pf->next;
	}
}

//按年度总工资排序
void sortstaff_name(struct Staff* head_staff){
	struct Staff* pb, * pf, temp;
	pf = head_staff;
	if (head_staff == NULL)
	{
		printf("只有一个结点,不用排序\n");
		return;
	}
	if (head_staff->next == NULL)
	{
		printf("只有一个节点,不用排序\n");
		return;
	}
	while (pf->next != NULL)
	{
		pb = pf->next;//pb从基准元素的下个元素开始
		while (pb != NULL)
		{
			if (strcmp(pf->name,pb->name)>0)
			{
				temp = *pb;
				*pb = *pf;
				*pf = temp;
				
				temp.next = pb->next;
				pb->next = pf->next;
				pf->next = temp.next;
			}
			pb = pb->next;
		}
		pf = pf->next;
	}
}

//按姓名排序
void sortstaff_total(struct Staff* head_staff){
	struct Staff* pb, * pf, temp;
	pf = head_staff;
	if (head_staff == NULL)
	{
		printf("只有一个结点,不用排序\n");
		return;
	}
	if (head_staff->next == NULL)
	{
		printf("只有一个节点,不用排序\n");
		return;
	}
	while (pf->next != NULL)
	{
		pb = pf->next;//pb从基准元素的下个元素开始
		while (pb != NULL)
		{
			if (pf->total > pb->total)
			{
				temp = *pb;
				*pb = *pf;
				*pf = temp;
				
				temp.next = pb->next;
				pb->next = pf->next;
				pf->next = temp.next;
			}
			pb = pb->next;
		}
		pf = pf->next;
	}
}



//浏览员工信息
void check(struct Staff* head_staff) {
	int choice;
	struct Staff* visit=NULL;
	do{
		printf("           		  ◆━━━━━━━━━━━━━━━━━━━━━━━━请选择功能━━━━━━━━━━━━━━━━━━━━◆\n");
		printf("            		   ┃   	 1. 选择浏览员工每月基本工资(每月底薪):		┃\n");
		printf("            		   ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("            		   ┃   	 2. 浏览员工每月补贴及税收:	                ┃\n");
		printf("            		   ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("            		   ┃  	 3. 浏览员工个人信息：	                        ┃\n");
		printf("            		   ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                       	   ┃	 0. 退出	     	                        ┃\n");
		printf("            	    	  ◆━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◆\n");		
		printf("\t\t\t\t请输入你的选择：");
		scanf("%d",&choice);
		char charm[10];
		int sj[13];
		switch(choice)
		{
		case 1:
			clearScreen();
			visit=head_staff;
			printf("==员工每月底薪表==\n");
			printf(" 工号 姓名   一月   二月   三月   四月   五月   六月   七月   八月   九月   十月 十一月 十二月\n");
			while (visit != NULL) {
				printf("%4d%5s%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d\n",visit->id, visit->name,visit->jc[1],visit->jc[2],visit->jc[3],visit->jc[4],visit->jc[5],visit->jc[6],
					visit->jc[7],visit->jc[8],visit->jc[9],visit->jc[10],visit->jc[11],visit->jc[12]);
				visit = visit->next;
			}	
			
			printf("\n\n\n\n是否浏览其他排序方式：(yes/no)");
			scanf("%s",charm);
			clearScreen();
			if(strcmp(charm,"yes")==0)
			{
				clearScreen();
				//struct Staff* visit=head_staff;
				visit=head_staff;
				sort_choice(visit);
				printf("==员工每月底薪表==\n");
				printf(" 工号 姓名   一月   二月   三月   四月   五月   六月   七月   八月   九月   十月  十一月  十二月\n");
				while (visit != NULL) {
					printf("%4d%5s%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d\n",visit->id, visit->name,visit->jc[1],visit->jc[2],visit->jc[3],visit->jc[4],visit->jc[5],visit->jc[6],
						visit->jc[7],visit->jc[8],visit->jc[9],visit->jc[10],visit->jc[11],visit->jc[12]);
					visit = visit->next;
					//	printf("%4d%5s%7d%7d%7d%7d%7d%7d%7d7%7d%7d%7d%7d%7d%7d%7d\n",visit->id, visit->name,visit->jc[1],visit->jc[2],visit->jc[3],visit->jc[4],visit->jc[5],visit->jc[6],
					//	visit->jc[7],visit->jc[8],visit->jc[9],visit->jc[10],visit->jc[11],visit->jc[12]);
					//	visit = visit->next;
				}	
			}
			break;
			
		case 2:
			clearScreen();	
			visit=head_staff;
			printf("==员工补贴税收表==\n");
			printf(" 工号 姓名 月水电费   一月   二月   三月   四月   五月   六月   七月   八月   九月   十月  十一月  十二月\n");
			while(visit !=NULL)
			{
				for(int i=1;i<=12;i++)
				{
					sj[i]=tax_month(visit->dx+visit->jc[i]);
				}
				printf("%4d%5s%9d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d\n",visit->id, visit->name, visit->sd, sj[1], sj[2], sj[3], sj[4], sj[5], sj[6], sj[7], sj[8], sj[9], sj[10], sj[11], sj[12]);
				visit=visit->next;
			}
			
			printf("\n\n\n\n是否浏览其他排序方式：(yes/no)");
			scanf("%s",charm);
			clearScreen();
			if(strcmp(charm,"yes")==0)
			{
				clearScreen();
				//struct Staff* visit=head_staff;
				visit=head_staff;
				sort_choice(visit);
				printf("==员工补贴及税收表==\n");
				printf(" 工号 姓名 月水电费   一月   二月   三月   四月   五月   六月   七月   八月   九月   十月  十一月  十二月\n");
				while(visit !=NULL){
					for(int i=1;i<=12;i++)
					{
						sj[i]=tax_month(visit->dx+visit->jc[i]);
					}
					printf("%4d%5s%9d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d%7d\n",visit->id, visit->name, visit->sd, sj[1], sj[2], sj[3], sj[4], sj[5], sj[6], sj[7], sj[8], sj[9], sj[10], sj[11], sj[12]);
					visit=visit->next;
				}		
			}			
			break;
		case 3:
			clearScreen();	
			//struct Staff* visit=NULL;
			visit=head_staff;
			printf("==员工个人信息表==\n");
			printf(" 工号 姓名         银行卡号\n");
			while(visit!=NULL)
			{
				printf("%4d%5s%18s\n",visit->id,visit->name,visit->bank);
				visit=visit->next;
			}
			
			printf("\n\n\n\n是否浏览其他排序方式：(yes/no)");
			scanf("%s",charm);
			clearScreen();
			if(strcmp(charm,"yes")==0)
			{
				clearScreen();
				//struct Staff* visit=NULL;
				sort_choice(visit);
				printf("==员工个人信息表==\n");
				printf(" 工号 姓名         银行卡号\n");
				while(visit!=NULL)
				{
					printf("%4d%5s%18s\n",visit->id,visit->name,visit->bank);
					visit=visit->next;
				}
			}
			break;
		case 0:
			break;
		default:
			printf("无效的选择，请重新输入。\n");
		}
	}while(choice!=0&&choice!=1&&choice!=2&&choice!=3);
}



//查询选择
void ask_choice(struct Staff* head_staff){
	int choice;
	do{
		printf("           		       ◆━━━━━━━━━━━━━━━━━━━请选择功能━━━━━━━━━━━━━━━◆\n");
		printf("            		        ┃		1. 按姓名查询	           ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("            		        ┃		2. 按工号查询	           ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("            		        ┃		3. 按年总工资查询          ┃\n");
		printf("            			┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("                    		┃		0. 退出		           ┃\n");
		printf("            		       ◆━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◆\n");
		printf("\t\t\t\t输入选择：");
		
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:
			clearScreen();
			ask_name(head_staff);
			break;
		case 2:
			clearScreen();
			ask_id(head_staff);
			break;
		case 3:
			clearScreen();
			ask_total(head_staff);
			break;
		case 0:
			clearScreen();
			break;
		default:
			printf("无效输入!\n");
			break;
			
		}
	}while(choice!=0);
}

//按姓名查询
void ask_name(struct Staff* head_staff) {
	char name[50];
	int f=0;
	printf("请输入你想查询的学生姓名：");
	while(1){
		scanf("%s", name);
		
		struct Staff* p1;
		p1 = head_staff;
		while(p1!=NULL){
			if(strcmp(p1->name,name)==0){
				Print(p1);
				f=1;
			}
			p1=p1->next;
		}
		if(f==0){
			printf("未找到该员工,请重新输入：");
		}
		else break;
	}
}

//按工号查询
void ask_id(struct Staff* head_staff) {
	int id = 0;
	
	printf("请输入你想查询的员工工号：");
	while(1){
		scanf("%d", &id);
		
		struct Staff* p1;
		p1 = head_staff;
		
		while (p1 != NULL) {
			if(p1->id == id){
				Print(p1);
				return;
			}
			p1 = p1->next;
		}
		printf("未找到该员工,请重新输入：");
	}
	
}

//按年度总工资查询      
void ask_total(struct Staff* head_staff){
	int start,end;
	int f=0;
	struct Staff *p = head_staff;
	printf("输入要查询员工的年度总工资范围：");
	scanf("%d%d",&start,&end);
	
	while (p != NULL){
		if(p->total>=start&&p->total<=end)
		{
			Print(p);
			f=1;
		}
		p = p->next;
	}
	if(f==0) printf("无员工的年度总工资在此范围内！\n"); 	
}


////打印
void Print(struct Staff* p){
	int sj[13];
	printf("\n该员工的工资的信息如下:\n");
	printf("职工工号:%d\n",p->id);
	printf("姓名:%s\n",p->name);
	printf("员工的银行卡号：%s\n",p->bank);
	printf("该职工12个月的月工资如下:");
	for (int i = 1; i <= 12; i++)
	{
		sj[i]=tax_month(p->dx+p->jc[i]);
		printf("%d  ", p->jc[i]+p->dx-sj[i]);
	}
	printf("\n月水电费：%d",p->sd);
	printf("\n该员工的年度总工资为:");
	printf("%d", p->total);
	printf("\n\n");
}



//员工登陆查询
void Print_personal(int username,struct Staff* head_staff){
	while(head_staff !=NULL){
		if(head_staff->id == username){
			Print(head_staff);
		}
		head_staff=head_staff->next;
	}
	
	
}


//税金
int tax_month(int gz){
	float ch;
	if(gz<=5000) ch=0;
	else if(gz<=8000) ch=(gz-5000)*0.03;
	else if(gz<=17000) ch=(gz-8000)*0.1;
	else ch=(gz-17000)*0.2;
	return ch;
}


