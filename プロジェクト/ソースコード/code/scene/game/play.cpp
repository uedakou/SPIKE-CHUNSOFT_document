//===========================================
// 
// �Q�[���S�̏���[play.h]
// Auther:UedaKou
// 
//===========================================
#include "play.h"// �v���C�V�[��
#include "../../object/player.h"	// �v���C���[
#include "game_data.h"
#include "scene_game_manager.h"

namespace Scene {
	class CTitle;
	namespace Game {
		//============================================
		// �R���X�g���N�^
		//============================================
		Play::Play(CBase* scene) :
			CBase(*scene)
		{
			CObject::ReleaseScene();

			CPlayer* pPlayer = CPlayer::create();
			pPlayer->SetReleaseScene(false);
			//pPlayer->SetNormalDraw(false);
			//pPlayer->SetPoseDraw(false);
			m_gameData->SetPlayer(pPlayer);


			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			//pSound->PlaySound(CSound::SOUND_LABEL::SOUND_STAGE_00);
			bPause = false;
		}
		Play::~Play()
		{
			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			pSound->StopSound(CSound::SOUND_LABEL::SOUND_STAGE_00);
		}

		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* Play::Update()
		{
			CInputKeyboard* Kye = CManager::GetInstance()->GetInKey();
			if (Kye->GetTrigger(DIK_P))
			{// �|�[�Y
				bPause = bPause ? false : true;
			}
			// �|�[�Y��
			if (bPause)
			{
				if (Kye->GetTrigger(DIK_RETURN))
				{
					return nsPrev::CBase::makeScene<CTitle>();
				}
			}
			else
			{
				CameraController();	// �J�����R���g���[��

			}
//#ifdef _DEBUG
//
//			if (Kye->GetTrigger(DIK_Z))
//			{
//				m_nScore++;
//			}
//			else if (Kye->GetTrigger(DIK_X))
//			{
//				m_nScore--;
//			}
//#endif // !_DEBUG
//			string Score = to_string(m_nScore);
//			Score.insert(0, 4 - Score.length(), '0');
//
//			string text = "SCORE : " + Score;
//			if (m_pText != nullptr)
//			{
//				m_pText->SetText(text);
//			}

			return this;
		}
		//============================================
		// �`��
		//============================================
		void Play::Draw() const
		{
			//if (m_pText != nullptr)
			//{
			//	m_pText->Draw();
			//}
		}
		
		//============================================
		// �|�[�Y���擾
		//============================================
		bool Play::GetPose()
		{
			if (bPause == true)
			{
				return true;
			}
			return false;
		}
		//============================================
		// �J��������
		//============================================
		void Play::CameraController()
		{
			//CCamera* pCamera = CManager::GetInstance()->GetCamera();
			//if (pCamera->GetCameraControllreFpllow() == false)
			//{
			//	CObject* object[MAX_PRIORITY];
			//	CObject::GetAllObject(object);
			//	CObject* Next = nullptr;
			//	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
			//	{
			//		while (object[nCnt] != nullptr)
			//		{
			//			Next = object[nCnt]->GetNext();
			//			// �L�����N�^�[�Ȃ�
			//			if (object[nCnt]->GetType() == CObject::TYPE::CHARACTER)
			//			{
			//				// �v���C���[�Ȃ�
			//				if (static_cast<CCharacter*>(object[nCnt])->GetType() == CCharacter::TYPE::PLAYER)
			//				{
			//					// �J������ݒ�
			//					D3DXVECTOR3 posPlsyer = ((CPlayer*)object[nCnt])->GetPos();
			//					pCamera->SetCameraPosR(D3DXVECTOR3(posPlsyer));	// �����_���v���C���[�ɂ���
			//					D3DXVECTOR3 rotCumera = pCamera->GetCameraRot();	// �J�����̌������擾
			//					D3DXVECTOR3 posV;	// �J�����̎��_�v�Z�p

			//					posV.x = posPlsyer.x - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * sinf(rotCumera.y) * POS_CAMERA;
			//					posV.y = posPlsyer.y - sinf(rotCumera.x - (D3DX_PI * 0.5f)) * POS_CAMERA;
			//					posV.z = posPlsyer.z - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * cosf(rotCumera.y) * POS_CAMERA;

			//					pCamera->SetCameraPosV(D3DXVECTOR3(posV));	// �����_���v���C���[�ɂ���

			//					break;
			//				}
			//			}
			//			object[nCnt] = Next;
			//		}			

			//	}
			//}
		}

		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<Play>(/*CGameManager* pGameManager*/) {
			return new Play(this);
		}
	}
}