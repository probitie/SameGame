#pragma once
#include "CSameGameBoard.h"
#include <stack>


class CSameGameDoc : public CDocument
{
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
	virtual ~CSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// game field params getters
	COLORREF getBlockColor(block_row_col row, block_row_col col)
	{
		return board->getBlockColor(row, col);
	}
	void setupBoard() { board->setupBoard(); }

	block_index getBlockWidth() { return board->getWidth(); }
	void setWidth(block_index value) { board->setWidth(value); }

	block_index getBlockHeight() { return board->getHeight(); }
	void setHeight(block_index value) { board->setHeight(value); }

	block_row_col getColumnsNumber() { return board->getColumnsNumber(); }
	void setColumnsNumber(block_row_col value) { board->setColumnsNumber(value); }

	block_row_col getRowsNumber() { return board->getRowsNumber(); }
	void setRowsNumber(block_row_col value) { board->setRowsNumber(value); }

	int GetNumColors() { return board->getColorsNumber(); }
	void deleteBoard() { board->deleteBoard(); }

	bool isGameOver() { return board->isGameOver(); }
	int deleteBlocks(int row, int col);
	int getRemainingBlocks()
	{
		return board->getRemainingBlocks();
	}
	void SetNumColors(int nColors)
	{
		// Сначала задаем количество цветов...
		board->setColorsNumber(nColors);

		// ...затем устанавливаем параметры игровой доски
		board->setupBoard();
	}

protected:
	DECLARE_MESSAGE_MAP()
	CSameGameDoc() noexcept;
	DECLARE_DYNCREATE(CSameGameDoc)

	// Функции очистки стеков «Отмена/Повтор»
	void ClearUndo();
	void ClearRedo();
	void UndoLast();
	void RedoLast();
	bool CanUndo();
	bool CanRedo();


#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:

	// todo сделать через ссылку
	CSameGameBoard* board = new CSameGameBoard();

	// Стек "Отмена"
	std::stack<CSameGameBoard*> m_undo{};

	// Стек "Повтор"
	std::stack<CSameGameBoard*> m_redo{};
};
