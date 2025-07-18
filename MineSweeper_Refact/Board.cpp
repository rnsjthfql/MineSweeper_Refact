#include "Board.h"
#include <iostream>
#include <random>
#include <iomanip>

CBoard::CBoard(int level) : checkCount(0)
{
	switch (level) {
	case 1:
		Row = 5;
		Col = 5;
		mineNum = 7;
		break;
	case 2:
		Row = 9;
		Col = 9;
		mineNum = 20;
		break;
	case 3:
		Row = 14;
		Col = 14;
		mineNum = 40;
		break;
	}

	board.resize(Row);
	for (int i = 0;i < Row;++i)
		board[i].resize(Col);

	for (int i = 0; i < Row; ++i) {
		for (int j = 0; j < Col; ++j) {
			FCell newCell;
			newCell.adjacentMines = 0;
			newCell.cellState = eCellState::Block;
			newCell.IsMine = false;
			board[i].push_back(newCell);
		}
		board.push_back(board[i]);
	}
}

CBoard::~CBoard()
{
}

void CBoard::SetMines()
{
	for (int i = 0;i < mineNum;++i) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, Row - 1);
		auto randRow = dist(mt);
		auto randCol = dist(mt);

		board[randRow][randCol].IsMine = true;
	}
	
	for (int i = 0;i < Row;++i) {
		for (int j = 0;j < Col;++j) {
			int mineCount = 0;
			if (i - 1 >= 0 && board[i - 1][j].IsMine == true)
				++mineCount;
			if (i + 1 <= Row && board[i + 1][j].IsMine == true)
				++mineCount;
			if (j - 1 >= 0 && board[i][j - 1].IsMine == true)
				++mineCount;
			if (j + 1 <= Col && board[i][j + 1].IsMine == true)
				++mineCount;

			if(board[i][j].IsMine == false)
				board[i][j].adjacentMines = mineCount;
		}
	}
}

void CBoard::SetIsMine(int row, int col)
{
	board[row][col].IsMine = true;
}

void CBoard::SetState(int row, int col, eCellState state)
{
	board[row][col].cellState = state;		
}

bool CBoard::GetIsMine(int row, int col)
{
	return board[row][col].IsMine;
}

eCellState CBoard::GetState(int row, int col)
{
	return board[row][col].cellState;
}

int CBoard::GetMineNum()
{
	return mineNum;
}

int CBoard::GetRow()
{
	return Row;
}

int CBoard::GetCol()
{
	return Col;
}

void CBoard::ShowBoard()
{
	for (int i = 0; i < Row; ++i)
	{
		for (int j = 0; j < Col; ++j)
		{
			if (board[i][j].cellState == eCellState::Block)
				std::cout << "■ ";
			else if (board[i][j].cellState == eCellState::Open) {
				if (GetIsMine(i, j) == true)
					std::cout << "＠ ";
				else if (GetIsMine(i, j) == false)
					std::cout << board[i][j].adjacentMines << " ";
			}
			else if (board[i][j].cellState == eCellState::Flag)
				std::cout << "▷ ";
		}
		std::cout << std::endl;
	}
}

void CBoard::ShowLoseBoard(int row, int col)
{
	for (int i = 0; i < Row; ++i)
	{
		for (int j = 0; j < Col; ++j)
		{
			if (board[i][j].IsMine == true && i == row && j == col)
				std::cout << "★ ";
			else if (board[i][j].IsMine == true)
				std::cout << "＠ ";
			else
				std::cout << board[i][j].adjacentMines << " ";
		}
		std::cout << std::endl;
	}
}

bool CBoard::CheckWin()
{
	checkCount = 0;
	for (int i = 0; i < Row; ++i)
	{
		for (int j = 0; j < Col; ++j)
		{
			if (board[i][j].IsMine == true && board[i][j].cellState == eCellState::Flag)
				++checkCount;
			if (board[i][j].IsMine == false && board[i][j].cellState == eCellState::Open)
				++checkCount;
		}
	}

	if (checkCount == Row * Col)
		return true;

	return false;
}

