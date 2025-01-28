#include <stdio.h>
#include <stdlib.h>

typedef struct nod{
    int value;
    struct nod *left, *right;
}NOD;


NOD *create_node(int value){
    NOD *new_node = malloc(sizeof(NOD));
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> value = value;
    return new_node;
}

NOD *add_node(NOD *root, int value){
    if(root == NULL)
        return create_node(value);
    
    if(value < root->value)
        root->left = add_node(root->left, value);
    else
        root->right = add_node(root -> right, value);
    
    return root;
}

void display_inordine(NOD *root){
    if(root){
        display_inordine(root->left);
        printf("%d " ,root->value);
        display_inordine(root->right);
    }
}

void display_inordine_reversed(NOD *root){
    if(root){
        display_inordine_reversed(root->right);
        printf("%d " ,root->value);
        display_inordine_reversed(root->left);
    }
}

int main(){
    int x;
    NOD *root_even = NULL, *root_odd = NULL;
    while((scanf("%d", &x)) != EOF){
        if(x%2)
            root_odd = add_node(root_odd, x);
        else
            root_even = add_node(root_even, x);
    }
    
    display_inordine(root_even);
    display_inordine_reversed(root_odd);
}
