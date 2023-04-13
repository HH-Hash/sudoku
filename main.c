#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 9

char solvable_sudoku[1024];
char solution_sudoku[1024];
int grid[N][N];
void generate_puzzle();

void choose_sudoku() {
    FILE* fp = fopen("sudokus.csv", "r");
    if (fp == NULL) {
        printf("Sudokun nouto epäonnistui");
        return;
    }
    
    int num_rows = 0;
    char line[1024];
    while (fgets(line, 1024, fp) != NULL) {
        num_rows++;
    }
   
    // Satunnainen rivin indeksi
    srand(time(NULL));
    int random_index = rand() % num_rows;

    // FILE-pointer tiedoston alkuun 
    fseek(fp, 0, SEEK_SET);

    // Iteroidaan kunnes saavutetaan valittu satunnainen rivi 
    for (int i = 0; i < random_index; i++) {
        fgets(line, 1024, fp);
    }
    if (fgets(line, 1024, fp) != NULL) {
        char* token = strtok(line, ",");
        strncpy(solvable_sudoku, token, 1024);
        token = strtok(NULL, ",");
        strncpy(solution_sudoku, token, 1024);
        printf("random rivi:\npöytä=%s\nratkaisu=%s\n", solvable_sudoku, solution_sudoku);
    }
}

void print_grid() {
    int columNum = 1;
    printf("\t");
    for(int i=1; i<=9; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t", columNum);
        columNum++;
        for (int j = 0; j < N; j++) {                        
            printf("%d ", grid[i][j]);
            
        }
        printf("\n");
    }
}



void generate_puzzle(char user_input[]) {
    // Initialize grid with all 0s
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = user_input[i*N+j] - '0'; // convert character to integer
        }
    }

}



void check_answer() {

}

int main() {
    choose_sudoku();
    generate_puzzle(solvable_sudoku);
    print_grid();
    return 0;
}

