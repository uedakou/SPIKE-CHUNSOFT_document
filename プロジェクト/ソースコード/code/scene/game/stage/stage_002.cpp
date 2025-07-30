//===========================================
// 
// �X�e�[�W002[stage_002.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_002.h"		// �X�e�[�W

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
#include "../scene_game_manager.h"		// �Q�[���}�l�[�W���[

#include <fstream>	// �t�@�C���̓ǂݍ��݂ɕK�v
#include <iostream>	// �t�@�C���̓ǂݍ��݂ɕK�v

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_002::s_fGool = 20000.0f;	// �S�[������
		const string CStage_002::s_aStage = "data/STAGE/Stage_001.txt";		// �X�e�[�W�p�X

		//============================================
		// �R���X�g
		//============================================
		CStage_002::CStage_002(CBase* scene) :
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
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ʒu�������ʒu�ɖ߂�
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// ���[�V�����ݒ�
			pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
			pPlayer->SetMove(true);	// ������ݒ�
			pPlayer->SetLife(1);	// �̗͐ݒ�

			// �J��������
			pCamera->SetRotX(1.3f);

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
		CStage_002::~CStage_002()
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
		nsPrev::CBase* CStage_002::Update()
		{



			return CStage_Base::Update();;
		}
		void CStage_002::Draw() const
		{
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		bool CStage_002::GetPose()
		{

			CStage_Base::Draw();

			return m_bPose;
		}

		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_002>() {
			return new CStage_002(this);
		}
	}
}