#include <stdio.h>
#include <string.h>

#define MAX_TAXA 10
#define MAX_SITES 100

typedef struct Node {
    int left, right;
    char label[20];
    int is_leaf;
} Node;

int num_taxa, num_sites;
char sequences[MAX_TAXA][MAX_SITES];
Node tree[MAX_TAXA * 2]; // internal + leaf nodes

// Set representation for Fitch algorithm
typedef struct {
    int set[4];  // A, C, G, T
} CharSet;

int char_to_index(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return -1;
    }
}

// Fitch Algorithm for one site
int fitch(Node tree[], int root, int site, CharSet sets[]) {
    if (tree[root].is_leaf) {
        int idx = char_to_index(sequences[root][site]);
        memset(&sets[root], 0, sizeof(CharSet));
        sets[root].set[idx] = 1;
        return 0;
    }

    int left_cost = fitch(tree, tree[root].left, site, sets);
    int right_cost = fitch(tree, tree[root].right, site, sets);

    CharSet left_set = sets[tree[root].left];
    CharSet right_set = sets[tree[root].right];

    CharSet intersect = {0};
    for (int i = 0; i < 4; i++) {
        if (left_set.set[i] && right_set.set[i]) {
            intersect.set[i] = 1;
        }
    }

    int cost = left_cost + right_cost;
    int has_common = 0;
    for (int i = 0; i < 4; i++) {
        if (intersect.set[i]) has_common = 1;
    }

    if (has_common) {
        sets[root] = intersect;
    } else {
        for (int i = 0; i < 4; i++) {
            sets[root].set[i] = left_set.set[i] | right_set.set[i];
        }
        cost += 1; // mutation needed
    }

    return cost;
}

int main() {
    printf("Enter number of taxa: ");
    scanf("%d", &num_taxa);
    printf("Enter number of sites per sequence: ");
    scanf("%d", &num_sites);

    printf("Enter sequences (only ACGT, no gaps):\n");
    for (int i = 0; i < num_taxa; i++) {
        printf("Taxon %d name: ", i);
        scanf("%s", tree[i].label);
        tree[i].is_leaf = 1;
    }
    for (int i = 0; i < num_taxa; i++) {
        printf("Sequence for %s: ", tree[i].label);
        scanf("%s", sequences[i]);
    }

    // For demo: Build a hardcoded binary tree manually
    // Tree: ((0,1),(2,3))
    int internal1 = num_taxa;
    tree[internal1].left = 0;
    tree[internal1].right = 1;
    tree[internal1].is_leaf = 0;

    int internal2 = num_taxa + 1;
    tree[internal2].left = 2;
    tree[internal2].right = 3;
    tree[internal2].is_leaf = 0;

    int root = num_taxa + 2;
    tree[root].left = internal1;
    tree[root].right = internal2;
    tree[root].is_leaf = 0;

    // Calculate total parsimony score
    int total_cost = 0;
    CharSet sets[MAX_TAXA * 2];
    for (int site = 0; site < num_sites; site++) {
        int cost = fitch(tree, root, site, sets);
        total_cost += cost;
    }

    printf("\nTotal Parsimony Score = %d\n", total_cost);

    return 0;
}
 