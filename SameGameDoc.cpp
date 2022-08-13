
// SameGameDoc.cpp: реализация класса CSameGameDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSameGameDoc

IMPLEMENT_DYNCREATE(CSameGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CSameGameDoc, CDocument)
END_MESSAGE_MAP()


// creation or destroy CSameGameDoc

CSameGameDoc::CSameGameDoc() noexcept
{
	

}

CSameGameDoc::~CSameGameDoc()
{
	// Удаляем текущую игровую доску
	delete board;

	// Удаляем всё из стека «Отмена» 
	ClearUndo();

	// Удаляем всё из стека «Повтор»
	ClearRedo();
}

BOOL CSameGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Enable (or reset) board params
	board->setupBoard();

	return TRUE;
}

void CSameGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// code for save
	}
	else
	{
		// code for load
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSameGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSameGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSameGameDoc::clearUndo()
{
}

void CSameGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

void CSameGameDoc::clearRedo()
{
}

#endif // SHARED_HANDLERS


#ifdef _DEBUG
void CSameGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSameGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

int CSameGameDoc::deleteBlocks(int row, int col)
{
	// Сохранение текущего состояния доски в стеке «Отмена»
	m_undo.push(new CSameGameBoard(*board));

	// Очищаем стек «Повтор»
	ClearRedo();

	// Затем удаляем блоки
	int blocks = board->deleteBlocks(row, col);

	// Очищаем стек «Отмена» в конце игры
	if (board->isGameOver())
		ClearUndo();

	// Возвращаем количество блоков
	return blocks;
}

void CSameGameDoc::UndoLast()
{
	// Смотрим, есть ли у нас что-нибудь в стеке «Отмена»
	if (m_undo.empty())
		return;

	// Помещаем текущую игровую доску в стек «Повтор»
	m_redo.push(board);

	// Назначаем верхний элемент стека «Отмена» текущим
	board = m_undo.top();
	m_undo.pop();
}

bool CSameGameDoc::CanUndo()
{
	// Убеждаемся, что у нас есть возможность выполнить отмену действия
	return !m_undo.empty();
}

void CSameGameDoc::RedoLast()
{
	// Смотрим, есть ли у нас что-нибудь в стеке «Повтор»
	if (m_redo.empty())
		return;

	// Помещаем текущую игровую доску в стек «Отмена»
	m_undo.push(board);

	// Назначаем верхний элемент стека «Повтор» текущим
	board = m_redo.top();
	m_redo.pop();
}

bool CSameGameDoc::CanRedo()
{
	// Убеждаемся, сможем ли мы выполнить повтор действия (не пуст ли стек)
	return !m_redo.empty();
}

void CSameGameDoc::ClearUndo()
{
	// Очищаем стек «Отмена»
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CSameGameDoc::ClearRedo()
{
	// Очищаем стек «Повтор»
	while (!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}
#endif //_DEBUG

