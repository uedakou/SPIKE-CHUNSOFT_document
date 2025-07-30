//===========================================
// 
// �V�[���}�l�[�W���[[scene_maneger.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_maneger.h"	// �V�[���}�l�[�W���[
#include "../base/manager.h"		// �}�l�[�W���[

namespace Scene {

	class CTitle;
	//============================================
	// �R���X�g
	//============================================
	CSceneManager::CSceneManager() :
		CBase(new CCommonData()),
		m_pScene(makeScene<CTitle>())
	{
		
	}
	//============================================
	// �f�X�g���N�^
	//============================================
	CSceneManager::~CSceneManager()
	{
		if (m_pScene != nullptr)
		{
			delete m_pScene;
		}
		delete m_pCommonData;
	}
	//============================================
	// �X�V
	//============================================
	CBase* CSceneManager::Update()
	{
		// �V�[���X�V
		CBase* pBaseScene = m_pScene->Update();

		if (pBaseScene != m_pScene)
		{// �Ԃ�l���ς���Ă�����V�[���ύX
			delete m_pScene;
			if (pBaseScene == nullptr)
			{
				CManager::GetInstance()->SetEnd(true);
			}
			m_pScene = pBaseScene;
		}
		return m_pScene;
	}
	//============================================
	// �`��
	//============================================
	void CSceneManager::Draw() const
	{
		if (m_pScene != nullptr)
		{
			m_pScene->Draw();
		}
	}

	//============================================
	// �|�[�Y���擾
	//============================================
	bool CSceneManager::GetPose()
	{
		if (m_pScene != nullptr)
		{
			return m_pScene->GetPose();
		}
		return false;
	}
}
