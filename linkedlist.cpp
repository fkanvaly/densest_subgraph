#include <stdio.h> 
#include <stdlib.h> 
#include <unordered_map> 
#include <iostream>

using namespace std;

// A linked list node 
template <typename T>
struct Node { 
    T data; 
    Node<T>* next; 
    Node<T>* prev; 
};



template <typename T>
struct Linkedlist{
    /* Given a reference (pointer to pointer) to the head of a list 
    and an int, inserts a new node on the front of the list. */
    static void push_ll(Node<T>** head_ref, T new_data) 
    { 
        Node<T>* new_node = (Node<T>*)malloc(sizeof(Node<T>)); 
    
        new_node->data = new_data; 
    
        new_node->next = (*head_ref); 
        new_node->prev = NULL; 
    
        if ((*head_ref) != NULL) 
            (*head_ref)->prev = new_node; 
    
        (*head_ref) = new_node; 

        track[new_data.id]= &new_node;
    } 

    static Node<int>* push_node(Node<T>** head_ref, T new_data) 
    {
        Node<T>* new_node = (Node<T>*)malloc(sizeof(Node<T>)); 
    
        new_node->data = new_data; 
    
        new_node->next = (*head_ref); 
        new_node->prev = NULL; 
    
        if ((*head_ref) != NULL) 
            (*head_ref)->prev = new_node; 
    
        (*head_ref) = new_node; 

        return new_node;
    } 

    static void push_node(Node<T>** head_ref, Node<T>* new_node) 
    {
        new_node->next = (*head_ref); 
        new_node->prev = NULL; 
    
        if ((*head_ref) != NULL) 
            (*head_ref)->prev = new_node; 
    
        (*head_ref) = new_node; 
    } 
    
    /* Given a node as next_node, insert a new node before the given node */
    static void insertBefore(Node<T>** head_ref, Node<T>* next_node, T new_data) 
    { 
        /*1. check if the given next_node is NULL */
        if (next_node == NULL) { 
            printf("the given next node cannot be NULL"); 
            return; 
        } 

        /* 2. allocate new node */
        Node<T>* new_node = (Node<T>*)malloc(sizeof(struct Node<T>)); 
    
        /* 3. put in the data */
        new_node->data = new_data; 
    
        /* 4. Make prev of new node as prev of next_node */
        new_node->prev = next_node->prev; 
    
        /* 5. Make the prev of next_node as new_node */
        next_node->prev = new_node; 
    
        /* 6. Make next_node as next of new_node */
        new_node->next = next_node; 
    
        /* 7. Change next of new_node's previous node */
        if (new_node->prev != NULL) 
            new_node->prev->next = new_node; 
        /* 8. If the prev of new_node is NULL, it will be
        the new head node */
        else
            (*head_ref) = new_node;
        
        track[new_data.id]= &new_node;
    } 
 
    // This function prints contents of linked list starting from the given node 
    static void printList(Node<T>* node) 
    { 
        struct Node<T>* last; 
        printf("\nTraversal in forward direction \n"); 
        while (node != NULL) { 
            printf("%d ", node->data); 
            last = node; 
            node = node->next; 
        } 
    } 

    /* Function to delete a node in a Doubly Linked List. 
    head_ref --> pointer to head node pointer. 
    del --> pointer to node to be deleted. */
    static void deleteNode(Node<T>** head_ref, Node<T>* del) 
    { 
        /* base case */
        if (*head_ref == NULL || del == NULL) 
            return; 
    
        /* If node to be deleted is head node */
        if (*head_ref == del) 
            *head_ref = del->next; 
    
        /* Change next only if node to be 
        deleted is NOT the last node */
        if (del->next != NULL) 
            del->next->prev = del->prev; 
    
        /* Change prev only if node to be 
        deleted is NOT the first node */
        if (del->prev != NULL) 
            del->prev->next = del->next; 
    
        /* Finally, free the memory occupied by del*/
        free(del); 
        return; 
    } 

    /* Function to delete a node in a Doubly Linked List. 
    head_ref --> pointer to head node pointer. 
    del --> pointer to node to be deleted. */
    static void detachNode(Node<T>** head_ref, Node<T>* del) 
    { 
        /* base case */
        if (*head_ref == NULL || del == NULL) 
            return; 
    
        /* If node to be deleted is head node */
        if (*head_ref == del) 
            *head_ref = del->next; 
    
        /* Change next only if node to be 
        deleted is NOT the last node */
        if (del->next != NULL) 
            del->next->prev = del->prev; 
    
        /* Change prev only if node to be 
        deleted is NOT the first node */
        if (del->prev != NULL) 
            del->prev->next = del->next; 
    
        /* Finally, free the memory occupied by del*/
        del->next = NULL; 
        del->prev = NULL; 
        return; 
    } 
}; 

typedef unordered_map<int, bool> map;

struct Degree_tracker
{
    Node< map* >** degree_head; // pointer to head node pointer. 
    unordered_map<int, Node< map* >** > track;
    
    Degree_tracker(){
        Node<int_node>* deg_init_head = NULL;
        unordered_map<int, bool>* degree_0 = new unordered_map<int, bool>();
        Linkedlist<int_node>::push_ll(&deg_init_head, degree_0);
        degree_head = &deg_init_head;
    }

    Node<int>* new_node (int node_id){
        return Linkedlist<int>::push_node((*track[0])->data.node_ref, node_id);
    }

    // void increase(Node<int>* node, int d){
    //     Linkedlist<int>::detachNode(&((*track[d])->data.node_ref), node);
        
    //     if (track.find(d+1)!=track.end()){
    //         Linkedlist<int>::push_node(&((*track[d+1])->data.node_ref), node);
    //     }else{
    //         Node<int>* head = NULL;
            
    //         if (*track[d] == *degree_head){ 
    //             Linkedlist<int_node>::push_ll(degree_head, int_node(d+1, head));
    //             Linkedlist<int>::push_node(&((*track[d+1])->data.node_ref), node); 
    //             printf("\nhead");
    //         }else{
    //             Linkedlist<int_node>::insertBefore(degree_head, *track[d], int_node(d+1, head));
    //             printf("not head");
    //             cout<<""<<endl;
    //             // printf("increase : %d", track[d+1]->data.id);

    //         }
    //     }

    //     if((*track[d])->data.node_ref == NULL){
    //         Linkedlist<int_node>::deleteNode(degree_head, (*track[d]));
    //         track.erase(d);
    //     }
         
    // }
};

void print_map(Node<int_node>* degree_head){

}


/* Driver program to test above functions*/
int main() 
{ 
    Degree_tracker deg_tracker = Degree_tracker();
    Node<int>* n1 = deg_tracker.new_node(1);
    // Node<int>* n2 = deg_tracker.new_node(2);
    // Node<int>* n3 = deg_tracker.new_node(4);

    // deg_tracker.increase(n2, 0);
    // deg_tracker.increase(n2, 1);
    // deg_tracker.increase(n1, 0);

    // cout<<&n1<<endl;
    // cout<<*((*track[0])->data.node_ref)<<endl;
    Linkedlist<int>::printList(n1);
    // Linkedlist<int>::printList(n1);
    // Linkedlist<int>::printList((*track[0])->data.node_ref);
    // Linkedlist<int>::printList(deg_tracker.track[1]->data.node_ref);
    // Linkedlist<int>::printList(deg_tracker.track[2]->data.node_ref);
}