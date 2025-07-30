//============================================
//
// �v�Z�p[calculation.h]
// Author:Uedakou
// 
//============================================
#include "calculation.h"
//=======================================
// �v�Z�p����
//=======================================

/// <summary>
/// ���W�A���i�ʓx�@�j����A���O���i�x���@�j�ւ̕ϊ����s���܂��B
/// </summary>
/// <param name="radian">���W�A���l�i�ʓx�@�̊p�x�j</param>
/// <returns>�A���O���l�i�x���@�j</returns>
float RadianToAngle(float radian)
{
	return(360.0f / (D3DX_PI * 2)) * radian;
}
/// <summary>
/// �A���O���i�x���@�j���烉�W�A���i�ʓx�@�j�ւ̕ϊ����s���܂��B
/// </summary>
/// <param name="fAngle">�A���O���l�i�x���@�j</param>
/// <returns>���W�A���l�i�ʓx�@�̊p�x�j</returns>
float AngleToRadian(float fAngle)
{
	return(D3DX_PI * 2 / 360.0f) * fAngle;
}
