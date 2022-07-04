#include<iostream>
using namespace std;
class Node{
    public:
     string data;
     Node* next;
};
class LinkedList{
 public:
     Node* head = new Node();
     
    static int size;
    void insert(string data)
    {
        Node* temp = new Node();
        temp->data = data;
        temp->next = head->next;
        head->next = temp;
        size++;
    }
    void add(string data)
    {
        size++;
        Node* t,*h;
        t = new Node();
        h = head;
        t->data = data;
        while(h->next!=NULL)
        h=h->next;
        h->next = t; 
    }
    string get(int i)
    {
        Node* temp = head->next;
        for(int j=0;j<i;j++)
         temp=temp->next;
        return temp->data; 
    }
    int exists(string data)
    {
        Node* temp = head->next;
        while(temp!=NULL && temp->data!=data)
        temp=temp->next;
        if(temp==NULL)
         return 0;
        return 1; 
    }
    int getsize()
    {
        return size;
    }
};

int LinkedList::size=0;