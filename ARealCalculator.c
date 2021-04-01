#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//定义两种链式栈
struct C_Node;
typedef struct C_Node *C_PNode;
struct C_Node
{
    int num;
    C_PNode link;
};
typedef struct C_Node *PCalculator;

struct Node;
typedef struct Node *PNode;
struct Node
{
    char c;
    PNode link;
};
typedef struct Node *Pstack;

PCalculator C_CreateEmptyStack (void)
{
    PCalculator pstack;
    pstack = (PCalculator)malloc(sizeof(struct C_Node));
    pstack->link = NULL;
    return pstack;
}

Pstack CreateEmptyStack (void)
{
    Pstack pstack;
    pstack = (Pstack)malloc(sizeof(struct Node));
    pstack->link = NULL;
    return pstack;
}

int C_isEmptyStack (PCalculator pstack)
{
    return (pstack->link == NULL);
}

int isEmptyStack (Pstack pstack)
{
    return (pstack->link == NULL);
}

void C_PushStack (PCalculator pstack, int num)
{
    C_PNode p;
    p = (C_PNode)malloc(sizeof (struct C_Node));
    p->num = num;
    p->link = pstack->link;
    pstack->link = p;
}

void PushStack (Pstack pstack, char c)
{
    PNode p;
    p = (PNode)malloc(sizeof (struct Node));
    p->c = c;
    p->link = pstack->link;
    pstack->link = p;
}

void C_PopStack (PCalculator pstack)
{
    C_PNode p;
    p = pstack->link;
    pstack->link = p->link;
    free(p);
}

void PopStack (Pstack pstack)
{
    PNode p;
    p = pstack->link;
    pstack->link = p->link;
    free(p);
}

int C_TopStack (PCalculator pstack)
{
    return pstack->link->num;
}

char TopStack (Pstack pstack)
{
    return pstack->link->c;
}

int main (void)
{
    char str[601];
    Pstack operator;
    char houzhui[601];
    int i=0,j=0;
    PCalculator Calculator;
    int integer,k,l,a,b,count;
    int n;
    char c;
    scanf("%d", &n);
    c = getchar();
    for (count=0;count<n;count++)
    {   //将中缀表达式转变为后缀表达式
        i=0;



        
        gets(str);
        operator = CreateEmptyStack();
        Calculator = C_CreateEmptyStack();
        while (str[i]!='\0')
        {
            if (str[i]!=32 && (str[i] < 48 || str[i] > 57) && (str[i+1] < 48 || str[i+1] > 57))
            {
                if (!isEmptyStack(operator))
                {
                    switch (str[i])
                    {
                        case 94:
                            if (TopStack(operator) == 94)
                            {
                                houzhui[j] = TopStack(operator);
                                houzhui[j+1] = 32;
                                PopStack (operator);
                                j+=2;
                            }
                            PushStack(operator, str[i]);
                            break;
                        case 42:
                        case 47:
                        case 43:
                        case 45:
                            while (TopStack(operator) == 94||TopStack(operator) == 42||TopStack(operator) == 47)
                            {
                                houzhui[j] = TopStack(operator);
                                houzhui[j+1] = 32;
                                PopStack(operator);
                                j+=2;
                                if (isEmptyStack(operator)) break;
                            }
                            PushStack(operator, str[i]);  
                            break;
                        case 40:
                            PushStack(operator, str[i]);
                            break;
                        case 41:
                            while (TopStack(operator)!= 40)
                            {
                                houzhui[j] = TopStack(operator);
                                houzhui[j+1] = 32;
                                PopStack(operator);
                                j+=2;
                                if (isEmptyStack(operator)) break;
                            }
                            PopStack (operator);
                            break;
                    }
                
                }
                else
                {
                    PushStack(operator, str[i]);
                }
            }
            else if (str[i] >= 48 && str[i] <= 57)
            {
                while (str[i+1] >= 48 && str[i+1] <= 57)
                {
                    houzhui[j] = str[i];
                    j++;
                    i++;
                }
                houzhui[j] = str[i];
                houzhui[j+1] = 32;
                j+=2;
            }
            else if (str[i] == 45 && str[i+1] != 32)
            {
                while (str[i+1] >= 48 && str[i+1] <= 57)
                {
                    houzhui[j] = str[i];
                    j++;
                    i++;
                }
                houzhui[j] = str[i];
                houzhui[j+1] = 32;
                j+=2;
            }
            i++;
        }
        while(!isEmptyStack(operator))
        {
            houzhui[j] = TopStack(operator);
            houzhui[j+1] = 32;
            PopStack(operator);
            j+=2;
        }
        i=0;
        houzhui[j] = '\0';
        while (houzhui[i] != '\0')//对后缀表达式进行计算
        {
            if (houzhui[i] >= 48 && houzhui[i] <= 57)
            {
                k = i-1;
                integer = 0;
                while (houzhui[i+1] >= 48 && houzhui[i+1]<=57)
                {
                    i++;
                }
                for (l=0;l<i-k;l++)
                {
                    integer += (houzhui[k+1+l]-48)*(int)pow(10,i-k-1-l);
                }
                C_PushStack (Calculator, integer);
            }
            if (houzhui[i] == 45 && houzhui[i+1] != 32)
            {
                i++;
                k = i-1;
                integer = 0;
                while (houzhui[i+1] >= 48 && houzhui[i+1]<=57)
                {
                    i++;
                }
                for (l=0;l<i-k;l++)
                {
                    integer += (houzhui[k+1+l]-48)*(int)pow(10,i-k-1-l);
                }
                integer = -integer;
                C_PushStack (Calculator, integer);
            }
            if ((houzhui[i] == 43 || houzhui[i] == 47 || houzhui[i] == 45 || houzhui[i] == 42 || houzhui[i] == 94)&&houzhui[i+1]==32)
            {
                switch (houzhui[i])
                {
                case 42:
                    a = C_TopStack(Calculator);
                    C_PopStack(Calculator);
                    b = C_TopStack(Calculator);
                    C_PopStack (Calculator);
                    C_PushStack(Calculator, a*b); 
                    break;           
                case 43:
                    a = C_TopStack(Calculator);
                    C_PopStack(Calculator);
                    b = C_TopStack(Calculator);
                    C_PopStack (Calculator);
                    C_PushStack(Calculator, a+b);
                    break;
                case 45:
                    a = C_TopStack(Calculator);
                    C_PopStack(Calculator);
                    b = C_TopStack(Calculator);
                    C_PopStack (Calculator);
                    C_PushStack(Calculator, b-a);
                    break;
                case 47:
                    a = C_TopStack(Calculator);
                    C_PopStack(Calculator);
                    b = C_TopStack(Calculator);
                    C_PopStack (Calculator);
                    C_PushStack(Calculator, b/a);
                    break;
                case 94:
                    a = C_TopStack(Calculator);
                    C_PopStack(Calculator);
                    b = C_TopStack(Calculator);
                    C_PopStack (Calculator);
                    C_PushStack(Calculator, (int)pow(b,a));
                    break;
                }
            }
            i++;
        }   

        if (!C_isEmptyStack(Calculator))
        {
            printf("%d\n", C_TopStack(Calculator));
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}