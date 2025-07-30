//============================================
//
// �A�C�e��(����)[scroll.cpp]
// Author:Uedakou
// 
//============================================
#include "scroll.h"	// �g�[���I�u�W�F�N�g
#include "player.h"	// �v���C���[

const D3DXVECTOR3 CScroll::s_Collision = { 100.0f, 100.0f, 200.0f };
/// <summary>
/// �f�X�g���N�^
/// </summary>
CScroll::~CScroll()
{
}
/// <summary>
/// ������
/// </summary>
bool CScroll::Init()
{
	CObjectX::Init();
	return true;
}
/// <summary>
/// �I��
/// </summary>
void CScroll::Uninit()
{
	CObjectX::Update();
}
/// <summary>
/// �X�V
/// </summary>
void CScroll::Update()
{
	AddRotY(0.1f);
	CObjectX::Update();
}
/// <summary>
/// �`��
/// </summary>
void CScroll::Draw()
{
	CObjectX::Draw();
}
/// <summary>
/// ����
/// </summary>
/// <param name="pos">�����ʒu</param>
/// <returns>��������Q��</returns>
CScroll* CScroll::clate(D3DXVECTOR3 pos)
{
	CScroll* pToll = new CScroll();

	pToll->SetPos(pos);
	pToll->Init();	/// ������

	return pToll;
}
CScroll* CScroll::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CScroll* pToll = new CScroll();

	pToll->SetPos(pos);
	pToll->SetRot(rot);
	pToll->Init();	/// ������

	return pToll;
}
/// <summary>
/// �R���X�g���N�^
/// </summary>
CScroll::CScroll()
{
	SetID(CModelX::Load("data/MODEL/Scroll/Scroll_000.x"));
}