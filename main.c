//Author Kashyap (Ka-Wab), May MMXXVI

#include <stdio.h> 

struct Gamestate{
    char board[3][3]; 
    char current_player;
    int moves_made; 
};
//struct Gamestate g; 

void init_board(struct Gamestate *g) {
    int row, col; 
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++ ) {
            g->board[row][col] = ' '; //space 
        }
    } 
    g->current_player = 'x';
    g->moves_made = 0; 

};

void print_board(struct Gamestate *g){
    int row, col; 
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            printf(" %c ", g->board[row][col]);
            if (col < 2) 
            putchar('|');
        }
        putchar('\n'); 
        if (row < 2) puts("---|---|---"); 
    }
 } 

 int make_move(struct Gamestate *g, int row, int col){
    if (row < 0 || row > 2 || col < 0 || col > 2)
    return 0;
    if (g->board[row][col] != ' ')
    return 0;
    g->board[row][col] = g->current_player;
    g->moves_made++; 
    return 1;
 }


char check_winner(struct Gamestate *g){
    //check row
    if(g->board[0][0] == g->board[0][1] && g->board[0][1] == g->board[0][2] && g->board[0][0] != ' ')
    return g->board[0][0];
    if(g->board[1][0] == g->board[1][1] && g->board[1][1] == g->board[1][2] && g->board[1][0] != ' ')
    return g->board[1][0];
    if(g->board[2][0] == g->board[2][1] && g->board[2][1] == g->board[2][2] && g->board[2][0] != ' ')
    return g->board[2][0];

    //check columns
    if(g->board[0][0] == g->board[1][0] && g->board[1][0] == g->board[2][0] && g->board[0][0] != ' ')
    return g->board[0][0];
    if(g->board[0][1] == g->board[1][1] && g->board[1][1] == g->board[2][1] && g->board[0][1] != ' ')
    return g->board[0][1];
    if(g->board[0][2] == g->board[1][2] && g->board[1][2] == g->board[2][2] && g->board[0][2] != ' ')
    return g->board[0][2];

    //check diagonals
    if(g->board[0][0] == g->board[1][1] && g->board[1][1] == g->board[2][2] && g->board[0][0] != ' ')
    return g->board[0][0];
    if(g->board[2][0] == g->board[1][1] && g->board[1][1] == g->board[0][2] && g->board[2][0] != ' ')
    return g->board[2][0];

    if (g->moves_made == 9)
    return 'D'; // D for draw, can use char (not strings) for correct return type
    return ' '; //returns empty space
};


void switch_player(struct Gamestate *g){
    if (g->current_player == 'x')  //note it's comparision '==' to check the input not assign '='
     g->current_player = 'o'; 
    else
    g->current_player = 'x';
};

// loop the game 
void game_loop(struct Gamestate *g) {
    int row, col;
    char winner;

    while (1) { //while 1 (true): keep looping forever until we break
        print_board(g); // shows the board
    
        printf("Player %c please enter row col (0 0): ", g->current_player); 
        
        // scanf("%d %d", &row, &col);
        // Note: this will give us trouble (infinite buffer loop) if a wrong input is privided. Scanf fails to read the input as integer. 

        if(scanf("%d %d", &row, &col) != 2) {
            puts("Invalid input, please try two co-ordinates e.g. 0 0");
            while(getchar() != '\n');
            continue;
        }

        if(make_move(g, row, col) == 0) { //note that make_move function above returns 0 and 1 to validate the row col
            puts("Invalid move try again!");
            continue; //jumps back to the loop
        }
    //check winner 
    winner = check_winner(g); 
    if (winner != ' ') {
    print_board(g); 
    if (winner == 'D')
        puts("It's a draw!");
    else
        printf("We have a winner: %c\n", winner); // use winner not g->current_player
    break; // stops the while loop
    }
    switch_player(g); 
    }

}

int main()
{
    struct Gamestate game; 
    init_board(&game);
    game_loop(&game); 
    // wait before closing the terminal (otherwise windows shuts the terminal as soon as main returns)
    printf("Please press a key to exit..");
    getchar();
    return 0;
}