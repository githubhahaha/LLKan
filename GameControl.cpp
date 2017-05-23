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


//bool CGameControl::Link(Vertex avPath[4], int&nVexnum) { //…… 
//														 // 判断是否连通 
//	if(m_GameLogic.IsLink(m_pGameMap,m_svSelFst,m_svSelSec)) { // 消子 
//		m_GameLogic.Clear(m_pGameMap,m_svSelFst,m_svSelSec);  // 返回路径顶点 
//		nVexnum=m_GameLogic.GetVexPath(avPath);
//		return true;
//	} 
//	return false;
//}


int CGameControl::s_nRows = ROW_NUM;
int CGameControl::s_nCols=COL_NUM;// 游戏列数
int CGameControl::s_nPicNum = PIC_NUM;

CGameControl::~CGameControl()
{
}
