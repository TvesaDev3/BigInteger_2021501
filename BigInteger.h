#ifndef BigInteger_h
#define BigInteger_h
struct node
{
    int data;
    struct node*next;
};
struct BigInteger
{
    struct node*L;
    int length;
    char sign;
};
void newnode(struct node**head,int val);
void newnodeAtTail(struct node**head,int val);
void reverse(struct node**head);
struct node* copy(struct node* a);
int compareb(struct BigInteger list1,struct BigInteger list2);
struct BigInteger deleteTrailingZeroes(struct BigInteger resdz);
struct BigInteger initialize(char *s);
void display(struct BigInteger);
struct BigInteger add(struct BigInteger list1,struct BigInteger list2);
struct BigInteger sub(struct BigInteger list1,struct BigInteger list2);
struct BigInteger mul(struct BigInteger list1,struct BigInteger list2);
struct BigInteger div1(struct BigInteger list1,struct BigInteger list2);
#endif