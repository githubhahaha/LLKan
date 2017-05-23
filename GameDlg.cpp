// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKan.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_GAME_START, &CGameDlg::OnClickedGameStart)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


//HRESULT CGameDlg::accDoDefaultAction(VARIANT varChild)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	return CDialogEx::accDoDefaultAction(varChild);
//}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitBackground();
	UpdateWindow();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::InitBackground() {
	CDC dc;
	HBITMAP hbmp; // 位图绘制对象句柄
	// 创建缓存DC (当前窗口DC的兼容DC)
	m_dcMem.CreateCompatibleDC(&dc);
	// 加载 "E:\bg.bmp" 到位图绘制对象 hbmp 中
	hbmp = (HBITMAP)LoadImage(
		NULL,           // 模块实例句柄(要加载的图片在其他DLL中时)
		_T("D:\\VS_workSpace\\LLKan\\LLKan\\theme\\picture\\llkan.bmp"),    // 位图路径
		IMAGE_BITMAP,   // 位图类型
		0,   // 指定图片宽
		0,  // 指定图片高
		LR_LOADFROMFILE // 从路径处加载图片
	);
	// 缓存DC选择位图绘制对象（可以理解为将图片存到mdc中）
	SelectObject(m_dcMem, hbmp);

}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // 绘制背景图片 
	dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcMem, 0, 0, SRCCOPY); 
}

void CGameDlg::UpdateWindow(void) { // 调整窗口大小 
	CRect rtWin; 
	CRect rtClient;
	this->GetWindowRect(rtWin); // 获得窗口大小 
	this->GetClientRect(rtClient); // 获得客户区大小
								// 标题栏和外边框的大小 
	int nSpanWidth=rtWin.Width()-rtClient.Width(); 
	int nSpanHeight=rtWin.Height()-rtClient.Height();
								// 设置窗口大小 
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
								// 设置对话框显示是，在 windows 窗口正中央。 
	CenterWindow();
}

void CGameDlg::InitElement() { 
	CClientDC dc(this);// 获得当前对话框的视频内存					 
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\animal_element.bmp"), // 加载 BMP 图片资源 
	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc); // 创建与视频内存兼容的内存 DC 
	m_dcElement.SelectObject(hBmp);// 将位图资源选入 DC 
	
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP,0,0,LR_LOADFROMFILE);// 加载掩码 BMP 图片资源 
	m_dcMask.CreateCompatibleDC(&dc); // 创建与视频内存兼容的内存 DC 
	m_dcMask.SelectObject(hMask);// 将位图资源选入 DC 
}

void CGameDlg::UpdateMap() { 
	for (int i = 0; i <ROW_NUM; i++) {
		for (int j = 0; j<COL_NUM; j++) { 			
			int nElemVal=m_GameC.GetElement(i,j);// 得到图片编号的值 
			m_dcMem.BitBlt(LEFT +j*ELEMW, TOP +i*ELEMH, ELEMW, ELEMH, 
				&m_dcMask,0,nElemVal*ELEMH,SRCPAINT); // 将背景与掩码相或，边保留，图像区域为 1 	

			m_dcMem.BitBlt(LEFT +j*ELEMW, TOP +i*ELEMH, ELEMW, ELEMH, 
				&m_dcElement,0,nElemVal*ELEMH,SRCAND);// 与元素图片相与，边保留，图像区域为元素图片 
		}
	}
	
	//UpdateWindow();
}

void CGameDlg::DrawTipLine(Vertex asvPath[4], int nVexnum) {
	CClientDC dc(this); 
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0)); 
	CPen*pOldPen = dc.SelectObject(&penLine);
	dc.MoveTo(m_ptGameTop.x + asvPath[0].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[0].row*m_sizeElem.cy + m_sizeElem.cy / 2);
	for (int i = 1; i<nVexnum; i++) {
		dc.LineTo(m_ptGameTop.x + asvPath[i].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[i].row*m_sizeElem.cy + m_sizeElem.cy / 2); 
	}
	dc.SelectObject(pOldPen);
}




//void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point){
//	int nRow, nCol;
//	// 判断鼠标点击的区域 
//	if(point.y<m_rtGameRect.top|| point.y>m_rtGameRect.bottom || point.x<m_rtGameRect.left|| point.x>m_rtGameRect.right) { 
//		return CDialogEx::OnLButtonUp(nFlags,point); 
//	}
//
//	//…… 
//	if(m_bFirstPoint){ // 第一个点  //……
//		CPoint point;
//		nRow = (point.y - 50) / 40;
//		nCol = (point.x - 50) / 40;
//		DrawTipFrame(nRow,  nCol);
//	} 
//	else  {// 第二个点 …… 
//		   // 连子判断 
//		bool bSuc=m_GameC.Link(avPath,nVexnum); 
//		if(bSuc==true) { // 画提示线 
//			DrawTipLine(avPath,nVexnum); // 更新地图 
//			UpdateMap(); 
//		} //…… 
//		// 判断胜负 
//		if(bSuc&&m_GameC.IsWin()) { //……
//	
//		} 
//	}
//	m_bFirstPoint = !m_bFirstPoint;
//
//}
//
//
void CGameDlg::OnClickedGameStart(){
	//m_bPlaying = true;
	m_GameC.StartGame();
	UpdateMap();
	Invalidate();
}
