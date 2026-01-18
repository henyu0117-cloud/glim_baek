
// GLIM_BAEKDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIM_BAEK.h"
#include "GLIM_BAEKDlg.h"
#include "afxdialogex.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGLIMBAEKDlg 대화 상자



CGLIMBAEKDlg::CGLIMBAEKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_BAEK_DIALOG, pParent)
	, PointSize(0)
	, LineWidth(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMBAEKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POINT_SIZE, PointSize);
	DDV_MinMaxInt(pDX, PointSize, 5, 100);
	DDX_Text(pDX, IDC_EDIT_LINE_WIDTH, LineWidth);
	DDV_MinMaxInt(pDX, LineWidth, 2, 50);
}

BEGIN_MESSAGE_MAP(CGLIMBAEKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CGLIMBAEKDlg::OnClickedButtonRandom)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGLIMBAEKDlg::OnClickedButtonReset)
//	ON_EN_CHANGE(IDC_EDIT_LINE_WIDTH, &CGLIMBAEKDlg::OnEnChangeEditLineWidth)
//	ON_EN_CHANGE(IDC_EDIT_POINT_SIZE, &CGLIMBAEKDlg::OnChangeEditPointSize)
ON_EN_KILLFOCUS(IDC_EDIT_LINE_WIDTH, &CGLIMBAEKDlg::OnKillfocusEditLineWidth)
//ON_EN_CHANGE(IDC_EDIT_POINT_SIZE, &CGLIMBAEKDlg::OnChangeEditPointSize)
ON_EN_KILLFOCUS(IDC_EDIT_POINT_SIZE, &CGLIMBAEKDlg::OnKillfocusEditPointSize)
ON_WM_SIZE()
END_MESSAGE_MAP()


// CGLIMBAEKDlg 메시지 처리기

BOOL CGLIMBAEKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	PointCount = 0;
	Dragging = FALSE;
	PointSize = 10;
	LineWidth = 5;
	IsRandomMoving = FALSE;
	UpdateData(FALSE);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGLIMBAEKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGLIMBAEKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		// 클라이언트 영역 크기 얻기
		CRect rect;
		GetClientRect(&rect);

		// m_image 생성 (또는 크기 변경 시 재생성)
		if (m_image.IsNull() || m_image.GetWidth() != rect.Width() || m_image.GetHeight() != rect.Height())
		{
			if (!m_image.IsNull())
				m_image.Destroy();
			m_image.Create(rect.Width(), -rect.Height(), 8);

			// 그레이스케일 팔레트 설정
			RGBQUAD rgb[256];
			for (int i = 0; i < 256; i++)
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}

		// 배경 흰색으로 초기화
		memset(m_image.GetBits(), 255, m_image.GetPitch() * rect.Height());

		// 점 그리기
		UpdateData(TRUE);  // Edit Control 값 읽기
		for (int i = 0; i < PointCount; i++)
		{
			DrawPoint(PointCoordinate[i], PointSize);

		}

		// 점 3개면 외심원 그리기
		if (PointCount == 3)
		{
			CPoint circumCenter;
			int circumRadius;
			if (Calculator(circumCenter, circumRadius))
			{
				DrawCircle(circumCenter, circumRadius, LineWidth);
			}
		}

		// 화면에 출력
		m_image.Draw(dc, 0, 0);
		dc.SetBkMode(TRANSPARENT);
		for (int i = 0; i < PointCount; i++)
		{
			CString strCoord;
			strCoord.Format(_T("(%d, %d)"), PointCoordinate[i].x, PointCoordinate[i].y);
			dc.TextOut(PointCoordinate[i].x + PointSize + 5, PointCoordinate[i].y - 5, strCoord);
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGLIMBAEKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGLIMBAEKDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CGLIMBAEKDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CGLIMBAEKDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	// 1. 가장 가까운 점 찾기
	int closestIndex = -1;
	int closestDist = INT_MAX;

	for (int i = 0; i < PointCount; i++)
	{
		int dx = point.x - PointCoordinate[i].x;
		int dy = point.y - PointCoordinate[i].y;
		int dist = dx * dx + dy * dy;

		if (dist <= PointSize * PointSize && dist < closestDist)
		{
			closestDist = dist;
			closestIndex = i;
		}
	}

	// 2. 가까운 점이 있으면 드래그 시작
	if (closestIndex >= 0)
	{
		Dragging = TRUE;
		DragIndex = closestIndex;
		SetCapture();
		return;
	}

	// 3. 새로운 점 찍기 (3개 미만일 때만)
	if (PointCount < 3)
	{
		PointCoordinate[PointCount] = point;
		PointCount++;
		Invalidate();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CGLIMBAEKDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (Dragging)
	{
		Dragging = FALSE;
		DragIndex = -1;
		ReleaseCapture();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGLIMBAEKDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (Dragging && DragIndex >= 0)
	{
		PointCoordinate[DragIndex] = point;
		Invalidate();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CGLIMBAEKDlg::DrawPoint(CPoint center, int radius)
{
	// TODO: 여기에 구현 코드 추가.
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int j = center.y - radius; j <= center.y + radius; j++) {
		for (int i = center.x - radius; i <= center.x + radius; i++) {
			// 이미지 범위 체크
			if (i < 0 || i >= nWidth || j < 0 || j >= nHeight)
				continue;

			
			int dx = i - center.x;
			int dy = j - center.y;
			if (dx * dx + dy * dy <= radius * radius) {
				fm[j * nPitch + i] = 0;
			}
		}
	}
}

void CGLIMBAEKDlg::DrawCircle(CPoint center, int radius, int lineWidth)
{
	// TODO: 여기에 구현 코드 추가.
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int inner = radius - lineWidth / 2;
	int outer = radius + lineWidth / 2;

	for (int j = center.y - outer; j <= center.y + outer; j++) {
		for (int i = center.x - outer; i <= center.x + outer; i++) {
			// 이미지 범위 체크
			if (i < 0 || i >= nWidth || j < 0 || j >= nHeight)
				continue;

			int dx = i - center.x;
			int dy = j - center.y;
			int dist = dx * dx + dy * dy;

			// 원 테두리 안에 있는지 확인
			if (inner * inner <= dist && dist <= outer * outer) {
				fm[j * nPitch + i] = 0;  // 검정색
			}
		}
	}
}

bool CGLIMBAEKDlg::Calculator(CPoint& center, int& radius)
{
	// TODO: 여기에 구현 코드 추가.
	double x1 = PointCoordinate[0].x;
	double y1 = PointCoordinate[0].y;
	double x2 = PointCoordinate[1].x;
	double y2 = PointCoordinate[1].y;
	double x3 = PointCoordinate[2].x;
	double y3 = PointCoordinate[2].y;

	// 세 점이 일직선인지 확인
	double d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
	if (fabs(d) < 1e-6)
		return FALSE;

	// 외심 좌표 계산
	double ux = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
	double uy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / d;

	// 반지름 계산
	double r = sqrt((x1 - ux) * (x1 - ux) + (y1 - uy) * (y1 - uy));

	center.x = (int)ux;
	center.y = (int)uy;
	radius = (int)r;

	return TRUE;
}

void CGLIMBAEKDlg::OnClickedButtonRandom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (PointCount < 3)
	{
		MessageBox(_T("점 3개를 찍어야 합니다."), _T("알림"), MB_OK | MB_ICONWARNING);
		return;
	}
	
	if (IsRandomMoving)
		return;

	IsRandomMoving = TRUE;
	AfxBeginThread(RandomMoveThread, this);
}

void CGLIMBAEKDlg::OnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PointCount = 0;
	Invalidate();

}


void CGLIMBAEKDlg::OnKillfocusEditLineWidth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	Invalidate();
}


void CGLIMBAEKDlg::OnKillfocusEditPointSize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	Invalidate();
}

BOOL CGLIMBAEKDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			// 엔터 누르면 포커스 이동 (다시 그리기 적용됨)
			NextDlgCtrl();
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE)
		{
			// ESC 누르면 아무것도 안함 (창 안 닫힘)
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

UINT CGLIMBAEKDlg::RandomMoveThread(LPVOID pParam)
{
	// TODO: 여기에 구현 코드 추가.
	CGLIMBAEKDlg* pDlg = (CGLIMBAEKDlg*)pParam;

    CRect rect;
    pDlg->GetClientRect(&rect);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < pDlg->PointCount; j++)
        {
            pDlg->PointCoordinate[j].x = rand() % rect.Width();
            pDlg->PointCoordinate[j].y = rand() % rect.Height();
        }

        pDlg->Invalidate();
        Sleep(500);
    }

    pDlg->IsRandomMoving = FALSE;
    return 0;
}

void CGLIMBAEKDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (GetDlgItem(IDC_BUTTON_RESET) == NULL)
		return;

	int margin = 10;
	int btnWidth = 75;
	int btnHeight = 23;
	int editWidth = 50;
	int editHeight = 20;
	int staticWidth = 55;

	GetDlgItem(IDC_BUTTON_RESET)->MoveWindow(cx - margin - btnWidth * 3 - 16, cy - margin - btnHeight, btnWidth, btnHeight);
	GetDlgItem(IDC_BUTTON_RANDOM)->MoveWindow(cx - margin - btnWidth * 2 - 8, cy - margin - btnHeight, btnWidth, btnHeight);
	GetDlgItem(IDCANCEL)->MoveWindow(cx - margin - btnWidth, cy - margin - btnHeight, btnWidth, btnHeight);
}
