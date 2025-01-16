#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    char cnp[14], nume[21];
    int an_nastere;
    struct node *next;
}node;

typedef struct list {
    int capacity;
    int dimension;
    float load;
    node **person;
}hashmap;

int get_an(char *cnp) {
    int an = (cnp[1]-'0')*10 + (cnp[2]-'0');
    if (an < 50)
        return 2000 + an;
    return 1900 + an;
}

/// functii node

node *create_node(char *cnp, char *nume) {
    node *new_node = malloc(sizeof(node));
    strcpy(new_node->cnp, cnp);
    strcpy(new_node->nume, nume);
    new_node->next = NULL;
    new_node->an_nastere = get_an(cnp);
    return new_node;
}
node *add_node(node *head, char *cnp, char *nume) {
    node *new_node = create_node(cnp, nume);
    if (head == NULL) {
        head = new_node;
    }
    else {
        node *current_node = head;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
    return head;
}

void display_list(node *head) {
    for (node *current_node = head; current_node != NULL; current_node = current_node->next) {
        printf("%s %s\n", current_node->nume, current_node->cnp);
    }
}

node *add_node_priority(node *head, char *cnp, char *nume) {
    node *new_node = create_node(cnp, nume);
    if (head == NULL) {
        head = new_node;
    }
    else if (head->an_nastere > new_node->an_nastere) {
        new_node->next = head;
        head = new_node;
    }
    else{
        node *current_node = head;
        while (current_node->next != NULL && current_node->next->an_nastere <= new_node->an_nastere) {
            current_node = current_node->next;
        }
        new_node->next = current_node->next;
        current_node->next = new_node;
    }
    return head;
}

/// functii hashmap

int hashing(char *cnp, int an, int size) {
    int numar = 0;
    for (int i = 7; i<13; i++) {
        numar = numar*10 + (cnp[i] - '0');
    }
    numar *= (an%100);
    return numar % size;
}

hashmap init_hashmap(hashmap map, int capacity) {
    map.capacity = capacity;
    map.dimension = 0;
    map.load = 0;
    map.person = calloc(map.capacity, sizeof(node *));
    return map;
}

void display_hashing(node *list, int size) {
    for (node *current_node = list; current_node != NULL; current_node = current_node->next) {
        printf("%d\n", hashing(current_node->cnp, current_node->an_nastere, size));
    }
}

hashmap create_hashmap(hashmap map, node *list) {
    for (node *current_node = list; current_node != NULL; current_node = current_node->next) {
        int key = hashing(current_node->cnp, current_node->an_nastere, map.capacity);
        if (map.person[key] == NULL) {
            map.dimension++;
            map.load = 1.0*map.dimension/map.capacity;
        }
        map.person[key] = add_node_priority(map.person[key], current_node->cnp, current_node->nume);
    }
    return map;
}

void display_person(node *head) {
    for (node *current_node = head; current_node != NULL; current_node = current_node->next) {
        printf("%s ", current_node->nume);
    }
}

void display_hashmap(hashmap map) {
    for (int i = 0; i < map.capacity; i++) {
        printf("%d: ", i);
        display_person(map.person[i]);
        printf("\n");
    }
}



int main() {
    int nr_buckets, nr_persons, test;
    char temp_nume[21], temp_cnp[14];
    hashmap map;
    node *list = NULL;
    scanf("%d", &nr_buckets);
    scanf("%d", &nr_persons);

    map = init_hashmap(map, nr_buckets);

    for (int i = 0; i < nr_persons; i++) {
        scanf("%s %s", temp_nume, temp_cnp);
        list = add_node(list, temp_cnp, temp_nume);
    }

    scanf("%d", &test);

    switch (test) {
        case 1: {
            printf("OK\n");
            display_list(list);
            break;
        }
        case 2: {
            display_hashing(list, nr_buckets);
            break;
        }
        case 3: {
            map = create_hashmap(map, list);
            display_hashmap(map);
            break;
        }
        case 4: {
            float limita;
            scanf("%f", &limita);
            hashmap map2;
            for (int i = 1; ; i++) {
                map2 = init_hashmap(map2, i);
                map2 = create_hashmap(map2, list);
                //printf("%d: %.2f\n", i, map2.load);
                if (map2.load < limita)
                    break;
            }
            printf("%d\n", map2.capacity);
            break;
        }
    }
}
