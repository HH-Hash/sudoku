#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char solvable_sudoku[128];
char solution_sudoku[128];

void choose_sudoku() {
    FILE* fp = fopen("sudokus.csv", "r");
    if (fp == NULL) {
        printf("Sudokun nouto epäonnistui");
        return;
    }
    
    int num_rows = 0;
    char line[128];
    while (fgets(line, 128, fp) != NULL) {
        num_rows++;
    }
   
    // Satunnainen rivin indeksi
    srand(time(NULL));
    int random_index = rand() % num_rows;

    // FILE-pointer tiedoston alkuun 
    fseek(fp, 0, SEEK_SET);

    // Iteroidaan kunnes saavutetaan valittu satunnainen rivi 
    for (int i = 0; i < random_index; i++) {
        fgets(line, 128, fp);
    }
    if (fgets(line, 128, fp) != NULL) {
        char* token = strtok(line, ",");
        strncpy(solvable_sudoku, token, 128);
        token = strtok(NULL, ",");
        strncpy(solution_sudoku, token, 128);
        printf("random rivi:\npöytä=%s\nratkaisu=%s\n", solvable_sudoku, solution_sudoku);
    }
}

void print_grid() {
    for(int i=0; i<=81; i++) {
        if(i % 9 == 0) {
            printf("\n");
        }
        printf("%c", solvable_sudoku[i]);
    }
}

void insert_grid() {}

int main() {
    choose_sudoku();
    print_grid();
    return 0;
}

