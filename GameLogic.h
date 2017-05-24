#pragma once
#include "global.h"

class CGameLogic{
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);//�жϺ����Ƿ���ͨ
	bool LinkInCol(int**pGameMap, Vertex v1, Vertex v2);// �ж������Ƿ���ͨ
	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2);// ֱ����ͨ X �� 
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol);// ֱ����ͨ Y ��
	void PushVertex(Vertex v);// ���һ��·������ 
	void PopVertex();// ȡ��һ������ 
	void ClearStack();// ���ջ
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2);// ����ֱ�������ж�
	bool IsBlank(int** pGameMap);// �ж�ͼ�ж����ǲ���ȫΪ��
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);// һ���յ���ͨ��duan
	
public:
	Vertex m_avPath[4];//�����ڽ��������ж�ʱ�������Ķ��� 
	int m_nVexNum;//������
	CGameLogic();
	int** InitMap();
	void ReleaseMap(int** &pGameMap);
	int GetVexPath(Vertex avPath[4]);// �õ�·�������ص��Ƕ���	
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);//��� IsLink ����������ͨ�ж� 
	void Clear(int** pGameMap, Vertex v1, Vertex v2);// ����

	~CGameLogic();
};

