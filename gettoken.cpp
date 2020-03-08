//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gettoken.h"

char token_text[20];//存放单词自身值
char string_num[20];//存放数字的字符串
int cnt_lines = 1;
extern FILE *fp;

int wordMap()
{
    int kind;
    if (fp == NULL)
    {
        printf("错误，文件未能正常打开\n");
    }
    printf("\n");
    printf("  单词类别");
    printf("\t单词值\n");
    do
    {
        kind = gettoken(fp);
        if (kind != ERROR_TOKEN)
        {
            switch (kind)
            {
            case IDENT:
                printf("   标识符");
                break;
            case INT_CONST:
                printf("  整型常量");
                break;
            case FLOAT_CONST:
                printf("浮点型常量");
                break;
            case CHAR_CONST:
                printf("  字符常量");
                break;
            case STRING_CONST:
                printf("字符串常量");
                break;
            case KEYWORD:
                printf("   关键字");
                break;
            case INT:
                printf("类型关键字");
                break;
            case DOUBLE:
                printf("类型关键字");
                break;
            case FLOAT:
                printf("类型关键字");
                break;
            case CHAR:
                printf("类型关键字");
                break;
            case SHORT:
                printf("类型关键字");
                break;
            case LONG:
                printf("类型关键字");
                break;
            case IF:
                printf("   关键字");
                break;
            case ELSE:
                printf("   关键字");
                break;
            case DO:
                printf("   关键字");
                break;
            case WHILE:
                printf("   关键字");
                break;
            case FOR:
                printf("   关键字");
                break;
            case STRUCT:
                printf("   关键字");
                break;
            case BREAK:
                printf("   关键字");
                break;
            case SWITCH:
                printf("   关键字");
                break;
            case CASE:
                printf("   关键字");
                break;
            case TYPEDEF:
                printf("   关键字");
                break;
            case RETURN:
                printf("   关键字");
                break;
            case CONTINUE:
                printf("   关键字");
                break;
            case VOID:
                printf("   关键字");
                break;
            case EQ:
                printf("   等于号");
                break;
            case NEQ:
                printf("  不等于号");
                break;
            case ASSIGN:
                printf("   赋值号");
                break;
            case LP:
                printf("   左括号");
                break;
            case RP:
                printf("   右括号");
                break;
            case LB:
                printf("  左大括号");
                break;
            case RB:
                printf("  右大括号");
                break;
            case LM:
                printf("  左中括号");
                break;
            case RM:
                printf("  右中括号");
                break;
            case SEMI:
                printf("     分号");
                break;
            case COMMA:
                printf("     逗号");
                break;
            case TIMES:
                printf("     乘号");
                break;
            case DIVIDE:
                printf("     除号");
                break;
            case ANNO:
                printf("     注释");
                break;
            case PLUS:
                printf("     加法");
                break;
            case PLUSPLUS:
                printf("  自增运算");
                break;
            case MINUS:
                printf("     减法");
                break;
            case MINUSMINUS:
                printf("  自减运算");
                break;
            case MORE:
                printf("   大于号");
                break;
            case MOREEQUAL:
                printf("大于等于号");
                break;
            case LESS:
                printf("   小于号");
                break;
            case LESSEQUAL:
                printf("小于等于号");
                break;
            case INCLUDE:
                printf("头文件引用");
                break;
            case MACRO:
                printf("   宏定义");
                break;
            case ARRAY:
                printf("     数组");
                break;
            }
            printf("\t%s\n", token_text);
        }
        else
        {
            printf("\t第%d行出现错误\n", cnt_lines);
            break;
        }
    } while (kind != -1);

    return 0;
}

//判断字符是否是数字
int isNum(char c)
{
    if (c >= 48 && c <= 57)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//判断字符是否是十六进制数
int isXnum(char c)
{
    if ((isNum(c)) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//判断字符是否是字母
int isLetter(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*判断字符是否是字母或数字*/
int isLorN(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*向字符数组中添加字符*/
int add_token(char *token, char c)
{
    int i = 0;
    while (*(token + i) != '\0')
    {
        i++;
    }
    /*读取的单词长度不能超过20*/
    if (i >= 19)
    {
        return -1;//添加失败
    }
    *(token + i) = c;
    *(token + i + 1) = '\0';
    return 1;
}

int gettoken(FILE *fp)
{
    int i;
    char c = '0';
    *(token_text) = '\0';
    /*过滤开头的空白字符*/
    if ((c = fgetc(fp)) == EOF)
    {
        ungetc(c, fp);
        return END;
    }
    else
    {
        ungetc(c, fp);
    }
    do
    {
        c = fgetc(fp);
        if (c == '\n')
        {
            cnt_lines++;
        }
    } while (c == ' ' || c == '\n');
    //识别标识符or关键字or数组
    if (isLetter(c) || c == '_')
    {
        do
        {
            add_token(token_text, c);
        } while (isLorN(c = fgetc(fp)));
        ungetc(c, fp);//退回多读的字符到文件缓冲区
        /*先判断是否是类型关键字*/
        if (strcmp(token_text, "int") == 0)
        {
            return INT;
        }
        if (strcmp(token_text, "double") == 0)
        {
            return DOUBLE;
        }
        if (strcmp(token_text, "char") == 0)
        {
            return CHAR;
        }
        if (strcmp(token_text, "short") == 0)
        {
            return SHORT;
        }
        if (strcmp(token_text, "long") == 0)
        {
            return LONG;
        }
        if (strcmp(token_text, "float") == 0)
        {
            return FLOAT;
        }
        /*判断是否是某种关键字*/
        if (strcmp(token_text, "if") == 0)
        {
            return IF;
        }
        if (strcmp(token_text, "else") == 0)
        {
            return ELSE;
        }
        if (strcmp(token_text, "do") == 0)
        {
            return DO;
        }
        if (strcmp(token_text, "while") == 0)
        {
            return WHILE;
        }
        if (strcmp(token_text, "for") == 0)
        {
            return FOR;
        }
        if (strcmp(token_text, "struct") == 0)
        {
            return STRUCT;
        }
        if (strcmp(token_text, "break") == 0)
        {
            return BREAK;
        }
        if (strcmp(token_text, "switch") == 0)
        {
            return SWITCH;
        }
        if (strcmp(token_text, "case") == 0)
        {
            return CASE;
        }
        if (strcmp(token_text, "typedef") == 0)
        {
            return TYPEDEF;
        }
        if (strcmp(token_text, "return") == 0)
        {
            return RETURN;
        }
        if (strcmp(token_text, "continue") == 0)
        {
            return CONTINUE;
        }
        if (strcmp(token_text, "void") == 0)
        {
            return VOID;
        }
        for (i = 0; i < 13; i++)
        {
            if (strcmp(token_text, KeyWords[i]) == 0)
            {
                return KEYWORD;
            }
            else
            {
                c = fgetc(fp);
                if (c == '[')
                {
                    //识别数组
                    add_token(token_text, c);
                    c = fgetc(fp);
                    while (c >= '0' && c <= '9')
                    {
                        add_token(token_text, c);
                        add_token(string_num, c);
                        c = fgetc(fp);
                    }
                    if (c != ']')
                    {
                        return ERROR_TOKEN;
                    }
                    add_token(token_text, c);
                    return ARRAY;
                }
                else
                {
                    ungetc(c, fp);
                    return IDENT;
                }
            }
        }
    }
    //识别整形常量和浮点型常量
    if (isNum(c))
    {
        do
        {
            add_token(token_text, c);
        } while (isNum(c = fgetc(fp)));
        if (c != '.' && c != 'u' && c != 'l')
        {
            if (c != ' ' && c != ';' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/')
            {
                return ERROR_TOKEN;
            }
            ungetc(c, fp);
            return INT_CONST;
        }
        else if (c == '.')
        {
            c = fgetc(fp);
            if (!isNum(c))
            {
                return ERROR_TOKEN;
            }
            else
            {
                ungetc(c, fp);
                c = '.';
                add_token(token_text, c);
                c = fgetc(fp);
                do
                {
                    add_token(token_text, c);
                } while (isNum(c = fgetc(fp)));
                if (c == 'f')
                {
                    add_token(token_text, c);
                    return FLOAT_CONST;
                }
                else
                {
                    ungetc(c, fp);
                }
                return FLOAT_CONST;
            }
        }
        else if (c == 'u')
        {
            add_token(token_text, c);
            c = fgetc(fp);
            if (c == 'l')
            {
                add_token(token_text, c);
                c = fgetc(fp);
                if (c == 'l')
                {
                    add_token(token_text, c);
                    return INT_CONST;
                }
                else
                {
                    ungetc(c, fp);
                    return INT_CONST;
                }
            }
            else
            {
                ungetc(c, fp);
                return INT_CONST;
            }
        }
        else if (c == 'l')
        {
            add_token(token_text, c);
            return INT_CONST;
        }
        else
        {
            return ERROR_TOKEN;
        }
    }

    //识别以小数点开头的浮点型常量
    if (c == '.')
    {
        do
        {
            add_token(token_text, c);
        } while (isNum(c = fgetc(fp)));
        ungetc(c, fp);
        return FLOAT_CONST;
    }

    //识别字符型常量
    if (c == '\'')
    {
        add_token(token_text, '\'');
        if ((c = fgetc(fp)) != '\\')
        {
            add_token(token_text, c);
            if ((c = fgetc(fp)) == '\'')
            {
                add_token(token_text, c);
                return CHAR_CONST;
            }
            else
            {
                return ERROR_TOKEN;
            }
        }
        else
        {
            /*转义字符*/
            add_token(token_text, '\\');
            c = fgetc(fp);
            if (c == 'n' || c == 't' || c == '\\' || c == '\'' || c == '\"')
            {
                /*普通转义字符*/
                add_token(token_text, c);
                if ((c = fgetc(fp)) == '\'')
                {
                    add_token(token_text, c);
                    return CHAR_CONST;
                }
                else
                {
                    return ERROR_TOKEN;
                }
            }
            else if (c == 'x')
            {
                /*十六进制数转义字符*/
                add_token(token_text, c);
                if (isXnum((c = fgetc(fp))))
                {
                    add_token(token_text, c);
                    if (isXnum((c = fgetc(fp))))
                    {
                        add_token(token_text, c);
                    }
                    else
                    {
                        ungetc(c, fp);
                    }
                    if ((c = fgetc(fp)) == '\'')
                    {
                        add_token(token_text, '\'');
                        return CHAR_CONST;
                    }
                    else
                    {
                        return ERROR_TOKEN;
                    }
                }
                else
                {
                    return ERROR_TOKEN;
                }
            }
            else if (c >= '0' && c <= '7')
            {
                /*八进制数转义字符*/
                add_token(token_text, c);
                if ((c = fgetc(fp)) >= '0' && c <= '7')
                {
                    add_token(token_text, c);
                    if ((c = fgetc(fp)) >= '0' && c <= '7')
                    {
                        add_token(token_text, c);
                        if ((c = fgetc(fp)) == '\'')
                        {
                            add_token(token_text, '\'');
                            return CHAR_CONST;
                        }
                        else
                        {
                            return ERROR_TOKEN;
                        }
                    }
                    else if (c == '\'')
                    {
                        add_token(token_text, '\'');
                        return CHAR_CONST;
                    }
                    else
                    {
                        return ERROR_TOKEN;
                    }
                }
                else
                {
                    if (c == '\'')
                    {
                        add_token(token_text, c);
                        return CHAR_CONST;
                    }
                    else
                    {
                        ungetc(c, fp);
                        return ERROR_TOKEN;
                    }
                }
            }
            else
            {
                return ERROR_TOKEN;
            }
        }
    }

    //识别字符串常量
    if (c == '"')
    {
        do
        {
            if (c != '\\')
                add_token(token_text, c);
            if (c == '\\')
            {
                c = fgetc(fp);
                add_token(token_text, c);
            }
        } while ((c = fgetc(fp)) != '"' && c != '\n');
        if (c == '"')
        {
            add_token(token_text, '"');
            return STRING_CONST;
        }
        else
        {
            return ERROR_TOKEN;
        }
    }

    //识别除号与注释
    if (c == '/')
    {
        add_token(token_text, c);
        if ((c = fgetc(fp)) == '/')
        {
            do
            {
                add_token(token_text, c);
            } while ((c = fgetc(fp)) != '\n');
            ungetc(c, fp);
            return ANNO;
        }
        else if (c == '*')
        {
            while (1)
            {
                add_token(token_text, c);
                c = fgetc(fp);
                if (c == '*')
                {
                    add_token(token_text, c);
                    if ((c = fgetc(fp)) == '/')
                    {
                        add_token(token_text, c);
                        return ANNO;
                    }
                }
                if (c == '\n')
                {
                    add_token(token_text, c);
                    c = '\t';
                    add_token(token_text, c);
                    add_token(token_text, c);
                }
            }
        }
        else
        {
            ungetc(c, fp);
            return DIVIDE;
        }
    }

    //识别头文件引用和宏定义
    if (c == '#')
    {
        add_token(token_text, c);
        if (isLetter(c = fgetc(fp)))
        {
            do
            {
                add_token(token_text, c);
            } while (isLetter(c = fgetc(fp)));
            if (strcmp(token_text, "#include") == 0)
            {
                do
                {
                    add_token(token_text, c);
                } while ((c = fgetc(fp)) != '\n');
                ungetc(c, fp);
                return INCLUDE;
            }
            else if (strcmp(token_text, "#define") == 0)
            {
                do
                {
                    add_token(token_text, c);
                } while ((c = fgetc(fp)) != '\n');
                ungetc(c, fp);
                return MACRO;
            }
            else
            {
                return ERROR_TOKEN;
            }
        }
        else
        {
            return ERROR_TOKEN;
        }
    }

    if (c == '@' || c == '?')
    {//一些非法字符
        return ERROR_TOKEN;
    }

    switch (c)
    {
    case ',':
        add_token(token_text, c);
        return COMMA;
    case ';':
        add_token(token_text, c);
        return SEMI;
    case '=':
        c = fgetc(fp);
        if (c == '=')
        {
            add_token(token_text, c);
            add_token(token_text, c);
            return EQ;
        }
        ungetc(c, fp);
        add_token(token_text, '=');
        return ASSIGN;
    case '!':
        c = fgetc(fp);
        if (c == '=')
        {
            add_token(token_text, '!');
            add_token(token_text, '=');
            return NEQ;
        }
        else
        {
            return ERROR_TOKEN;
        }
    case '+':
        c = fgetc(fp);
        if (c == '+')
        {
            add_token(token_text, c);
            add_token(token_text, c);
            return PLUSPLUS;
        }
        ungetc(c, fp);
        add_token(token_text, '+');
        return PLUS;
    case '-':
        c = fgetc(fp);
        if (c == '-')
        {
            add_token(token_text, c);
            add_token(token_text, c);
            return MINUSMINUS;
        }
        ungetc(c, fp);
        add_token(token_text, '-');
        return MINUS;
    case '(':
        add_token(token_text, c);
        return LP;
    case ')':
        add_token(token_text, c);
        return RP;
    case '{':
        add_token(token_text, c);
        return LB;
    case '}':
        add_token(token_text, c);
        return RB;
    case '[':
        add_token(token_text, c);
        return LM;
    case ']':
        add_token(token_text, c);
        return RM;
    case '*':
        add_token(token_text, c);
        return TIMES;
    case '>':
        add_token(token_text, c);
        if ((c = fgetc(fp)) == '=')
        {
            add_token(token_text, c);
            return MOREEQUAL;
        }
        else
        {
            ungetc(c, fp);
            return MORE;
        }
    case '<':
        add_token(token_text, c);
        if ((c = fgetc(fp)) == '=')
        {
            add_token(token_text, c);
            return LESSEQUAL;
        }
        else
        {
            ungetc(c, fp);
            return LESS;
        }
    case '~':
        return -1;
    }
}
