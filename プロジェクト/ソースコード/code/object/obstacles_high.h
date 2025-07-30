//============================================
//
// ��Q��(high)[obstacles_high.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_HIGH_H_
#define _OBJECT_HIGH_H_

#include "obstacles.h"
class CObstaclesHigh : public CObstacles
{
public:
	virtual ~CObstaclesHigh();
	virtual bool Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

	virtual void HitTest() override;	// �����蔻��

	static CObstaclesHigh* clate(D3DXVECTOR3 pos);	// ����
	static CObstaclesHigh* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ����
private:	// �v���C�x�[�g
	CObstaclesHigh();

};

#endif // !_OBJECT_HIGH_H_