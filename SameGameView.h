
// SameGameView.h: интерфейс класса CSameGameView
//

#pragma once


class CSameGameView : public CView
{
protected: // создать только из сериализации
	CSameGameView() noexcept;
	DECLARE_DYNCREATE(CSameGameView)

// Атрибуты
public:
	CSameGameDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	void ResizeWindow();
	virtual void OnInitialUpdate();
	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
// Созданные функции схемы сообщений
protected:

public:
	// afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	afx_msg void setNColors(int n);
public:
	
	afx_msg void OnLevel3Color();
	afx_msg void OnLevel4Color();
	afx_msg void OnLevel5Color();
	afx_msg void OnLevel6Color();
	afx_msg void OnLevel7Color();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateLevel3Color(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel4Color(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel5Color(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel6Color(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel7Color(CCmdUI* pCmdUI);
	afx_msg void OnBlockAmount();
	afx_msg void OnBlockSize();
	afx_msg void OnEditRetry();
	afx_msg void OnUpdateEditRetry(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // версия отладки в SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
   { return reinterpret_cast<CSameGameDoc*>(m_pDocument); }
#endif

