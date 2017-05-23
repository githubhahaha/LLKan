#pragma once

class CGameException:public CException
{
public:
	CGameException(char *msg);
	~CGameException();
};

