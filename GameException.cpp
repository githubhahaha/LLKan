#include "stdafx.h"
#include "GameException.h"


CGameException::CGameException(char *msg):CException(*msg){
	AfxMessageBox((LPCTSTR)msg, MB_ICONSTOP);
}


CGameException::~CGameException()
{
}
