#pragma once
#ifndef _FORMAT_H_
#define _FORMAT_H_

typedef struct token
{
    char *str;
    struct token *next;
}token;

void format();
token *readline();

#endif