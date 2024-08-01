#include "DamkaGeneralH.h"



void InitializingBoard(Board board) {//function that set the players on their starting position in the board

    int i, j;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if ((i + j) % 2 == 1)
            {
                if (i <= 2)
                {
                    board[i][j] = PLAYER1;
                }
                else if (i >= 5)
                {
                    board[i][j] = PLAYER2;
                }
                else
                {
                    board[i][j] = EMPTY;
                }
            }
            else
            {
                board[i][j] = EMPTY;
            }
        }
    }
}

void Turn(Board board, Player player)// gets as an input a board and a player, and play the best move in the possible noves list
{
    MultipleSourceMovesList* listOfAllPlayerMoves;
    SingleSourceMovesList* nextMove;

    listOfAllPlayerMoves = FindAllPossiblePlayerMoves(board, player);

    nextMove = findNextMove(listOfAllPlayerMoves, player);

    boardAfterNextMove(nextMove, board, player);

    printf("%c%c->%c%c\n", nextMove->head->position->row, nextMove->head->position->col, nextMove->tail->position->row, nextMove->tail->position->col);

    freeLOPM(listOfAllPlayerMoves);

}

SingleSourceMovesList* findNextMove(MultipleSourceMovesList* listOfAllPlayerMoves, Player player)//gets a list of possible moves and a player and return the best move that the player should play
{
    MultipleSourceMovesListCell* curr = listOfAllPlayerMoves->head->next;
    SingleSourceMovesListCell* max = listOfAllPlayerMoves->head->single_source_moves_list->tail;
    SingleSourceMovesList* maxList = listOfAllPlayerMoves->head->single_source_moves_list;

    if (player == PLAYER1)
    {
        while (curr != NULL)
        {
            if ((curr->single_source_moves_list->tail->captures >= max->captures && curr->single_source_moves_list->head->next != NULL) || maxList->head == maxList->tail)
            {
                max = curr->single_source_moves_list->tail;
                maxList = curr->single_source_moves_list;
            }

            curr = curr->next;
        }
    }
    else//if PLAYER2
    {
        while (curr != NULL)
        {
            if ((curr->single_source_moves_list->tail->captures > max->captures && curr->single_source_moves_list->head->next != NULL) || maxList->head == maxList->tail)
            {
                max = curr->single_source_moves_list->tail;
                maxList = curr->single_source_moves_list;
            }

            curr = curr->next;
        }
    }

    return maxList;
}

void movePlayerPawn(Board board, int NewRow, int NewCol, chekersPos* orgPos) //function that move a player's pawn on the board
{
    int oldRow;
    int oldCol;
    char currPos;

    changePosCharToInt(orgPos->row, orgPos->col, &oldRow, &oldCol);

    currPos = (char)board[oldRow][oldCol];

    board[oldRow][oldCol] = EMPTY;
    board[NewRow][NewCol] = currPos;

}

void copyBoard(Board CurrBoard, Board NewBoard)//copy one board to another
{

    int i, j;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            NewBoard[i][j] = CurrBoard[i][j];
        }
    }

}

void boardAfterNextMove(SingleSourceMovesList* nextMove, Board board, Player player)//gets as an input a board and a move and make all the changes in the board after the move
{
    int newRow, newCol;
    int currRow, currCol;
    int moveByPlayer;
    SingleSourceMovesListCell* curr = nextMove->head;

    if (player == PLAYER1)
        moveByPlayer = 1;
    else
        moveByPlayer = -1;

    while (curr->next != NULL)
    {
        changePosCharToInt(curr->position->row, curr->position->col, &currRow, &currCol);
        changePosCharToInt(curr->next->position->row, curr->next->position->col, &newRow, &newCol);

        switch (newCol - currCol)  //if a cupture occured
        {
        case 2:
            board[currRow + moveByPlayer][currCol + 1] = EMPTY;
            break;
        case (-2):
            board[currRow + moveByPlayer][currCol - 1] = EMPTY;
        default:
            break;
        }

        curr = curr->next;
    }

    changePosCharToInt(nextMove->tail->position->row, nextMove->tail->position->col, &newRow, &newCol);

    movePlayerPawn(board, newRow, newCol, nextMove->head->position);
}

void changePosCharToInt(char row, char col, int* newRow, int* newCol)//converts position on the board to matrix indexes
{
    *newRow = (int)(row - 'A');
    *newCol = (int)(col - '0' - 1);
}

void changePosIntToChar(int row, int col, char* newRow, char* newCol) //converts matrix indexes to position on the board
{
    *newRow = (char)(row + 'A');
    *newCol = (char)(col + '0' + 1);
}

void freeLOPM(MultipleSourceMovesList* listOfAllPlayerMoves)// frees the list of all player moves
{
    MultipleSourceMovesListCell* currLOL = listOfAllPlayerMoves->head;
    SingleSourceMovesListCell* curr = currLOL->single_source_moves_list->head;
    MultipleSourceMovesListCell* tempLOL;
    SingleSourceMovesListCell* temp;

    while (currLOL != NULL)
    {
        while (curr != NULL)
        {
            free(curr->position);
            temp = curr->next;
            free(curr);
            curr = temp;
        }

        tempLOL = currLOL->next;
        free(currLOL);
        currLOL = tempLOL;
    }
}

void printBoard(Board board)//prints the current board
{
    int i, j;
    char row_idx = 'A';

    printFrameLine();
    printf("\n");
    printColsIndexLine();
    printf("\n");
    printFrameLine();
    printf("\n");


    for (i = 0; i < BOARD_SIZE; i++)
    {
        printf("|%c|", row_idx);

        for (j = 0; j < BOARD_SIZE; j++)
        {
            printf("%c|", board[i][j]);
        }

        printf("\n");
        printFrameLine();
        printf("\n");
        row_idx++;
    }
}

void printFrameLine()//prints the outline of the board
{
    int i;

    for (i = 0; i < LEN_OF_LINE / 2; i++)
    {
        printf("+-");
    }

    printf("+");
}

void printColsIndexLine()//prints the cols indexes line on the board
{
    int i;
    int num = 1;

    printf("+ |");

    for (i = 0; i < LEN_OF_LINE / 2 - 1; i++)
    {
        printf("%d|", num);
        num++;
    }

}

void PlayGame(Board board, Player starting_player) //recives a board and a starting player and every turn the function will print the move that was played and the board after it
{
    int numOfMovesT = 0, numOfMovesB = 0;
    int maxCapturesT = 0, maxCapturesB = 0;
    int numOfPawnsT = STARTING_NUM_OF_PAWNS, numOfPawnsB = STARTING_NUM_OF_PAWNS;
    char winner = EMPTY;
    bool isGameOver = false;
    char currPlayer = (char)starting_player;

    printBoard(board);

    while (isGameOver == false) //continue while no victory achived
    {
        printf("\n%c's turn:\n", currPlayer);

        Turn(board, currPlayer);

        printBoard(board);

        isGameOver = checkIfGameOver(board, &maxCapturesT, &maxCapturesB, &numOfPawnsT, &numOfPawnsB, &winner); 

        if (currPlayer == PLAYER1) //change turns
        {
            numOfMovesT++;
            currPlayer = PLAYER2;
        }
        else
        {
            numOfMovesB++;
            currPlayer = PLAYER1;
        }
    }

    printf("\n%c wins!\n", winner);

    printGameStatistics(winner, numOfMovesT, numOfMovesB, maxCapturesT, maxCapturesB);
}

bool checkIfGameOver(Board board, int* maxCapturesT, int* maxCapturesB, int* numOfPawnsT, int* numOfPawnsB, char* winner) //retuen true if a player won
{
    int i, j;
    int newNumOfPawnsT = 0, newNumOfPawnsB = 0;
    bool res = false;

    for (i = 0; i < BOARD_SIZE; i++) //checks if a player reached to the end of the board and counts pawns
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == PLAYER1)
            {
                newNumOfPawnsT++;
                if (res == false)
                    res = isLastRow(i, PLAYER1, winner);
            }
            else if (board[i][j] == PLAYER2)
            {
                newNumOfPawnsB++;
                if (res == false)
                    res = isLastRow(i, PLAYER2, winner);
            }
        }
    }

    updateMaxCapture(*numOfPawnsT, newNumOfPawnsT, maxCapturesB);

    updateMaxCapture(*numOfPawnsB, newNumOfPawnsB, maxCapturesT);

    *numOfPawnsT = newNumOfPawnsT;

    *numOfPawnsB = newNumOfPawnsB;

    if (res == false)
        res = isAllPawnsCaptured(newNumOfPawnsT, PLAYER1, winner) || isAllPawnsCaptured(newNumOfPawnsB, PLAYER2, winner);

    return res;
}

bool isAllPawnsCaptured(int numOfPawns, Player player, char* winner)//check if all pawns captured
{
    bool res = false;

    if (numOfPawns == 0)
    {
        res = true;

        if (player == PLAYER1)
            *winner = PLAYER2;
        else
            *winner = PLAYER1;
    }

    return res;
}

bool isLastRow(int row, Player player, char* winner)//checks if a pawn reached to the end of the board
{
    bool res = false;

    if (row == LAST_ROW_T && player == PLAYER1)
    {
        res = true;
        *winner = PLAYER1;
    }
    else if (row == LAST_ROW_B && player == PLAYER2)
    {
        res = true;
        *winner = PLAYER2;
    }

    return res;
}

void updateMaxCapture(int oldNumOfPawns, int newNumOfPawns, int* maxCaptures) // updates the max number of captures
{
    int diff = oldNumOfPawns - newNumOfPawns;

    if (diff > *maxCaptures)
        *maxCaptures = diff;
}

void printGameStatistics(char winner, int numOfMovesT, int numOfMovesB, int maxCapturesT, int maxCapturesB)// prints the game statistics
{
    if (winner == PLAYER1)
        printf("%c performed %d moves.\n", winner, numOfMovesT);
    else
        printf("%c performed %d moves.\n", winner, numOfMovesB);

    if (maxCapturesB > maxCapturesT)
        printf("B performed the highest number of captures in a single move - %d\n", maxCapturesB);
    else if (maxCapturesB < maxCapturesT)
        printf("T performed the highest number of captures in a single move - %d\n", maxCapturesT);
    else
        printf("B and T both performed the highest number of captures in a single move - %d\n", maxCapturesT);
}