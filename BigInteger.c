#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include"BigInteger.h"
void newnode(struct node**head,int val)
{
    struct node*new=(struct node*)malloc(sizeof(struct node));
    if(!new) return;
    new->data=val;
    if(!(*head))
    {
        *head=new;
        new->next=NULL;
        return;
    }
    new->next=*head;
    *head=new;
    return;
}
void newnodeAtTail(struct node**head,int val)
{
    struct node*new=(struct node*)malloc(sizeof(struct node));
    if(!new)   return;
    new->data=val;
    new->next=NULL;
    if(!(*head))
    {
        *head=new;
        return;
    }
    struct node*itr=*head;
    while(itr->next)
    itr=itr->next;
    itr->next=new;
    return;
}
struct BigInteger initialize(char *s)
{
    struct BigInteger newlist;
    newlist.length=strlen(s);
    newlist.L=NULL;
    if(s[0]=='-')
    {
        newlist.sign='-';
        s=&s[1];
    }
    else
    newlist.sign='+';
    for(int i=0;s[i]!='\0';i++)
    newnode(&(newlist.L),s[i]-'0');
    return newlist;
}
void reverse(struct node**head)
{
    struct node*prev=NULL;
    struct node*current=*head;
    struct node*next=NULL;
    while(current)
    {
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    *head=prev;
}
struct node* copy(struct node* a)
{
    struct node*copyListHead=NULL;
    while(a)
    {
        newnodeAtTail(&copyListHead,a->data);
        a=a->next;
    }
    return copyListHead;
}
int compareb(struct BigInteger list1,struct BigInteger list2)
{
    if(list1.length<list2.length)
    return -1;
    else if(list1.length>list2.length)
    return 1;
    else
    {
        struct node*itr1=copy(list1.L);
        struct node*itr2=copy(list2.L);
        reverse(&itr1);
        reverse(&itr2);
        while(itr1)
        {
            if(itr1->data>itr2->data)
            return 1;
            if(itr1->data<itr2->data)
            return -1;
            itr1=itr1->next;
            itr2=itr2->next;
        }
        return 0;
    }
}
struct BigInteger deleteTrailingZeroes(struct BigInteger resdz)
{
   while(resdz.L!=NULL  && resdz.L->data==0)
   {
       resdz.L=resdz.L->next;
       resdz.length--;
   }
   return resdz;
}
void display(struct BigInteger todis)
{
    if(todis.sign=='-')
    printf("%c",todis.sign);
    struct node*dis=todis.L;
    while(dis)
    {
        printf("%d",dis->data);
        dis=dis->next;
    }
    return;
}
struct BigInteger add(struct BigInteger list1,struct BigInteger list2)
{
    int count=0,carry=0,r;
    struct node*itr1=list1.L;
    struct node*itr2=list2.L;
    struct BigInteger res;
    res.sign='+';
    res.L=NULL;
    while(itr1||itr2)
    {
        int val1=itr1?itr1->data:0;
        int val2=itr2?itr2->data:0;
        r=val1+val2+carry;
        carry=r/10;
        newnode(&(res.L),(r%10));
        count++;
        if(itr1) itr1=itr1->next;
        if(itr2) itr2=itr2->next;
    }
    if(carry)
    {
       newnode(&(res.L),carry);
       count++;
    }
    res.length=count;
    return res;
}
struct BigInteger sub(struct BigInteger list1,struct BigInteger list2)
{
    int count=0,r,c;
    struct node*itr1=NULL;
    struct node*itr2=NULL;
    struct BigInteger res;
    res.L=NULL;
    struct node*cnum1=copy(list1.L);
    struct node*cnum2=copy(list2.L);
    c=compareb(list1,list2);
    if(c==1)
    {
        itr1=cnum1;
        itr2=cnum2;
        res.sign='+';
    }
    else if(c==-1)
    {
        itr2=cnum1;
        itr1=cnum2;
        res.sign='-';
    }
    else
    {
        newnode(&(res.L),0);
        res.length=1;
        res.sign='+';
        return res;
    }
    while(itr1||itr2)
    {
        int val1=itr1?itr1->data:0;
        int val2=itr2?itr2->data:0;
        r=val1-val2;
        if(r<0)
        {
            r=r+10;
            itr1->next->data-=1;
        }
        newnode(&(res.L),r);
        count++;
        if(itr1) itr1=itr1->next;
        if(itr2) itr2=itr2->next;
    }
    res.length=count;
    res=deleteTrailingZeroes(res);
    return res;
}
struct BigInteger mul(struct BigInteger list1,struct BigInteger list2)
{
    int count=0,carry,r,i=0,j,x,y;
    struct node*itr1=list1.L;
    struct node*itr2=list2.L;
    struct BigInteger res;
    res.sign='+';
    res.L=NULL;
    while(itr2)
    {
        carry=0;
        itr1=list1.L;
        struct BigInteger internal;
        internal.sign='+';
        internal.L=NULL;
        internal.length=0;
        for(j=0;j<i;j++)
        newnodeAtTail(&(internal.L),0);
        while(itr1)
        {
            x=itr1->data;
            y=itr2->data;
            r=((itr1->data)*(itr2->data))+carry;
            carry=r/10;
            newnodeAtTail(&(internal.L),(r%10));
            itr1=itr1->next;
        }
        if(carry)
        newnodeAtTail(&(internal.L),carry);
        res=add(internal,res);
        reverse(&(res.L));
        i++;
        itr2=itr2->next;
    }
    reverse(&(res.L));
    itr1=res.L;
    while(itr1)
    {
        count++;
        itr1=itr1->next;
    }
    res.length=count;
    return res;
}
struct BigInteger div1(struct BigInteger list1,struct BigInteger list2)
{
    int count = 0, c;
    struct node *cnum1 = copy(list1.L);

    struct BigInteger copylist1;
    copylist1.sign = '+';
    copylist1.length = list1.length;
    copylist1.L = cnum1;

    c = compareb(copylist1, list2);

    struct BigInteger res;
    res.L = NULL;
    res.sign = '+';
    newnode(&(res.L), 0);

    struct BigInteger one;
    one.sign = '+';
    one.L = NULL;
    one.length = 1;
    newnode(&(one.L), 1);

    if (list2.length == 0 || (list2.length == 1 && list2.L->data == 0))
    {
        printf("Division by zero is not allowed.\n");
        exit(1);
    }

    if (c == -1)
    {
        return res;
    }

    if (c == 0)
    {
        res.L->data = 1;
        return res;
    }

    while (c != -1)
    {
        copylist1 = sub(copylist1, list2);
        reverse(&(copylist1.L));
        res = add(res, one);
        c = compareb(copylist1, list2);
    }

    struct node *itr1 = res.L;
    while (itr1)
    {
        count++;
        itr1 = itr1->next;
    }
    res.length = count;
    reverse(&(res.L));
    return res;
}
