//===========================================
// 
// �X�e�[�W000[stage_000.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_000.h"		// �`���[�g���A���X�e�[�W
#include "../scene_game_stageselect.h"	// �X�e�[�W�I���V�[��
#include "../scene_game_manager.h"		// �Q�[���}�l�[�W���[

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
namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_000::s_fGool = 15000.0f;	// �S�[������
		const string CStage_000::s_aStage = "data/STAGE/Stage_000.txt";	// �`���[�g���A���̃|�b�v�A�b�v�̑傫��

		const float CStage_000::s_fTutorialRange = 200.0f;	// �`���[�g���A�������蔻��͈�
		// �`���[�g���A��
		const float CStage_000::s_fTutorial_000 = 2000.0f;		// �`���[�g���A���C�x���g
		const float CStage_000::s_fTutorial_001 = 4000.0f;		// �`���[�g���A���C�x���g
		const float CStage_000::s_fTutorial_002 = 6000.0f;		// �`���[�g���A���C�x���g
		const float CStage_000::s_fTutorial_003 = 8000.0f;		// �`���[�g���A���C�x���g

		const bool CStage_000::s_bCanShownTutorial_000 = false;	// �`���[�g���A���C�x���g
		const bool CStage_000::s_bCanShownTutorial_001 = false;		// �`���[�g���A���C�x���g
		const bool CStage_000::s_bCanShownTutorial_002 = false;		// �`���[�g���A���C�x���g
		const bool CStage_000::s_bCanShownTutorial_003 = false;		// �`���[�g���A���C�x���g

		const D3DXVECTOR3 CStage_000::s_TutorialPopupPos = { 1000.0f, 300.0f, 0.0f };	// �`���[�g���A���̃|�b�v�A�b�v�̈ʒu
		const D3DXVECTOR3 CStage_000::s_TutorialPopupSiz = { 300.0f, 200.0f, 0.0f };	// �`���[�g���A���̃|�b�v�A�b�v�̑傫��

		//============================================
		// �R���X�g
		//============================================
		CStage_000::CStage_000(CBase* scene) :
			CStage_Base(scene)
		{
			CManager* pManager = CManager::GetInstance();	// �S�̃}�l�[�W���[
			CCamera* pCamera = pManager->GetCamera();	// �J����
			CSound* pSound = pManager->GetSound();	// �T�E���h
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_STAGE_00);	// BGM���~�߂�

			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

			// �����o�ϐ��ݒ�
			m_bPose = false;	// �|�[�Y��Ԑݒ�
			m_fGool = s_fGool;	// �S�[�������ݒ�

			m_fTutorialRange = s_fTutorialRange;	// �`���[�g���A���C�x���g�����͈̔͏�����

			m_bCanShownTutorial_000 = s_bCanShownTutorial_000;	// �`���[�g���A���C�x���g�t���O
			m_bCanShownTutorial_001 = s_bCanShownTutorial_001;	// �`���[�g���A���C�x���g�t���O
			m_bCanShownTutorial_002 = s_bCanShownTutorial_002;	// �`���[�g���A���C�x���g�t���O
			m_bCanShownTutorial_003 = s_bCanShownTutorial_003;	// �`���[�g���A���C�x���g�t���O

			m_bHasShownTutorial_000 = false;	// �C�x���g���s�������ǂ���
			m_bHasShownTutorial_001 = false;	// �C�x���g���s�������ǂ���
			m_bHasShownTutorial_002 = false;	// �C�x���g���s�������ǂ���
			m_bHasShownTutorial_003 = false;	// �C�x���g���s�������ǂ���

			for (int nCnt = 0; nCnt < static_cast<int>(TUTORIAL::MAX); nCnt++)
			{
				m_pTutorealPopup[nCnt] = CObject2D::create(D3DXVECTOR3(s_TutorialPopupPos), D3DXVECTOR3(s_TutorialPopupSiz));// ����
				m_pTutorealPopup[nCnt]->SetPoseDraw(false);
				m_pTutorealPopup[nCnt]->SetNormalDraw(false);
				switch (static_cast<TUTORIAL>(nCnt))
				{
				case TUTORIAL::Tutorial_000:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_000.png");
					break;
				case TUTORIAL::Tutorial_001:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_001.png");
					break;
				case TUTORIAL::Tutorial_002:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_002.png");
					break;
				case TUTORIAL::Tutorial_003:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_003.png");
					break;
				default:
					Beep(1000, 300);
					break;
				}
			}

			// �v���C���[�ݒ�
			pPlayer->SetNormalUpdate(true);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetNormalDraw(true);	// �ʏ펞�`��ݒ�
			pPlayer->SetPoseDraw(true);		// �|�[�Y���`��ݒ�
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ʒu�������ʒu�ɖ߂�
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// ���[�V�����ݒ�
			pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
			pPlayer->SetMove(true);	// ������ݒ�
			pPlayer->SetLife(1);	// �̗͐ݒ�

			pPlActiv->SetInUP(false);		// ����͐ݒ�
			pPlActiv->SetInDown(false);		// �����͐ݒ�
			pPlActiv->SetInLeft(false);		// �����͐ݒ�
			pPlActiv->SetInRight(false);	// �E���͐ݒ�

			//�t�B�[���h����
			CObject3D* pField = nullptr;
			pField = CObject3D::create(
				D3DXVECTOR3(0.0f, 0.0f, s_fGool * 0.5f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 0.0f, 100.0f + 1000.0f));
			pField->SetBlock(100, static_cast<int>(s_fGool / 100.0f) + 1000);
			pField->SetTexture("data/TEXTURE/Load_000.png");

			// �J��������
			pCamera->SetRotX(1.3f);


			// �X�e�[�W�ǂݍ���
			Load(s_aStage);
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CStage_000::~CStage_000()
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
		nsPrev::CBase* CStage_000::Update()
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾
			CCamera* pCamera = pManager->GetCamera();		// �J�����擾
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�̈ʒu���擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �X�g���e�W�[�擾
			;
			bool bGoal = (dynamic_cast<CStage_Base::Stage_Goal_Strategy*>(CStage_Base::m_pStrategy));

			if (m_bPose == false &&
				bGoal != true)
			{
				// �`���[�g���A���C�x���g����
				if (playerPos.z > s_fGool &&
					playerPos.z < s_fGool + 3.0f)
				{
					return makeScene<CScen_Game_StageSelect>();
				}
				else if (playerPos.z < s_fTutorial_000 &&
					playerPos.z > s_fTutorial_000 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_000 == false)
					{
						pPlayer->SetMove(false);	// �������~�߂�
						pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
						pPlActiv->SetInLeft(true);		// �����͐ݒ�
						pPlActiv->SetInRight(true);	// �E���͐ݒ�
						pPlActiv->SetInUP(false);		// �����͐ݒ�
						pPlActiv->SetInDown(false);	// �E���͐ݒ�

						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��

						m_bCanShownTutorial_000 = true;		// �t���O�𗧂Ă�
					}
				}
				else if (playerPos.z < s_fTutorial_001 &&
					playerPos.z > s_fTutorial_001 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_001 == false)
					{
						pPlayer->SetMove(false);	// �������~�߂�
						pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
						pPlActiv->SetInLeft(false);		// �����͐ݒ�
						pPlActiv->SetInRight(false);	// �E���͐ݒ�
						pPlActiv->SetInUP(true);		// �����͐ݒ�
						pPlActiv->SetInDown(false);	// �E���͐ݒ�
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��
						m_bCanShownTutorial_001 = true;		// �t���O�𗧂Ă�
					}
				}
				else if (playerPos.z < s_fTutorial_002 &&
					playerPos.z > s_fTutorial_002 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_002 == false)
					{
						pPlayer->SetMove(false);	// �������~�߂�
						pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
						pPlActiv->SetInLeft(false);		// �����͐ݒ�
						pPlActiv->SetInRight(false);	// �E���͐ݒ�
						pPlActiv->SetInUP(false);		// �����͐ݒ�
						pPlActiv->SetInDown(true);	// �E���͐ݒ�

						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��
						m_bCanShownTutorial_002 = true;
					}
				}
				else if (playerPos.z < s_fTutorial_003 &&
					playerPos.z > s_fTutorial_003 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_003 == false)
					{
						pPlayer->SetMove(false);	// �������~�߂�
						pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��
						m_bCanShownTutorial_003 = true;
					}
				}

				// �`���[�g���A���C�x���g
				if (m_bCanShownTutorial_000 &&
					m_bHasShownTutorial_000 == false)
				{
					// ���ɓ��͂�����
					if (pKey->GetTrigger(DIK_A) ||
						pKey->GetTrigger(DIK_LEFT))
					{
						m_bHasShownTutorial_000 = true;
						pPlayer->SetMove(true);			// ������
						pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
						pPlActiv->InputLeft();	// ������
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					}

					if (pKey->GetTrigger(DIK_D) ||
						pKey->GetTrigger(DIK_RIGHT))
					{
						m_bHasShownTutorial_000 = true;
						pPlayer->SetMove(true);			// ������
						pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
						pPlActiv->InputRight();	// �E����
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					}
				}
				else if (m_bCanShownTutorial_001 &&
					m_bHasShownTutorial_001 == false)
				{
					// ���ɓ��͂�����
					if (pKey->GetTrigger(DIK_W) ||
						pKey->GetTrigger(DIK_UP) ||
						pKey->GetTrigger(DIK_SPACE))
					{
						m_bHasShownTutorial_001 = true;
						pPlayer->SetMove(true);			// ������
						pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
						pPlActiv->InputUP();	// �����
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					}
				}
				else if (m_bCanShownTutorial_002 &&
					m_bHasShownTutorial_002 == false)
				{
					// �E�ɓ��͂�����
					if (pKey->GetTrigger(DIK_S) ||
						pKey->GetTrigger(DIK_DOWN) ||
						pKey->GetTrigger(DIK_LSHIFT))
					{
						m_bHasShownTutorial_002 = true;
						pPlayer->SetMove(true);			// ������
						pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
						pPlActiv->InputDown();	// ������
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					}
				}
				else if (m_bCanShownTutorial_003 &&
					m_bHasShownTutorial_003 == false)
				{
					// �������͂�����
					if (pKey->GetTrigger())
					{
						m_bHasShownTutorial_003 = true;
						pPlayer->SetMove(true);			// ������
						pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					}
				}
			}

			return CStage_Base::Update();
		}
		void CStage_000::Draw() const
		{
			CStage_Base::Draw();
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		bool CStage_000::GetPose()
		{
			return m_bPose;
		}

		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_000>() {
			return new CStage_000(this);
		}
	}
}