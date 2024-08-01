#ifndef DAMKA_TREES_H
#define DAMKA_TREES_H


#define LEFT_SON 0
#define RIGHT_SON 1
#define NOT_DECIDED_YET (-1)

#include "DamkaGeneralH.h"



SingleSourceMovesTreeNode* helperBuildMovesTree(Board board, int row, int col, chekersPos* orgPos, int captureCount, int prevPos, char myPlayer);

SingleSourceMovesTreeNode* createNewSourceMovesTreeNode(Board CurrBoard, int row, int col, int captureCount, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right);

void checkAllocOfTN(SingleSourceMovesTreeNode* root);

void checkAllocOfCPos(chekersPos* pos);

void checkAllocOfTree(SingleSourceMovesTree* tr);

void checkAllocOfSingleMovesLst(SingleSourceMovesList* lst);

void checkAllocOfSingleMovesCell(SingleSourceMovesListCell* cell);

void checkAllocOfMultipleSourceMovesList(MultipleSourceMovesList* lst);

void checkAllocOfMultipleSourceMovesCell(MultipleSourceMovesListCell* cell);

void updateBoard(Board board, int row, int col, chekersPos* orgPos, SingleSourceMovesTreeNode* root);

bool noMoreCaptures(Board board, int goForward, int goLeft, int goRight, char opponent);

void removeFromBoard(SingleSourceMovesTreeNode* root, int row, int col);

void whoAmI(char myPlayer, char* opponent, int* nextRow, int currRow);




#endif#pragma once
