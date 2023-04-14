#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 9

char solvable_sudoku[1024];
char solution_sudoku[1024];
int game_over;
int win;
int solvable_grid[N][N];
int solution_grid[N][N];
int guesses = 10;

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

// Tulostetaan sudoku
void print_grid() {
    printf("Jäljellä olevat arvaukset: %d\n", guesses);
    int colum = 1;
    printf("\t");
    for(int i=1; i<=9; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t", colum);
        colum++;
        for (int j = 0; j < N; j++) {                        
            printf("%d ", solvable_grid[i][j]);
            
        }
        printf("\n");
    }
}

// Muutetaan yksiulotteiset arrayt ongelma ja ratkaisu kaksiuloitteiseksi 
void convert_grids() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            solvable_grid[i][j] = solvable_sudoku[i*N+j] - '0';
            solution_grid[i][j] = solution_sudoku[i*N+j] - '0';
        }
    }
}

// Tarkistaa onko käyttäjän syöte oikea
void check_answer(int row, int col, int value) {
   if(solution_grid[row][col] == value) {
       solvable_grid[row][col] = value;
   } else {
       guesses--;
       printf("Väärä numero!\n");
   }
}

// Käyttäjän syöte
void insert_grid() {
    int row;
    int col;
    int value;
    
    printf("Syötä rivi: ");
    fflush( stdout );
    scanf("%d", &row);
    printf("Syötä sarake: ");
    fflush( stdout );
    scanf("%d", &col);
    printf("Syötä luku: ");
    fflush( stdout );
    scanf("%d", &value);
    fflush( stdout );
    row--;
    col--;
    check_answer(row, col, value);
}

// Pelin tilan tarkistus
int game_status() {
    //pelin tilanne chekataan täällä voitto tai häviö
    //tarkista onko liikaa vääriä arvauksia jolloin häviö
    if(guesses > 0) {   
    //jos ratkaisu valmis eli grid täynnä, voitto
        for(int i = 0; i<N; i++) {
            for (int j=0; j<N; j++) {
                if(solvable_grid[i][j]!=0) {
                    continue;
                } else {
                    return win;
                }
            }
        }
    } else {
        game_over = 1;
        return game_over;
    }
    win = 1;
    return win;
}

// Peli-loop
void game() {
    game_over = 0;
    win = 0;   
    while(!game_over && !win) {
        //peli pyörii täällä eli siirretään pelin logiikka tänne
        game_status();
        print_grid();
        insert_grid();
    }
}

int main() {
    choose_sudoku();
    convert_grids();
    game();
    return 0;
}


