//===========================================
// 
// �Q�[���S�̏���[play.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _OBJECT_SELECT_H_
#define _OBJECT_SELECT_H_
#include "base/object_2D.h"	// �I�u�W�F�N�g2D
#include "../base/pch.h"	// �v���R���p�C��
class CSelect : public CObject2D
{
public:
	CSelect() {};
	CSelect(int nP):
		CObject2D(nP)
	{};
	virtual ~CSelect() {};
	virtual bool Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
private:
};

#endif // !_OBJECT_SELECT_H_