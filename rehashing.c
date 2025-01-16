#include <stdio.h>
#include <stdlib.h>

typedef struct bucket{
    int value;
} bucket;

typedef struct hashmap{
    int capacity;
    int dimension;
    float load;
    bucket **entries;
}hashmap;

bucket *create_bucket(int value){
    bucket *new_bucket = malloc(sizeof(bucket));
    new_bucket -> value = value;
    return new_bucket;
}

hashmap init_hashmap(hashmap map, int size){
    map.capacity = size;
    map.dimension = 0;
    map.load = 0;
    map.entries = calloc(size, sizeof(bucket*));
    return map;
}

hashmap destroy_hashmap(hashmap map){
    for(int i = 0; i < map.capacity; i++)
        free(map.entries[i]);
    free(map.entries);
    return map;
}

void display(hashmap map){
    for(int i = 0; i<map.capacity; i++)
        if(map.entries[i])
            printf("%d: %d\n", i, map.entries[i]->value);
        else
            printf("%d: \n", i);
}

hashmap add_entrie(hashmap map, int value){
    //printf("Vreau sa adaug %d\n", value);
    int key;
    if(value < 0)
        key = map.capacity - abs(value) % map.capacity;
    else
        key = value % map.capacity;
    
    while(map.entries[key] != NULL){
        key = (key+1) % map.capacity;
    }
    
    map.entries[key] = create_bucket(value);
    
    map.dimension ++;
    map.load = 1.0 * map.dimension / map.capacity;
    
    return map;
}

hashmap rehashing(hashmap map){
    hashmap new_map;
    new_map = init_hashmap(new_map, map.capacity * 2);
    
    for(int i = 0; i < map.capacity; i++){
        if(map.entries[i] != NULL)
            add_entrie(new_map, map.entries[i]->value);
    }
    
    new_map.dimension = map.dimension;
    
    map = destroy_hashmap(map);
    return new_map;
}

int main(){
    int command, value;
    scanf("%d", &command);
    hashmap map;
    map = init_hashmap(map, 2);
    
    do{
        switch(command){
            case 1:{ // introduce element
                scanf("%d", &value);
                if(map.load >= 0.75){
                    map = rehashing(map);
                    printf("rehashing\n");
                }
                
                map = add_entrie(map, value);
                break;
            }
            case 2:{ // afisare elemente
                display(map);
                break;
            }
            default:{
                exit(0);
            }
        }
        scanf("%d", &command);
    }while(command != 3);
}
