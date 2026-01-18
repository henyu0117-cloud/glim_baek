
// GLIM_BAEKDlg.h: 헤더 파일
//

#pragma once


// CGLIMBAEKDlg 대화 상자
class CGLIMBAEKDlg : public CDialogEx
{
// 생성입니다.
public:
	CGLIMBAEKDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_BAEK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	int PointCount;
	CPoint PointCoordinate[3];
	bool Dragging;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int PointSize;
	int LineWidth;
	void DrawPoint(CPoint center, int radius);
	void DrawCircle(CPoint center, int radius, int lineWidth);
	CImage m_image;
	// 몇 번째 점 골랐는지
	int DragIndex;
	bool Calculator(CPoint& center, int& radius);
	afx_msg void OnClickedButtonRandom();
	afx_msg void OnClickedButtonReset();
//	afx_msg void OnEnChangeEditLineWidth();
//	afx_msg void OnChangeEditPointSize();
	afx_msg void OnKillfocusEditLineWidth();
//	afx_msg void OnChangeEditPointSize();
	afx_msg void OnKillfocusEditPointSize();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool IsRandomMoving;
	static UINT RandomMoveThread(LPVOID pParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
