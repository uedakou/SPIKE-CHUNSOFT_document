//============================================
//
// ��Q��(low)[obstacles_low.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_LOW_H_
#define _OBJECT_LOW_H_
#include "obstacles.h"

class CObstaclesLow : public CObstacles
{
public:
	virtual ~CObstaclesLow();
	virtual bool Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

	virtual void HitTest() override;	// �����蔻��

	static CObstaclesLow* clate(D3DXVECTOR3 pos);	// ����
	static CObstaclesLow* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ����
private:	// �v���C�x�[�g
	CObstaclesLow();

};

#endif // !_OBJECT_LOW_H_