//===========================================
// 
// �X�e�[�W001[stage_001.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_001.h"		// �X�e�[�W

#include "../../../object/player.h"	// �v���C���[
#include "../../../object/base/object_2D.h"	// �|�b�v�A�b�v�p2D
#include "../../../object/base/object_3D.h"	// �|�b�v�A�b�v�p3D
#include "../../../object/base/object_X.h"	// �|�b�v�A�b�v�pX
#include "../../../object/base/object_fade.h"	// �t�F�[�h
#include "../../../object/base/object_billboard.h"	// �r���{�[�h
#include "../game_data.h"	// �Q�[���f�[�^
#include "../../../object/base/text.h"	// �e�L�X�g
#include "../../../object/obstacles_tall.h"	// ��Q��
#include "../../../object/obstacles_high.h"	// ��Q��
#include "../../../object/obstacles_low.h"	// ��Q��

#include <fstream>	// �t�@�C���̓ǂݍ��݂ɕK�v
#include <iostream>	// �t�@�C���̓ǂݍ��݂ɕK�v
#include "../scene_game_manager.h"		// �Q�[���}�l�[�W���[
namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_001::s_fGool = 20000.0f;	// �S�[������
		const string CStage_001::s_aStage = "data/STAGE/Stage_001.txt";		// �X�e�[�W�p�X
		const D3DXVECTOR3 CStage_001::s_PlayerFirstPos = { 0.0f, 0.0f, 0.0f };		// �v���C���[�ŏ��ʒu

		//============================================
		// �R���X�g
		//============================================
		CStage_001::CStage_001(CBase* scene) :
			CStage_Base(scene)
		{
			CManager* pManager = CManager::GetInstance();	// �S�̃}�l�[�W���[
			CCamera* pCamera = pManager->GetCamera();	// �J����
			CSound* pSound = pManager->GetSound();	// �T�E���h
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_STAGE_00);	// BGM���Đ�


			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾

			// �����o�ϐ��ݒ�
			m_bPose = false;
			m_fGool = s_fGool;

			// �v���C���[�ݒ�
			pPlayer->SetNormalUpdate(true);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetNormalDraw(true);	// �ʏ펞�`��ݒ�
			pPlayer->SetPoseDraw(true);		// �|�[�Y���`��ݒ�
			pPlayer->SetPos(s_PlayerFirstPos);	// �ʒu�������ʒu�ɖ߂�
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// ���[�V�����ݒ�
			pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
			pPlayer->SetMove(true);	// ������ݒ�
			pPlayer->SetLife(1);	// �̗͐ݒ�

			D3DXVECTOR3 cameraPos = D3DXVECTOR3(s_PlayerFirstPos.x, s_PlayerFirstPos.y + sinf(m_fCameraRot) * m_fCameraRange, s_PlayerFirstPos.z + cosf(m_fCameraRot) * m_fCameraRange);
			pCamera->SetPosV(cameraPos);	// �J�����ɓK��

			// �J��������
			pCamera->SetRotX(D3DX_PI - 2.0f);

			//�t�B�[���h����
			CObject3D* pField = nullptr;
			pField = CObject3D::create(
				D3DXVECTOR3(0.0f, 0.0f, s_fGool * 0.5f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 0.0f, 100.0f + 1000.0f));
			pField->SetBlock(100, static_cast<int>(s_fGool / 100.0f) + 1000);
			pField->SetTexture("data/TEXTURE/Load_000.png");

			// �X�e�[�W�ǂݍ���
			Load(s_aStage);
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CStage_001::~CStage_001()
		{

			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[
			CSound* pSound = pManager->GetSound();			// �T�E���h
			pSound->StopSound(CSound::SOUND_LABEL::SOUND_STAGE_00);	// BGM���~�߂�

			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

			pPlActiv->SetInUP(true);		// ����͐ݒ�
			pPlActiv->SetInDown(true);		// �����͐ݒ�
			pPlActiv->SetInLeft(true);		// �����͐ݒ�
			pPlActiv->SetInRight(true);	// �E���͐ݒ�
		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CStage_001::Update()
		{
			return CStage_Base::Update();;
		}
		void CStage_001::Draw() const
		{
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		bool CStage_001::GetPose()
		{

			CStage_Base::Draw();

			return m_bPose;
		}

		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_001>() {
			nsPrev::CBase* p = new CStage_001(this);
			// �����ŃQ�[���}�l�[�W���[�̃l�N�X�g�ɐ��������C���X�^���X��n��

			return p;
		}
	}
}