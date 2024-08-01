#include "DamkaTreesH.h"
#include "ListDamkaH.h"


SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) //gets a tree of posible moves a return a list of the best move
{
	SingleSourceMovesList* optimalMoveLst;
	chekersPos* final_move;
	int max_captures = 0;
	bool FinalMoveFound = false;
	char player;
	int row;
	int	col;
	int left, right;

	changePosCharToInt(moves_tree->source->pos->row, moves_tree->source->pos->col, &row, &col);

	final_move = (chekersPos*)malloc(sizeof(chekersPos));

	checkAllocOfCPos(final_move);

	final_move->row = moves_tree->source->pos->row;
	final_move->col = moves_tree->source->pos->col;

	player = (char)moves_tree->source->board[row][col];

	determineDirections(&left, &right, player);

	FindFinalMove(moves_tree->source, final_move, &max_captures, player, left, right);

	optimalMoveLst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));

	checkAllocOfSingleMovesLst(optimalMoveLst);

	makeEmptyList(optimalMoveLst);

	buildOptimalMoveList(moves_tree->source, final_move, optimalMoveLst, &FinalMoveFound);


	return optimalMoveLst;

}

void FindFinalMove(SingleSourceMovesTreeNode* root, chekersPos* final_move, int* max_captures, char player, int left, int right) {//gets a possible moves tree and find the final position of the board

	if (root == NULL)
	{
		return;
	}

	if (root->total_captures_so_far >= *max_captures)
	{
		updateFinalMove(root, final_move, max_captures);
	}


	FindFinalMove(root->next_move[left], final_move, max_captures, player, left, right);
	FindFinalMove(root->next_move[right], final_move, max_captures, player, left, right);

}

void buildOptimalMoveList(SingleSourceMovesTreeNode* root, chekersPos* final_move, SingleSourceMovesList* OptimalMoveLst, bool* FinalMoveFound) {//build a list of optimal moves based on the tree of possible moves

	if (root == NULL)
	{
		return;
	}

	if (root->pos->col == final_move->col && root->pos->row == final_move->row)
		*FinalMoveFound = true;


	if (*FinalMoveFound == false)
	{
		buildOptimalMoveList(root->next_move[LEFT_SON], final_move, OptimalMoveLst, FinalMoveFound);

		if (*FinalMoveFound == false)
			buildOptimalMoveList(root->next_move[RIGHT_SON], final_move, OptimalMoveLst, FinalMoveFound);
	}

	if (*FinalMoveFound == true)
	{
		insertMoveToStartList(root, OptimalMoveLst);
		return;
	}

}

void insertMoveToStartList(SingleSourceMovesTreeNode* root, SingleSourceMovesList* OptimalMoveLst)//insert a move to the start of the moves list
{
	SingleSourceMovesListCell* newHead;

	newHead = creteNewListNode(root, NULL);
	insertNodeToStartList(OptimalMoveLst, newHead);

}

SingleSourceMovesListCell* creteNewListNode(SingleSourceMovesTreeNode* root, SingleSourceMovesListCell* next)//creates new list node
{

	SingleSourceMovesListCell* newHead = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));

	checkAllocOfSingleMovesCell(newHead);

	newHead->captures = root->total_captures_so_far;
	newHead->position = root->pos;
	newHead->next = next;

	return newHead;
}

void insertNodeToStartList(SingleSourceMovesList* OptimalMoveLst, SingleSourceMovesListCell* newHead)//insert a move node to the start of the list
{

	if (isEmptyList(OptimalMoveLst) == true)
	{
		newHead->next = NULL;
		OptimalMoveLst->head = OptimalMoveLst->tail = newHead;
	}
	else
	{
		newHead->next = OptimalMoveLst->head;
		OptimalMoveLst->head = newHead;
	}
}

bool isEmptyList(SingleSourceMovesList* OptimalMoveLst)// return true if the list is empty
{

	if (OptimalMoveLst->head == NULL)
		return true;
	else
		return false;

}

void makeEmptyList(SingleSourceMovesList* OptimalMoveLst) //makes a list empty
{
	OptimalMoveLst->head = OptimalMoveLst->tail = NULL;
}

void updateFinalMove(SingleSourceMovesTreeNode* root, chekersPos* final_move, int* max_captures)//update the final move based on the tree node
{

	*max_captures = root->total_captures_so_far;
	final_move->col = root->pos->col;
	final_move->row = root->pos->row;

}

void determineDirections(int* left, int* right, char player)//change the movind direction depends on the player
{
	if (player == PLAYER1) {
		*left = 0;
		*right = 1;
	}
	else {
		*left = 1;
		*right = 0;
	}
}

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) {//gets a board and a player and return a list of all the best moves that the player can move with each pawn

	int row, col;
	chekersPos pos;
	SingleSourceMovesTree* possiblesTR;
	SingleSourceMovesList* optimalMoveList;
	MultipleSourceMovesList* allPosMoveLOL;


	allPosMoveLOL = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));

	checkAllocOfMultipleSourceMovesList(allPosMoveLOL);

	makeEmptyLOL(allPosMoveLOL);


	for (row = 0; row < BOARD_SIZE; row++)
	{

		for (col = 0; col < BOARD_SIZE; col++)
		{

			if (board[row][col] == player)
			{
				changePosIntToChar(row, col, &pos.row, &pos.col);

				possiblesTR = FindSingleSourceMoves(board, &pos); //build a tree of move option for each pawn

				optimalMoveList = FindSingleSourceOptimalMove(possiblesTR); //find the best move on the tree and create a list

				insertOptMoveListToEndLOL(optimalMoveList, allPosMoveLOL); //insert that list to the list of all the possible moves

			}

		}

	}

	return allPosMoveLOL;

}

void insertOptMoveListToEndLOL(SingleSourceMovesList* data, MultipleSourceMovesList* lst)//insert a move list to the list of all the possible moves
{

	MultipleSourceMovesListCell* newTail;

	newTail = creteNewLOLNode(data, NULL);

	insertNodeToEndLOL(newTail, lst);

}

MultipleSourceMovesListCell* creteNewLOLNode(SingleSourceMovesList* data, MultipleSourceMovesListCell* next) {//creates a multiple mource moves list cell

	MultipleSourceMovesListCell* res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));

	checkAllocOfMultipleSourceMovesCell(res);

	res->single_source_moves_list = data;

	res->next = next;

	return res;

}

void insertNodeToEndLOL(MultipleSourceMovesListCell* newTail, MultipleSourceMovesList* lst) { //insert a multiple mource moves list cell to the end of the list

	if (isEmptyLOL(lst) == true)
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}

	newTail->next = NULL;

}

bool isEmptyLOL(MultipleSourceMovesList* lst)//return true if the multiple mource moves list is empty
{

	if (lst->head == NULL)
		return true;
	else
		return false;

}

void makeEmptyLOL(MultipleSourceMovesList* lst)// make the multiple mource moves list empty
{
	lst->head = lst->tail = NULL;
}
