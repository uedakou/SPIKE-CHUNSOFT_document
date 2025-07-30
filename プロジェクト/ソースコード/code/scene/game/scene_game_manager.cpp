//===========================================
// 
// �Q�[���}�l�[�W���[[scene_game_manager.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_manager.h"	// �Q�[���}�l�[�W���[	
#include "game_data.h"			// �Q�[���f�[�^

#define g_bDebug 1
namespace nsThis = Scene::Game;
namespace Scene {
	namespace Game {
		class Play;						// �Q�[���S�̏���
		class CSceneDebug;				// �f�o�b�O
		class CStage_Tutorial;			// �`���[�g���A��
		class CScen_Game_StageSelect;	// �X�e�[�W�I��
		//============================================
		// �R���X�g���N�^
		//============================================
		CGameManager::CGameManager(nsPrev::CBase* scene) :
			CBase(scene, new CGameData())

		{

			m_pScene = makeScene<Play>();
#if g_bDebug
			m_pStageController = makeScene<CScen_Game_StageSelect>();
#else 
			m_pStageController = makeScene<CSceneDebug>(m_gameData);
#endif // 0
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CGameManager::~CGameManager()
		{
			if (m_pScene != nullptr)
			{
				delete m_pScene;
			}
			if (m_pStageController != nullptr)
			{
				delete m_pStageController;
			}
			if (m_gameData != nullptr)
			{
				delete m_gameData;
			}
		}

		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CGameManager::Update()
		{
			if (m_pScene != nullptr)
			{
				auto pBaseScene = m_pScene->Update();
			}
			if (m_pStageController != nullptr)
			{
				auto pBaseScene = m_pStageController->Update();
				if (pBaseScene != m_pStageController)
				{
					delete m_pStageController;

					auto pBaseScene2 = dynamic_cast<CBase*>(pBaseScene);
					if (pBaseScene2 != nullptr)
					{
						m_pStageController = pBaseScene2;
						return this;
					}
					else
					{
						m_pStageController = nullptr;
						return pBaseScene;
					}
				}
			}
			return this;
		}
		//============================================
		// �`��
		//============================================
		void CGameManager::Draw() const
		{
			if (m_pScene != nullptr)
			{
				m_pScene->Draw();
			}
			if (m_pStageController != nullptr)
			{
				m_pStageController->Draw();
			}
		}
		//============================================
		// �R���X�g���N�^
		//============================================

		//============================================
		// �|�[�Y���擾
		//============================================
		bool CGameManager::GetPose()
		{
			if (m_pScene != nullptr)
			{
				return m_pScene->GetPose();
			}
			return false;
		}
		/// <summary>
		/// ���V�[�����ݒ肳��Ă�����ς���
		/// </summary>
		nsPrev::CBase* CGameManager::JoinNextScene()
		{
			// ���V�[�����L��Ȃ�
			if (m_pNextScene)
			{
				delete m_pScene;	// ���݃V�[����j��
				auto p2 = dynamic_cast<CBase*>(m_pNextScene);
				if (p2 != nullptr)
				{
					m_pScene = p2;
					return this;
				}
				else
				{
					m_pScene = nullptr;
					return m_pNextScene;
				}
			}
			return this;
		}
	}
	template<>
	Scene::CBase* nsThis::nsPrev::CBase::makeScene<nsThis::CGameManager>() {
		return new nsThis::CGameManager(this);
	}
}