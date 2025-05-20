#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX 100

typedef struct {
    char label[100];     // Label for the node
    int used;            // Flag to mark merged clusters
    int size;            // Size of the cluster
} Cluster;

double dist[MAX][MAX];   // Distance matrix
Cluster clusters[MAX];
int n;                   // Number of initial taxa (species/sequences)

// Function to find the pair of clusters with minimum distance
void find_min_pair(int *a, int *b) {
    double min_dist = DBL_MAX;
    for (int i = 0; i < n; i++) {
        if (clusters[i].used) continue;
        for (int j = i + 1; j < n; j++) {
            if (clusters[j].used) continue;
            if (dist[i][j] < min_dist) {
                min_dist = dist[i][j];
                *a = i;
                *b = j;
            }
        }
    }
}

// UPGMA Algorithm
void upgma() {
    int total_clusters = n;
    while (1) {
        int i, j;
        find_min_pair(&i, &j);

        if (i == j || clusters[i].used || clusters[j].used)
            break;  // No more pairs to merge

        // Create new cluster label
        char new_label[200];
        snprintf(new_label, sizeof(new_label), "(%s,%s)", clusters[i].label, clusters[j].label);

        // Mark old clusters as used
        clusters[i].used = 1;
        clusters[j].used = 1;

        // Add new cluster
        strcpy(clusters[total_clusters].label, new_label);
        clusters[total_clusters].used = 0;
        clusters[total_clusters].size = clusters[i].size + clusters[j].size;

        // Update distance matrix
        for (int k = 0; k < total_clusters; k++) {
            if (k == i || k == j || clusters[k].used) continue;
            double new_dist = (
                dist[i][k] * clusters[i].size +
                dist[j][k] * clusters[j].size
            ) / (clusters[i].size + clusters[j].size);

            dist[total_clusters][k] = dist[k][total_clusters] = new_dist;
        }

        // Mark old distances as infinity (or large number)
        for (int k = 0; k <= total_clusters; k++) {
            dist[i][k] = dist[k][i] = DBL_MAX;
            dist[j][k] = dist[k][j] = DBL_MAX;
        }

        total_clusters++;
        if (total_clusters - n == n - 1) break; // Stop when only one cluster remains
    }

    // Print final tree label
    printf("\nFinal UPGMA Tree: %s\n", clusters[total_clusters - 1].label);
}

int main() {
    printf("Enter number of taxa: ");
    scanf("%d", &n);

    printf("Enter taxa names:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", clusters[i].label);
        clusters[i].used = 0;
        clusters[i].size = 1;
    }

    printf("Enter distance matrix (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &dist[i][j]);
        }
    }

    upgma();

    return 0;
}
