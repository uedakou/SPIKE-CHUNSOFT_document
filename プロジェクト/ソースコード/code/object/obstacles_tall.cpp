//============================================
//
// ��Q��(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_tall.h"	// �g�[���I�u�W�F�N�g
#include "player.h"

/// <summary>
/// �f�X�g���N�^
/// </summary>
CObstaclesToll::~CObstaclesToll()
{
}
/// <summary>
/// ������
/// </summary>
bool CObstaclesToll::Init()
{
	CObstacles::Init();
	return true;
}
/// <summary>
/// �I��
/// </summary>
void CObstaclesToll::Uninit()
{
	CObstacles::Update();
}
/// <summary>
/// �X�V
/// </summary>
void CObstaclesToll::Update()
{
	CObstacles::Update();
}
/// <summary>
/// �`��
/// </summary>
void CObstaclesToll::Draw()
{
	CObstacles::Draw();
}
/// <summary>
/// �����蔻��
/// </summary>
void CObstaclesToll::HitTest()
{
	CObject* pObject[MAX_PRIORITY];
	CObject* pNext = nullptr;
	CObject::GetAllObject(pObject);
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		while (pObject[nCnt] != nullptr)
		{
			pNext = pObject[nCnt]->GetNext();
			if (CPlayer* player = dynamic_cast<CPlayer*>(pObject[nCnt]))
			{
				D3DXVECTOR3 PLpos = player->GetPos();
				D3DXVECTOR3 PLcol = player->GetCollisionSiz();
				D3DXVECTOR3 pos = GetPos();

				if (PLpos.z + PLcol.z * 0.5f > pos.z - s_Collision.z * 0.5f &&
					PLpos.z - PLcol.z * 0.5f < pos.z + s_Collision.z * 0.5f &&
					PLpos.x + PLcol.x * 0.5f > pos.x - s_Collision.x * 0.5f &&
					PLpos.x - PLcol.x * 0.5f < pos.x + s_Collision.x * 0.5f)
				{
					player->Hit(1);
				}
				break;
			}
			pObject[nCnt] = pNext;
		}
	}
}
/// <summary>
/// ����
/// </summary>
/// <param name="pos">�����ʒu</param>
/// <returns>��������Q��</returns>
CObstaclesToll* CObstaclesToll::clate(D3DXVECTOR3 pos)
{
	CObstaclesToll* pToll = new CObstaclesToll();

	pToll->SetPos(pos);
	pToll->Init();	/// ������

	return pToll;
}
CObstaclesToll* CObstaclesToll::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObstaclesToll* pToll = new CObstaclesToll();

	pToll->SetPos(pos);
	pToll->SetRot(rot);
	pToll->Init();	/// ������

	return pToll;
}
/// <summary>
/// �R���X�g���N�^
/// </summary>
CObstaclesToll::CObstaclesToll()
{
	SetID(CModelX::Load("data/MODEL/Obstacles/Obstacles_Tall/Obstacles_Tall_000.x"));
}