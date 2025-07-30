//===========================================
// 
// �S�̃}�l�[�W���[[managerer.cpp]
// Auther:UedaKou
// 
//===========================================
#include "manager.h"	// �}�l�[�W���[
#include "../object/base/object.h"
#include "../object/base/text.h"	// �e�L�X�g


// �O���[�o�X�ϐ�
bool CManager::m_bEnd = false;	// �I���t���O

/// <summary>
/// �R���X�g���N�^
/// </summary>
CManager::CManager()
{
	m_pRenderer = nullptr;			// �����_���[
	m_pLight = nullptr;				// ���C�g
	m_pCamera = nullptr;			// �J����
	m_pFog = nullptr;				// �t�H�O
	m_pSound = nullptr;				// �T�E���h

	m_pInkey = nullptr;				// �L�[�{�[�h
	m_pInMouse = nullptr;			// �}�E�X
	m_pJoiKey = nullptr;			// �W���C�p�b�h

	m_pSceneManager = nullptr;		// �V�[���}�l�[�W���[

	m_pDebugText = nullptr;			// �f�o�b�O�p�e�L�X�g
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CManager::~CManager()
{
}
/// <summary>
/// ������
/// </summary>
/// <param name="hInstance">�C���X�^���X�n���h��</param>
/// <param name="nWnd">�E�B���h�E�n���h��</param>
/// <param name="bWindow"></param>
/// <returns>���������� : S_OK</returns>
HRESULT CManager::Init(HINSTANCE hInstance, HWND nWnd, BOOL bWindow)
{
	// �����_���[
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(nWnd, bWindow);
	}
	// ���C�g
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}
	// �J����
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}
	// �t�H�O
	if (m_pFog == nullptr)
	{
		m_pFog = CFog::create();
	}
	// �T�E���h
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound;
		m_pSound->InitSound(nWnd);
	}



	// ����
	if (m_pInkey == nullptr)
	{// �L�[�{�[�h
		m_pInkey = new CInputKeyboard;
		m_pInkey->Init(hInstance, nWnd);
	}
	if (m_pInMouse == nullptr)
	{// �}�E�X
		m_pInMouse = new CInputMouse;
		m_pInMouse->Init(hInstance, nWnd);
	}
	// �W���C�p�b�h����
	if (m_pJoiKey == nullptr)
	{
		m_pJoiKey = new CInputJoypad;
		m_pJoiKey->Init();
	}
	// �V�[���}�l�[�W���[
	if (m_pSceneManager == nullptr)
	{
		m_pSceneManager = new Scene::CSceneManager;
	}
	// �f�o�b�O�e�L�X�g
	if (m_pDebugText == nullptr)
	{
		m_pDebugText = CText::create();
		m_pDebugText->SetReleaseScene(false);


	}

	return S_OK;
}
/// <summary>
/// �I������
/// </summary>
void CManager::Uninit()
{
	// �f�o�b�O�e�L�X�g
	if (m_pDebugText != nullptr)
	{
		m_pDebugText->Release();
		m_pLight = nullptr;
	}
	// ���C�g
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	// �J����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	// �L�[�{�[�h����
	if (m_pInkey != nullptr)
	{
		m_pInkey->Uninit();
		delete m_pInkey;
		m_pInkey = nullptr;
	}
	// �W���C�p�b�h����
	if (m_pJoiKey != nullptr)
	{
		m_pJoiKey->Uninit();
		delete m_pJoiKey;
		m_pJoiKey = nullptr;
	}
	// �V�[���}�l�[�W���[
	if (m_pSceneManager != nullptr)
	{
		delete m_pSceneManager;
		m_pSceneManager = nullptr;
	}
	// �����_���[
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}
/// <summary>
/// �X�V
/// </summary>
void CManager::Update()
{
	// �f�o�b�O�e�L�X�g
	if (m_pDebugText != nullptr)
	{
		m_pDebugText->ClearText();
	}
	// �����_���[
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
	// ���C�g
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}
	// �J����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	// �L�[�{�[�h����
	if (m_pInkey != nullptr)
	{
		m_pInkey->Update();
	}
	// �}�E�X����
	if (m_pInMouse != nullptr)
	{
		m_pInMouse->Update();
	}
	// �W���C�p�b�h����
	if (m_pJoiKey != nullptr)
	{
		m_pJoiKey->Update();
	}
	// �V�[���}�l�[�W���[
	if (m_pSceneManager != nullptr)
	{
		m_pSceneManager->Update();
	}

	CObject::ReleaseDeathFlag();
}
/// <summary>
/// �`��
/// </summary>
void CManager::Draw()
{
	// �����_���[
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();	
	}
}