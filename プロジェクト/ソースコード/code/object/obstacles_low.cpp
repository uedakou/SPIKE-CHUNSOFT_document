//============================================
//
// ��Q��(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_low.h"// ���E�I�u�W�F�N�g
#include "player.h"

/// <summary>
/// �f�X�g���N�^
/// </summary>
CObstaclesLow::~CObstaclesLow()
{
}
/// <summary>
/// ������
/// </summary>
bool CObstaclesLow::Init()
{
	CObstacles::Init();
	return true;
}
/// <summary>
/// �I��
/// </summary>
void CObstaclesLow::Uninit()
{
	CObstacles::Uninit();
}
/// <summary>
/// �X�V
/// </summary>
void CObstaclesLow::Update()
{
	CObstacles::Update();
}
/// <summary>
/// �`��
/// </summary>
void CObstaclesLow::Draw()
{
	CObstacles::Draw();
}
/// <summary>
/// �����蔻��
/// </summary>
void CObstaclesLow::HitTest()
{
	CObject* pObject[MAX_PRIORITY];
	CObject* pNext = nullptr;
	CObject::GetAllObject(pObject);
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		while (pObject[nCnt] != nullptr)
		{
			pNext = pObject[nCnt]->GetNext();
			CPlayer* player = dynamic_cast<CPlayer*>(pObject[nCnt]);
			if (player)
			{
				D3DXVECTOR3 PLpos = player->GetPos();
				D3DXVECTOR3 PLcol = player->GetCollisionSiz();
				D3DXVECTOR3 pos = GetPos();
				if (PLpos.z + PLcol.z * 0.5f > pos.z - s_Collision.z * 0.5f &&
					PLpos.z - PLcol.z * 0.5f < pos.z + s_Collision.z * 0.5f &&
					PLpos.x + PLcol.x * 0.5f > pos.x - s_Collision.x * 0.5f &&
					PLpos.x - PLcol.x * 0.5f < pos.x + s_Collision.x * 0.5f)
				{
					if (player->IsJanp() != true)
					{
						player->Hit(1);
					}
				}
			}
			pObject[nCnt] = pNext;
		}
	}
}
/// <summary>
/// ����
/// </summary>
/// <param name="pos">�����ʒu</param>
/// <returns>���������I�u�W�F�N�g</returns>
CObstaclesLow* CObstaclesLow::clate(D3DXVECTOR3 pos)
{
	CObstaclesLow* pLow = new CObstaclesLow();

	pLow->SetPos(pos);
	pLow->Init();	/// ������

	return pLow;
}
CObstaclesLow* CObstaclesLow::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObstaclesLow* pLow = new CObstaclesLow();

	pLow->SetPos(pos);
	pLow->SetRot(rot);
	pLow->Init();	/// ������

	return pLow;
}
/// <summary>
/// �R���X�g���N�^
/// </summary>
CObstaclesLow::CObstaclesLow()
{
	SetID(CModelX::Load("data/MODEL/Obstacles/Obstacles_Low/Obstacles_Low_000.x"));
}