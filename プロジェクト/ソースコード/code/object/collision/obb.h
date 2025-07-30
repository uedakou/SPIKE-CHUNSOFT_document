//=================================
// 
// �L�����E�{�b�N�X �N���X�@obb.h
//outher kida ibuki 
// 
//==================================
#ifndef _OBB_H_
#define _OBB_H_
#include "../../base/pch.h"

class OBB
{
public:
	OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfwidths, const D3DXMATRIX& rotationMatrix);
	D3DXVECTOR3 GetCenter() const { return center; }  // ���S���擾
	D3DXVECTOR3 GetAxis(int index) const { return axes[index]; }  // �����擾
	D3DXVECTOR3 GetHalfwidths() const { return halfWidths; }      // �������擾
	D3DXVECTOR3 GetVertex(int index) const;   // ���_���擾
	bool CheckOverlap(const OBB& other) const;  // OBB���m�̏Փ˔���
private:
	float ProjectOntoAxis(const D3DXVECTOR3& axis) const;   // �w�莲�ւ̓��e�������v�Z

	D3DXVECTOR3 center;   // ���S�ʒu
	D3DXVECTOR3 axes[3];  // ���[�J����(x,y,z)
	D3DXVECTOR3 halfWidths;  // �e�������̔����̒���

};

#endif