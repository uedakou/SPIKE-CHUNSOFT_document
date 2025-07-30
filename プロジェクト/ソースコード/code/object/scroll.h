//============================================
//
// �A�C�e��(����)[scroll.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _SCROLL_H_
#define _SCROLL_H_
#include "base/object_X.h"

class CScroll : public CObjectX
{
public:
	virtual ~CScroll();
	virtual bool Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��
	D3DXVECTOR3 GetCollisionSiz() { return s_Collision; }	// �R���W�����擾

	static CScroll* clate(D3DXVECTOR3 pos);	// ����
	static CScroll* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ����
private:	// �v���C�x�[�g
	CScroll();
	static const D3DXVECTOR3 s_Collision ;	// �����蔻��
};

#endif // !_SCROLL_H_