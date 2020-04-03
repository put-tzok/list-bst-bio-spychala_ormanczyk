#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

unsigned int ns[] = { 30000 /* TODO: fill values which will be used as lists' sizes */ };


struct node {
    int key;
    struct node *left;
    struct node *right;
};


struct node *root = NULL;

struct node **tree_search(struct node **candidate, int value) {
    //def tree_search(nodeptr, value)
    if(*candidate==NULL)
    {
        return candidate;
    }
    if (value < ((*candidate)->key)) // jesli value jest mniejsza od liscia
        return tree_search(&(*candidate)->left, value);//to wyszukaj w lewej galezi bo tam sa mniejsze wartosci
    if (value > ((*candidate)->key))//jesli value jest wieksza od liscia
        return tree_search(&(*candidate)->right, value);// to wyszukaj w prawej galezi bo tam sa wieksze wartosci
    return candidate;
    // TODO: implement
    //return NULL;
}

struct node* tree_insert(int value) {
    //def tree_insert(value)
     struct node *nodeptr = malloc(sizeof(struct node));; // stworz pomocnicza strukture
    nodeptr->key = value;
    nodeptr->left = NULL;
    nodeptr->right = NULL;
    struct node **candidate = tree_search(&root, value); // wyszukaj miejsce gdzie pasuje value
    *candidate = nodeptr;
     //createNode(key ← value, left ← null, right ← null)
    // TODO: implement
    return NULL;
}



struct node **tree_maximum(struct node **candidate) {
    //def tree_maximum(nodeptr)
    if (((*candidate)->right) != NULL) // jesli jest cos po prawej stronie w wezle to znaczy ze dana wartosc nie byla najwieksza
        return tree_maximum(&(*candidate)->right);// wiec sprawdz czy ta prawa jest najwieksza..
    return (candidate);
    // TODO: implement
    //return NULL;
}

void tree_delete(int value) {
    //def tree_delete(value)

    struct node **candidate = tree_search(&root, value);//znajdujemy wskaznik na dane value
    struct node *nodeptr = *candidate;
    if ((nodeptr->left) == NULL && (nodeptr->right) == NULL) //jesli nie ma prawego ani leego dziecka
        *candidate = NULL; // to po prostu bez konsekwencji usuwamy sobie
    else if ((nodeptr->left) != NULL && (nodeptr->right) == NULL) // jesli lewe mlodsze dziecko jest, ale nie ma starszego
        *candidate = nodeptr->left; // to zamiast usuwanego elementu wstawimy lewe dziecko
    else if ((nodeptr->left) == NULL && (nodeptr->right) != NULL) // jesli prawe starsze dziekco jest,
        *candidate = nodeptr->right; // to zamiast usuwanego wpisujemy prawe
    else // jesli mamy oba liscie
        {

        struct node **maxcandidate= tree_maximum(&nodeptr->left); // to znajdujemy najwiekszy element w drzewku z lewej strony i wpisujemy go w wskaznik max
        struct node *maxnodeptr = *maxcandidate;
       // *candidate->key = *maxcandidate->key; // usuwamy value wpisujac zamiast niego max element z lewej storny
         nodeptr->key = maxnodeptr->key; // ???
         *maxcandidate = maxnodeptr->left; // max element z lewej strony wpisujemy lewy jego element czyli null??
        }
    // TODO: implement
}
/*unsigned int tree_rozmiar(struct node *element)
{
    int size = 0;
    if (element->right != NULL)
    {
        size++;
        tree_rozmiar(element->right);
    }
     if (element->left != NULL)
    {
      size++;
      tree_rozmiar(element->left);
    }
    return size;
}
*/
unsigned int tree_size(struct node *element) {
if (element == NULL)
{
    return 0;
}
else
{
    return 1 + tree_size(element->left) + tree_size(element->right);
}
 //   return (tree_rozmiar(element) + 1);
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


void tree_insert_biject(int *t, int p, int r) {
    //def tree_insert_biject(t, p, r)
    if (p == r)
        tree_insert(t[p]);
    else if ((r - p) == 1)
        {
        tree_insert(t[p]);
        tree_insert(t[r]);
        }
    else
        {
        int q;
        q =  p + (r - p)/2;
        tree_insert(t[q]);
        tree_insert_biject(t, p, q-1);
        tree_insert_biject(t, q+1, r);
        }
    // TODO: implement
}
void insert_binary(int *t, int n) {
    //def tree_insert_biject(t, p, r)
    tree_insert_biject( t, 0, n-1);
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
