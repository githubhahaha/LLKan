#pragma once
#include "global.h"
#include "GameLogic.h"
class CGameControl{
protected:
	Vertex m_svSelFst;// ѡ�еĵ�һ����
	Vertex m_svSelSec;// ѡ�еĵڶ�����
	int** m_pGameMap;// ��Ϸ��ͼ����ָ�� 

public:
	static int s_nRows;//��Ϸ����
	static int s_nCols;// ��Ϸ����
	static int s_nPicNum;// ͼƬ��
	CGameLogic m_GameLogic;// ��Ϸ�߼���������
	void StartGame(void);// ��ʼ��Ϸ 
	int GetElement(int nRow, int nCol);// �õ�ĳһ��Ԫ��
	void SetFirstPoint(int nRow, int nCol);// ���õ�һ����
	void SetSecPoint(int nRow, int nCol);// ���õڶ����� 
	bool Link(Vertex avPath[4], int&nVexnum);// �����ж�(·���ݶ�Ϊ 2 �����㣬�����ٶԸ� ���������޶�)
	bool IsWin(void);// �ж��Ƿ��ʤ


	CGameControl();
	~CGameControl();
};

