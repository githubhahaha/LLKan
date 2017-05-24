#pragma once
#include "global.h"
#include "GameControl.h"

// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	CDC m_dcMem;
	CDC m_dcBG;
	CDC m_dcElement;
	CDC m_dcMask;
	CPoint m_ptGameTop;
	CSize m_sizeElem;
	CRect m_rtGameRect;
	CGameControl m_GameC;
	bool m_bFirstPoint;//��ʶ�Ƿ��ǵ�һ����
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void InitElement(void);
	bool m_bPlaying;// ��Ϸ״̬��ʶ
	DECLARE_MESSAGE_MAP()
public:
	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	virtual BOOL OnInitDialog();
	void InitBackground();
	void UpdateWindow(void);
	afx_msg void OnPaint();
	void UpdateMap(void);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol);
	bool LineX(int**pGameMap, int nRow, int nCol1, int nCol2);
	bool LineY(int**pGameMap, int nRow1, int nRow2, int nCol);
	void DrawTipLine(Vertex asvPath[4], int nVexnum);




	afx_msg void OnClickedGameStart();
};
