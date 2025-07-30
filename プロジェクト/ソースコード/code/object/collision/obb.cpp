//=================================
// 
// �L�����E�{�b�N�X �N���X�@obb.cpp
//outher kida ibuki 
// 
//==================================

#include "obb.h"
//========================================
// �R���X�g���N�^
//========================================
OBB::OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfWidths, const D3DXMATRIX& rotationMatrix)
{
	this->center = center;
	this->halfWidths = halfWidths;

	// ��]�s�񂩂烍�[�J������ݒ�
	axes[0] = D3DXVECTOR3(rotationMatrix._11, rotationMatrix._12, rotationMatrix._13);  // x��
	axes[1] = D3DXVECTOR3(rotationMatrix._21, rotationMatrix._22, rotationMatrix._23);  // y��
	axes[2] = D3DXVECTOR3(rotationMatrix._31, rotationMatrix._32, rotationMatrix._33);  // z��

}
//========================================
// ���_���擾
//========================================
D3DXVECTOR3 OBB::GetVertex(int index) const
{
	D3DXVECTOR3 vertex = center;

	int signX = (index & 1) ? 1 : -1;
	int signY = (index & 2) ? 1 : -1;
	int signZ = (index & 4) ? 1 : -1;

	vertex += axes[0] * (signX * halfWidths.x);
	vertex += axes[1] * (signY * halfWidths.y);
	vertex += axes[2] * (signZ * halfWidths.z);

	return vertex;
}
//========================================
// OBB���m�̏Փ˔���
//========================================
bool OBB::CheckOverlap(const OBB& other) const
{
    D3DXVECTOR3 axesToTest[15];
    int axisIndex = 0;

    // ���g�Ƒ���OBB�̎�
    for (int i = 0; i < 3; ++i) 
    {
        axesToTest[axisIndex++] = axes[i];
        axesToTest[axisIndex++] = other.axes[i];
    }

    // ���̃N���X��
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j) 
        {
            D3DXVECTOR3 crossAxis;
            D3DXVec3Cross(&crossAxis, &axes[i], &other.axes[j]);
            if (D3DXVec3Length(&crossAxis) > 0.0001f)
            { // �L���Ȏ�
                axesToTest[axisIndex++] = crossAxis;
            }
        }
    }

    // ���S�Ԃ̋���
    D3DXVECTOR3 t = other.center - center;

    // ���������Ƃɔ���
    for (int i = 0; i < axisIndex; ++i)
    {
        const D3DXVECTOR3& axis = axesToTest[i];
        D3DXVECTOR3 normAxis;
        D3DXVec3Normalize(&normAxis, &axis);

        // �eOBB�����ɓ��e
        float projection1 = ProjectOntoAxis(normAxis);
        float projection2 = other.ProjectOntoAxis(normAxis);
        float centerDistance = fabs(D3DXVec3Dot(&t, &normAxis));

        // ���e���������Ă���ꍇ
        if (centerDistance > projection1 + projection2)
        {
            return false;
        }
    }

    return true;  // �������Ă��Ȃ� -> �Փ�
}
//========================================
// �w�莲�ւ̓��e�������v�Z
//========================================
float OBB::ProjectOntoAxis(const D3DXVECTOR3& axis) const
{
    return fabs(D3DXVec3Dot(&axes[0], &axis) * halfWidths.x) +
        fabs(D3DXVec3Dot(&axes[1], &axis) * halfWidths.y) +
        fabs(D3DXVec3Dot(&axes[2], &axis) * halfWidths.z);
}

#if 0
// �g����
CObject* pTopObject[NUM_MAX_PRIORITY];
CObject::GetObj(pTopObject);
for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
{
	//�I�u�W�F�N�g�擾
	CObject* pObj = pTopObject[nPriority];

	//��ނ̎擾
	while (pObj != nullptr)
	{
		CObject::TYPE type = pObj->GetType();
		CObject* pNext = pObj->GetNext(); // ���̃|�C���^���擾
		if (type == CObject::TYPE::ENEMY_X)
		{
			CEnemyX* pEnemy = (CEnemyX*)pObj; //�_�E���L���X�g
			D3DXVECTOR3 enemyPos = pEnemy->GetPos();
			D3DXVECTOR3 enemySize = pEnemy->GetSize();
			// OBB1��OBB2��������
			D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // �G�̒��S�_�ƃT�C�Y
			D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // �v���C���[�̒��S�_�ƃT�C�Y

			D3DXMATRIX rotation1, rotation2;
			D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
			D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

			OBB obb1(center1, halfWidths1, rotation1);
			OBB obb2(center2, halfWidths2, rotation2);

			// �Փ˔���
			if (obb1.CheckOverlap(obb2))
			{
				//std::cout << "OBB�͌������Ă��܂��I" << std::endl;
			}
			else
			{
				//std::cout << "OBB�͌������Ă��܂���B" << std::endl;
			}

		}

		pObj = pNext; // �I�u�W�F�N�g�̃|�C���^�����ɐi�߂�
	}
}


#endif