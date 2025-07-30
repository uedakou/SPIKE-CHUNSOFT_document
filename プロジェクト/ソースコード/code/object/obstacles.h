//============================================
//
// ��Q��[obstacles.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBSTACLES_H_
#define _OBSTACLES_H_
#include "base/object_X.h"

class CPlayer;	// �v���C���[
class CObstacles : public CObjectX
{
public:
	virtual ~CObstacles();
	virtual bool Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

	virtual void HitTest() = 0;	// �����蔻��
private:	// �v���C�x�[�g

protected:
	CObstacles();
	static const D3DXVECTOR3 s_Collision;	// �I�u�W�F�N�g�R���W����
};

#endif // !_OBSTACLES_H_