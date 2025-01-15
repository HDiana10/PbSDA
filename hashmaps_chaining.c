#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
}node;

typedef struct hashmap{
    int capacity;
    int dimension;
    node **bucket;
}hashmap;

void initializare_hashmap(hashmap *map, int m){
    map->capacity = m;
    map->dimension = 0;
    map->bucket = calloc(m,sizeof(node*));
}

int hashing(int n, int m){
    if(n<0)
        return m-abs(n)%m;
    return n%m;
}

node *create_node(int value){
    node *new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void add_element(hashmap *map, int value, int key){
    node *new_element = create_node(value);
    if(map->bucket[key] == NULL){
        map->bucket[key] = new_element;    
    }
    else{
        node *current = map->bucket[key];
        while(current->next !=NULL)
            current = current->next;
        current->next = new_element;
    }
    map->dimension++;
}


void afisare_bucket(node *head){
    for(node *nod = head; nod; nod = nod->next)
        printf("%d ", nod->value);
    printf("\n");
}

void afisare(hashmap map){
    for(int i=0; i<map.capacity; i++){
        if(map.bucket[i] == NULL)
            printf("%d: \n", i);
        else{
            printf("%d: ", i);    
            afisare_bucket(map.bucket[i]);
        }
    }
}
int main(){
    int n, m, value;
    hashmap map;
    scanf("%d%d", &m, &n);
    
    initializare_hashmap(&map, m);
    
    for(int i=0; i<n; i++){
        scanf("%d", &value);
        int key = hashing(n, m);
        add_element(&map, n, key);
    }
    
    afisare(map);
}
