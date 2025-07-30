//===========================================
// 
// ���C��[main.cpp]
// Auther:UedaKou
// 
//===========================================
#include "main.h"		// ���C���w�b�_
#include "manager.h"	// �S�̊Ǘ��}�l�[�W���[

// �O���[�o���錾
int g_nCountFPS = 0;// FPS�J�E���g�p�̃O���[�o���ϐ�

// �A�v���P�[�V�����N���X�ւ̃O���[�o���A�N�Z�X�p�|�C���^
// WindowProc �ȂǁA�񃁃��o�֐����� CApplication �ɃA�N�Z�X���邽�߂ɕK�v
static CApplication* g_pApp = nullptr;

//// <summary>
/// �A�v���P�[�V�����̃G���g���[�|�C���g�i���C���֐��j
/// Windows API�ɂ����� WinMain �֐�
/// </summary>
/// <param name="hInstance">���݂̃A�v���P�[�V�����C���X�^���X�̃n���h��</param>
/// <param name="hInstancePrev">�ȑO�̃C���X�^���X�i��� NULL�j</param>
/// <param name="lpCmdLine">�R�}���h���C������������</param>
/// <param name="nCmdShow">�E�B���h�E�̕\�����</param>
/// <returns>�A�v���P�[�V�����̏I���R�[�h�i0�Ő���I���j</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hindtscePrev, _In_ LPSTR LpCmdline, _In_ int nCmdShow)
{
	CApplication app;	// �A�v���P�[�V�����{�̂̃C���X�^���X�i���[�J���j

	g_pApp = &app;		// �O���[�o���|�C���^�ɓo�^�iWindowProc �Ȃǂ���Q�Ƃ��邽�߁j

	// �����������i�E�B���h�E�����ADirectX�������Ȃǁj
	if (!app.Init(hInstance, nCmdShow))
	{
		return -1;
	}

	app.Run();	// ���C�����[�v�i�X�V�E�`�揈���j

	app.Uninit();	// ���\�[�X����ȂǏI������

	return 0;	// �I���R�[�h�i����I���j
}
/// <summary>
/// �E�B���h�E�v���V�[�W���i���b�Z�[�W�����֐��j
/// Windows OS���瑗���Ă���e�탁�b�Z�[�W����������
/// </summary>
/// <param name="hWnd">�E�B���h�E�̃n���h��</param>
/// <param name="uMsg">���b�Z�[�W�̎�ށi��FWM_DESTROY�AWM_KEYDOWN�Ȃǁj</param>
/// <param name="wParam">�ǉ��̏��i�L�[�R�[�h��}�E�X�{�^�����Ȃǁj</param>
/// <param name="lParam">�ǉ��̏��i�ʒu���W��g�����Ȃǁj</param>
/// <returns>�������ʁiOS�֕Ԃ��l�j</returns>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	CManager* instance = CManager::GetInstance();// �}�l�[�W���[�C���X�^���X�擾


	switch (uMsg)
	{
	case WM_CREATE:  // �E�B���h�E���쐬���ꂽ�Ƃ��̃��b�Z�[�W
		// �E�B���h�E��������ɑ����郁�b�Z�[�W�i�����ł͉������Ȃ��j
		break;

	case WM_DESTROY:
		// �E�B���h�E�j�����F�A�v���P�[�V�����I�����b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		// �L�[���͂��������ꍇ �� �A�v���P�[�V�����N���X�̏����ɈϏ�
		if (g_pApp)
		{
			g_pApp->OnKeyDown(wParam);
		}
		break;

	case WM_COMMAND: // �{�^���Ȃǂ̃R�}���h�����������Ƃ�
		// ���j���[��{�^���̑���Ȃǁi����͖��g�p�j
		break;

	case WM_CLOSE:
		// �E�B���h�E�E��́u�~�v�{�^���������̏���
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			instance->Uninit();		// �I�����������s
			DestroyWindow(hWnd);	// �E�B���h�E��j������
		}
		else
		{
			// ���[�U�[���L�����Z�������ꍇ�͏I�����f
			return 0;//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_LBUTTONDOWN:	// �}�E�X���N���b�N�̃��b�Z�[�W
		// �E�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	}

	// ����̃��b�Z�[�W�������Ăяo��
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
/// <summary>
/// ���݂�FPS���擾����
/// </summary>
/// <returns>FPS�l</returns>
int GetFPS()
{
	return g_nCountFPS;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
CApplication::CApplication()
	: m_hWnd(NULL), m_dwExecLastTime(0), m_dwFPSLostTime(0), m_dwFrameCount(0)
{
	ZeroMemory(&m_wcex, sizeof(WNDCLASSEX));
	ZeroMemory(&m_msg, sizeof(MSG));
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CApplication::~CApplication()
{
}
/// <summary>
/// �E�B���h�E������DirectX������
/// </summary>
/// <param name="hInstance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
/// <param name="nCmdShow">�E�B���h�E�̕\�����</param>
/// <returns>���������ʁi����: true / ���s: false�jtrue<</returns>
bool CApplication::Init(HINSTANCE hInstance, int nCmdShow)
{
	CManager* instance = CManager::GetInstance();// �}�l�[�W���[�C���X�^���X�擾

	// �E�B���h�E�N���X�̐ݒ�
	m_wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							// �E�B���h�E�̃X�^�C��
		WindowProc,							// �E�B���h�E�v���V���[�V
		0,									// �O�ɂ���i�ʏ�͎g�p���Ȃ��j
		0,									// �O�ɂ���i�ʏ�͎g�p���Ȃ��j
		hInstance,							// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		// �^�X�N�o�[�A�C�R��
		LoadCursor(NULL, IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			// �N���C�A���g�̈�̔w�i�F
		NULL,								// ���j���[�o�[
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&m_wcex);

	// �E�B���h�E�̃N���C�A���g�̈�T�C�Y�̎w��
	RECT rect = { 0,0,SCREEN_W,SCREEN_H };

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//	�E�B���h�E�𐶐�
	m_hWnd = CreateWindowEx(0,	// �g���E�B���h�E�X�^�C��
		CLASS_NAME,				// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,			// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
		0,//CW_USEDEFAULT,		// �E�B���h�E�̍����x���W
		0,//CW_USEDEFAULT,		// �E�B���h�E�̍����y���W
		(rect.right - rect.left),	// �E�B���h�E�̕�
		(rect.bottom - rect.top),	// �E�B���h�E�̍���
		NULL,
		NULL,
		hInstance,
		NULL);

	// �E�B���h�E�̕\���ƍX�V
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	// �����������iDirectX��T�u�V�X�e���Ȃǁj
	if (FAILED(instance->Init(hInstance, m_hWnd, TRUE)))
	{
		return false; // ���������s���͏I��
	}

	// �^�C�}�[����\���~���b�P�ʂɁiCPU�ɕ��ׂ͂����邪���x����j
	timeBeginPeriod(1);

	// �e�^�C�~���O�ϐ���������
	m_dwExecLastTime = timeGetTime();	// �Ō�ɏ��������������擾
	m_dwFPSLostTime = timeGetTime();	// �Ō��FPS���v������������������

	return true;
}
/// <summary>
/// �I������
/// </summary>
void CApplication::Uninit()
{
	CManager::GetInstance()->Uninit();
	UnregisterClass(CLASS_NAME, m_wcex.hInstance);
}
/// <summary>
/// ���C��ry�|�v����
/// </summary>
void CApplication::Run()
{
	CManager* instance = CManager::GetInstance();
	//----------------------------------------------
	// ���C�����[�v
	//----------------------------------------------
	while (1)
	{
		// ���b�Z�[�W������Ώ����i��u���b�L���O�j
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE) != 0)
		{

			if (m_msg.message == WM_QUIT)
			{
				break;	// �A�v���P�[�V�����I���v��
			}
			else
			{
				TranslateMessage(&m_msg);
				DispatchMessage(&m_msg);
			}
		}
		// DirectX�̏���
		else
		{
			// ���Ԏ擾�i�t���[������p�j
			DWORD dwCuppentTime = timeGetTime();

			// FPS�v���i0.5�b�����ɍX�V�j
			if ((dwCuppentTime - m_dwFPSLostTime) >= 500)
			{
				// FPS���v��
				g_nCountFPS = (m_dwFrameCount * 1000) / (dwCuppentTime - m_dwFPSLostTime);
				m_dwFPSLostTime = dwCuppentTime;
				m_dwFrameCount = 0;

			}
			// ���Ԋu�i��F60FPS�Ȃ��16.66ms�j�ōX�V�E�`�揈��
			if ((dwCuppentTime - m_dwExecLastTime) >= (1000 / FPS))
			{// 60����1�b�o��

//  �x���␳�t���̍X�V���g�p���邩�ǂ���
#if IS_DELAY_UPDATE
				// ==============================
				// �x���␳�t���̍X�V�������[�v
				// ==============================
				while ((dwCuppentTime - m_dwExecLastTime) >= (1000 / FPS)) // 16.66ms �o�߂��Ă�����
				{
					// �X�V���� (�x��Ă�����ǂ����܂Ŏ��s)
					instance->Update();

					// ���̃t���[�����s���Ԃɐi�߂�i16.66ms���i�߂�j
					m_dwExecLastTime += (1000 / FPS);

					// �t���[�����J�E���g�iFPS�v���p�j
					m_dwFrameCount++;
				}
#else
				// �X�V����
				instance->Update();
#endif
				// �`�揈�� (1�񂾂�)
				instance->Draw();
			}

		}
		// �O���[�o���ȏI���v���t���O�������Ă����烋�[�v�𔲂���
		if (CManager::GetEnd() == true)
		{
			break;
		}
	}
}
/// <summary>
/// �L�[�{�[�h���́i�L�[�����j�ɑ΂��鏈��
/// </summary>
/// <param name="key">�����ꂽ�L�[�̉��z�L�[�R�[�h�iWPARAM�j</param>
void CApplication::OnKeyDown(WPARAM key)
{
	if (key == VK_ESCAPE)
	{
		int result = MessageBox(m_hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (result == IDYES)
		{
			CManager::GetInstance()->Uninit();
			DestroyWindow(m_hWnd);
		}
	}
}