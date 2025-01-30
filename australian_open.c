#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char nume[31];
    struct node *left, *right, *parrent;
}node;

node *create_node(char *nume){
    node *new_node = malloc(sizeof(node));
    strcpy(new_node -> nume, nume);
    new_node -> left = new_node -> right = new_node -> parrent = NULL;
    return new_node;
}

node *merge_jucatori(node **jucatori, int n){
    
    for(int i = 0, j = n; j<2*n-1; i+=2, j++){
        jucatori[j] = create_node("");
        jucatori[j] -> left = jucatori[i];
        jucatori[j] -> right = jucatori[i + 1];
        jucatori[i] -> parrent = jucatori[j];
        jucatori[i+1] -> parrent = jucatori[j];
    }
    
    return jucatori[2*n-2];
}

void display_jucatori(node **jucatori, int n){
    for(int i = 0; i<n; i+=2){
        printf("%s\n%s\n\n", jucatori[i]->nume, jucatori[i+1] -> nume);
    }
}

void display_bracket(node *bracket){
    if(bracket->left->left->left){
        display_bracket(bracket->left);
        display_bracket(bracket->right);
    }
    else if(bracket->left->left){
        printf("%s\n%s\n\n", bracket -> left -> nume, bracket -> right -> nume);
    }
}

node *get_jucator(node **jucatori, char *nume, int n){
    for(int i = 0; i < n; i++)
        if(strcmp(jucatori[i] -> nume, nume) == 0)
            return jucatori[i];
}

int runda_directa(node **jucatori, char *nume1, char *nume2, int n){
    node *jucator1 = get_jucator(jucatori, nume1, n);
    node *jucator2 = get_jucator(jucatori, nume2, n);
    int runda = 0;
    while(jucator1 != jucator2){
        jucator1 = jucator1 -> parrent;
        jucator2 = jucator2 -> parrent;
        runda++;
    }
    
    return runda;
}

void citire(int *vec, int n){
      for(int i = 0; i<n; i++){
        scanf("%d", &vec[i]);
    }  
}

int game(){
    int p, jucator1 = 0, jucator2 = 0;
    scanf("%d", &p);
    
    int set1[p], set2[p];
    
    citire(set1, p);
    citire(set2, p);
    
    for(int i = 0; i<p; i++){
        if(set1[i] == 6)
            jucator1 ++;
        else
            jucator2 ++;
    }
    
    if(jucator1 == 3)
        return 1;
    return 2;
}

void simulare_joc(node **jucator, int n){
    for(int i = 0; i<n; i+=2){
        
        switch(game()){
            case 1:{
                strcpy(jucator[i]->parrent->nume, jucator[i] -> nume);
                break;
            }
            case 2:{
                strcpy(jucator[i]->parrent->nume, jucator[i+1] -> nume);
                break;
            }
        }
    }
}


int suma(int *v1, int *v2, int p){
    int suma = 0;
    
    for(int i = 0; i<p; i++)
        suma += v1[i] + v2[i];
    
    return suma;
}

int cel_mai_lung_meci(node **jucatori, int n){
    int game_max = 0, p;
    node *meci = NULL;
    
    for(int i = 0; i<n; i+=2){
        scanf("%d", &p);
        int vec1[p], vec2[p];
        citire(vec1, p);
        citire(vec2, p);
        
        int gameuri = suma(vec1, vec2, p);
        
        if(gameuri > game_max){
            game_max = gameuri;
            meci = jucatori[i]->parrent;
        }
    }
    
    printf("%s\n%s\n", meci->left->nume, meci->right->nume);
    
}

void simulare_campionat(node **jucator, int n){
    
    for(int i = 0, j = n; j<2*n-1; i+=2, j++){
        switch(game()){
            case 1:{
                strcpy(jucator[j]->nume, jucator[i] -> nume);
                break;
            }
            case 2:{
                strcpy(jucator[j]->nume, jucator[i+1] -> nume);
                break;
            }
        }
    }
}

int main(){
    int n, test;
    char temp_nume1[31], temp_nume2[31];
    
    scanf("%d", &n);
    
    node **jucatori = calloc(2*n, sizeof(node));
    
    for(int i = 0; i < n; i++){
        scanf("%s", temp_nume1);
        jucatori[i] = create_node(temp_nume1);
    }
    
    node *bracket = merge_jucatori(jucatori, n);
    
    scanf("%d", &test);
    
    switch(test){
        case 1:{
            display_jucatori(jucatori, n);
            break;
        }
        case 2:{
            scanf("%s%s", temp_nume1, temp_nume2);
            printf("%d", runda_directa(jucatori, temp_nume1, temp_nume2, n));
            break;
        }
        case 3:{
            simulare_joc(jucatori, n);
            display_bracket(bracket);
            break;
        }
        case 4:{
            cel_mai_lung_meci(jucatori, n);
            break;
        }
        case 5:{
            simulare_campionat(jucatori, n);
            printf("%s\n", bracket->nume);
            break;
        }
    }
}
