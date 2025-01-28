#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char nume[20];
    int distanta;
    struct node *left, *right;
}NOD;


NOD *new_node(char *temp_nume, int temp_distanta){
    NOD *new_node = malloc(sizeof(NOD));
    strcpy(new_node -> nume, temp_nume);
    new_node -> distanta = temp_distanta;
    new_node -> left = NULL;
    new_node -> right = NULL;
    return new_node;
}

NOD *add_node(NOD *root, char *temp_nume, int temp_distanta){
    if(root == NULL)
        return new_node(temp_nume, temp_distanta);
    if(strcmp(temp_nume, root->nume) < 0)
        root -> left = add_node (root -> left, temp_nume, temp_distanta);
    else
        root -> right = add_node (root -> right, temp_nume, temp_distanta);
    return root;
}

NOD *get_node(NOD *root, char *temp_nume){
    if(root){
        if(strcmp(temp_nume, root -> nume) == 0)
            return root;
        else if(strcmp(temp_nume, root -> nume) < 0 )
            root -> left = get_node(root -> left, temp_nume);
        else
            root -> right = get_node ( root -> right, temp_nume);
    }
}

int numar_orase(NOD *root){
    if(root == NULL)
        return 0;
    return 1 + numar_orase(root->left) + numar_orase(root->right);
}


NOD *get_ancestor_comun(NOD *root, char *oras1, char *oras2){
    NOD *ancestor_comun, *nod1, *nod2;
    nod1 = nod2 = ancestor_comun = root;
    
    int cmp1 = strcmp(root->nume, oras1), cmp2 = strcmp(root->nume, oras2);
    
    while(cmp1 && cmp2){ //cat timp nu am ajuns in unul dintre orasele cautate
        if(cmp1 > 0 ) // vedem in ce directie trebuie sa o luam ca sa ajungem la orasul 1
            nod1 = nod1 -> left;
        else
            nod1 = nod1 -> right;
        
        if(cmp2 > 0 ) // vedem in ce directie trebuie sa o luam ca sa ajungem la orasul 2
            nod2 = nod2 -> left;
        else
            nod2 = nod2 -> right;
        
        cmp1 = strcmp(nod1->nume, oras1); // compara numele oraselor
        cmp2 = strcmp(nod2->nume, oras2);
        
         
        if(nod1 == nod2) // verificam daca drumul coincide si ne aflam in acelasi oras, asta inseamna ca nodul curent este o radacina comuna
            ancestor_comun = nod1; // ultimul nod salvat in ancestor_comun o sa fie cel mai apropiat ancestor comun al celor doua orase (ultimul punct de intersectie al drumurilor)
       
        // dupa ce drumurile catre orase se despart, nu va mai exista niciun nod comun, deci putem opri fortat cautarea
        else 
            break;
    }
    
    return ancestor_comun;
}

int calcul_distanta(NOD *root, char *oras1){
    int distanta = 0;
    NOD *current = root;
    
    while(strcmp(current -> nume, oras1)){
        if(strcmp(current -> nume, oras1) < 0) // verificam in ce directie trebuie sa mergem ca sa ajungem la oras
            current = current -> right;
        else
            current = current -> left;
        
        distanta += current -> distanta;
    }
    
    return distanta;
}

int main(){
    int n, temp_distanta, comanda;
    char temp_nume[20], oras1[20], oras2[20];
    NOD *root = NULL;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i ++){
        scanf("%s%d", temp_nume, &temp_distanta);
        root = add_node(root, temp_nume, temp_distanta);
    }
    
    scanf("%d", &comanda);
    
    switch(comanda){
        case 1:{
            scanf("%s", temp_nume);
            printf("%d", numar_orase(get_node(root, temp_nume)) - 1);
            break;
        }
        case 2:{
            scanf("%s%s", oras1, oras2);
            NOD *parinte_comun = get_ancestor_comun(root, oras1, oras2);
            
            int distanta_orase = calcul_distanta(parinte_comun, oras1) + calcul_distanta(parinte_comun, oras2);
            
            printf("%d", distanta_orase);
            break;
        }
    }
}
