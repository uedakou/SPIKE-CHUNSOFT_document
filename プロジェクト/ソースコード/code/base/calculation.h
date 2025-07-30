//============================================
//
// �v�Z�p[calculation.h]
// Author:Uedakou
// 
//============================================
#ifndef _CALCULATION_H_
#define _CALCULATION_H_
//********************************************
// �C���N���[�h
//********************************************
#include "manager.h"
//***************************************
// �v�Z�p��`
//***************************************

#define TAU (D3DX_PI * 2)	// ��

// �g�����X�t�H�[��
typedef struct {
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	D3DXVECTOR3 scl;	// �傫��(�{��)
}Transform;

// �g�����X�t�H�[��
class X : public Transform
{
public:
	X() {}
	X(D3DXVECTOR3 Vec3pos, D3DXVECTOR3 Vec3rot, D3DXVECTOR3 Vec3siz) {
		pos = Vec3pos;
		rot = Vec3rot;
		scl = Vec3siz;
	}
	X& operator+= (const X& transform)
	{
		pos.x += transform.pos.x;
		pos.y += transform.pos.y;
		pos.z += transform.pos.z;

		rot.x += transform.rot.x;
		rot.y += transform.rot.y;
		rot.z += transform.rot.z;

		scl.x += transform.scl.x;
		scl.y += transform.scl.y;
		scl.z += transform.scl.z;
		return *this;
	}
	X& operator-= (const X& transform)
	{
		pos.x -= transform.pos.x;
		pos.y -= transform.pos.y;
		pos.z -= transform.pos.z;

		rot.x -= transform.rot.x;
		rot.y -= transform.rot.y;
		rot.z -= transform.rot.z;

		scl.x -= transform.scl.x;
		scl.y -= transform.scl.y;
		scl.z -= transform.scl.z;
		return *this;
	}
	X& operator*= (const X& transform)
	{
		pos.x *= transform.pos.x;
		pos.y *= transform.pos.y;
		pos.z *= transform.pos.z;

		rot.x *= transform.rot.x;
		rot.y *= transform.rot.y;
		rot.z *= transform.rot.z;

		scl.x *= transform.scl.x;
		scl.y *= transform.scl.y;
		scl.z *= transform.scl.z;
		return *this;
	}
	X& operator/= (const X& transform)
	{
		pos.x /= transform.pos.x;
		pos.y /= transform.pos.y;
		pos.z /= transform.pos.z;

		rot.x /= transform.rot.x;
		rot.y /= transform.rot.y;
		rot.z /= transform.rot.z;

		scl.x /= transform.scl.x;
		scl.y /= transform.scl.y;
		scl.z /= transform.scl.z;
		return *this;
	}
};
//***************************************
// �v�Z
//***************************************
float RadianToAngle(float radian);	// ���W�A������A���O���ւ̕ϊ�
float AngleToRadian(float fAngle);	// �A���O�����烉�W�A���ւ̕ϊ�

#endif // !_CALCULATION_H_