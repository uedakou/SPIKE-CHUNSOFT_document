//============================================
//
// �v���C���[[obstacles.cpp]
// Author:Uedakou
// 
//============================================
#include"obstacles.h"	// �I�u�W�F�N�g��Q��
#include "player.h"		// �v���C���[
#include "base/character.h"	// �L�����N�^�[




const D3DXVECTOR3 CObstacles::s_Collision = { 20.0f, 50.0f, 20.0f };
/// <summary>
/// �R���X�g���N�^
/// </summary>
CObstacles::CObstacles()
{
	SetType(CObjectX::TYPE::OBSTACLES);	// ��ނ���Q���ɐݒ�
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CObstacles::~CObstacles()
{
}
/// <summary>
/// ����������
/// </summary>
bool CObstacles::Init()
{
	CObjectX::Init();
	return true;
}
/// <summary>
/// �I������
/// </summary>
void CObstacles::Uninit()
{
	CObjectX::Uninit();
}
/// <summary>
/// �X�V
/// </summary>
void CObstacles::Update()
{
	CObjectX::Update();
	HitTest();
}
/// <summary>
/// �`��
/// </summary>
void CObstacles::Draw()
{
	CObjectX::Draw();
}