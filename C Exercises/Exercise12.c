#include <stdio.h>
#include <stdlib.h>

// tougher part involves actually sorting all of this stuff, since it is SLL
// pretty close to fixing the deleteDupes right [DONE]
// now just need to sort, prolly using a quick sort import that i'll do tomorrow []

struct node {
    int value;
    struct node* next;
};

struct node* deleteDupes(struct node* head){

    // check that the sll is not empty
    struct node* temp = head;

    if (head == NULL){
        return NULL;
    }

    while (temp != NULL){
        
        // get the integer that needs to be removed from the rest of the list (we can assume the prior nodes have no dupes)
        struct node* current = temp->next;
        struct node* previous = temp;
        int toBeRemoved = temp->value;

        while (current != NULL){
            
            // if that node is a duplicate
            if (current->value == toBeRemoved){
                // make a pointer to free this patch of dataprintf("CurrentNode: %d\n", current->value);
                struct node* toBeFreed = current; 
                // link to the node that comes after
                previous->next = current->next;
                // free the data 
                free(toBeFreed);
                // cycle through to the new "next" node
                current = previous->next;
            }

            // otherwise cycle though
            else {
                previous = previous->next;
                current = current->next;
            }
        }

        // continue to cycle through the nodes
        temp = temp->next;
    }

}

struct node* deleteDuplicates(struct node* head) {

    deleteDupes(head);
    
    return head;
}

void addNode(struct node* head, int data){

    struct node* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    } 

    temp->next = (struct node*) malloc(sizeof(struct node));
    temp->next->value = data;

    return;
}

int main(){

    struct node* testNode = (struct node*) malloc(sizeof(struct node));
    testNode->value = 1;

    addNode(testNode, 1);
    addNode(testNode, 1);
    addNode(testNode, 3);
    addNode(testNode, 3);
    addNode(testNode, 2);

    struct node* temp = testNode;
    while (temp != NULL){
        printf("%d\n", temp->value);
        temp = temp->next;
    }
    printf("end\n");

    testNode = deleteDuplicates(testNode);
    
    struct node* temp2 = testNode;
    while (temp2 != NULL){
        printf("%d\n", temp2->value);
        temp2 = temp2->next;
    }

    return 0;
}