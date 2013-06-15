/*
 * =====================================================================================
 *
 *       Filename:  addressbook.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月15日 13时07分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#ifndef __ADDRESSBOOK_H_
#define __ADDRESSBOOK_H_

#define DEBUG
#define NAME_LEN 32
#define NUMBER_LEN 32


typedef struct contact_person{
	char number[NUMBER_LEN];
	char name[NAME_LEN];
	struct contact_person *next;
}Node, *LinkList;

int welcome_menu(char *choice, LinkList head);
int init(LinkList *head);
int add(LinkList head);
int del(LinkList head);
int modify(LinkList head);
int query(LinkList head);
int load(LinkList head);
int save(LinkList head);
int list(LinkList head);


#endif

