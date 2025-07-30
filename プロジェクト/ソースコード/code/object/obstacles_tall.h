//============================================
//
// ��Q��(toll)[obstacles_toll.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_TOLL_H_
#define _OBJECT_TOLL_H_

#include "obstacles.h"
class CObstaclesToll : public CObstacles
{
public:
	virtual ~CObstaclesToll();
	virtual bool Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

	virtual void HitTest() override;	// �����蔻��

	static CObstaclesToll* clate(D3DXVECTOR3 pos);	// ����
	static CObstaclesToll* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ����
private:	// �v���C�x�[�g
	CObstaclesToll();
};

#endif // !_OBJECT_TOLL_H_