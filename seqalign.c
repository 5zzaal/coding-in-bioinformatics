#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATCH 1
#define MISMATCH -1
#define GAP -2

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    else if (b >= a && b >= c) return b;
    else return c;
}

void sequenceAlignment(char *seq1, char *seq2) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);

    int score[len1+1][len2+1];
    int i, j;

    // Initialize scoring matrix
    for (i = 0; i <= len1; i++) {
        score[i][0] = i * GAP;
    }
    for (j = 0; j <= len2; j++) {
        score[0][j] = j * GAP;
    }

    // Fill scoring matrix
    for (i = 1; i <= len1; i++) {
        for (j = 1; j <= len2; j++) {
            int matchScore = (seq1[i-1] == seq2[j-1]) ? MATCH : MISMATCH;
            score[i][j] = max(
                score[i-1][j-1] + matchScore, // Diagonal (match/mismatch)
                score[i-1][j] + GAP,          // Up (gap in seq2)
                score[i][j-1] + GAP           // Left (gap in seq1)
            );
        }
    }

    // Traceback to find alignment
    char aligned1[1000], aligned2[1000];
    int pos = 0;
    i = len1;
    j = len2;

    while (i > 0 && j > 0) {
        int scoreDiag = score[i-1][j-1];
        int scoreUp = score[i-1][j];
        int scoreLeft = score[i][j-1];
        int matchScore = (seq1[i-1] == seq2[j-1]) ? MATCH : MISMATCH;

        if (score[i][j] == scoreDiag + matchScore) {
            aligned1[pos] = seq1[i-1];
            aligned2[pos] = seq2[j-1];
            i--; j--;
        } else if (score[i][j] == scoreUp + GAP) {
            aligned1[pos] = seq1[i-1];
            aligned2[pos] = '-';
            i--;
        } else {
            aligned1[pos] = '-';
            aligned2[pos] = seq2[j-1];
            j--;
        }
        pos++;
    }

    // Fill remaining gaps
    while (i > 0) {
        aligned1[pos] = seq1[i-1];
        aligned2[pos] = '-';
        i--; pos++;
    }
    while (j > 0) {
        aligned1[pos] = '-';
        aligned2[pos] = seq2[j-1];
        j--; pos++;
    }

    // Reverse and print
    aligned1[pos] = '\0';
    aligned2[pos] = '\0';

    strrev(aligned1);
    strrev(aligned2);

    printf("\nAligned Sequence 1: %s", aligned1);
    printf("\nAligned Sequence 2: %s\n", aligned2);
    printf("Alignment Score: %d\n", score[len1][len2]);
}

int main() {
    char seq1[100], seq2[100];

    printf("Enter first sequence: ");
    scanf("%s", seq1);

    printf("Enter second sequence: ");
    scanf("%s", seq2);

    sequenceAlignment(seq1, seq2);
    return 0;
}
