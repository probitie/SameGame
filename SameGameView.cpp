
// SameGameView.cpp: реализация класса CSameGameView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "OptionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// macros for getting the document
#define GET_DOCUMENT()\
			CSameGameDoc* document = GetDocument();\
			ASSERT_VALID(document);\
			if (!document)\
			return;


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)



// Создание или уничтожение CSameGameView

CSameGameView::CSameGameView() noexcept
{
	// TODO: добавьте код создания

}

void CSameGameView::ResizeWindow()
{
	GET_DOCUMENT();

	CRect rcClient, rcWindow;

	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);

	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	rcWindow.right = rcWindow.left
		+ document->getBlockWidth() * document->getColumnsNumber() + nWidthDiff;

	rcWindow.bottom = rcWindow.top
		+ document->getBlockHeight() * document->getRowsNumber() + nHeightDiff;

	GetParentFrame()->MoveWindow(&rcWindow);
}

void CSameGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	ResizeWindow();
}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSameGameView

void CSameGameView::OnDraw(CDC* deviceContext)
{
	// pointer to the document
	GET_DOCUMENT();
	
	int deviceContextState = deviceContext->SaveDC();

	// get background rect
	CRect clientField;
	GetClientRect(&clientField);

	COLORREF color = document->getBlockColor(-1, -1);

	// make background black
	deviceContext->FillSolidRect(&clientField, color);

	// get brush for draw 
	CBrush brush;
	brush.CreateStockObject(HOLLOW_BRUSH);
	CBrush* oldBrush = deviceContext->SelectObject(&brush);

	// Рисуем блоки
	for (int row = 0; row < document->getRowsNumber(); row++)
	{
		for (int col = 0; col < document->getColumnsNumber(); col++)
		{

			color = document->getBlockColor(row, col);

			// calculate block size
			CRect rcBlock;
			rcBlock.top = row * document->getBlockWidth();
			rcBlock.left = col * document->getBlockWidth();
			rcBlock.right = rcBlock.left + document->getBlockWidth();
			rcBlock.bottom = rcBlock.top + document->getBlockHeight();

			// fill block with specific color
			deviceContext->FillSolidRect(&rcBlock, color);

			// draw contour
			deviceContext->Rectangle(&rcBlock);
		}
	}


	// restore device state (TODO: why for??)
	deviceContext->RestoreDC(deviceContextState);
	brush.DeleteObject();



}


// Диагностика CSameGameView

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSameGameView



void CSameGameView::setNColors(int n)
{

	GET_DOCUMENT();

	// set colors
	document->SetNumColors(n);

	// redraw window
	Invalidate();
	UpdateWindow();
	
}
BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_COMMAND(ID_LEVEL_3_COLOR, &CSameGameView::OnLevel3Color)
	ON_COMMAND(ID_LEVEL_4_COLOR, &CSameGameView::OnLevel4Color)
	ON_COMMAND(ID_LEVEL_5_COLOR, &CSameGameView::OnLevel5Color)
	ON_COMMAND(ID_LEVEL_6_COLOR, &CSameGameView::OnLevel6Color)
	ON_COMMAND(ID_LEVEL_7_COLOR, &CSameGameView::OnLevel7Color)
	ON_WM_LBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3_COLOR, &CSameGameView::OnUpdateLevel3Color)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4_COLOR, &CSameGameView::OnUpdateLevel4Color)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5_COLOR, &CSameGameView::OnUpdateLevel5Color)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6_COLOR, &CSameGameView::OnUpdateLevel6Color)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7_COLOR, &CSameGameView::OnUpdateLevel7Color)
	ON_COMMAND(ID_BLOCK_AMOUNT, &CSameGameView::OnBlockAmount)
	ON_COMMAND(ID_BLOCK_SIZE, &CSameGameView::OnBlockSize)
	ON_COMMAND(ID_EDIT_RETRY, &CSameGameView::OnEditRetry)
	ON_UPDATE_COMMAND_UI(ID_EDIT_RETRY, &CSameGameView::OnUpdateEditRetry)
	ON_COMMAND(ID_EDIT_UNDO, &CSameGameView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSameGameView::OnUpdateEditUndo)
END_MESSAGE_MAP()


void CSameGameView::OnLevel3Color()
{
	setNColors(3);
}


void CSameGameView::OnLevel4Color()
{
	setNColors(4);
}


void CSameGameView::OnLevel5Color()
{
	setNColors(5);
}


void CSameGameView::OnLevel6Color()
{
	setNColors(6);
}


void CSameGameView::OnLevel7Color()
{
	setNColors(7);
}


void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{

	// pointer to the document
	GET_DOCUMENT();

	// which block was clicked by
	block_row_col row = point.y / document->getBlockHeight();
	block_row_col col = point.x / document->getBlockWidth();

	block_index amountDeletedBlocks = document->deleteBlocks(row, col);

	// if at least one block was deleted
	if (amountDeletedBlocks > 0)
	{
		// redraw View
		Invalidate();
		UpdateWindow();

		// check if the game was finished
		if (document->isGameOver())
		{
			block_index remainingBlocks = document->getRemainingBlocks();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"), remainingBlocks);

			// show the result of the game
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);

		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CSameGameView::OnUpdateLevel3Color(CCmdUI* pCmdUI)
{
	GET_DOCUMENT();
	
	// left here magical number because in another way i need to introduce type of color amount
	pCmdUI->SetCheck(document->GetNumColors() == 3);
}


void CSameGameView::OnUpdateLevel4Color(CCmdUI* pCmdUI)
{
	GET_DOCUMENT();

	// left here magical number because in another way i need to introduce type of color amount
	pCmdUI->SetCheck(document->GetNumColors() == 4);
}


void CSameGameView::OnUpdateLevel5Color(CCmdUI* pCmdUI)
{
	GET_DOCUMENT();

	// left here magical number 3 because in another way i need to introduce type of color amount
	pCmdUI->SetCheck(document->GetNumColors() == 5);
}


void CSameGameView::OnUpdateLevel6Color(CCmdUI* pCmdUI)
{
	GET_DOCUMENT();

	// left here magical number because in another way i need to introduce type of color amount
	pCmdUI->SetCheck(document->GetNumColors() == 6);
}


void CSameGameView::OnUpdateLevel7Color(CCmdUI* pCmdUI)
{
	GET_DOCUMENT();

	// left here magical number because in another way i need to introduce type of color amount
	pCmdUI->SetCheck(document->GetNumColors() == 7);
}

// 
void CSameGameView::OnBlockAmount()
{
	// Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Создаем диалоговое окно
	COptionDialog dlg(true, this);

	// Устанавливаем параметры строк и столбцов
	dlg.m_nValue1 = pDoc->getRowsNumber();
	dlg.m_nValue2 = pDoc->getColumnsNumber();

	// Отображаем полученное окно
	if (dlg.DoModal() == IDOK)
	{
		// Сначала удаляем игровое поле
		pDoc->deleteBoard();

		// Устанавливаем значения, переданные пользователем
		pDoc->setRowsNumber(dlg.m_nValue1);
		pDoc->setColumnsNumber(dlg.m_nValue2);

		// Обновляем игровое поле
		pDoc->setupBoard();

		// Изменяем размеры View
		ResizeWindow();
	}
}


void CSameGameView::OnBlockSize()
{
	// Указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Создаем диалоговое окно
	COptionDialog dlg(false, this);

	// Устанавливаем параметры «Ширины/Высоты»
	dlg.m_nValue1 = pDoc->getBlockWidth();
	dlg.m_nValue2 = pDoc->getBlockHeight();

	// Отображаем окно
	if (dlg.DoModal() == IDOK)
	{
		// Удаляем игровое поле
		pDoc->deleteBoard();

		// Считываем введенные пользователем параметры
		pDoc->setWidth(dlg.m_nValue1);
		pDoc->setHeight(dlg.m_nValue2);

		// Обновляем игровую доску
		pDoc->setupBoard();

		// Изменяем размеры View
		ResizeWindow();
	}
}


void CSameGameView::OnEditRetry()
{
	GET_DOCUMENT();

	document->RedoLast();

	// Перерисовываем View
	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdateEditRetry(CCmdUI* pCmdUI)
{
	GET_DOCUMENT();
	pCmdUI->Enable(document->CanRedo());
}


void CSameGameView::OnEditUndo()
{
	GET_DOCUMENT();
	document->UndoLast();

	// Перерисовываем View
	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	GET_DOCUMENT();
	pCmdUI->Enable(document->CanUndo());
}
