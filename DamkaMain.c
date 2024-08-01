/****** Welcome to the Damka Game created by Or Hershko (id:322316514) and Adi Karif (id:208295587)! ******/


#include "DamkaGeneralH.h"



int main()
{

    char startingPlayer;
    Board board;

    InitializingBoard(board);

    printf("Please enter a starting player (B or T)\n");

    scanf("%c", &startingPlayer);

    while (startingPlayer != PLAYER1 && startingPlayer != PLAYER2)
    {
        printf("Wrong input, try again.\n");
        scanf("\n%c", &startingPlayer);
    }


    PlayGame(board, startingPlayer);

}



