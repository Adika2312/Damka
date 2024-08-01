#ifndef DAMKAPROJECT_DAMKALISTH_H
#define DAMKAPROJECT_DAMKALISTH_H

#include "DamkaGeneralH.h"


void FindFinalMove(SingleSourceMovesTreeNode* root, chekersPos* final_move, int* max_captures, char player, int left, int right);

void buildOptimalMoveList(SingleSourceMovesTreeNode* root, chekersPos* final_move, SingleSourceMovesList* OptimalMoveLst, bool* FinalMoveFound);

void insertMoveToStartList(SingleSourceMovesTreeNode* root, SingleSourceMovesList* OptimalMoveLst);

SingleSourceMovesListCell* creteNewListNode(SingleSourceMovesTreeNode* root, SingleSourceMovesListCell* next);

void insertNodeToStartList(SingleSourceMovesList* OptimalMoveLst, SingleSourceMovesListCell* newHead);

bool isEmptyList(SingleSourceMovesList* OptimalMoveLst);

void makeEmptyList(SingleSourceMovesList* OptimalMoveLst);

void updateFinalMove(SingleSourceMovesTreeNode* root, chekersPos* final_move, int* max_captures);

void determineDirections(int* left, int* right, char player);

void makeEmptyLOL(MultipleSourceMovesList* lst);

bool isEmptyLOL(MultipleSourceMovesList* lst);

void insertNodeToEndLOL(MultipleSourceMovesListCell* newTail, MultipleSourceMovesList* lst);

MultipleSourceMovesListCell* creteNewLOLNode(SingleSourceMovesList* data, MultipleSourceMovesListCell* next);

void insertOptMoveListToEndLOL(SingleSourceMovesList* data, MultipleSourceMovesList* lst);



#endif

