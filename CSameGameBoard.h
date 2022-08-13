#pragma once

#include "types.h"

/**/
class CSameGameBoard
{

public:
	
	CSameGameBoard();

	// конструктор копирования
	CSameGameBoard(const CSameGameBoard& );

	// деструктор
	~CSameGameBoard();

	/* adds random blocks to the board - in a start of the game */
	void setupBoard();

	/* 
	while we have an dynamic array for the board (but it would be better to use smart pointer)
	we need to delete it manually
	*/
	void deleteBoard();

	/* gets color of a block
	@param row row number of the element on the board
	@param col col number of the element on the board

	@return COLORREF - rgb in UL number
	*/
	COLORREF getBlockColor(block_row_col row, block_row_col col);

	
	block_index getWidth() const { return this->width; }
	void setWidth(block_index value) { width = value; }

	block_index getHeight() const { return this->height; }
	void setHeight(block_index value) { height = value; }

	block_row_col getColumnsNumber() const { return this->columnsNumber; }
	void setColumnsNumber(block_row_col value) { columnsNumber = value; }

	block_row_col getRowsNumber() const { return this->rowsNumber; }
	void setRowsNumber(block_row_col value) { rowsNumber = value; }

	int getColorsNumber() const { return this->colorsNumber; }

	// от 3 до 7 цветов возможно
	void setColorsNumber(int value);

	// Мы закончили игру?
	bool isGameOver(void) const;

	// Подсчет количества оставшихся блоков
	int getRemainingBlocks(void) const { return remainingBlocks; }

	// Функция для удаления всех примыкающих блоков
	int deleteBlocks(int row, int col);

private:

	block_index remainingBlocks;

	block_index** boardArray;

	// here 0 elem - is the background color and others are colors of the blocks
	COLORREF boardColors[8];

	// how many colors will be on the board
	int colorsNumber;

	block_index width;
	block_index height;

	block_row_col columnsNumber;
	block_row_col rowsNumber;

	/* Creates 2D array, each cell is filled by 0 */
	void createBoard();


	// Перечисление с вариантами направления (откуда мы пришли) потребуется для удаления блоков
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	// Вспомогательная рекурсивная функция для удаления примыкающих блоков
	int DeleteNeighborBlocks(int row, int col, int color,
		Direction direction);

	// Функция для сжатия доски после того, как были удалены блоки
	void CompactBoard(void);

};
