//============================================
//
// ����[light.h]
// Author:Uedakou
// 
//============================================
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"	

#define MAX_LIGHT (3)	// ����������
class CLight
{
public:
	CLight();
	~CLight();
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
private:
	D3DLIGHT9 m_light[MAX_LIGHT];	// ����
};




#endif // _LIGHT_H_