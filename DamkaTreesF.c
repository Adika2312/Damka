#include "DamkaTreesH.h"



SingleSourceMovesTree* FindSingleSourceMoves(Board board, chekersPos* src) { //Function that gets a position on the board and return a tree of moving ways

    SingleSourceMovesTree* tr;
    int row;
    int col;
    char myPlayer;

    changePosCharToInt(src->row, src->col, &row, &col);
    myPlayer = (char)board[row][col];


    if (myPlayer == EMPTY)
    {
        return NULL;
    }
    else
    {
        tr = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));

        checkAllocOfTree(tr);

        tr->source = helperBuildMovesTree(board, row, col, src, 0, NOT_DECIDED_YET, myPlayer);
    }

    return tr;

}

SingleSourceMovesTreeNode* helperBuildMovesTree(Board board, int row, int col, chekersPos* orgPos, int captureCount, int prevPos, char myPlayer)// builds a moves tree in a recursive way
{
    SingleSourceMovesTreeNode* left = NULL, * right = NULL, * root = NULL;
    int goForward;
    int goLeft = col - 1;
    int goRight = col + 1;
    char opponent;

    whoAmI(myPlayer, &opponent, &goForward, row);

    if (checkBoundaries(row, col) == false) // checks if position is beyond the limits of the board
        return NULL;

    if (board[row][col] == myPlayer && row != (orgPos->row - 'A')) //checks if position has our pawn
        return NULL;

    if (board[row][col] == EMPTY && captureCount == 0) //checks if the position is empty
        return createNewSourceMovesTreeNode(board, row, col, captureCount, NULL, NULL);


    if (board[row][col] == opponent) //checks for a possible capture
    {
        if (checkBoundaries(goForward, goLeft) == true && board[goForward][goLeft] == EMPTY && prevPos == LEFT_SON)
        {
            left = helperBuildMovesTree(board, goForward, goLeft, orgPos, captureCount + 1, LEFT_SON, myPlayer);

            if (left != NULL)
                updateBoard(left->board, row, col, orgPos, left);

            return left;
        }
        if (checkBoundaries(goForward, goRight) == true && board[goForward][goRight] == EMPTY && prevPos == RIGHT_SON)
        {
            right = helperBuildMovesTree(board, goForward, goRight, orgPos, captureCount + 1, RIGHT_SON, myPlayer);

            if (right != NULL)
                updateBoard(right->board, row, col, orgPos, right);

            return right;
        }
        return NULL;
    }

    if (board[row][col] == EMPTY && captureCount > 0)  // if there is a process of a capture
    {
        if (noMoreCaptures(board, goForward, goLeft, goRight, opponent) == true)
        {
            return createNewSourceMovesTreeNode(board, row, col, captureCount, NULL, NULL);
        }

        if (checkBoundaries(goForward, goLeft) == true && board[goForward][goLeft] == opponent)
        {
            left = helperBuildMovesTree(board, goForward, goLeft, orgPos, captureCount, LEFT_SON, myPlayer);
        }

        if (checkBoundaries(goForward, goRight) == true && board[goForward][goRight] == opponent)
        {
            right = helperBuildMovesTree(board, goForward, goRight, orgPos, captureCount, RIGHT_SON, myPlayer);
        }

        return createNewSourceMovesTreeNode(board, row, col, captureCount, left, right);
    }


    left = helperBuildMovesTree(board, goForward, goLeft, orgPos, captureCount, LEFT_SON, myPlayer);
    right = helperBuildMovesTree(board, goForward, goRight, orgPos, captureCount, RIGHT_SON, myPlayer);

    root = createNewSourceMovesTreeNode(board, row, col, captureCount, left, right);

    return root;
}

SingleSourceMovesTreeNode* createNewSourceMovesTreeNode(Board board, int row, int col, int captureCount, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right)//creates a node in the tree of moves
{
    SingleSourceMovesTreeNode* res;

    res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
    checkAllocOfTN(res);

    res->pos = (chekersPos*)malloc(sizeof(chekersPos));
    checkAllocOfCPos(res->pos);

    changePosIntToChar(row, col, &res->pos->row, &res->pos->col);

    copyBoard(board, res->board);

    res->total_captures_so_far = captureCount;

    res->next_move[LEFT_SON] = left;

    res->next_move[RIGHT_SON] = right;


    return res;
}

void checkAllocOfTN(SingleSourceMovesTreeNode* root)
{
    if (root == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
}

void checkAllocOfCPos(chekersPos* pos)
{
    if (pos == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
}

void checkAllocOfTree(SingleSourceMovesTree* tr)
{
    if (tr == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
}

void checkAllocOfSingleMovesLst(SingleSourceMovesList* lst)
{
    if (lst == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
}

void checkAllocOfSingleMovesCell(SingleSourceMovesListCell* cell)
{
    if (cell == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
}

void checkAllocOfMultipleSourceMovesList(MultipleSourceMovesList* lst)
{
    if (lst == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
}

void checkAllocOfMultipleSourceMovesCell(MultipleSourceMovesListCell* cell)
{
    if (cell == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
}

bool checkBoundaries(int row, int col) {//return false if the position exceed the limit, otherwise return true

    if (row == BOARD_SIZE || col == BOARD_SIZE || row < 0 || col < 0)
        return false;

    else
        return true;

}

void updateBoard(Board board, int row, int col, chekersPos* orgPos, SingleSourceMovesTreeNode* root)//updaes the board by movving the play and deletes the captures
{
    movePlayerPawn(board, row, col, orgPos);
    removeFromBoard(root, row, col);
}

bool noMoreCaptures(Board board, int goForward, int goLeft, int goRight, char opponent)//return false if the capturing process is done
{
    if (checkBoundaries(goForward, goLeft) == true && checkBoundaries(goForward, goRight) == true && board[goForward][goLeft] != opponent && board[goForward][goRight] != opponent)
        return true;

    if (checkBoundaries(goForward, goLeft) == false && checkBoundaries(goForward, goRight) == true && board[goForward][goRight] != opponent)
        return true;

    if (checkBoundaries(goForward, goRight) == false && checkBoundaries(goForward, goLeft) == true && board[goForward][goLeft] != opponent)
        return true;


    return false;
}

void removeFromBoard(SingleSourceMovesTreeNode* root, int row, int col) //deletes the pwans that were captured in the board of the tree node
{
    if (root == NULL)
        return;

    root->board[row][col] = EMPTY;

    removeFromBoard(root->next_move[LEFT_SON], row, col);
    removeFromBoard(root->next_move[RIGHT_SON], row, col);
}

void whoAmI(char myPlayer, char* opponent, int* nextRow, int currRow)//change the next row and the opponent based on the player
{

    if (myPlayer == PLAYER1) {
        *nextRow = currRow + 1;
        *opponent = PLAYER2;
    }
    else {
        *nextRow = currRow - 1;
        *opponent = PLAYER1;
    }

}