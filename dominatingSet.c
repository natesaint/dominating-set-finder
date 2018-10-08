// Nathen St. Germain
// CIS*3150 - Assignment 2 - Question 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

#define MAX_N 101

int n, m, k, binaryString[MAX_N], found;

// Generate binary strings of length n with k 1s
void listBinary(int t, int numOnes, int matrix[MAX_N][MAX_N]) {
    if (found == 1) return;

    // Strings of length n with k ones
    if (t > n) {
        // Check if a dominating set of size k
        int checkCol = 1;
        for (int i = 1; i < n + 1; i++) {
            int checkRow = 0;
            for (int j = 1; j < n + 1; j++) {
                if (binaryString[j] == 1 && matrix[i][j] == 1) {
                    j = n + 1;
                    checkRow = 1;
                }
            }
            if (!checkRow) {
                i = n + 1;
                checkCol = 0;
            }
        }
        if (checkCol) found = 1;
    // Concat. new parts of binary string
    } else {
        if (n - t + 1 > k - numOnes && found != 1) {
            binaryString[t] = 0;
            listBinary(t + 1, numOnes, matrix);
        }

        if (numOnes < k && found != 1) {
            binaryString[t] = 1;
            listBinary(t + 1, numOnes + 1, matrix);
        }
    }
}

// Read in edge listing, and update the adjancency matrix
void readEdgeListing(char *filename, int matrix[MAX_N][MAX_N]) {
    int readFirst = 0;
    char line[20];
    FILE *fp = fopen(filename, "r");

    while (fgets(line, 20, fp)) {
        char *token = strtok(line, " \n");
        if (readFirst) {
            int x, y;
            x = (int)strtol(token, NULL, 10);
            token = strtok(NULL, " \n");
            y = (int)strtol(token, NULL, 10);
            matrix[x][y] = 1;
            matrix[y][x] = 1;
        } else {
            n = (int)strtol(token, NULL, 10);
            token = strtok(NULL, " \n");
            m = (int)strtol(token, NULL, 10);
            token = strtok(NULL, " \n");
            k = (int)strtol(token, NULL, 10);
        }
        readFirst = 1;
    }

    fclose(fp);
}

// Handle the calling of functions to read data, gen strings, check dom. set
void checkDominatingSet(char *filename) {
    int matrix[MAX_N][MAX_N];
    struct timeb start, end;

    // Initialize matrix for repeated runs
    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            matrix[i][j] = 0;
    found = 0;

    readEdgeListing(filename, matrix);
    printf("n = %d vertices, m = %d edges, k = %d\n", n, m, k);
    ftime(&start);
    listBinary(1, 0, matrix);
    ftime(&end);

    // Print results
    if (found) {
        printf("Dominating set of size k=%d {", k);
        for (int i = 1; i < n + 1; i++) {
            if (binaryString[i] == 1) {
                printf("%d", i);
                if (i != n - 1) printf(",");
                else printf("}: ");
            }
        }
    } else
        printf("No dominating set of size k=%d: ", k);
    printf("%.3fs\n", (float)((1000.0 * (end.time - start.time) + (end.millitm - start.millitm)) / 1000.0));
}

int main () {
    int i = 0;
    printf("Graph %d:  ", ++i); checkDominatingSet("test_graph.txt");
    return 0;
}