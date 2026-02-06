#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct Game {
    char board[3][3];
    int turn;
    int status;
};

void printBoard(struct Game *g) {
    system("clear");
    printf("\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf(" %c ", g->board[i][j]);
            if(j<2) printf("|");
        }
        printf("\n");
        if(i<2) printf("---+---+---\n");
    }
    printf("\n");
}

int checkWin(struct Game *g, char p){
    for(int i=0;i<3;i++)
        if(g->board[i][0]==p && g->board[i][1]==p && g->board[i][2]==p)
            return 1;

    for(int i=0;i<3;i++)
        if(g->board[0][i]==p && g->board[1][i]==p && g->board[2][i]==p)
            return 1;

    if(g->board[0][0]==p && g->board[1][1]==p && g->board[2][2]==p)
        return 1;

    if(g->board[0][2]==p && g->board[1][1]==p && g->board[2][0]==p)
        return 1;

    return 0;
}

int checkDraw(struct Game *g){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(g->board[i][j]==' ')
                return 0;
    return 1;
}

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("Usage: %s X/O\n", argv[0]);
        return 0;
    }

    char player = argv[1][0];

    key_t key = 1234;
    int shmid = shmget(key, sizeof(struct Game), 0666 | IPC_CREAT);
    struct Game *g = (struct Game*) shmat(shmid, NULL, 0);
    
    if(player == 'O'){
       sleep(1);
    }

    if(player == 'X'){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            g->board[i][j] = ' ';

    g->turn = 0;
    g->status = 0;
}

    while(g->status == 0){

        printBoard(g);

        if((g->turn==0 && player=='X') || (g->turn==1 && player=='O')){
            int r,c;
            printf("Your move (%c). Enter row col: ", player);
            scanf("%d %d",&r,&c);

            if(g->board[r][c]==' '){
                g->board[r][c] = player;

                if(checkWin(g, player)){
                    g->status = 1;
                    printBoard(g);
                    printf("Player %c wins!\n", player);
                    break;
                }

                if(checkDraw(g)){
                    g->status = 2;
                    printBoard(g);
                    printf("Draw!\n");
                    break;
                }

                g->turn = 1 - g->turn;
            }
        }
        else{
            printf("Waiting for opponent...\n");
            sleep(1);
        }
    }

    shmdt(g);
    if(player=='X')
        shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
