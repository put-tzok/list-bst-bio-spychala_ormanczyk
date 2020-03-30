#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

unsigned int ns[] = { 10, /* TODO: fill values which will be used as lists' sizes */ };

// each tree node contains an integer key and pointers to left and right children nodes
struct node {
    int key;
    struct node *left;
    struct node *right;
};

// tree's beginning is called the root
struct node *root = NULL;

struct node **tree_search(struct node **candidate, int value) {
    //def tree_search(nodeptr, value)
    if (value < ((*candidate)->key)) // jesli value jest mniejsza od liscia
        return tree_search((*candidate)->left, value);//to wyszukaj w lewej galezi bo tam sa mniejsze wartosci
    if (value > ((*candidate)->key))//jesli value jest wieksza od liscia
        return tree_search((*candidate)->right, value);// to wyszukaj w prawej galezi bo tam sa wieksze wartosci
    return candidate; //nwm jeszcze czy z * czy bez
    // TODO: implement
    //return NULL;
}

struct node* tree_insert(int value) {
    //def tree_insert(value)
    struct node *nodeptr = malloc(sizeof(nodeptr));; // stworz pomocnicza strukture
    nodeptr = tree_search(&root, value); // wyszukaj miejsce gdzie pasuje value
    nodeptr->key = value;
    nodeptr->left = NULL;
    nodeptr->right = NULL;
     //createNode(key ← value, left ← null, right ← null)
    // TODO: implement
    return NULL;
}



struct node **tree_maximum(struct node **candidate) {
    //def tree_maximum(nodeptr)
    if (((*candidate)->right) != NULL) // jesli jest cos po prawej stronie w wezle to znaczy ze dana wartosc nie byla najwieksza
        return tree_maximum((*candidate)->right);// wiec sprawdz czy ta prawa jest najwieksza..
    return (candidate);
    // TODO: implement
    //return NULL;
}

void tree_delete(int value) {
    //def tree_delete(value)
    struct node *nodeptr = malloc(sizeof(nodeptr));
    nodeptr = tree_search(&root, value);//znajdujemy wskaznik na dane value
    if ((nodeptr->left) == NULL && (nodeptr->right) == NULL) //jesli nie ma prawego ani leego dziecka
        nodeptr = NULL; // to po prostu bez konsekwencji usuwamy sobie
    else if ((nodeptr->left) != NULL && (nodeptr->right) == NULL) // jesli lewe mlodsze dziecko jest, ale nie ma starszego
        nodeptr = nodeptr->left; // to zamiast usuwanego elementu wstawimy lewe dziecko
    else if ((nodeptr->left) == NULL && (nodeptr->right) != NULL) // jesli prawe starsze dziekco jest,
        nodeptr = nodeptr->right; // to zamiast usuwanego wpisujemy prawe
    else // jesli mamy oba liscie
        {
        struct node *maxnodeptr = malloc(sizeof(maxnodeptr));
        maxnodeptr = tree_maximum(nodeptr->left); // to znajdujemy najwiekszy element w drzewku z lewej strony i wpisujemy go w wskaznik max
        nodeptr->key = maxnodeptr->key; // usuwamy value wpisujac zamiast niego max element z lewej storny
        maxnodeptr = maxnodeptr->left; // max element z lewej strony wpisujemy lewy jego element czyli null??
        }
    // TODO: implement
}

unsigned int tree_size(struct node *element) {
    //def list_size()
    //element = head;
     int size = 0;
     if (element->right != NULL)
    {
        size++;
        tree_size(element->right);
    }
     if (element->left != NULL)
    {
      size++;
      tree_size(element->left);
    }

     /*int size = 0;
    while (element != NULL)
        {size++;
        element = element->key;}
        */
    return size;
// TODO: implement
   // return 0;
}

/*
 * Fill an array with increasing values.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}

/*
 * Reorder array elements in a random way.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

/*
 * Check if tree is a valid BST.
 *
 * Parameters:
 *      struct node *element:   pointer to node to be checked
 *
 * Returns:
 *      bool:                   true if subtree rooted in "element" is a BST
 */
bool is_bst(struct node *element) {
    // empty tree is a valid BST
    if (element == NULL) {
        return true;
    }
    // leaf node is valid
    if (element->left == NULL && element->right == NULL) {
        return true;
    }
    // only right subnode? check it recursively
    if (element->left == NULL && element->right != NULL) {
        return (element->key < element->right->key) && is_bst(element->right);
    }
    // only left subnode? check it recursively
    if (element->left != NULL && element->right == NULL) {
        return (element->key > element->left->key) && is_bst(element->left);
    }
    // both subnodes present? check both recursively
    return (element->key > element->left->key)
        && (element->key < element->right->key)
        && is_bst(element->left)
        && is_bst(element->right);
}

void insert_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        tree_insert(t[i]);
    }
}

void insert_random(int *t, int n) {
    shuffle(t, n);
    for (int i = 0; i < n; i++) {
        tree_insert(t[i]);
    }
}

void insert_binary(int *t, int n) {
    // TODO: implement
}

char *insert_names[] = { "Increasing", "Random", "Binary" };
void (*insert_functions[])(int*, int) = { insert_increasing, insert_random, insert_binary };

int main(int argc, char **argv) {
    for (unsigned int i = 0; i < sizeof(insert_functions) / sizeof(*insert_functions); i++) {
        void (*insert)(int*, int) = insert_functions[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];

            // crate an array of increasing integers: 0, 1, 2, ...
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // insert data using one of methods
            clock_t insertion_time = clock();
            insert(t, n);
            insertion_time = clock() - insertion_time;

            assert(tree_size(root) == n);       // after all insertions, tree size must be `n`
            assert(is_bst(root));               // after all insertions, tree must be valid BST

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node **pnode = tree_search(&root, t[k]);
                struct node *iter = *pnode;
                assert(iter != NULL);           // found element cannot be NULL
                assert(iter->key == t[k]);      // found element must contain the expected value
            }
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            for (unsigned int l = 0, m = n; l < n; l++, m--) {
                assert(tree_size(root) == m);   // tree size must be equal to the expected value
                tree_delete(t[l]);
                assert(is_bst(root));           // after deletion, tree must still be valid BST
            }
            assert(tree_size(root) == 0);       // after all deletions, tree has size zero

            free(root);
            free(t);

            printf("%d\t%s\t%f\t%f\n",
                    n,
                    insert_names[i],
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}