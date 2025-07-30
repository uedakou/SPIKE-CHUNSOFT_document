//============================================
//
// �v���C���[[player.cpp]
// Author:Uedakou
// 
//============================================
#include "player.h"	// �v���C���[
#include "../base/manager.h"	// �}�l�[�W���[
#include "enemy.h"	// �G�l�~�[
#include "../scene/scene_base.h"	// �V�[���x�[�X
#include <strsafe.h>
#include "collision/obb.h"		// OBB

#define PlayerMove true

//const int CPlayer::s_nLife = 1;			// �v���C���[���C�t
const float CPlayer::s_fSpeed = 20.0f;	// �v���C���[���x
const bool CPlayer::s_bMove = true;		// �v���C���[�������œ������ǂ���
const float CPlayer::s_fLane = 200.0f;	// ���C���̕�
const X CPlayer::s_Collision = { { 0.0f, 0.0f, 0.0f }, { 0.0f ,0.0f, 0.0f },{ 10.0f, 10.0f, 70.0f } };	// �R���W�����傫��
const float CPlayer::s_fGravity = 1.0f;	// �d��
const float CPlayer::s_fJanp = 15.0f;	// �W�����v��

//============================================
// �R���X�g
//============================================
CPlayer::CPlayer()
{
	SetLife(s_nLife);
	m_fSpeed = s_fSpeed;	// �������x�ݒ�
	m_bMove = s_bMove;
	m_fLane = s_fLane;

	m_bSliding = false;	// �W�����v�\��
	m_bJanp = false;	// �W�����v�\��
	SetAttcak(1);

	m_pActivityStrategy = new PlayerNomarActivity(this);

	m_pEffect = nullptr;
}
//============================================
// �f�X�g��
//============================================
CPlayer::~CPlayer()
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect->DeathFlag();
		m_pEffect = nullptr;
	}
}
//============================================
// ������
//============================================
bool CPlayer::Init()
{
	//m_obje[0] = CObjectX::create(pos, rot, siz, CObjectX::TYPE_X_PLAYER);
	CObjectMotion::Load(PLAYER_MOTIONFILE_A);
	CCharacter::Init();
	CCharacter::SetCollisionX(s_Collision);
	CObjectMotion::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	//SetMotion(1);
	SetLife(s_nLife);
	return true;
}
//============================================
// �I��
//============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}
//============================================
// �X�V
//============================================
void CPlayer::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKey = pManager->GetInKey();


	// �d��
	AddMovePosY(-s_fGravity);
	D3DXVECTOR3 pos = GetPos();
	// �����ݒ�
	if (pos.y <= 0.0f)
	{
		SetPosY(0.0f);
		SetMovePosY(0.0f);
	}

	// �����ړ���true�Ȃ�
	if (m_bMove == true)
	{
		// m_fSpeed�i�߂�

		AddPosZ(m_fSpeed);
	}

	// ��ɓ��͂�����
	if (pKey->GetTrigger(DIK_W) ||
		pKey->GetTrigger(DIK_UP) ||
		pKey->GetTrigger(DIK_SPACE))
	{
		m_pActivityStrategy->InputUP();
	}
	// ���ɓ��͂�����
	else if (pKey->GetTrigger(DIK_S) ||
		pKey->GetTrigger(DIK_DOWN) ||
		pKey->GetTrigger(DIK_LSHIFT))
	{
		m_pActivityStrategy->InputDown();
	}
	// ���ɓ��͂�����
	else if (pKey->GetTrigger(DIK_A) ||
		pKey->GetTrigger(DIK_LEFT))
	{
		m_pActivityStrategy->InputLeft();
	}
	// �E�ɓ��͂�����
	else if (pKey->GetTrigger(DIK_D) ||
		pKey->GetTrigger(DIK_RIGHT))
	{
		m_pActivityStrategy->InputRight();
	}
	// �X�V
	ActivityStrategy* p = m_pActivityStrategy->Update();
	// �Ԃ�l���ς���Ă�����
	if (p != m_pActivityStrategy)
	{
		// ����ւ���
		delete m_pActivityStrategy;
		m_pActivityStrategy = p;
	}

	CCharacter::Update();
}
//============================================
// �`��
//============================================
void CPlayer::Draw()
{
	CCharacter::Draw();
}
//============================================
// �q�b�g����
//============================================
void CPlayer::Hit(int nDamage)
{
	CCharacter::Hit(nDamage);
}
void CPlayer::Hit(int nCntInvincible, int nDamage)
{
}
void CPlayer::Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage)
{
}
//============================================
// ����
//============================================
CPlayer* CPlayer::create()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}
//============================================
// �ړ�����
//============================================
void CPlayer::MoveAttenuation()
{
	CCharacter::MoveAttenuation();
}
//============================================
// ���[�v���Ȃ����[�V�����̎��̃��[�V����
//============================================
int CPlayer::GetNextMotion()
{
	D3DXVECTOR3 move = GetMovePos();
	if (GetLife() <= 0)
	{
		// ���S���[�V����
		//return static_cast<int>(Motion::ACTIVITY_DETHILoop); ;
	}
	else
	{
		if (GetMotion() == static_cast<int>(Motion::ACTIVITY_JANP))
		{
			return static_cast<int>(Motion::ACTIVITY_MOVE);
		}
	}

	return static_cast<int>(Motion::ACTIVITY_NEUTRAL);
}
/// <summary>
/// ���X�V
/// </summary>
/// <returns>this�ȊO�ŃX�g���e�W�[�`�F���W</returns>
CPlayer::ActivityStrategy* CPlayer::ActivityStrategy::Update()
{
	switch (m_type)
	{
		//����`�F���W
	case CPlayer::ActivityStrategy::Type::Ran:
		return new PlayerNomarActivity(m_pPrimary);
		break;
		//���[���`�F���W
	case CPlayer::ActivityStrategy::Type::LaneChangeL:
		return new PlayerLaneChangeActivity(m_pPrimary, PlayerLaneChangeActivity::LR::L);
		break;
	case CPlayer::ActivityStrategy::Type::LaneChangeR:
		return new PlayerLaneChangeActivity(m_pPrimary, PlayerLaneChangeActivity::LR::R);
		break;
		//�W�����v
	case CPlayer::ActivityStrategy::Type::Janp:
		return new PlayerJanpActivity(m_pPrimary);
		break;
		//�X���C�f�B���O
	case CPlayer::ActivityStrategy::Type::Sliding:
		return new PlayerSlidingActivity(m_pPrimary);
		break;
	default:
		// �����Ȃ���Α���
		return this;
		break;
	}

}
/// <summary>
/// �ʏ펞�X�g���e�W�[�R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
CPlayer::PlayerNomarActivity::PlayerNomarActivity(CPlayer* player):
	ActivityStrategy(player)
{
	// ���胂�[�V�����ɐݒ�
	m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_MOVE));
}
/// <summary>
/// �ʏ펞�X�g���e�W�[�f�X�g���N�^
/// </summary>
CPlayer::PlayerNomarActivity::~PlayerNomarActivity()
{
}
/// <summary>
/// �ʏ펞�W�����v���͏���
/// </summary>
void CPlayer::PlayerNomarActivity::InputUP()
{
	if (m_bInUP)
	{
		m_type = Type::Janp;
	}
}
/// <summary>
/// �ʏ펞�X���C�f�B���O����
/// </summary>
void CPlayer::PlayerNomarActivity::InputDown()
{
	if (m_bInDown)
	{
		m_type = Type::Sliding;
	}
}
/// <summary>
/// �ʏ펞�����͏���
/// </summary>
void CPlayer::PlayerNomarActivity::InputLeft()
{
	if (m_bInLeft)
	{
		m_type = Type::LaneChangeL;
	}
}
/// <summary>
/// �ʏ펞���͉E����
/// </summary>
void CPlayer::PlayerNomarActivity::InputRight()
{
	if (m_bInRight)
	{
		m_type = Type::LaneChangeR;
	}
}
/// <summary>
/// ���[���`�F���W���R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
/// <param name="lr">���E</param>
CPlayer::PlayerLaneChangeActivity::PlayerLaneChangeActivity(CPlayer* player, LR lr) :
	ActivityStrategy(player)
{
	m_LR = lr;			// ���E�ړ������ݒ�
	m_type = Type::Ran;	// ���A�N�V����������
	m_nCnt = 0;			// �A�N�V�����J�E���g������

	if (lr == LR::L)
	{
		//m_pPrimary->AddPosX(-m_pPrimary->m_fLane);	// ���Ɉړ�
		float posX = m_pPrimary->GetPosX();	// �v���C���[�̈ʒu�擾
		// �v���C���[�����[���O�ɏo�Ă�����
		if (posX > -m_pPrimary->m_fLane)
		{
			m_nCnt = s_nCnt;
		}

	}
	else
	{
		//m_pPrimary->AddPosX(m_pPrimary->m_fLane);	// �E�Ɉړ�
		float posX = m_pPrimary->GetPosX();	// �v���C���[�̈ʒu�擾
		// �v���C���[�����[���O�ɏo�Ă�����
		if (posX < m_pPrimary->m_fLane)
		{
			m_nCnt = -s_nCnt;
		}
	}
}
/// <summary>
/// ���[���`�F���W���f�X�g���N�^
/// </summary>
CPlayer::PlayerLaneChangeActivity::~PlayerLaneChangeActivity()
{
}
/// <summary>
/// ���[���`�F���W���X�V
/// </summary>
/// <returns></returns>
CPlayer::ActivityStrategy* CPlayer::PlayerLaneChangeActivity::Update()
{
	// �O�Ɍ������P����
	int nRot = (m_nCnt < 0) - (m_nCnt > 0);
	m_nCnt += nRot;
	m_pPrimary->AddPosX(s_fLane / s_nCnt * nRot);


	if (m_nCnt == 0)
	{
		//m_pPrimary->AddPosX(s_fLane);
		return ActivityStrategy::Update();
	}
	return this;
}
/// <summary>
/// ���[���`�F���W���W�����v����
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputUP()
{
}
/// <summary>
/// ���[���`�F���W���X���C�e�B���O����
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputDown()
{
}
/// <summary>
/// ���[���`�F���W��������
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputLeft()
{
}
/// <summary>
/// ���[���`�F���W���E����
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputRight()
{
}
/// <summary>
/// �W�����v���R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
CPlayer::PlayerJanpActivity::PlayerJanpActivity(CPlayer* player) :
	ActivityStrategy(player)
{
	m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_JANP));	// ���[�V�����ݒ�
	m_pPrimary->m_bJanp = true;	// �W�����v�����ǂ����ݒ�
	m_type = Type::Ran;			// ���𑖂��
	m_pPrimary->AddMovePosY(s_fJanp);
}
/// <summary>
/// �W�����v���f�X�g���N�^
/// </summary>
CPlayer::PlayerJanpActivity::~PlayerJanpActivity()
{
	m_pPrimary->m_bJanp = false;	// �W�����v�����ǂ����ݒ�
}
/// <summary>
/// �W�����v���X�V
/// </summary>
/// <returns></returns>
CPlayer::ActivityStrategy* CPlayer::PlayerJanpActivity::Update()
{
	// ���n������ʏ�ɕς���
	if (m_pPrimary->GetPosY() <= 0.0f)
	{
		return ActivityStrategy::Update();
	}
	return this;
}
/// <summary>
/// �W�����v���W�����v����
/// </summary>
void CPlayer::PlayerJanpActivity::InputUP()
{
}
// �W�����v���X���C�f�B���O����
void CPlayer::PlayerJanpActivity::InputDown()
{
}
/// <summary>
/// �W�����v��������
/// </summary>
void CPlayer::PlayerJanpActivity::InputLeft()
{
}
/// <summary>
/// �W�����v���E����
/// </summary>
void CPlayer::PlayerJanpActivity::InputRight()
{
}
/// <summary>
/// �X���C�f�B���O���R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
CPlayer::PlayerSlidingActivity::PlayerSlidingActivity(CPlayer* player) :
	ActivityStrategy(player)
{
	m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_SLIDING));	// ���[�V�����ݒ�
	m_pPrimary->m_bSliding = true;	// �X���C�f�B���O�����ǂ����ݒ�
	m_type = Type::Ran;			// ���𑖂��
	m_nCnt = 0;					// �J�E���g������
}
/// <summary>
/// �X���C�f�B���O���f�X�g���N�^
/// </summary>
CPlayer::PlayerSlidingActivity::~PlayerSlidingActivity()
{
	m_pPrimary->m_bSliding = false;	// �X���C�f�B���O�����ǂ����ݒ�
}
/// <summary>
/// �X���C�e�B���O���A�b�v�f�[�g
/// </summary>
/// <returns></returns>
CPlayer::ActivityStrategy* CPlayer::PlayerSlidingActivity::Update()
{
	m_nCnt++;
	if (m_nCnt >= s_nCnt)
	{
		return ActivityStrategy::Update();
	}
	return this;
}
/// <summary>
/// �X���C�f�B���O���W�����v����
/// </summary>
void CPlayer::PlayerSlidingActivity::InputUP()
{
}
/// <summary>
/// �X���C�f�B���O���X���C�e�B���O����
/// </summary>
void CPlayer::PlayerSlidingActivity::InputDown()
{
}
/// <summary>
/// �X���C�f�B���O��������
/// </summary>
void CPlayer::PlayerSlidingActivity::InputLeft()
{
}
/// <summary>
/// �X���C�f�B���O���E����
/// </summary>
void CPlayer::PlayerSlidingActivity::InputRight()
{
}