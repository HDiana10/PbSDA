#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod{
    int data;
    char c;
    struct nod * left;
    struct nod * right;
    struct nod * next;
}nod;

char cod[256][100];

nod *create_node(char c, int nr){
    nod *new_node = malloc(sizeof(nod));
    new_node -> data = nr;
    new_node -> c = c;
    new_node -> left = new_node -> right = new_node -> next = NULL;
    return new_node;
}

/// adauga un nod in lista sortata
nod *add_node(nod *head, char c, int nr){
    nod *new_node = create_node(c, nr);
    if(head == NULL)
        return new_node;
    
    nod *current = head;
    if(head -> data > nr){
        new_node -> next = head;
        return new_node;
    }
    
    for(; current -> next && (current -> next -> data < nr || (current -> next -> data == nr) && current -> next -> c < c); current = current -> next);
    new_node -> next = current -> next;
    current -> next = new_node;
    //printf("Am adaugat %c in lista\n", new_node -> c);
    return head;
}

/// simulez huffman pana la pasul 3 
 nod *huffman_fake(nod *head){
    for(int i = 0; i<3; i++){
        nod *nod1 = head, *nod2 = head -> next;
        head = head -> next -> next;
        head = add_node(head, '\0', nod1->data + nod2->data);
    }
    return head;
}

/// insert node
nod *insert_node(nod *head, nod *new_node) {
    if (head == NULL) {
        return new_node;
    }
    nod *current = head;
    
    if(current -> data >= new_node -> data){
        new_node -> next = head;
        return new_node;
    }
    
    while (current->next && (current->next->data < new_node->data || (current->next->data == new_node->data && current->next->c <= new_node->c))) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    return head;
}


void afisare_lista(nod *head){
    for(nod *current = head; current; current = current -> next)
        printf("%c:%d\n", current -> c, current -> data);
}

/// creez graful huffman
nod *real_huffman(nod *lista) {
    nod *current = lista;
    while (current && current->next) {  // Ensure there are at least two nodes left
        nod *new_node = create_node('\0', current->data + current->next->data);
        new_node->left = current;
        new_node->right = current->next;
        current = current->next->next;  // Move to the next pair
        current = insert_node(current, new_node);  // Insert the new node
    }

    // Return the remaining root of the tree (last node or internal node)
    return current;  // This will be the root node of the Huffman tree
}
void afisare_noduri(nod *head){
    for(nod *current = head; current; current = current -> next)
        printf("%d ", current -> data);
}

void afisare_huffman(nod *root){
    if(root){
        afisare_huffman(root -> left);
        printf("%c - %d\n", root -> c, root -> data);
        afisare_huffman(root -> right);
    }
}

void codificare_huffman(nod *root, char *s){
    if(root){
        strcpy(cod[(int)root->c], s);
        // folosesc doua siruri ca sa salvez pathul parcurs pana la nod si il concatenez cu urmatorul pas (0 - stanga, 1 - dreapta)
        char left[100], right[100]; 
        
        strcpy(left, s);
        strcpy(right, s);
        strcat(left, "0");
        strcat(right, "1");
        
        codificare_huffman(root -> left, left);
        codificare_huffman(root -> right, right);
    }
}

void afisare_coduri(nod *lista, int nr){
    nod *current = lista; // aici parcurgem lista normal, folosind next, dar ea are valorile salvate pentru coduri, caci nodurile sunt aceleasi ca cele din arbore
    for(int i = 0; i < nr; i++, current = current -> next){
        if(current -> c) // Mi-am stricat lista initiala si prin ea mai am unele noduri de la huffman, care au c = null, deci, cand ajung pe unul din ele, decrementez i ca sa continui pana afisez toate caracterele initiale
            printf("%c:%s\n", current -> c, cod[(int) current -> c]);
        else
            i--;
    }
}

void codificare_cuvant(char *cuvant, char *s){
    
    for(int i = 0; cuvant[i]; i++)
        strcat(s, cod[(int)cuvant[i]]);
}

int main(){
    //struct nod * huffman = huffman_tree();
    int frecventa[130] = {0}, test, nr = 0;
    char cuvant[200];
    
    scanf("%[^\n]", cuvant);
    
    for(int i = 0; cuvant[i]; i++){
        if(frecventa[(int)cuvant[i]] == 0)
            nr++;
        frecventa[(int)cuvant[i]] ++;
    }
    
    nod *lista = NULL;
    
    for(int i = 0, p = 0; p < nr; i++)
        if(frecventa[i]){
            lista = add_node(lista, (char)i, frecventa[i]);
            p++;
        }
    
    scanf("%d", &test);
    switch(test){
        case 1:{
            afisare_lista(lista);
            break;
        }
        case 2:{
            lista = huffman_fake(lista);
            afisare_noduri(lista);
            break;
        }
        case 3:{
            nod *huffman = real_huffman(lista);
            codificare_huffman(huffman, "");
            afisare_coduri(lista, nr);
            break;
        }
        case 4:{
            nod *huffman = real_huffman(lista);
            codificare_huffman(huffman, "");
            char s[10000] ="\0";
            codificare_cuvant(cuvant, s);
            printf("%s\n", s);
            break;
        }
        case 5:{
            nod *huffman = real_huffman(lista);
            codificare_huffman(huffman, "");
            char s[10000] ="\0";
            codificare_cuvant(cuvant, s);
            printf("%d\n", strlen(cuvant) * 8 - strlen(s));
            break;
        }
    }
}
