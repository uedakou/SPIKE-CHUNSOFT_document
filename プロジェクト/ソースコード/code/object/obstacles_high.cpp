//============================================
//
// ��Q��(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_high.h"// �n�C�h�I�u�W�F�N�g
#include "player.h"
/// <summary>
/// �f�X�g���N�^
/// </summary>
CObstaclesHigh::~CObstaclesHigh()
{
}
/// <summary>
/// ������
/// </summary>
bool CObstaclesHigh::Init()
{
	CObstacles::Init();
	return true;
}
/// <summary>
/// �I��
/// </summary>
void CObstaclesHigh::Uninit()
{
	CObstacles::Uninit();
}
/// <summary>
/// �X�V
/// </summary>
void CObstaclesHigh::Update()
{
	CObstacles::Update();
}
/// <summary>
/// �`��
/// </summary>
void CObstaclesHigh::Draw()
{
	CObstacles::Draw();
}
/// <summary>
/// �����蔻��
/// </summary>
void CObstaclesHigh::HitTest()
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
					if (player->IsSliding() != true)
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
CObstaclesHigh* CObstaclesHigh::clate(D3DXVECTOR3 pos)
{
	CObstaclesHigh* pHigh = new CObstaclesHigh();

	pHigh->SetPos(pos);
	pHigh->Init();	/// ������

	return pHigh;
}
CObstaclesHigh* CObstaclesHigh::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObstaclesHigh* pHigh = new CObstaclesHigh();

	pHigh->SetPos(pos);
	pHigh->SetRot(rot);
	pHigh->Init();	/// ������

	return pHigh;
}
/// <summary>
/// �R���X�g���N�^
/// </summary>
CObstaclesHigh::CObstaclesHigh()
{
	SetID(CModelX::Load("data/MODEL/Obstacles/Obstacles_High/Obstacles_High_000.x"));
}