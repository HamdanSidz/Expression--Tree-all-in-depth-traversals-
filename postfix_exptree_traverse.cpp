//Using inbuilt stack library to create stack
#include <iostream>
#include <stack>
using namespace std;

int priority (char alpha){
    if(alpha == '+' || alpha =='-')
        return 1;
 
    if(alpha == '*' || alpha =='/')
        return 2;
 
    if(alpha == '^')
        return 3;
    else
    return 0;
}

int isoperator(char val)
{
    if ((val == '+') || (val == '-') || (val == '*') || (val == '/') || (val == '%') || (val == '^'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string convert(string infix)
{
    int i = 0;
    string postfix = "";
    // using inbuilt stack< > from C++ stack library
    stack <int>s;

    while(infix[i]!='\0')
    {
        // if operand add to the postfix expression
        if(infix[i]>='a' && infix[i]<='z'|| infix[i]>='A'&& infix[i]<='Z')          
        {
            postfix += infix[i];
            i++;
        }
        // if opening bracket then push the stack
        else if(infix[i]=='(')
        {
            s.push(infix[i]);
            i++;
        }
        // if closing bracket encounted then keep popping from stack until 
        // closing a pair opening bracket is not encountered
        else if(infix[i]==')')
        {
            while(s.top()!='('){
                postfix += s.top();
                s.pop();
            }
            s.pop();
            i++;
        }
        else            
        {
            while (!s.empty() && priority(infix[i]) <= priority(s.top())){
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);
            i++;
        }
    }
    while(!s.empty()){
        postfix += s.top();
        s.pop();
    }
    return postfix;
}


class node{
    public:
        node* left;
        node* right;
        string data;
        node* nxt;

    void set(char val){
        this->data = val;
        this->left = NULL;
        this->right = NULL;
    }     

};


class stackk:public node{
    public:
        node* head = NULL;

    void push(node *n){

        if(head == NULL){
            head = n;
        }
        else{
            n->nxt = head;
            head = n;
        }
    }

    node* pop(){

        node* last = head;
        head = head->nxt;
        return last;

    }
};


void inorder(node* exp){
    if(exp == NULL){
        return ;
    }
    else
    {
        inorder(exp->left);
        cout<< exp->data<<" ";
        inorder(exp->right);
    }

}


void preorder(node* exp){
    if(exp == NULL){
        return ;
    }
    else
    {        
        cout<< exp->data<<" ";
        preorder(exp->left);
        preorder(exp->right);
    }

} 

void postorder(node* exp){
    if(exp == NULL){
        return ;
    }
    else
    {        
        postorder(exp->left);
        postorder(exp->right);
        cout<< exp->data<<" ";

    }

} 



int main()
{
    string infix = "a+b*c-d"; 
    string postfix;
    postfix = convert(infix);
    stackk s;
    node* x ;
    node* y;
    node* z ;

    for(int i = 0; i < postfix.length() ; i++){
        if(isoperator(postfix[i]) == 0){
            z = new node();
            z->set(postfix[i]);
            s.push(z);

        }
        
        else{
            z = new node();
            z->data = postfix[i];
            x = s.pop();
            y = s.pop();
            z->left = y;
            z->right = x;
            s.push(z);   
        }
    }

    inorder(z);
    cout<<endl;
    preorder(z);
    cout<<endl;
    postorder(z);



    return 0;
}