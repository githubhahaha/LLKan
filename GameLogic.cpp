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

//bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2) {
//	PushVertex(v1);
//	//X ֱ����ʽ
//	if(v1.row==v2.row) { //����
//	
//	} //Y ֱ����ʽ 
//	if(v1.col==v2.col) { //��.. 
//
//	} 
//		return false;
//}
//
//bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2) {//�жϺ����Ƿ���ͨ�� 
//	int nCol1 = v1.col; int nCol2 = v2.col; int nRow = v1.row; //��֤ nCol1 ��ֵС�� nCol2 
//	if(nCol1>nCol2) { //���ݽ��� 
//		int nTemp=nCol1; 
//		nCol1=nCol2; 
//		nCol2=nTemp;
//	}														//ֱͨ 
//	for(int i=nCol1+1;i<=nCol2;i++) { 
//		if(i==nCol2)
//			return true;
//		if(pGameMap[nRow][i]!=BLANK)
//			break; 
//	} 
//	return false;
//}
//
//
//bool CGameLogic::LinkInCol(int**pGameMap, Vertex v1, Vertex v2)
//{
//	int nRow1 = v1.row; 
//	int nRow2 = v2.row; 
//	int nCol = v1.col; 
//	if (nRow1>nRow2) { 
//		int nTemp = nRow1; 
//		nRow1 = nRow2; 
//		nRow2 = nTemp;
//	} //ֱͨ 
//	for(int i=nRow1+1;i<=nRow2;i++) { 
//		if(i==nRow2)
//			return true; 
//		if(pGameMap[i][nCol]!=BLANK)
//			break;
//	}
//	return false;
//}
//
//int CGameLogic::GetVexPath(Vertex avPath[4]) { 
//	for (int i = 0; i< m_nVexNum; i++) { 
//		avPath[i] = m_avPath[i]; 
//	} 
//	return m_nVexNum;
//}





CGameLogic::~CGameLogic()
{
}
