#include <stdio.h>
#include <string.h>

// Function to get the complement base
char getComplement(char base) {
    switch(base) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
        default: return base; // In case of invalid input
    }
}

// Function to generate the coding strand (5’ -> 3’)
void getCodingStrand(char template[], char coding[]) {
    int len = strlen(template);
    char complement[len + 1];

    // Step 1: Get complement
    for(int i = 0; i < len; i++) {
        complement[i] = getComplement(template[i]);
    }
    complement[len] = '\0';

    // Step 2: Reverse the complement to get the coding strand
    for(int i = 0; i < len; i++) {
        coding[i] = complement[len - 1 - i];
    }
    coding[len] = '\0';
}

// Function to transcribe DNA to mRNA
void transcribeToMRNA(char coding[], char mRNA[]) {
    int len = strlen(coding);
    for(int i = 0; i < len; i++) {
        if(coding[i] == 'T')
            mRNA[i] = 'U';
        else
            mRNA[i] = coding[i];
    }
    mRNA[len] = '\0';
}

// Function to extract and print reading frames
void extractReadingFrames(char mRNA[]) {
    int len = strlen(mRNA);
    int maxFrames = len / 3;

    printf("\nReading Frames:\n");
    for(int i = 0; i < maxFrames; i++) {
        for(int j = 0; j < 12 && (i*3 + j) < len; j++) {
            printf("%c", mRNA[i*3 + j]);
        }
        printf("\n");
    }
}

int main() {
    char template[1000];
    char coding[1000];
    char mRNA[1000];

    printf("Enter DNA template strand (3’ -> 5’):\n");
    scanf("%s", template);

    getCodingStrand(template, coding);
    transcribeToMRNA(coding, mRNA);

    printf("\nCoding Strand (5’ -> 3’):\n%s\n", coding);
    printf("\nmRNA Sequence (5’ -> 3’):\n%s\n", mRNA);

    extractReadingFrames(mRNA);

    return 0;
}
