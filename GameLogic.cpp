#include "stdafx.h"
#include "GameLogic.h"
#include "global.h"
#include "GameControl.h"
#include "GameException.h"

CGameLogic::CGameLogic()
{
}



int** CGameLogic::InitMap() { //…… // 开辟内存区域 
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum; 
	int** pGameMap=new int*[nRows]; 
	if(pGameMap==NULL) { 
		throw new CGameException(("内存操作异常！\n")); 
	} 
	else { 
		for(int i=0;i<nRows;i++){ 
			pGameMap[i]=new int[nCols]; 
			if(pGameMap == NULL){
				throw new CGameException(("内存操作异常！\n"));
			} 
			memset(pGameMap[i], NULL, sizeof(int)*nCols);
		}
	}
	// 多少花色 
	if((nRows*nCols)%(nPicNum*2)!=0) { 
		ReleaseMap(pGameMap); 
		throw new CGameException(("游戏花色与游戏地图大小不匹配！"));
	} 
	int nRepeatNum=nRows*nCols/nPicNum; 
	int nCount=0; 
	for(int i=0;i<nPicNum;i++) { // 重复数 
		for(int j=0;j<nRepeatNum;j++) {
			pGameMap[nCount/nCols][nCount%nCols]=i; 
			nCount++; 
		} 
	}
	// 设置种子 
	srand((int)time(NULL));
	// 随机任意交换两个数字 
	int nVertexNum=nRows*nCols;
	for(int i=0;i<nVertexNum;i++) { // 随机得到两个坐标 
		int nIndex1=rand()%nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// 交换两个数值 
		int nTmp=pGameMap[nIndex1/nCols][nIndex1%nCols]; 
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2%nCols];
		pGameMap[nIndex2/nCols][nIndex2%nCols]=nTmp; 
	}
	return pGameMap;

}

void CGameLogic::ReleaseMap(int** &pGameMap) {
	for (int i = 0; i<CGameControl::s_nRows; i++) { 
		delete[]pGameMap[i]; 
	}
	delete[]pGameMap; 
}


bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2) {
	PushVertex(v1);
	
	if(v1.row==v2.row) { //X 直连方式
		if (abs(v1.col - v2.col) == 1)
			return true;
	} 
	if(v1.col==v2.col) { //Y 直连方式 
		if (abs(v1.row - v2.row) == 1)
			return true;
	}
	if (OneCornerLink(pGameMap, v1, v2))  return true;
	if (TwoCornerLink(pGameMap, v1, v2)) return true;
		return false;
}

bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2) {
// 直角能够消子，那么顶点一定在与两个点的行和列相交的点，只有这两个点为空，才有可能实现二条直线消子
	if (pGameMap[v1.row][v2.col] == BLANK) {
		if (LineY(pGameMap, v1.row, v2.row, v2.col) && LineX(pGameMap, v1.row, v1.col, v2.col)) { 
			Vertex v = { v1.row,v2.col,BLANK }; 
			PushVertex(v); return true; 
		}
	}
	if (pGameMap[v2.row][v1.col] == BLANK) {
		if (LineY(pGameMap, v1.row, v2.row, v1.col) && LineX(pGameMap, v2.row, v1.col, v2.col)) { 
			Vertex v = { v2.row,v1.col,BLANK }; 
			PushVertex(v);
			return true;
		}
	}
	return false;

}

bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2) {// 三条直线消子判断
	for (int nCol = 0; nCol<CGameControl::s_nCols; nCol++) { // 找到一条与 Y 轴平行的连通线段 
		if (pGameMap[v1.row][nCol] == BLANK&&pGameMap[v2.row][nCol] == BLANK) {
			if (LineY(pGameMap, v1.row, v2.row, nCol)) {
				if (LineX(pGameMap, v1.row, v1.col, nCol) && LineX(pGameMap, v2.row, v2.col, nCol)) {
					// 保存节点 
					Vertex vx1 = { v1.row,nCol,BLANK };
					Vertex vx2 = { v2.row,nCol,BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow<CGameControl::s_nRows; nRow++) { // 找到一条与 X 轴平行的连通线段 
		if (pGameMap[nRow][v1.col] == BLANK&&pGameMap[nRow][v2.col] == BLANK) {
			if (LineX(pGameMap, nRow, v1.col, v2.col)) {
				if (LineY(pGameMap, nRow, v1.row, v1.col) && LineY(pGameMap, nRow, v2.row, v2.col)) { // 保存节点
					Vertex vx1 = { nRow,v1.col,BLANK };
					Vertex vx2 = { nRow,v2.col,BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	return false;
}


bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2) {//判断横向是否连通。 
	int nCol1 = v1.col; int nCol2 = v2.col; int nRow = v1.row; //保证 nCol1 的值小于 nCol2 
	if(nCol1>nCol2) { //数据交换 
		int nTemp=nCol1; 
		nCol1=nCol2; 
		nCol2=nTemp;
	}														//直通 
	for(int i=nCol1+1;i<=nCol2;i++) { 
		if(i==nCol2)
			return true;
		if(pGameMap[nRow][i]!=BLANK)
			break; 
	} 
	return false;
}


bool CGameLogic::LinkInCol(int**pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row; 
	int nRow2 = v2.row; 
	int nCol = v1.col; 
	if (nRow1>nRow2) { 
		int nTemp = nRow1; 
		nRow1 = nRow2; 
		nRow2 = nTemp;
	} //直通 
	for(int i=nRow1+1;i<=nRow2;i++) { 
		if(i==nRow2)
			return true; 
		if(pGameMap[i][nCol]!=BLANK)
			break;
	}
	return false;
}


bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2) {// 直线连通 X 轴 
	if (nCol1 > nCol2) {
		int tmp;
		tmp = nCol1;
		nCol1 = nCol2;
		nCol2 = tmp;
	}
	if (nCol1 == nCol2)
		return false;
	for (int i = nCol1; i <= nCol2; i++) {
			if (i == nCol2) return true;
			if (pGameMap[nRow][i] != BLANK)
				break;
		}

	return false;
}

bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol) {// 直线连通 Y 轴
	if (nRow1 > nRow2) {
		int tmp;
		tmp = nRow1;
		nRow1 = nRow2;
		nRow2 = tmp;
	}
	if (nRow1 == nRow2)
		return false;
	for (int i = nRow1; i <= nRow2; i++) {
		if (i == nRow2) return true;
		if (pGameMap[nCol][i] != BLANK)
			break;
	}
	return false;
}


int CGameLogic::GetVexPath(Vertex avPath[4]) {
	for (int i = 0; i< m_nVexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::PushVertex(Vertex v) {// 添加一个路径顶点 
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}


void CGameLogic::PopVertex() {// 取出一个顶点 

}


void CGameLogic::ClearStack() {// 清除栈

}





bool CGameLogic::IsBlank(int** pGameMap) {// 判断图中顶点是不是全为空
	return false;
}




CGameLogic::~CGameLogic()
{
}
