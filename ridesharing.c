#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    char numar_inmatriculare[8], cnp[14], judet[3];
    float suma, rating;
    int an;
    struct node *next;
}node;

typedef struct hashmap {
    struct node **masina;
    int capacity;
    int dimension;
    int load;
}hashmap;

node *creare_node(char *numar_inmatriculare, char *cnp, float suma, float rating) {
    node *new_node = malloc(sizeof(node));
    strcpy(new_node->numar_inmatriculare, numar_inmatriculare);
    strcpy(new_node->cnp, cnp);
    new_node->suma = suma;
    new_node->rating = rating;
    new_node -> next = NULL;
    new_node->an = (cnp[1]-'0')*10 + (cnp[2]-'0');
    if (new_node->an >= 50)
        new_node->an += 1900;
    else
        new_node->an += 2000;

    new_node->judet[0]=numar_inmatriculare[0];
    if (isalpha(numar_inmatriculare[1])) {
        new_node->judet[1]=numar_inmatriculare[1];
        new_node->judet[2]='\0';
    }
    else {
        new_node->judet[1]='\0';
    }
    return new_node;
}
node *add_node(node *head, char *numar_inmatriculare, char *cnp, float suma, float rating){
    node *new_node = creare_node(numar_inmatriculare, cnp, suma, rating);
    if (head == NULL) {
        return new_node;
    }
    else {
        node *current = head;
        if (head->an > new_node->an) {
            new_node->next = head;
            return new_node;
        }
        while (current->next != NULL && current->an >= new_node->an) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    return head;
}

node *add_node_rating(node *head, char *numar_inmatriculare, char *cnp, float suma, float rating){
    node *new_node = creare_node(numar_inmatriculare, cnp, suma, rating);
    if (head == NULL) {
        return new_node;
    }
    else {
        node *current = head;
        if (head->rating > new_node->rating) {
            new_node->next = head;
            return new_node;
        }
        while (current->next != NULL && current->rating >= new_node->rating) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    return head;
}

int hashing(char *numar_inmatriculare, int size) {
    int suma = numar_inmatriculare[0];
    if (isalpha(numar_inmatriculare[1])) {
        suma += numar_inmatriculare[1];
    }
    return suma%size;
}

hashmap init_hashmap(int size) {
    hashmap map;
    map.masina = calloc((size), sizeof(node));
    map.capacity = size;
    map.dimension = 0;
    map.load = 0;
    return map;
}

hashmap add_masina(hashmap map, char numar_inmatriculare[], char cnp[14], float suma, float rating) {
    int key = hashing(numar_inmatriculare, map.capacity);
    map.masina[key] = add_node(map.masina[key], numar_inmatriculare, cnp, suma, rating);
    map.dimension++;
    map.load = map.dimension/map.capacity * 100;
    //printf("Am adaugat masina %s in bucketul %d\n", numar_inmatriculare, key);
    return map;
}

void afisare_nr_inmatriculare(hashmap map) {
    for (int i = 0; i < map.capacity; i++)
        if (map.masina[i] != NULL) {
            for (node *current = map.masina[i]; current != NULL; current = current->next) {
                printf("%s\n", current->numar_inmatriculare);
            }
        }
}

void afisare_judet(hashmap map, char *judet) {
    int key = hashing(judet, map.capacity);
    if (map.masina[key] != NULL) {
        for (node *current = map.masina[key]; current != NULL; current = current->next) {
            if (strcmp(judet, current->judet) == 0) {
                printf("%s %s %.2f %.2f\n", current->numar_inmatriculare, current->cnp, current->suma, current->rating);
            }
        }
    }
}

void calcul_judet(hashmap map, char *judet) {
    int nr_masini = 0;
    float suma_totala = 0, suma_medie, rating_mediu =0;
    int key = hashing(judet, map.capacity);
    if (map.masina[key] != NULL) {
        for (node *node = map.masina[key]; node != NULL; node = node->next) {
            if (strcmp(judet, node->judet) == 0) {
                suma_totala += node->suma;
                rating_mediu += node->rating;
                nr_masini++;
            }
        }
    }
    suma_medie = suma_totala/nr_masini;
    rating_mediu = rating_mediu/nr_masini;
    printf("%s %d %.2f %.2f %.2f\n", judet, nr_masini, suma_totala, suma_medie, rating_mediu);
}

void afisare_rating_masini(node *head, float rating) {
    for (node *current = head; current != NULL && current->rating <rating; current = current->next) {
        printf("%s %.2f\n", current->numar_inmatriculare, current->rating);
    }
}
int main() {
    int nr_masini, nr_buckets;
    scanf("%d", &nr_masini);
    scanf("%d", &nr_buckets);
    hashmap ridesharing = init_hashmap(nr_buckets);
    node *masini = NULL;

    char temp_inmatriculare[8], temp_cnp[14];
    float temp_suma, temp_rating;
    for (int i = 0; i < nr_masini; i++) {
        scanf("%s%s%f%f", temp_inmatriculare, temp_cnp, &temp_suma, &temp_rating);
        ridesharing = add_masina(ridesharing, temp_inmatriculare, temp_cnp, temp_suma, temp_rating);
        masini = add_node_rating(masini, temp_inmatriculare, temp_cnp, temp_suma, temp_rating);
    }

    int test;
    scanf("%d", &test);
    switch (test) {
        case 1: {
            afisare_nr_inmatriculare(ridesharing);
            break;
        }
        case 2: {
            char *judet[3];
            scanf("%s", judet);
            afisare_judet(ridesharing, judet);
            break;
        }
        case 3: {
            char *judet1[3], judet2[3];
            scanf("%s", judet1);
            scanf("%s", judet2);
            calcul_judet(ridesharing, judet1);
            calcul_judet(ridesharing, judet2);
            break;
        }
        case 4: {
            float rating;
            scanf("%f", &rating);
            afisare_rating_masini(masini, rating);
            // nu stiu daca e ok sa am lista aditionala, daca trebuia folosit doar hashmapul, trebuia bagat un ok in structura care sa zica daca am afisat sau nu un indice
            // si sa tot cautam elementul cu cel mai mic rating si sa il afisam, pana ratingul minim gasit era mai mare decat cel specificat la intrare
            break;
        }
    }
}
