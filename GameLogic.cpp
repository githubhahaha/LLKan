#include "stdafx.h"
#include "GameLogic.h"
#include "global.h"
#include "GameControl.h"
#include "GameException.h"

CGameLogic::CGameLogic()
{
}



int** CGameLogic::InitMap() { //���� // �����ڴ����� 
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum; 
	int** pGameMap=new int*[nRows]; 
	if(pGameMap==NULL) { 
		throw new CGameException(("�ڴ�����쳣��\n")); 
	} 
	else { 
		for(int i=0;i<nRows;i++){ 
			pGameMap[i]=new int[nCols]; 
			if(pGameMap == NULL){
				throw new CGameException(("�ڴ�����쳣��\n"));
			} 
			memset(pGameMap[i], NULL, sizeof(int)*nCols);
		}
	}
	// ���ٻ�ɫ 
	if((nRows*nCols)%(nPicNum*2)!=0) { 
		ReleaseMap(pGameMap); 
		throw new CGameException(("��Ϸ��ɫ����Ϸ��ͼ��С��ƥ�䣡"));
	} 
	int nRepeatNum=nRows*nCols/nPicNum; 
	int nCount=0; 
	for(int i=0;i<nPicNum;i++) { // �ظ��� 
		for(int j=0;j<nRepeatNum;j++) {
			pGameMap[nCount/nCols][nCount%nCols]=i; 
			nCount++; 
		} 
	}
	// �������� 
	srand((int)time(NULL));
	// ������⽻���������� 
	int nVertexNum=nRows*nCols;
	for(int i=0;i<nVertexNum;i++) { // ����õ��������� 
		int nIndex1=rand()%nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// ����������ֵ 
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
	
	if(v1.row==v2.row) { //X ֱ����ʽ
		if (abs(v1.col - v2.col) == 1)
			return true;
	} 
	if(v1.col==v2.col) { //Y ֱ����ʽ 
		if (abs(v1.row - v2.row) == 1)
			return true;
	}
	if (OneCornerLink(pGameMap, v1, v2))  return true;
	if (TwoCornerLink(pGameMap, v1, v2)) return true;
		return false;
}

bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2) {
// ֱ���ܹ����ӣ���ô����һ��������������к����ཻ�ĵ㣬ֻ����������Ϊ�գ����п���ʵ�ֶ���ֱ������
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

bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2) {// ����ֱ�������ж�
	for (int nCol = 0; nCol<CGameControl::s_nCols; nCol++) { // �ҵ�һ���� Y ��ƽ�е���ͨ�߶� 
		if (pGameMap[v1.row][nCol] == BLANK&&pGameMap[v2.row][nCol] == BLANK) {
			if (LineY(pGameMap, v1.row, v2.row, nCol)) {
				if (LineX(pGameMap, v1.row, v1.col, nCol) && LineX(pGameMap, v2.row, v2.col, nCol)) {
					// ����ڵ� 
					Vertex vx1 = { v1.row,nCol,BLANK };
					Vertex vx2 = { v2.row,nCol,BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow<CGameControl::s_nRows; nRow++) { // �ҵ�һ���� X ��ƽ�е���ͨ�߶� 
		if (pGameMap[nRow][v1.col] == BLANK&&pGameMap[nRow][v2.col] == BLANK) {
			if (LineX(pGameMap, nRow, v1.col, v2.col)) {
				if (LineY(pGameMap, nRow, v1.row, v1.col) && LineY(pGameMap, nRow, v2.row, v2.col)) { // ����ڵ�
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


bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2) {//�жϺ����Ƿ���ͨ�� 
	int nCol1 = v1.col; int nCol2 = v2.col; int nRow = v1.row; //��֤ nCol1 ��ֵС�� nCol2 
	if(nCol1>nCol2) { //���ݽ��� 
		int nTemp=nCol1; 
		nCol1=nCol2; 
		nCol2=nTemp;
	}														//ֱͨ 
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
	} //ֱͨ 
	for(int i=nRow1+1;i<=nRow2;i++) { 
		if(i==nRow2)
			return true; 
		if(pGameMap[i][nCol]!=BLANK)
			break;
	}
	return false;
}


bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2) {// ֱ����ͨ X �� 
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

bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol) {// ֱ����ͨ Y ��
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

void CGameLogic::PushVertex(Vertex v) {// ���һ��·������ 
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}


void CGameLogic::PopVertex() {// ȡ��һ������ 

}


void CGameLogic::ClearStack() {// ���ջ

}





bool CGameLogic::IsBlank(int** pGameMap) {// �ж�ͼ�ж����ǲ���ȫΪ��
	return false;
}




CGameLogic::~CGameLogic()
{
}
