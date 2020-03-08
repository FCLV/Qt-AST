#pragma once
#ifndef _AST_H_
#define _AST_H_

typedef struct AST     //AST本质为n叉树，使用孩子兄弟表示法转化为二叉树
{
    struct AST *l;
    struct AST *r;
    int type;
    struct data
    {
        int type;
        char *data;
    }data;
}AST;

//存储变量名，用于检查变量定义
typedef struct VarNode
{
    int size;//记录变量个数
    char *variable[20];//用于记录变量名
    struct VarNode *next;
}VNode;

typedef enum data_kind
{
    EXTDEFLIST = 1,
    EXTVARDEF,
    EXTVARTYPE,
    EXTVARLIST,//外部变量名序列结点
    EXTVAR,//外部变量名结点
    FUNCDEF,//函数定义结点
    FUNCRETURNTYPE,//函数返回值类型结点
    FUNCNAME,//函数名结点
    FUNCFORMALPARALIST,//函数形式参数序列结点
    FUNCFORMALPARADEF,//函数形式参数结点(10)
    FUNCFORMALPARATYPE,//函数形参类型结点
    FUNCFORMALPARA,//函数形参名结点
    FUNCBODY,//函数体结点
    LOCALVARDEFLIST,//局部变量定义序列结点
    LOCALVARDEF,//局部变量定义结点(15)
    LOCALVARTYPE,//局部变量类型结点
    LOCALVARNAMELIST,//局部变量名序列
    LOCALVARNAME,//局部变量名
    STATELIST,//语句序列结点
    OPERAND,//操作数结点(20)
    OPERATOR,//运算符结点
    EXPRESSION,//表达式
    IFPART,//if语句部分
    ELSEPART,//else部分
    IFSTATEMENT,//if语句(25)
    IFELSESTATEMENT,//if-else语句
    WHILESTATEMENT,//while语句结点
    WHILEPART,//while条件语句结点
    WHILEBODY,//while语句体
    FORSTATEMENT,//for语句结点(30)
    FORPART,//for条件语句
    FORPART1,//for语句条件一
    FORPART2,//for语句条件二
    FORPART3,//for语句条件三
    FORBODY,//for语句体(35)
    RETURNSTATEMENT,//return语句
    BREAKSTATEMENT,//break语句
    DOWHILESTATEMENT,//do-while循环语句
    DOWHILEBODY,//do-while语句体
    DOWHILECONDITION,//do-while条件(40)
    CONTINUESTATEMENT,//continue语句
    FUNCCLAIM,//函数声明
    ARRAYDEF,//数组定义
    ARRAYTYPE,//数组类型
    ARRAYNAME,//数组名(45)
    ARRAYSIZE,//数组大小
}kind;

void startAST();//语义分析函数
void freeTree(AST *root);//释放root为根的全部结点
AST *program();//<程序>子程序
AST *ExtDefList();//<外部函数定义序列>子程序
AST *ExtDef();
AST *ExtVarDef();
AST *FuncDef();
AST *FormParaList();//形参序列
AST *FormParaDef();//形参定义
AST *CompState();//<复合语句>子程序
AST *LocalVarDefList();//局部变量定义子程序
AST *StateList();//<语句序列>子程序
AST *Statement();//<语句>子程序
AST *Expression(int endsym);//<表达式>子程序
char Precede(int c1, int c2);//比较优先级函数
void returntoken(int w, FILE *fp);//将读出的tokem返回到文件流中
void showType(int type);
void PreorderTranverse(AST *root, int depth);
int addname(char *token_text);//将变量名添加到结点中
int checkname_exist(char *token_text);
AST *ArrayDef();

#endif