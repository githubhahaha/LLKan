#include "stdafx.h"
#include "GameControl.h"
#include "GameLogic.h"

CGameControl::CGameControl(){

}


void CGameControl::StartGame() {
	m_pGameMap=m_GameLogic.InitMap();
}

int CGameControl::GetElement(int nRow, int nCol) {
	return m_pGameMap[nRow][nCol];
}


bool CGameControl::Link(Vertex avPath[4], int&nVexnum) { 
// �����ж�(·���ݶ�Ϊ 2 �����㣬�����ٶԸ� ���������޶�)	
// �ж��Ƿ�ͬһ��ͼƬ 
	if(m_svSelFst.row==m_svSelSec.row&&m_svSelFst.col==m_svSelSec.col) { 
		return false; 
	} // �ж�ͼƬ�Ƿ���ͬ 
	if(m_pGameMap[m_svSelFst.row][m_svSelFst.col]!=m_pGameMap[m_svSelSec.row][m_svSelSec.col]) { 
		return false; 
	}
	if(m_GameLogic.IsLink(m_pGameMap,m_svSelFst,m_svSelSec)) { // �ж��Ƿ���ͨ 
		m_GameLogic.Clear(m_pGameMap,m_svSelFst,m_svSelSec);  // ���� 
		nVexnum=m_GameLogic.GetVexPath(avPath);// ����·������ 
		return true;
	} 
	return false;
}


int CGameControl::s_nRows = ROW_NUM;
int CGameControl::s_nCols=COL_NUM;// ��Ϸ����
int CGameControl::s_nPicNum = PIC_NUM;

CGameControl::~CGameControl()
{
}
