//===========================================
// 
// �Q�[���X�e�[�W�I��[scene_game_stageselect.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_stageselect.h"			// �X�e�[�W�Z���N�g
#include "../../object/base/object.h"		// �I�u�W�F�N�g
#include "../../object/base/object_3D.h"	// �I�u�W�F�N�g3d
#include "../../object/base/object_2D.h"	// �I�u�W�F�N�g2d
#include "../../base/input.h"				// ����
#include "../../object/player.h"			// �v���C���[
#include "game_data.h"						//�@�Q�[���f�[�^
#include "../scene_title.h"		// �^�C�g��

namespace Scene {
	class CTitle;
	namespace Game {
		// ���N���X
		class CSceneDebug;				// �f�o�b�O
		class CStage_000;				// �X�e�[�W000
		class CStage_001;				// �X�e�[�W001
		class CStage_002;				// �X�e�[�W001

		// �萔��`
		const D3DXVECTOR3 CScen_Game_StageSelect::s_SelectSiz = { 100.0f, 100.0f, 0.0f };	// ���͊J�n�J�E���g
		const D3DXVECTOR3 CScen_Game_StageSelect::s_SelectEvaluationSiz = { 300.0f, 100.0f, 0.0f };	// ���͊J�n�J�E���g

		CScen_Game_StageSelect::CScen_Game_StageSelect(CBase* scene) :
			CBase(*scene)
		{
			CObject::ReleaseScene();	// �V�[�������[�X
			CManager* pManager = CManager::GetInstance();	// �S�̃}�l�[�W���[
			CCamera* pCamera = pManager->GetCamera();	// �J����
			CSound* pSound = pManager->GetSound();	// �T�E���h
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_STAGE_SELECT_000);	// BGM���~�߂�

			m_bPose = false;	// �|�[�Y���
			m_nSetlect = 0;	// ���I��
			m_bNext = false;	// ���I���ς݂��ǂ���
			// �X�e�[�W���J��Ԃ�
			for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++ )
			{
				// �X�e�[�W�Z���N�g�쐬
				m_pStage[nCnt] = CObject2D::create(D3DXVECTOR3(SCREEN_W * 0.5f + 200.0f * nCnt, SCREEN_H * 0.5f, 0.0f), s_SelectSiz);
				switch (static_cast<Select>(nCnt))
				{
				case Select::STAGE_000:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_000.png");
					break;
				case Select::STAGE_001:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_001.png");
					break;
				case Select::STAGE_002:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_002.png");
					break;
				default:
					break;
				}
			}
			// ��ڂ̃T�C�Y��I���ς݂ɂ���
			m_pStage[0]->SetScl(D3DXVECTOR3(2.0f, 2.0f, 0.0f));

			// �X�e�[�W�]���쐬
			m_pStageEvaluation = CObject2D::create(6, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5 + 200.0f, 0.0f), s_SelectEvaluationSiz);
			m_pStageEvaluation->SetTexture("data/TEXTURE/Stor_000.png");	// �e�N�X�`��
			// �]��UV�ݒ�
			m_pStageEvaluation->SetUV({ 0.25f * m_gameData->m_nScore[0], 0.25f + 0.25f * m_gameData->m_nScore[0], 0.0f, 1.0f });

			// �w�i
			CObject2D* pBG = nullptr;
			pBG = CObject2D::create(2, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0));	// ����
			pBG->SetTexture("data/TEXTURE/BG_000.png");	// �e�N�X�`��

			pCamera->SetPosV(D3DXVECTOR3(0.0f, 100.0f, -400.0f));
			pCamera->SetRotX(1.3f);	// �J��������

			// �v���C���[�ݒ�
			CPlayer* pPlayer = m_gameData->GetPlayer();
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾
			pPlayer->SetNormalUpdate(false);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetPoseUpdate(false);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetNormalDraw(false);	// �ʏ펞�`��ݒ�
			pPlayer->SetPoseDraw(false);		// �|�[�Y���`��ݒ�
			pPlayer->SetMove(false);	// ���[�V�����̓�����ݒ�
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ʒu�������ʒu�ɖ߂�

					// �������
			CObject2D* m_pControlDescription;
			m_pControlDescription = CObject2D::create(4, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H - SCREEN_H / 10 * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H / 10, 0.0f));
			m_pControlDescription->SetTexture("data/TEXTURE/SelectedOption_StageSelect_000.png");
		}

		CScen_Game_StageSelect::~CScen_Game_StageSelect()
		{
			CManager* pManager = CManager::GetInstance();	// �S�̃}�l�[�W���[
			CSound* pSound = pManager->GetSound();	// �T�E���h
			pSound->StopSound(CSound::SOUND_LABEL::SOUND_STAGE_SELECT_000);	// BGM���~�߂�
		}

		nsPrev::CBase* CScen_Game_StageSelect::Update()
		{

			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[
			CInputKeyboard* pInKey = pManager->GetInKey();	// �L�[�{�[�h����
			CSound* pSound = pManager->GetSound();			// �T�E���h

			if (pInKey->GetTrigger(DIK_P))
			{
				m_bPose = !m_bPose;
			}
			if (m_bPose == false)
			{
				int nSetlectOld = m_nSetlect;	// ���ʒu���L��
				// �����͂�����
				if (pInKey->GetTrigger(DIK_A) ||
					pInKey->GetTrigger(DIK_LEFT))
				{
					// �I�������肳��Ă��Ȃ�������
					if (m_bNext == false)
					{
						// �I������߂�
						m_nSetlect--;
						// �ŏ��ȉ��Ȃ�߂�Ȃ��悤�ɂ���
						if (m_nSetlect < 0)
						{
							m_nSetlect = 0;
						}
						// �I���T�E���h�Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL::SE_CHOICE_000);
					}

				}
				// �E���͂�����
				else if (pInKey->GetTrigger(DIK_D) ||
					pInKey->GetTrigger(DIK_RIGHT))
				{
					// �I�������肳��Ă��Ȃ�������
					if (m_bNext == false)
					{
						// �I������i�߂�
						m_nSetlect++;
						// �ő�ȏ�Ȃ��ɐi�܂Ȃ��悤�ɂ���
						if (m_nSetlect >= static_cast<int>(Select::MAX))
						{
							m_nSetlect = static_cast<int>(Select::MAX) - 1;
						}
						// �I���T�E���h�Đ�
						pSound->PlaySoundA(CSound::SOUND_LABEL::SE_CHOICE_000);
					}
				}

				// �������͂�����
				if (pInKey->GetTrigger(DIK_RETURN) ||
					pInKey->GetTrigger(DIK_SPACE))
				{
					m_bNext = true;
					// ����T�E���h�Đ�
					pSound->PlaySoundA(CSound::SOUND_LABEL::SE_DECISION_000);
				}
				// �������͂�����
				if (pInKey->GetTrigger(DIK_Q))
				{
					return nsPrev::CBase::makeScene<CTitle>();
				}

#ifdef _DEBUG
				if (pInKey->GetTrigger(DIK_W))
				{
					m_gameData->m_nScore[m_nSetlect]++;
					if (m_gameData->m_nScore[m_nSetlect] > 3)
					{
						m_gameData->m_nScore[m_nSetlect] = 3;
					}
					// �]��UV�ݒ�
					m_pStageEvaluation->SetUV({ 0.25f * m_gameData->m_nScore[m_nSetlect], 0.25f + 0.25f * m_gameData->m_nScore[m_nSetlect], 0.0f, 1.0f });
				}
				if (pInKey->GetTrigger(DIK_S))
				{
					m_gameData->m_nScore[m_nSetlect]--;
					if (m_gameData->m_nScore[m_nSetlect] < 0)
					{
						m_gameData->m_nScore[m_nSetlect] = 0;
					}
					// �]��UV�ݒ�
					m_pStageEvaluation->SetUV({ 0.25f * m_gameData->m_nScore[m_nSetlect], 0.25f + 0.25f * m_gameData->m_nScore[m_nSetlect], 0.0f, 1.0f });
				}

#endif // !_DEBUG




				//���I���ƌ��I�����������
				if (m_nSetlect != nSetlectOld)
				{
					// �I����������傫������
					m_pStage[m_nSetlect]->SetScl(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
					// �I�����Ă�����������������
					m_pStage[nSetlectOld]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 0.0f
					));
					// ���ɑI��������
					if (m_nSetlect < nSetlectOld)
					{
						// ���Ɉړ�������
						for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++)
						{
							m_pStage[nCnt]->AddPosX(200.0f);
						}
					}
					// �E�ɑI��������
					else
					{
						// �E�Ɉړ�������
						for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++)
						{
							m_pStage[nCnt]->AddPosX(-200.0f);
						}
					}
					// �]��UV�ݒ�
					m_pStageEvaluation->SetUV({ 0.25f * m_gameData->m_nScore[m_nSetlect], 0.25f + 0.25f * m_gameData->m_nScore[m_nSetlect], 0.0f, 1.0f });
				}

				if (m_bNext == true)
				{// �I�������肵����
					switch (static_cast<Select>(m_nSetlect))
					{
					case Select::STAGE_000:

						return makeScene<CStage_000>();
						break;
					case Select::STAGE_001:
						return makeScene<CStage_001>();
						break;
					case Select::STAGE_002:
						return makeScene<CStage_002>();
						break;
					default:
						break;
					}
				}
			}
			return this;
		}

		void CScen_Game_StageSelect::Draw() const
		{
		}

		bool CScen_Game_StageSelect::GetPose()
		{
			return m_bPose;
		}
		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CScen_Game_StageSelect>() {
			return new CScen_Game_StageSelect(this);
		}
	}
}