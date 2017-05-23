// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLKan.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg �Ի���

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


// CGameDlg ��Ϣ�������


//HRESULT CGameDlg::accDoDefaultAction(VARIANT varChild)
//{
//	// TODO: �ڴ����ר�ô����/����û���
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::InitBackground() {
	CDC dc;
	HBITMAP hbmp; // λͼ���ƶ�����
	// ��������DC (��ǰ����DC�ļ���DC)
	m_dcMem.CreateCompatibleDC(&dc);
	// ���� "E:\bg.bmp" ��λͼ���ƶ��� hbmp ��
	hbmp = (HBITMAP)LoadImage(
		NULL,           // ģ��ʵ�����(Ҫ���ص�ͼƬ������DLL��ʱ)
		_T("D:\\VS_workSpace\\LLKan\\LLKan\\theme\\picture\\llkan.bmp"),    // λͼ·��
		IMAGE_BITMAP,   // λͼ����
		0,   // ָ��ͼƬ��
		0,  // ָ��ͼƬ��
		LR_LOADFROMFILE // ��·��������ͼƬ
	);
	// ����DCѡ��λͼ���ƶ��󣨿������Ϊ��ͼƬ�浽mdc�У�
	SelectObject(m_dcMem, hbmp);

}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // ���Ʊ���ͼƬ 
	dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcMem, 0, 0, SRCCOPY); 
}

void CGameDlg::UpdateWindow(void) { // �������ڴ�С 
	CRect rtWin; 
	CRect rtClient;
	this->GetWindowRect(rtWin); // ��ô��ڴ�С 
	this->GetClientRect(rtClient); // ��ÿͻ�����С
								// ����������߿�Ĵ�С 
	int nSpanWidth=rtWin.Width()-rtClient.Width(); 
	int nSpanHeight=rtWin.Height()-rtClient.Height();
								// ���ô��ڴ�С 
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
								// ���öԻ�����ʾ�ǣ��� windows ���������롣 
	CenterWindow();
}

void CGameDlg::InitElement() { 
	CClientDC dc(this);// ��õ�ǰ�Ի������Ƶ�ڴ�					 
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\animal_element.bmp"), // ���� BMP ͼƬ��Դ 
	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc); // ��������Ƶ�ڴ���ݵ��ڴ� DC 
	m_dcElement.SelectObject(hBmp);// ��λͼ��Դѡ�� DC 
	
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP,0,0,LR_LOADFROMFILE);// �������� BMP ͼƬ��Դ 
	m_dcMask.CreateCompatibleDC(&dc); // ��������Ƶ�ڴ���ݵ��ڴ� DC 
	m_dcMask.SelectObject(hMask);// ��λͼ��Դѡ�� DC 
}

void CGameDlg::UpdateMap() { 
	for (int i = 0; i <ROW_NUM; i++) {
		for (int j = 0; j<COL_NUM; j++) { 			
			int nElemVal=m_GameC.GetElement(i,j);// �õ�ͼƬ��ŵ�ֵ 
			m_dcMem.BitBlt(LEFT +j*ELEMW, TOP +i*ELEMH, ELEMW, ELEMH, 
				&m_dcMask,0,nElemVal*ELEMH,SRCPAINT); // ��������������򣬱߱�����ͼ������Ϊ 1 	

			m_dcMem.BitBlt(LEFT +j*ELEMW, TOP +i*ELEMH, ELEMW, ELEMH, 
				&m_dcElement,0,nElemVal*ELEMH,SRCAND);// ��Ԫ��ͼƬ���룬�߱�����ͼ������ΪԪ��ͼƬ 
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
//	// �ж������������ 
//	if(point.y<m_rtGameRect.top|| point.y>m_rtGameRect.bottom || point.x<m_rtGameRect.left|| point.x>m_rtGameRect.right) { 
//		return CDialogEx::OnLButtonUp(nFlags,point); 
//	}
//
//	//���� 
//	if(m_bFirstPoint){ // ��һ����  //����
//		CPoint point;
//		nRow = (point.y - 50) / 40;
//		nCol = (point.x - 50) / 40;
//		DrawTipFrame(nRow,  nCol);
//	} 
//	else  {// �ڶ����� ���� 
//		   // �����ж� 
//		bool bSuc=m_GameC.Link(avPath,nVexnum); 
//		if(bSuc==true) { // ����ʾ�� 
//			DrawTipLine(avPath,nVexnum); // ���µ�ͼ 
//			UpdateMap(); 
//		} //���� 
//		// �ж�ʤ�� 
//		if(bSuc&&m_GameC.IsWin()) { //����
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
