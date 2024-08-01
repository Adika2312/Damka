#ifndef _DAMKA_GENERAL_H
#define _DAMKA_GENERAL_H

#define _CRT_SECURE_NO_WARNINGS

#define STARTING_NUM_OF_PAWNS 12
#define BOARD_SIZE 8
#define PLAYER1 'T'
#define PLAYER2 'B'
#define EMPTY ' '
#define LEN_OF_LINE 19
#define LAST_ROW_T 7
#define LAST_ROW_B 0

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct _checkersPos {
	char row;
	char col;
}chekersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE]; 

typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode {

	Board board;
	chekersPos* pos; 
	unsigned short total_captures_so_far; 
	struct _SingleSourceMovesTreeNode* next_move[2];

}SingleSourceMovesTreeNode;

typedef struct _SingleSourseMovesTree {

	SingleSourceMovesTreeNode* source;

}SingleSourceMovesTree;

SingleSourceMovesTree* FindSingleSourceMoves(Board board, chekersPos* src); 

typedef struct _SingleSourceMovesListCell {

	chekersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;


}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {

	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;

}SingleSourceMovesList;

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);

typedef struct _multipleSourceMovesListCell {

	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;

}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList {

	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;

}MultipleSourceMovesList;

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player); 

void Turn(Board board, Player player);

SingleSourceMovesList* findNextMove(MultipleSourceMovesList* listOfAllPlayerMoves, Player player);

void boardAfterNextMove(SingleSourceMovesList* nextMove, Board board, Player player);

void PlayGame(Board board, Player starting_player);

void InitializingBoard(Board board);

void copyBoard(Board CurrBoard, Board NewBoard);

void printBoard(Board board);

void printFrameLine();

void printColsIndexLine();

void movePlayerPawn(Board board, int NewRow, int NewCol, chekersPos* orgPos);

bool checkBoundaries(int row, int col);

bool checkIfGameOver(Board board, int* maxCapturesT, int* maxCapturesB, int* numOfPawnsT, int* numOfPawnsB, char* winner);

bool isAllPawnsCaptured(int numOfPawns, Player player, char* winner);

bool isLastRow(int row, Player player, char* winner);

void updateMaxCapture(int oldNumOfPawns, int newNumOfPawns, int* maxCaptures);

void printGameStatistics(char winner, int numOfMovesT, int numOfMovesB, int maxCapturesT, int maxCapturesB);

void changePosCharToInt(char row, char col, int* newRow, int* newCol);

void changePosIntToChar(int row, int col, char* newRow, char* newCol);

void freeLOPM(MultipleSourceMovesList* listOfAllPlayerMoves);



#endif
