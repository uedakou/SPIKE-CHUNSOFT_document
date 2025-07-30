//===========================================
// 
// �f�o�b�N�V�[��[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_debug.h"	// �f�o�b�N�V�[��
#include "../../../base/manager.h"		// �}�l�[�W���[
#include "../game_data.h"		// �Q�[���f�[�^
#include "../../../object/base/object_3D.h"	// �RD�I�u�W�F�N�g
#include "../../../object/base/text.h"	// �RD�I�u�W�F�N�g
#include "../../../object/obstacles_tall.h"	// ��Q��
#include "../../../object/obstacles_high.h"	// ��Q��
#include "../../../object/obstacles_low.h"	// ��Q��
#include "../scene_game_manager.h"		// �Q�[���}�l�[�W���[

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const bool CSceneDebug::s_bCameraFollowPlayer = true;
		const float CSceneDebug::s_fCameraRot = 2.6f;
		const float CSceneDebug::s_fGool = 2000.0f;
		//============================================
		// �R���X�g���N�^
		//============================================
		CSceneDebug::CSceneDebug(CBase* scene) :
			CStage_Base(scene)
		{
			CObject::ReleaseScene();	// �V�[�������[�X

			CPlayer* pPlayer = m_gameData->GetPlayer();
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

			
			m_bPose = false;	// �|�[�Y��Ԑݒ�
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
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();
			pCamera->SetRotX(1.3f);

			m_fCameraRot = s_fCameraRot;	// �J�������v���C���[��Ǐ]���邩�ǂ���

			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// �J�������v���C���[��Ǐ]���邩�ǂ���

			//�t�B�[���h����
			CObject3D* pField = nullptr;
			pField = CObject3D::create(
				D3DXVECTOR3(0.0f, 0.0f, s_fGool * 0.5f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 0.0f, 100.0f + 1000.0f));
			pField->SetBlock(100, static_cast<int>(s_fGool / 100.0f) + 1000);
			pField->SetTexture("data/TEXTURE/Glass000.png");

			// ��Q��
			CObstaclesToll::clate(D3DXVECTOR3(0.0f, 0.0f, 1000.0f));
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CSceneDebug::~CSceneDebug()
		{
			int a = 0;
		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CSceneDebug::Update()
		{
			//CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			//CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾
			//CCamera* pCamera = pManager->GetCamera();		// �J�����擾
			//CPlayer* pPlayer = m_gameData->GetPlayer();

			return CStage_Base::Update();;
			
			return this;
		}
		//============================================
		// �`��
		//============================================
		void CSceneDebug::Draw() const
		{
			return CStage_Base::Draw();;
		}

		//============================================
		// �|�[�Y���擾
		//============================================
		bool CSceneDebug::GetPose()
		{
			return false;
		}

		template<>
		nsPrev::CBase* CGameManager::makeScene<CSceneDebug>() {
			return new CSceneDebug(this);
		}
	}
}