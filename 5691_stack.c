#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>   /* error numbers */
#define BASE         (10)  /* use decimal */
#include<ctype.h>
#define size 256


/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union
{
    float fData;
    char* cpData;
} Item;
/*
 *
 */
typedef struct
{
    Item *ar;
    int Top;
} Stack;
/*
 *
 *//*
 char* convertArrayWithOutSpace(char *postfix)
 {


 }*/
int n;


int charIsDigit(char digi)
{
    if(digi=='0'||digi=='1'||digi=='2'||digi=='3'||digi=='4'||digi=='5'||digi=='6'||digi=='7'||digi=='8'||digi=='9'||digi=='-'||digi=='.')
        return 1;
    else
        return 0;
}

float convArray(char *post)
{
    char* errCheck;
    char *buf2 = post;
    float converted = strtod(buf2,&errCheck);
    if(errCheck == post)
    {
        printf("Conversion error:%s\n",post);
        return EIO;
    }
    return converted;
}
void init(Stack *s)
{
    s->ar=(Item*)malloc(size*sizeof(Item));
    s->Top=-1;
}
/*
 *
 */
int isEmpty(Stack *s)
{
    if(s->Top==-1)
        return 1;
    else
        return 0;
}
/*
 *
 */
int Top(Stack *s)
{
    return s->Top;
}
Item top(Stack *s)
{
    if(s->Top<0)
        return;
    else
    {
        Item A;
        A.cpData=s->ar[s->Top].cpData;
        return A ;
    }
}
/*
 *
 */
Item pop(Stack *s)
{
    Item B ;
    if(isEmpty(s));
    else
    {
        B=top(s);
        s->Top--;
    }
    return B;
}
/*
 *
 */
void push(Stack *s, Item val)
{
    if (s->Top>=size-1)
        printf("No more Space\n");
    else
    {
        s->Top++;
        s->ar[s->Top].cpData=val.cpData;
    }
}

void destroy(Stack *s)
{
    free(s->ar);
    s->Top=-1;
}
int level(char opr )
{
    if(opr=='^')
        return 4;
    else if(opr=='*'||opr=='/')
        return 3;
    else if(opr=='+'||opr=='-')
        return 1;
    else
        return 0;
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)*4 --> 23+4*
 */
void infixToPostfix(char* infix, char* postfix)
{
    char postfixExpr[256] = "";
    Stack s;
    init(&s);
    int i=0;
    n=0;
    Item F,f,g;
    g.cpData='(';
    push(&s,g);
    strcat(infix,")");
    while(infix[i]!= '\0')
    {
        if(infix[i]=='(')
        {
            g.cpData='(';
            push(&s,g);
        }
        else if(infix[i]==')')
        {
            while(top(&s).cpData!='(')
            {
                 postfix[n]=' ';
                n++;
                f=pop(&s);
                postfix[n]=f.cpData;
                n++;
            }
            pop(&s);// TO POP THE OPEN BRACKET "("
        }
        else if(infix[i]=='+'||infix[i]=='*'||infix[i]=='/'||infix[i]=='^')
        {
            char Tooop=top(&s).cpData;
            if(level(infix[i])<=level(Tooop))
            {

                f=pop(&s);
                postfix[n]=f.cpData;
                n++;
                f.cpData=infix[i];
                push(&s,f);
            }
            else
            {
                f.cpData=infix[i];
                push(&s,f);
            }
        }
        else           // TO ADD NUMBERS
        {
            postfix[n]=infix[i];
            n++;

        }
        i++;
    }
    while(isEmpty(&s)==0)
    {
        F=pop(&s);
        postfix[n]=F.cpData;
        n++;
    }
     postfix[n] = '\0';
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
    Stack D;
    init(&D);
    char *token;
    char temp;
    /* get the first token */
    token = strtok(postfix," ");

    float a,b,result;
    Item g;
    if(n<3)
    {
        printf("Can't do the operation or No Array Found");
        return -1;
    }
    else
    {
        while( token != NULL )
        {
            if(strcmp(token,"+")==0||strcmp(token,"*")==0||strcmp(token,"/")==0||strcmp(token,"^")==0)
            {
                if(strcmp(token,"+")==0)
                {
                    b=pop(&D).fData;
                    a=pop(&D).fData;
                    result =a+b;
                    g.fData=result;
                    push(&D,g);
                }
                if(strcmp(token,"*")==0)
                {
                    b=pop(&D).fData;
                    a=pop(&D).fData;
                    result =a*b;
                    g.fData=result;
                    push(&D,g);
                }
                if(strcmp(token,"/")==0)
                {
                    b=pop(&D).fData;
                    a=pop(&D).fData;
                    result =a/b;
                    g.fData=result;
                    push(&D,g);
                }
                if(strcmp(token,"^")==0)
                {
                    b=pop(&D).fData;
                    a=pop(&D).fData;
                    result=pow(a,b);
                    g.fData=result;
                    push(&D,g);
                }
                else;
            }
            else
            {
                g.fData=convArray(token);
                push(&D,g);
            }
            token = strtok(NULL, " ");
        }
    }
    destroy(&D);
    return result;
}

// return g.fData;

/*
 *
 */
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }


    return 0;
}
