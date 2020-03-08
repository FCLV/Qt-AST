#define _CRT_SECURE_NO_WARNINGS
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gettoken.h"

extern FILE *fp, *to_formatText;
extern char token_text[20]; //存放自身单词值

void format()
{
    int tabs = 0; //控制缩进
    int i;
    int flag = 0; //用于标记无大括号但需要缩进的情况
    token *head, *tail, *p;
    while (1)
    {
        head = readline();
        if (head == NULL)
        {
            break;
        }
        tail = head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        if (strcmp(head->str, "}") == 0)
        {
            tabs--;
        }
        for (i = 0; i < tabs; i++)
        { //输出缩进
            printf("\t");
            fprintf(to_formatText, "\t");
        }
        if (flag == 1)
        {
            tabs--;
            flag = 0;
        }
        p = head;
        while (p != NULL)   //此循环跳出即为读完一行
        {
            printf("%s ", p->str);
            fprintf(to_formatText, "%s ", p->str);
            p = p->next;
        }
        printf("\n");
        fprintf(to_formatText, "\n");
        if (strcmp(tail->str, "{") == 0)
        {
            tabs++;
        }
        p = head;
        while (p != NULL)
        {
            if ((strcmp(p->str, "if") == 0) || (strcmp(p->str, "for") == 0) || (strcmp(p->str, "while") == 0))
            {
                if (strcmp(tail->str, "{") != 0 && strcmp(tail->str, ";") != 0)
                {
                    tabs++;    //一行的末尾既非'{'也非';' 且在不考虑语法错误的情况下认为是if,else,while等，需要换行
                    flag = 1;
                }
            }
            p = p->next;
        }
    }
}

token *readline()
{
    char c;
    int w;
    token *head = NULL;
    token *tail = head; //初始化链表头尾指针
    w = gettoken(fp);
    if (w == EOF)
    {
        return NULL;
    }
    head = (token *)malloc(sizeof(token));
    char *token_text1 = (char *)malloc(25 * sizeof(char));
    strcpy(token_text1, token_text);
    head->str = token_text1;
    head->next = NULL;
    tail = head;
    while ((c = fgetc(fp)) != '\n')//每识别完一个单词就判断单词后面是不是换行符
    {
        ungetc(c, fp);
        gettoken(fp);
        tail->next = (token *)malloc(sizeof(token));
        tail = tail->next;
        token_text1 = (char *)malloc(25 * sizeof(char));
        strcpy(token_text1, token_text);    //token_text为所有文件的全局变量，由gettoken过程中获得
        tail->str = token_text1;
        tail->next = NULL;
    }
    return head;
}