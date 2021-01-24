// C++ program to illustrate inserting a node_t in
// a Cicular Doubly Linked list in begging, end
// and middle
#include <iostream>
using namespace std;

// Structure of a node_t
struct node_t
{
	int data;
	node_t *next;
	node_t *prev;
	node_t():next(NULL), prev(NULL){}
};

// Function to insert at the end
node_t* insertEnd(node_t** start, int value)
{
	// If the list is empty, create a single node
	// circular and doubly list
	if (*start == NULL)
	{
		node_t* new_node = new node_t;
		new_node->data = value;
		new_node->next = new_node->prev = new_node;
		*start = new_node;
		return new_node;
	}

	// If list is not empty

	/* Find last node */
	node_t *last = (*start)->prev;

	// Create node_t dynamically
	node_t* new_node = new node_t;
	new_node->data = value;

	// Start is going to be next of new_node
	new_node->next = *start;

	// Make new node previous of start
	(*start)->prev = new_node;

	// Make last preivous of new node
	new_node->prev = last;

	// Make new node next of old last
	last->next = new_node;

    return new_node;
}

// Function to insert node_t at the beginning
// of the List,
node_t* insertBegin(node_t** start, int value)
{
	// If the list is empty, create a single node
	// circular and doubly list
	if (*start == NULL)
	{
		node_t* new_node = new node_t;
		new_node->data = value;
		new_node->next = new_node->prev = new_node;
		*start = new_node;
		return new_node;
	}

	// Pointer points to last node_t
	node_t *last = (*start)->prev;

	node_t* new_node = new node_t;
	new_node->data = value; // Inserting the data

	// setting up previous and next of new node
	new_node->next = *start;
	new_node->prev = last;

	// Update next and previous pointers of start
	// and last.
	last->next = (*start)->prev = new_node;

	// Update start pointer
	*start = new_node;
    return new_node;
}

// Function to insert node with value as value1.
// The new node is inserted after the node with
// with value2
node_t* insertAfter(node_t** start, int value1,
									node_t* temp)
{
	node_t* new_node = new node_t;
	new_node->data = value1; // Inserting the data

	// Find node having value2 and next node of it
	node_t *next = temp->next;

	// insert new_node between temp and next.
	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = next;
	next->prev = new_node;
    return new_node;
}

void deletenode(node_t** start, node_t* curr) 
{ 
    // If list is empty 
    if (*start == NULL) 
        return; 

	assert(curr != NULL);
    // Find the required node 
    // Declare two pointers and initialize them 
    node_t *prev_1 = curr->prev; 
  
    // Check if node is the only node in list 
    if (curr == *start && curr->next == *start && prev_1 == *start) { 
		// printf("%p, %p\n",curr->next, *start);
		// printf("here wrong\n");
        (*start) = NULL; 
        free(curr); 
        return; 
    } 

    // If list has more than one node, 
    // check if it is the first node 
    if (curr == *start) { 
		// printf("it is the first node\n");

        // Move prev_1 to last node 
        prev_1 = (*start)->prev; 
  
        // Move start ahead 
        *start = (*start)->next; 
  
        // Adjust the pointers of prev_1 and start node 
        prev_1->next = *start; 
        (*start)->prev = prev_1; 
        free(curr); 
    } 
  
    // check if it is the last node 
    else if (curr->next == *start) { 
		// printf("it is the last node \n");
        // Adjust the pointers of prev_1 and start node 
        prev_1->next = *start; 
        (*start)->prev = prev_1; 
        free(curr); 
    } 
    else { 
		// printf("middle node \n");
        // create new pointer, points to next of curr node 
        node_t* temp = curr->next; 
  
        // Adjust the pointers of prev_1 and temp node 
        prev_1->next = temp; 
        temp->prev = prev_1; 
        free(curr); 
    } 
} 


void display(node_t* start)
{
	if(start==NULL){
		printf("\nempty list\n");
		return;
	}
	node_t *temp = start;

	// printf("Traversal in forward direction \n");
	while (temp->next != start)
	{
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("%d \n", temp->data);
}


// node_t* copy_linkedlist(node_t** head){
// 	if(*head==NULL){
// 		return NULL;
// 	}
	
// 	node_t* new_start = NULL;
// 	node_t* iter = *head;
// 	while (iter->next != *head)
// 	{
// 		insertEnd(&new_start, iter->data);
// 		iter = iter->next;
// 	}
// 	insertEnd(&new_start, iter->data);
// 	printf("copied ll: start:%i\n",new_start->data);
// 	display(new_start);
// 	return new_start;
// }

/* Driver program to test above functions*/
int main_()
{
	/* Start with the empty list */
	node_t* start = NULL;

	// Insert 5. So linked list becomes 5->NULL
	node_t* deg0 = insertEnd(&start, 0);

	// // Insert 4 at the beginning. So linked 
	// // list becomes 4->5
	node_t* deg1 = insertEnd(&start, 1);
	node_t* deg2 = insertEnd(&start, 2);
	display(start);
	printf("test : \n%p\n%p\n\n%p\n%p\n", deg1, start, deg0->next, deg0->prev);
	// // Insert 7 at the end. So linked list
	// // becomes 4->5->7
	// node_t* deg2 = insertEnd(&start, 2);

	// // Insert 8 at the end. So linked list 
	// // becomes 4->5->7->8
	// node_t* deg4 = insertEnd(&start, 4);

	// node_t* deg3 = insertAfter(&start, 3, deg4->prev);
	display(start);
    deletenode(&start, deg0);
	display(start);

	return 0;
}