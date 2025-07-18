#include "GameManager.h"
#include "Board.h"
#include <iostream>
#include <Windows.h>

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

void CGameManager::Run()
{
	int level;
	int menu;
	int bRow;
	int bCol;

	while (true)
	{
		

		std::cout << "레벨을 입력하세요(1:하, 2:중, 3:상): ";
		std::cin >> level;
		if (level < 1 || level > 3) {
			std::cout << "레벨을 다시 입력하세요." << std::endl;
			continue;
		}
		break;
	}
	
	std::shared_ptr<CBoard> board = std::make_shared<CBoard>(level);

	mineCount = board->GetMineNum();

	board->SetMines();

	while (true)
	{
		system("cls");
		if (board->CheckWin() == true && mineCount == 0)
		{
			ShowWin();
			exit(1);
		}

		board->ShowBoard();
		ShowMenu();
		std::cout << "지뢰 개수: " << board->GetMineNum() << std::endl;
		std::cout << "메뉴를 입력하세요: ";
		std::cin >> menu;

		if (menu < 1 || menu > 4) {
			std::cout << "메뉴를 다시 입력하세요." << std::endl;
			continue;
		}

		if (menu == 4)
		{
			std::cout << "게임을 종료합니다." << std::endl;
			exit(1);
		}

		while (true)
		{
			std::cout << "행을 입력하세요: ";
			std::cin >> bRow;
			if (bRow < 1 || bRow > board->GetRow()) {
				std::cout << "행을 다시 입력하세요.(1~" << board->GetRow() << ")" << std::endl;
				continue;
			}
			break;
		}

		while (true)
		{
			std::cout << "열을 입력하세요: ";
			std::cin >> bCol;
			if (bCol < 1 || bCol > board->GetCol()) {
				std::cout << "열을 다시 입력하세요.(1~" << board->GetCol() << ")" << std::endl;
				continue;
			}
			break;
		}

		--bRow;
		--bCol;

		if (menu == 1)	//칸 열기
		{
			if (board->GetState(bRow, bCol) == eCellState::Open)
			{
				std::cout << "칸이 이미 열려있습니다." << std::endl;
				continue;
			}
			else {
				board->SetState(bRow, bCol, eCellState::Open);
				if (board->GetIsMine(bRow, bCol))
				{
					system("cls");
					ShowLose();
					board->ShowLoseBoard(bRow, bCol);
					exit(1);
				}
			}
		}
		else if (menu == 2) //깃발 꽂기
		{
			board->SetState(bRow, bCol, eCellState::Flag);
			if (board->GetIsMine(bRow, bCol) == true)
			{
				--mineCount;
			}
		}
		else if (menu == 3) // 깃발 취소
		{
			if (board->GetState(bRow, bCol) == eCellState::Open)
			{
				std::cout << "칸이 이미 열려있습니다." << std::endl;
				continue;
			}
			else if (board->GetState(bRow, bCol) == eCellState::Flag)
			{
				if (board->GetIsMine(bRow, bCol) == true)
					++mineCount;
				board->SetState(bRow, bCol, eCellState::Block);
				continue;
			}
		}
	}
}

void CGameManager::ShowMenu()
{
	std::cout << "========== 메뉴 ==========" << std::endl;
	std::cout << "1.칸 열기" << std::endl;
	std::cout << "2.깃발 꽂기" << std::endl;
	std::cout << "3.깃발 취소" << std::endl;
	std::cout << "4.종료" << std::endl;
	std::cout << "==========================" << std::endl;
}

void CGameManager::ShowWin()
{
	std::cout << "YOU WIN!!" << std::endl;
}

void CGameManager::ShowLose()
{
	std::cout << "YOU LOSE..." << std::endl;
}

