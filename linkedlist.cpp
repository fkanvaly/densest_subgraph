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
};

// Function to insert at the end
void insertEnd(node_t** start, int value)
{
	// If the list is empty, create a single node
	// circular and doubly list
	if (*start == NULL)
	{
		node_t* new_node = new node_t;
		new_node->data = value;
		new_node->next = new_node->prev = new_node;
		*start = new_node;
		return;
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
}

// Function to insert node_t at the beginning
// of the List,
void insertBegin(node_t** start, int value)
{
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
}

// Function to insert node with value as value1.
// The new node is inserted after the node with
// with value2
void insertAfter(node_t** start, int value1,
									int value2)
{
	node_t* new_node = new node_t;
	new_node->data = value1; // Inserting the data

	// Find node having value2 and next node of it
	node_t *temp = *start;
	while (temp->data != value2)
		temp = temp->next;
	node_t *next = temp->next;

	// insert new_node between temp and next.
	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = next;
	next->prev = new_node;
}


void display(node_t* start)

	/* Start with the empty list */
	node_t* start = NULL;

	// Insert 5. So linked list becomes 5->NULL
	insertEnd(&start, 5);

	// Insert 4 at the beginning. So linked 
	// list becomes 4->5
	insertBegin(&start, 4);

	// Insert 7 at the end. So linked list
	// becomes 4->5->7
	insertEnd(&start, 7);

	// Insert 8 at the end. So linked list 
	// becomes 4->5->7->8
	insertEnd(&start, 8);

	// Insert 6, after 5. So linked list 
	// becomes 4->5->6->7->8
	insertAfter(&start, 6, 5);

	printf("Created circular doubly linked list is: ");
	display(start);

	return 0;
}
