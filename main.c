#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACK_SIZE 100
#define TYPE float


typedef struct
{
char symbol[100];
float value;
struct node *next;
} node;

typedef struct
{
 node *head ;
 node *tail ;
} linkedList;

node* newNode(char symbol[],float value){
    node* n=( node*) malloc(sizeof(node));
   strcpy(n->symbol,symbol);
    n->value=value;
    n->next=NULL;
    return n;
}
void initializeLinkedList(linkedList *list){
    list->head=NULL;
    list->tail=NULL;
}

void addTail(linkedList *list,char symbol[],float value){
    node* n=newNode(symbol,value);
    if(list->tail)
        list->tail->next=n;

    list->tail=n;

    if(!list->head)
        list->head=n;

}

node* search(linkedList *list,char symbol[]){
    node *n=list->head;
    while(n){
        if(strcmp(n->symbol,symbol)==0)
            return n;
        n=n->next;
    }
    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////

typedef struct{
int top;
TYPE items[STACK_SIZE];
}Stack;
void initialize(Stack*s)
{
    s->top=0;
}
void push(Stack*s,TYPE value)
{
 s->items[s->top++]=value;
}
TYPE pop(Stack*s)
{
    return s->items[--s->top];
}
int isfull(Stack*s)
{
    if(s->top<STACK_SIZE)
        return 0;
    else return 1;
}
int isempty(Stack*s)
{
    if(s->top>0)
        return 0;
    else return 1;
}
float top(Stack*s)
{
    int x=pop(s);
    push(s,x);
    return x;
}


 int order(char c)
{
 switch(c){
 case'(':
 case')':
    return 2;
 case'*':
 case'/':
     return 1;
 case'+':
 case'-':
     return 0;
 }
}

 char* topostfix(char infix[]){
 Stack s;
 initialize(&s);
 char* postfix;
 postfix=(char*)malloc(100*sizeof(char));
 char c;
 int i=0; int j=0;
 while(infix[i]!='\0')

 {
     c=infix[i];
    if(c>='0'&&c<='9'){
         postfix[j]=c;
            j++;

    if(!(infix[i+1]>='0'&&infix[i+1]<='9')){
       if(infix[i+1]!='.'){
        postfix[j]=' ';
        j++;
       }
    }
    }
    if(isalpha(c)){
         postfix[j]=c;
            j++;

    if(!isalpha(infix[i+1])){
       if(infix[i+1]!='.'){
        postfix[j]=' ';
        j++;
       }
    }
    }
    else if(c=='.'){
        postfix[j]=c;
            j++;
    }



    else if(c=='('){
      push(&s,c);
      }
    else if(c==')'){
        if(isempty(&s)){printf("ERROR\n"); start();}
        while(top(&s)!='(')
    {
        postfix[j]=pop(&s);
        j++;
         postfix[j]=' ';
        j++;
    }
    pop(&s);
    }
    else if(c=='+'||c=='-'||c=='*'||c=='/'){
    if(isempty(&s))
        push(&s,c);
    else{
        while(!isempty(&s)&&order(top(&s))>=order(c)&&top(&s)!='(')
    {
      postfix[j]=pop(&s);
      j++;
       postfix[j]=' ';
        j++;
    }

    push(&s,c);}
   }
   else{}
    i++;}
    while(!isempty(&s))
    {
        postfix[j]=pop(&s);
        j++;
         postfix[j]=' ';
        j++;

    }
    postfix[j]='\0';
    return postfix;
    }
float toString(char a[]){
    int point=100,i=0; float n=0,j=0.1;
    for(i=0;a[i]!='\0';i++)
{
    if(a[i]=='.')
        point=i;
}
 for(i=0;a[i]!='\0';i++)
{
   if(i<point)
      n = n * 10 + a[i] - '0';
  else if(i>point) {
      n = n + (a[i] - '0')*j;
      j=j/10;
   }
}
  return n;
    }
linkedList list;
float evaluate(char* infix)
{  char x[10],y[10];

    Stack s;
    initialize(&s);
    int i=0;
    while(infix[i]!='\0')
    {
        if((infix[i]<='9'&&infix[i]>='0')||infix[i]=='.'){
                {
                    int j=0;
               while((infix[i]<='9'&&infix[i]>='0')||infix[i]=='.'){
                x[j]=infix[i];
                i++; j++;
               }
               x[j]='\0';
           }
           push(&s,toString(x));

        }
        else if(isalpha(infix[i])){

              int j=0;
               while(isalpha(infix[i])){
                y[j]=infix[i];
                i++;
                j++;
               }
               y[j]='\0';
         if(search(&list,y)!=NULL){
          push(&s, search(&list,y)->value);
         } else{
             printf("ERROR...Invalid symbol %s\n",y);
         start();
         }
          }
         else if (infix[i]==' ')
           i++;
            else if (infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/')
        {
             float a,b;
            if(isempty(&s))
                {
                    printf("ERROR\n");
                    start();
                }
            else a=pop(&s);
            if(isempty(&s))
               {
                    printf("ERROR\n");
                    start();
                }
            else b=pop(&s);
            switch(infix[i])
         {case '+': push(&s,a+b); break;
            case '-': push(&s,b-a); break;
            case '*': push(&s,a*b); break;
            case '/': push(&s,b/a); break;
            }
           i++; }

    }
    return pop(&s);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



char* removeSpace(char expression[]){
    int i=0,j;
while(expression[i]!='\0'){
        j=i;
    if(expression[i]==' ')
    while(expression[j]!='\0'){
        expression[j]=expression[j+1];
        j++;
        i=-1;
    }
    i++;
}
return expression;
}
//////////////////////////////////////////////////////////////////////////////
int equal(char expression[]){
    int count=0,i=0;
while(expression[i]!='\0'){
    if(expression[i]=='=')
       {
        count++;
       }
        i++;
}
if(count!=1)
    return 0;
else { i=0;
    while(expression[i]!= '='){
        if(!isalpha(expression[i]))
            return 0;
           else
            i++;
    }

}
return 1;
}
//////////////////////////////////////////////////////////////////////////////
void split(char*symbol,char*value,char expression[]){
int i=0,j=0;
while(expression[i]!='='){
    symbol[i]=expression[i];
    i++;
}
symbol[i]='\0';
while(expression[i+1]!='\0'){
    value[j]=expression[i+1];
    i++;
    j++;
}
value[j]='\0';
}
/////////////////////////////////////////////////////////////////////////////////////////
int check(char infix[]){
    int i=0,count1=0,count2=0;
    if(!(infix[i]>='0'&&infix[i]<='9'))
      if(!isalpha(infix[i]))
        if(infix[i]!='(')
        return 0;
    while(infix[i]!='\0'){
            char c = infix[i];
            char x =infix[i+1];
            //checking invalid symbol
    if(!(c>='0'&&c<='9')){
      if(!(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='('||c==')'||c=='.')) {
        if(!isalpha(c)){
           return 0;}}}
     //checking numbers
    if(c>='0'&&c<='9'){
         if(x=='('||isalpha(x)){
               return 0;}}
   //checking strings
   if(isalpha(c))
   if((x>='0'&&x<='9')||x=='.'||x=='('){
         return 0;
      }

 //checking operators
  if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'){
        if(x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x==')'||x=='.'){
            return 0;
        }
   }
//checking maths error
  if(c=='/'){
       if(x=='0'){
            return 0;}}
//checking floating point
  if(infix[i]=='.'){
           if(!(x>='0'&&x<='9')){
               return 0;}}
   //checking brackets
if(c=='('){

if(x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x==')'||x=='.'){
      return 0;
}
  count1++;
}

if(c==')'){
    if(x=='.'||x=='('||(x>='0'&&x<='9')||isalpha(x)){
     return 0;
   }
   count2++;
}

if(count1<count2)
    return 0;

        i++;

    }
    if(count1!=count2){
        return 0;
    }

return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void calculate(char expression[]){

char symbol[10];
char infix[100];
float value;
char copy[100];

strcpy(copy,removeSpace(expression));

if(equal(copy)==0){
    printf("ERROR\n");
    start();
}

split(symbol,infix,copy);

if(check(infix)==0){
printf("error\n");
start();}

strcpy(copy,topostfix(infix));

value=evaluate(copy);

printf("The value of entered expression is %s = %.3f\n",symbol,value);
strcpy(copy,symbol);
node*n=search(&list,copy);
if(n!=NULL)
{
    n->value=value;
}
else
addTail(&list,copy,value);
start();
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void start(){
char expression[100];
printf("Enter the expression or 'end' to exit:\t");
gets(expression);
if(strcmp(expression,"end")==0)
exit(-1);
else
calculate(expression);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    initializeLinkedList(&list);
    start();
    return 0;
}
