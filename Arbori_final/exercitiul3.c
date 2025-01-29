#include <stdio.h>
#include <stdlib.h>

typedef struct NOD{
    int value;
    struct NOD *left, *right;
}NOD; // structura pentru arbore

typedef struct node{ // stiva in care vom salva vectorul de valori
    int value;
    struct node *next;
}node;

node *create_node(int number){
    node *new_node = malloc(sizeof(node));
    new_node -> next = NULL;
    new_node -> value = number;
    return new_node;
}

node *push(node *head, int number){
    node *new_node = create_node(number);
    if(head == NULL)
        return new_node;
    
    node *current = head;
    if(new_node -> value < head -> value){
        new_node -> next = head;
        return new_node;
    }
    
    while(current -> next && new_node -> value > current -> next -> value)
        current = current -> next;
        
    if(current -> next && new_node -> value == current -> next -> value)
        return head;
        
    new_node -> next = current -> next;
    current -> next = new_node;
    return head;
}

node *pop(node *head, int *num){
    node *aux = head;
    *num = head -> value;
    head = head -> next;
    free(aux);
    return head;
}

NOD *create_NOD(int value){
    NOD *new_node = malloc(sizeof(NOD));
    new_node -> left = new_node -> right = NULL;
    new_node -> value = value;
    return new_node;
}

NOD *generate_min_heap(int nr1, int nr2){
    NOD *root = create_NOD(nr1+nr2);
    root -> left = create_NOD(nr1);
    root -> right = create_NOD(nr2);
    return root;
}

void display_preordine(NOD *root){
    if(root){
        printf("%d\n", root -> value);
        display_preordine(root -> left);
        display_preordine(root -> right);
    }
}

int main(){
    int number, nr1, nr2;;
    node *stack = NULL;
    NOD **fathers = calloc(1000, sizeof(NOD*));
    
    while((scanf("%d", &number)) != EOF){
        stack = push(stack, number);
    }
    
    /*
    for(node *current = stack; current; current = current -> next){
        printf("%d ", current -> value);
    }
    */
    
    //printf("\nOK1\n");
    
    while(stack->next){
        stack = pop(stack, &nr1);
        stack = pop(stack, &nr2);
        
        fathers[nr1+nr2] = generate_min_heap(nr1, nr2);
        stack = push(stack, nr1+nr2);
        //printf("Father: %d, left son: %d, right son: %d\n", fathers[nr1+nr2]->value, fathers[nr1+nr2]->left->value, fathers[nr1+nr2]->right->value);
    
        if(fathers[nr1]){
            fathers[nr1+nr2]->left -> left = fathers[nr1] -> left;
            fathers[nr1+nr2]->left -> right = fathers[nr1] -> right;
            //printf("Am lipit %d\n", nr1);
        }
        if(fathers[nr2]){
            fathers[nr1+nr2]->right -> left = fathers[nr2] -> left;
            fathers[nr1+nr2]->right -> right = fathers[nr2] -> right;
            //printf("Am lipit %d\n", nr2);
            
        }
        //printf("\n");
    }
    
    display_preordine(fathers[nr1+nr2]);
}
