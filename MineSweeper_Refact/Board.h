#pragma once
#include <vector>

enum class eCellState : unsigned char
{
	Block,
	Open,
	Flag,
	End
};

struct FCell
{
	bool IsMine = false;
	int adjacentMines = 0;
	eCellState cellState = eCellState::Block;
};

class CBoard
{
private:
	int Level;
	int Row;
	int Col;
	int mineNum;
	int checkCount;
	std::vector<std::vector<FCell>> board;

public:
	CBoard(int level);
	~CBoard();

	void SetMines();
	void SetIsMine(int row, int col);
	void SetState(int row, int col, eCellState state);
	bool GetIsMine(int row, int col);
	eCellState GetState(int row, int col);
	int GetMineNum();
	int GetRow();
	int GetCol();

	void ShowBoard();
	void ShowLoseBoard(int row, int col);
	bool CheckWin();

	std::vector<FCell>& operator[] (int idx)
	{
		return board.at(idx);
	}
};

