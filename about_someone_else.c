#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char denumire[21], culoare[21];
    int marime;
    struct node *next;
}node;

typedef struct hashmap{
    int capacity;
    int dimension;
    float load;
    int coliziuni;
    node **articol;
}hashmap;

int hashing(char *denumire, char *culoare, int marime, int size){
    int suma = marime;
    for(int i = 0; denumire[i]; i++)
        suma += denumire[i];
    for(int i = 0; culoare[i]; i++)
        suma += culoare[i];
    return suma%size;
}

void initializeaza_hashmap(hashmap *stoc, int m){
    stoc -> capacity = m;
    stoc -> dimension = 0;
    stoc -> load = 0;
    stoc -> coliziuni = 0;
    stoc -> articol = calloc(m, sizeof(node*));
}

node *creare_nod(char *denumire, int marime, char *culoare){
    node *new_node = malloc(sizeof(node));
    strcpy(new_node -> denumire, denumire);
    new_node -> marime = marime;
    strcpy(new_node -> culoare, culoare);
    new_node -> next = NULL;
    return new_node;
}

node *adauga_nod(node *head, char *denumire, int marime, char *culoare){
    node *new_node = creare_nod(denumire, marime, culoare);
    if(head == NULL)
        return new_node;
    
    node * current = head;
    for(; current->next; current = current -> next);
    current->next = new_node;
    return head;
}

void adauga_articol(hashmap *stoc, char *denumire, int marime, char *culoare, int key){
    stoc->articol[key] = adauga_nod(stoc->articol[key], denumire, marime, culoare);
    stoc->dimension ++;
    stoc->load = stoc->dimension/stoc->capacity * 100;
}

void afisare_articole(node *head){
    for(node *nod = head; nod; nod = nod->next)
        printf("%s %d %s\n", nod->denumire, nod->marime, nod->culoare);
}

void afisare_stoc(hashmap stoc){
    for(int i=0; i<stoc.capacity; i++)
        if(stoc.articol[i]){
            for(node *nod = stoc.articol[i]; nod; nod = nod->next)
                printf("%s %d %s %d\n", nod->denumire, nod->marime, nod->culoare, i);
        }
}
void sterge_hashmap(hashmap *stoc){
    for(int i = 0; i<stoc->capacity; i++)
        free(stoc->articol[i]);
}

hashmap create_hashmap(hashmap stoc, node *articole){
    for(node *nod = articole; nod; nod = nod -> next){
        int key = hashing(nod->denumire, nod->culoare, nod->marime, stoc.capacity);
        if(stoc.articol[key] != NULL)
            stoc.coliziuni = 1;
        adauga_articol(&stoc, nod->denumire, nod->marime, nod->culoare, key);
    }
    return stoc;
}

int main(){
    int m, n;
    hashmap stoc;
    node *articole = NULL;
    
    scanf("%d%d", &m, &n);
    initializeaza_hashmap(&stoc, m);
    
    char temp_denumire[21], temp_culoare[21];
    int temp_marime;
    
    for(int i = 0; i < n; i++){
        scanf("%s%d%s", temp_denumire, &temp_marime, temp_culoare);
        articole = adauga_nod(articole, temp_denumire, temp_marime, temp_culoare);
    }
    
    int test;
    
    scanf("%d", &test);
    
    switch(test){
        case 1:{
            afisare_articole(articole);
            break;
        }
        case 2:{
            stoc = create_hashmap(stoc, articole);
            afisare_stoc(stoc);
            break;
        }
        case 3:{
            hashmap test;
            for(int i = n; ; i++){
                initializeaza_hashmap(&test, i);
                test = create_hashmap(test, articole);
                if(test.coliziuni == 0)
                    break;
                sterge_hashmap(&test);
            }
            printf("%d", test.capacity);
            break;
        }
    }
}
