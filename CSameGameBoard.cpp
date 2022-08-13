#include "pch.h"
#include "CSameGameBoard.h"

CSameGameBoard::CSameGameBoard() : width{ 35 },
                                   height{ 35 },
                                   rowsNumber{ 15 },
                                   columnsNumber{ 15 },
                                   boardArray{ nullptr },
								   remainingBlocks{ 0 },
								   colorsNumber { 3 }
{
    // initialize colors
	boardColors[0] = RGB(0, 0, 0);
	boardColors[1] = RGB(255, 0, 0);
	boardColors[2] = RGB(255, 255, 64);
	boardColors[3] = RGB(0, 0, 255);

	boardColors[4] = RGB(0, 255, 0);
	boardColors[5] = RGB(0, 255, 255);
	boardColors[6] = RGB(255, 0, 128);
	boardColors[7] = RGB(0, 64, 0);
}

CSameGameBoard::CSameGameBoard(const CSameGameBoard& other)
{
	width = other.width;
	height = other.height;
	rowsNumber = other.rowsNumber;
	columnsNumber = other.columnsNumber;
	remainingBlocks = other.remainingBlocks;
	colorsNumber = other.colorsNumber;

	boardArray = nullptr;

	// ����������� �������� ���������
	for (int i = 0; i < 8; i++)
		boardColors[i] = other.boardColors[i];

	// �������� ������ �������� ����
	createBoard();

	// ����������� ����������� �������� ����
	for (int row = 0; row < rowsNumber; row++)
		for (int col = 0; col < columnsNumber; col++)
			boardArray[row][col] = other.boardArray[row][col];
}

CSameGameBoard::~CSameGameBoard()
{
    deleteBoard();
}

void CSameGameBoard::setupBoard()
{
	if (boardArray == nullptr)
		createBoard();

	// generate random block color 1-3
	for (int row = 0; row < rowsNumber; row++)
		for (int col = 0; col < columnsNumber; col++)
			boardArray[row][col] = (rand() % colorsNumber) + 1;

	remainingBlocks = rowsNumber * columnsNumber;
}

void CSameGameBoard::deleteBoard()
{
	if (boardArray != nullptr)
	{
		for (int row = 0; row < rowsNumber; row++)
		{
			if (boardArray[row] != nullptr)
			{
				// delete each row
				delete[] boardArray[row];
				boardArray[row] = nullptr;
			}
		}

		delete[] boardArray;
		boardArray = nullptr;
	}
}

void CSameGameBoard::createBoard()
{
	// if there is a previous board - delete it
	if (boardArray != nullptr)
		deleteBoard();

	boardArray = new int* [rowsNumber];

	for (int row = 0; row < rowsNumber; row++)
	{
		boardArray[row] = new int[columnsNumber];

		// value for each cell will be default color
		for (int col = 0; col < columnsNumber; col++)
			boardArray[row][col] = 0;
	}
}

COLORREF CSameGameBoard::getBlockColor(block_row_col row, block_row_col col)
{
	// TODO a bit strange condition
	if (row < 0 || row >= rowsNumber || col < 0 || col >= columnsNumber)
		return boardColors[0];

	return boardColors[boardArray[row][col]];
}


int CSameGameBoard::DeleteNeighborBlocks(int row, int col, int color, Direction direction)
{
	// ��������� �� ������������ ������� ������ � �������
	if (row < 0 || row >= rowsNumber || col < 0 || col >= columnsNumber)
		return 0;

	// �������� �� ��, ��� ���� ����� ��� �� ����
	if (boardArray[row][col] != color)
		return 0;
	int nCount = 1;
	boardArray[row][col] = 0;

	// ��������� �������� �����������

	if (direction != DIRECTION_UP)
		nCount += DeleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
	if (direction != DIRECTION_DOWN)
		nCount += DeleteNeighborBlocks(row + 1, col, color, DIRECTION_UP);
	if (direction != DIRECTION_LEFT)
		nCount += DeleteNeighborBlocks(row, col - 1, color, DIRECTION_RIGHT);
	if (direction != DIRECTION_RIGHT)
		nCount += DeleteNeighborBlocks(row, col + 1, color, DIRECTION_LEFT);

	// ���������� ����� ���������� ��������� ������
	return nCount;
}

void CSameGameBoard::CompactBoard(void)
{
	// move to the bottom
		// ������� �� �� �������� ����
	for (int col = 0; col < columnsNumber; col++)
	{
		int nNextEmptyRow = rowsNumber - 1;
		int nNextOccupiedRow = nNextEmptyRow;
		while (nNextOccupiedRow >= 0 && nNextEmptyRow >= 0)
		{
			// ������� ������ ������
			while (nNextEmptyRow >= 0 &&
				boardArray[nNextEmptyRow][col] != 0)
				nNextEmptyRow--;
			if (nNextEmptyRow >= 0)
			{
				// ����� ������� ������� ������, ������������� ������ �� ������
				nNextOccupiedRow = nNextEmptyRow - 1;
				while (nNextOccupiedRow >= 0 &&
					boardArray[nNextOccupiedRow][col] == 0)
					nNextOccupiedRow--;
				if (nNextOccupiedRow >= 0)
				{
					// ������ ���������� ����� � ������� ������ �� ������
					boardArray[nNextEmptyRow][col] =
						boardArray[nNextOccupiedRow][col];
					boardArray[nNextOccupiedRow][col] = 0;
				}
			}
		}
	}
	// ����� ��, ��� ��������� ������, ������� �����
	int nNextEmptyCol = 0;
	int nNextOccupiedCol = nNextEmptyCol;
	while (nNextEmptyCol < columnsNumber && nNextOccupiedCol < columnsNumber)
	{
		// ������� ������ �������
		while (nNextEmptyCol < columnsNumber &&
			boardArray[rowsNumber - 1][nNextEmptyCol] != 0)
			nNextEmptyCol++;
		if (nNextEmptyCol < columnsNumber)
		{
			// ����� ������� ������� �������, ������������� ������ �� ������
			nNextOccupiedCol = nNextEmptyCol + 1;
			while (nNextOccupiedCol < columnsNumber &&
				boardArray[rowsNumber - 1][nNextOccupiedCol] == 0)
				nNextOccupiedCol++;
			if (nNextOccupiedCol < columnsNumber)
			{
				// �������� ���� ������� �����
				for (int row = 0; row < rowsNumber; row++)
				{
					boardArray[row][nNextEmptyCol] = boardArray[row][nNextOccupiedCol];
					boardArray[row][nNextOccupiedCol] = 0;
				}
			}
		}
	}

	// move to the right
}

void CSameGameBoard::setColorsNumber(int value)
{
	if (value >= 3 && value <= 7)
	{
		colorsNumber = value;
	}
}

bool CSameGameBoard::isGameOver(void) const
{
	// ��������� ������� �� �������� (�����-�������)
	for (int col = 0; col < columnsNumber; col++)
	{
		// ������ �� ������� (�����-�����)
		for (int row = rowsNumber - 1; row >= 0; row--)
		{
			int nColor = boardArray[row][col];

			// ���� �� ������ �� ������ � ������ ����, �� ��� ������, ��� ������� ��� ���������
			if (nColor == 0)
				break;
			else
			{
				// ��������� ������ � ������
				if (row - 1 >= 0 &&
					boardArray[row - 1][col] == nColor)
					return false;
				else if (col + 1 < columnsNumber &&
					boardArray[row][col + 1] == nColor)
					return false;
			}
		}
	}
	// ���� ����������� ������ �� ����������, ��
	return true;
}

int CSameGameBoard::deleteBlocks(int row, int col)
{
	// check if row and col in ranges
	if (row < 0 || row >= rowsNumber || col < 0 || col >= columnsNumber)
		return -1;

	// can not delete background block 
	COLORREF color = boardArray[row][col];
	if (color == 0)
		return -1;

	// is there blocks with the same color
	int count = -1;

	if (
		(row - 1 >= 0 && boardArray[row - 1][col] == color) || // top
		(row + 1 < rowsNumber && boardArray[row + 1][col] == color) || // bottom
		(col - 1 >= 0 && boardArray[row][col - 1] == color) || // left
		(col + 1 < columnsNumber && boardArray[row][col + 1] == color) // right
		)
	{
		// calling recursive function

		// up
		count += DeleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
	
		// down
		count += DeleteNeighborBlocks(row + 1, col, color, DIRECTION_UP);
		
		// left
		count += DeleteNeighborBlocks(row, col - 1, color, DIRECTION_RIGHT);
		
		// right
		count += DeleteNeighborBlocks(row, col + 1, color, DIRECTION_LEFT);

		// compress game board
		CompactBoard();

		// decrease delete blocks from blocks amount
		remainingBlocks -= count;
	}

	// number of deleted blocks
	return count;
}
