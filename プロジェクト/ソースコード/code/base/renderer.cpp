//===========================================
// 
// �����_���[[renderer.cpp]
// Auther:UedaKou
// 
//===========================================
#include "renderer.h"	// �����_���[
#include "main.h"		// ���C��
#include "manager.h"	// �}�l�[�W���[

#include "../object/base/object.h"		// �I�u�W�F�N�g
#include "../object/base/text.h"		// �e�L�X�g�N���X

const D3DXCOLOR CRenderer::s_BGColor = D3DCOLOR_RGBA(50, 150, 255, 255);

/// <summary>
/// �R���X�g���N�^
/// </summary>
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_BGColor = s_BGColor;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CRenderer::~CRenderer()
{
}
/// <summary>
/// ����������
/// </summary>
/// <param name="hWnd">�E�B���h�E�̃n���h��</param>
/// <param name="bWindow">�E�B���h�E���[�h (TRUE: �E�B���h�E, FALSE: �t���X�N���[��)</param>
/// <returns>���������ʁi����: S_OK / ���s: E_FAIL�j</returns>
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL; // ���s���͑��I��
	}
	// ���݂̃f�B�X�v���C���[�h�擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL; // ���s���͑��I��
	}

	// �v���[���e�[�V�����p�����[�^�i�������j
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_W;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_H;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@��16bit�g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// ----------------------------------------
	// Direct3D �f�o�C�X�̍쐬�i�D�揇�Ƀg���C�j
	// ----------------------------------------

	// 1. �n�[�h�E�F�A���_�����i�ł������j
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// 2. �\�t�g�E�F�A���_����
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// 3. ���t�@�����X�f�o�C�X�i���ᑬ��������m�F�p�r�j
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;	// �ǂ�����s
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}
/// <summary>
/// �I������
/// </summary>
void CRenderer::Uninit()
{
	timeEndPeriod(1);	// fps���Z�b�g
	CObject::ReleaseAll();
}
/// <summary>
/// �X�V����
/// </summary>
void CRenderer::Update()
{
	CObject::UpdateAll();

	timeEndPeriod(1);	// fps���Z�b�g
}
/// <summary>
/// �`�揈��
/// </summary>
void CRenderer::Draw()
{
	// �S�̃}�l�[�W���[�C���X�^���X
	CManager* instance = CManager::GetInstance();
	// �J�����擾
	CCamera* pCamera = instance->GetCamera();
	// �V�[���}�l�[�W���[
	Scene::CBase* Scene = instance->GetSceneManager();

	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		m_BGColor,	// �w�i�F
		1.0f,
		0);

	// �`��J�n�i�`��R�}���h�̔��s�J�n�j
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �J��������̋��������ɕ`��I�u�W�F�N�g�̃\�[�g
		CObject::CalculateDistanceToCamera();
		CObject::Sort();

		// �J�����̃r���[�s��^�ˉe�s����f�o�C�X�ɐݒ�
		if (pCamera != nullptr)
		{
			pCamera->SetCamera();
		}

		// ���ׂẴQ�[���I�u�W�F�N�g��`��i�ÓI�E���I��킸�j
		CObject::DrawAll();

		// ���݃A�N�e�B�u�ȃV�[���ɉ������`�揈�������s�i�^�C�g���^�Q�[�����^���U���g���j
		Scene->Draw();

#ifdef _DEBUG
		// �f�o�b�O�p��FPS�\����`��
		DrawFPS();
#endif // !_DEBUG
		// �`��R�}���h�̏I���iGPU�ֈꊇ���M�j
		m_pD3DDevice->EndScene();
	}
	// ��ʂɕ`�������e���t�����g�o�b�t�@�֔��f�i���ۂɕ\�������j
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
/// <summary>
/// FPS�\��
/// </summary>
void CRenderer::DrawFPS()
{
	// �S�̃}�l�[�W���[
	CManager* pManager = CManager::GetInstance();
	// �f�o�b�N�e�L�X�g�擾
	CText* pText = pManager->GetDebugText();

	// �f�o�b�N�e�L�X�g�����݂�����
	if (pText != nullptr)
	{
		// FPS���擾
		int nCountFPS = GetFPS();
		string aStr;	// �\���p�̕�����o�b�t�@
		wsprintf(&aStr[0], "FPS:%d\n", nCountFPS);	// �e�L�X�g�ێ�
		pText->PrintText(aStr);
	}
}
/// <summary>
/// Direct3D�f�o�C�X�擾
/// </summary>
/// <returns>���ݎg�p����Direct3D�f�o�C�X</returns>
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}
