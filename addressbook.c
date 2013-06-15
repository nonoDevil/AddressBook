/*
 * =====================================================================================
 *
 *       Filename:  addressbook.c
 *
 *    Description:  通讯录管理系统
 *
 *        Version:  1.0
 *        Created:  2013年06月15日 13时06分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addressbook.h"


int main(int argc, char *argv[])
{
	LinkList head = NULL;
	char choice = '\0';

	init(&head);
	load(head);
	welcome_menu(&choice, head);
		
	return EXIT_SUCCESS;
}


/*
 * Descritpion: 欢迎界面
 */
int welcome_menu(char *choice, LinkList head)
{
menu:
	printf("-----------------------------------------------------\n");
	printf("\t\t\t通讯录管理系统\t\t\t\n");
	printf("\n");
	printf("\t\t\t1.查询联系人\n");
	printf("\t\t\t2.增加联系人\n");
	printf("\t\t\t3.编辑联系人\n");
	printf("\t\t\t4.删除联系人\n");
	printf("\t\t\t5.退出通讯录系统\n");
	printf("-----------------------------------------------------\n");

	*choice = getchar();
	printf("choice = %c\n", *choice);
	setbuf(stdin, NULL);
	
	system("clear");
	list(head);
	switch (*choice) {
		case '1': 
			query(head); 
			break;
		case '2': 
			add(head); 
			save(head); 
			break;
		case '3': 
			modify(head); 
			save(head);
			break;
		case '4': 
			del(head);
			save(head);
			break;
		case '5':
			exit(0);
		default : 
			printf("输入的选项有误，请重新输入!\n");
			goto menu;
	}
	getchar();
	goto menu;

	return 0;
}

/*
 * Description: 初始化
 */
int init(LinkList *head)
{
	*head = (LinkList)malloc(sizeof(Node));
#ifdef DEBUG
	printf("head->number = %s\n", (*head)->number);
#endif

	strcpy((*head)->number,"\0");

#ifdef DEBUG
	printf("head->number = %s\n", (*head)->number);
#endif

	strcpy((*head)->name,"\0");
	(*head)->next = NULL;

	return 0;
}

/*
 * Description:　增加
 */
int add(LinkList head)
{
	Node *newnode = NULL;	

	if (!(newnode = (Node *)malloc(sizeof(Node)))) {
		perror("malloc");
	}

	printf("请输入联系人姓名:\n");
	scanf("%s", newnode->name);
	printf("请输入联系人号码:\n");
	scanf("%s", &newnode->number);
	

#ifdef DEBUG
	printf("newnode->name = %s\n", newnode->name);
	printf("newnode->number = %s\n", newnode->number);
#endif

	/*头插法*/
	newnode->next = head->next;
	head->next = newnode;

	return 0;
}

/*
 * Description: 删除
 */
int del(LinkList head)
{
	char d_name[NAME_LEN];
	Node *cur = NULL;
	Node *pre = NULL;
	list(head);
	printf("请输入要删除的联系人姓名:\n");
	scanf("%s", d_name);
	
	cur = head->next;
	pre = head;
	while (cur != NULL) {
		if (0 == (strcmp(d_name, cur->name))) {
			printf("将要删除联系人:%s 号码:%s\n", cur->name, cur->number);
			pre->next = cur->next;
			free(cur);
		}
		pre = pre->next;
		cur = cur->next;
	}

	printf("删除成功！\n");

	return 0;
}



/*
 * Description:　修改
 */
int modify(LinkList head)
{
	Node *cur = NULL;
	char m_name[NAME_LEN];	

	printf("请输入要修改的联系人姓名:\n");
	scanf("%s", m_name);

	cur = head->next;
	while (cur != NULL) {
		if (0 == (strcmp(m_name, cur->name))) {
			printf("请重新输入姓名:");
			scanf("%s", cur->name);
			printf("请重新输入电话号码:");
			scanf("%s", cur->number);
			printf("修改成功!\n");
			
		#ifdef DEBUG
			list(head);
		#endif
			return 0;
		}
		cur = cur->next;
	}

	printf("未找到联系人:%s\n", m_name);

	return 0;
}

/*
 * Description: 查询
 */
int query(LinkList head)
{
	Node *cur = NULL;
	char q_name[NAME_LEN];

	printf("请输入要查询的联系人姓名或号码:\n");
	scanf("%s", q_name);
	cur = head->next;
	while (cur != NULL) {
		if ((0 == strcmp(q_name, cur->name)) || (0 == strcmp(q_name, cur->number))) {
			printf("查询到的联系人信息如下:\n");
			printf("\t姓名\t\t号码\n");
			printf("\t%s\t\t%s\n", cur->name, cur->number);
			return 0;
		}
		cur = cur->next;
	}
	
	printf("数据库无相关信息!\n");

	return 0;
}


/*
 * Description: 加载
 */
int load(LinkList head)
{
	FILE *r_file = NULL;
	Node *newnode = NULL;

	r_file = fopen("./data.txt", "rt");
	if (!r_file) {
		perror("fopen");
		r_file = fopen("./data.txt", "wt");
		fclose(r_file);
		return 0;
	}
	
	
	while (!feof(r_file)) {
		if (!(newnode = (Node *)malloc(sizeof(Node)))) {
			perror("malloc");
			exit(-1);
		}
		fscanf(r_file, "%s\t%s\n", newnode->name, newnode->number);
		printf("读入数据:%s\t%s...\n", newnode->name, newnode->number);
		newnode->next = head->next;
		head->next = newnode;
	}
	printf("读入数据完毕!\n");

	fclose(r_file);

#ifdef DEBUG
	list(head);
#endif 


	return 0;
}

/*
 * Description: 保存
 */
int save(LinkList head)
{
	Node *cur = NULL;
	FILE *w_file = NULL;

	w_file = fopen("./data.txt", "wt");
	if (!w_file) {
		perror("fopen");
		exit(-1);
	}

	cur = head->next;
	while (cur != NULL) {
		fprintf(w_file, "%s\t%s\n", cur->name, cur->number);
		printf("正在写入数据: %s\t%s...\n", cur->name, cur->number);
		cur = cur->next;
	}
	
	printf("保存数据成功!\n");

	return 0;
}

/*
 * Description: 列出信息
 */
int list(LinkList head)
{
	Node *cur = NULL;
	
	printf("\t姓名\t\t\t号码\n");
	
	cur = head->next;
	while (cur != NULL) {
		printf("\t%s\t\t%s\n", cur->name, cur->number);	
		cur = cur->next;
	}

	return 0;
}
