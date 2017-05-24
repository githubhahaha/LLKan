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
// 消子判断(路径暂定为 2 个顶点，后面再对该 函数进行修订)	
// 判断是否同一张图片 
	if(m_svSelFst.row==m_svSelSec.row&&m_svSelFst.col==m_svSelSec.col) { 
		return false; 
	} // 判断图片是否相同 
	if(m_pGameMap[m_svSelFst.row][m_svSelFst.col]!=m_pGameMap[m_svSelSec.row][m_svSelSec.col]) { 
		return false; 
	}
	if(m_GameLogic.IsLink(m_pGameMap,m_svSelFst,m_svSelSec)) { // 判断是否连通 
		m_GameLogic.Clear(m_pGameMap,m_svSelFst,m_svSelSec);  // 消子 
		nVexnum=m_GameLogic.GetVexPath(avPath);// 返回路径顶点 
		return true;
	} 
	return false;
}


int CGameControl::s_nRows = ROW_NUM;
int CGameControl::s_nCols=COL_NUM;// 游戏列数
int CGameControl::s_nPicNum = PIC_NUM;

CGameControl::~CGameControl()
{
}
