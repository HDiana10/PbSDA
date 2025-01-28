#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int value;
    struct node *left, *right;
} NOD;

NOD *create_node(int value){
    NOD *new_node = malloc(sizeof(NOD));
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> value = value;
    return new_node;
}

NOD *adauga_nod(NOD *root, int value){
    if(root == NULL)
        return create_node(value);
    if(value < root -> value)
        root -> left = adauga_nod(root->left, value);
    else
        root -> right = adauga_nod(root -> right, value);
    return root;
}

void afisare_inordine_reversed(NOD *root, int val){
    if(root){
        afisare_inordine_reversed(root->right, val);
        if(val <= root->value){
            printf("%d ", root->value);
            afisare_inordine_reversed(root->left, val);
        }
        
    }    
}

int main(){
    int value;
    char s[10];
    NOD *root = NULL;
    
    scanf("%s", s);
    while(strcmp(s, "stop")!=0){
        value = strtol(s, NULL, 10);
        root = adauga_nod(root, value);
        scanf("%s", s);
    }

    int Vt;
    scanf("%d", &Vt);
    
    afisare_inordine_reversed(root, Vt);
}
