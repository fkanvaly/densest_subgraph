#pragma once

template <typename T>
struct LNode
{
    /* data */
    T* node;
    LNode<T>* prev;
    LNode<T>* next;
    
    LNode():node(nullptr), next(nullptr), prev(nullptr){}
    LNode(T* node_):node(node_), next(nullptr), prev(nullptr){} 
};

template <typename T>
struct Linkedlist
{
    /* data */
    LNode<T>* head = nullptr;
    int size;

    Linkedlist(){
        size = 0;
        head=nullptr;
    }

    void push_back(T* node){
        LNode<T>* new_node = new LNode<T>(node);
        node->degree_node = new_node;

        // if empty
        if(head==nullptr){
            head = new_node;
        }

        new_node->next = head;
        head->prev = new_node;

        head = new_node;
        size++;
    }

    void detach_and_push(T* node){
        LNode<T>* new_node = node->degree_node;

        // remove from previous linkedlist 
        if(new_node->prev!=nullptr)
            new_node->prev->next = new_node->next;
        if(new_node->next!=nullptr)
            new_node->next->prev =  new_node->prev;

        new_node->next=nullptr; new_node->prev=nullptr; 

        // add the now to the current linkedlist
        if(head==nullptr){
            head = new_node;
        }

        new_node->next = head;
        head->prev = new_node;

        head = new_node;
        size++;
    }

    static void detach(T* node){
        LNode<T>* degree_node = node->degree_node;

        // remove from previous linkedlist 
        if(degree_node->prev!=nullptr)
            degree_node->prev->next = degree_node->next;
        if(degree_node->next!=nullptr)
            degree_node->next->prev =  degree_node->prev;

        degree_node->next=nullptr; degree_node->prev=nullptr; 
    }

    get_size

    LNode<T>* get_head(){
        return head;
    }
};