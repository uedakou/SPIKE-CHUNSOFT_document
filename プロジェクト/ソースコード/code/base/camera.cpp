//============================================
//
// �J����[camera.cpp]
// Author:Uedakou
// 
//============================================
#include "camera.h"		// �J�����N���X
#include "manager.h"	// �}�l�[�W���[
#include <strsafe.h>	// StringCbPrintf���g�p����ɂ̂ɕK�v
#include "../object/Base/object.h"	// �I�u�W�F�N�g
#include "../object/base/text.h"

// �J�����萔
//const CCamera::ProjectionType CCamera::CAMERA_TYPE = CCamera::ProjectionType::Perspective;	// ���e����
//const bool CCamera::CAMERA_CONTROLLER = false;	// �J�����ŃR���g���[���[�����邩
const D3DXVECTOR3 CCamera::CAMERA_V = { 0.0f, 40.0f, -POS_CAMERA };	// �J�����ʒu�擾
const D3DXVECTOR3 CCamera::CAMERA_ROT = { 1.5f, 0.0f, 0.0f };	// �J���������擾
const D3DXVECTOR3 CCamera::CAMERA_U = { 0.0f, 1.0f, 0.0f };			// �����


/// <summary>
/// �R���X�g���N�^
/// </summary>
CCamera::CCamera()
{
	m_CameraType = CAMERA_TYPE;					// �J�������ߓ��e
	m_bCumeraController = CAMERA_CONTROLLER;	// �v���C���[�Ǐ]

	m_posV = CAMERA_V;		// ���_
	m_vecU = CAMERA_U;		// �����
	m_rot = CAMERA_ROT;		// ����
	m_fLeng = POS_CAMERA;	// ���_�ƒ����_�̋���

	m_posR.x = cos(m_rot.x) + sin(m_rot.y) * m_fLeng;	// �����_
	m_posR.z = cos(m_rot.x) + cos(m_rot.y) * m_fLeng;	// �����_
	m_posR.y = sin(m_rot.x) * m_fLeng;	// �����_


	m_rotTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����(�ڕW)
	m_bRotTarget = false;						// �␳��]������

	m_fMoveSpeed = MOVE_SPEED;			// �ʏ펞�J�������x
	m_fMoveFastSpeed = MOVE_SPEED_FAST;	// �������J�������x

	m_pCameraStrategy = nullptr;	// �`��X�g���e�W�[
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CCamera::~CCamera()
{
	Uninit();
}
/// <summary>
/// ������
/// </summary>
/// <returns>�����������󋵂�Ԃ�</returns>
HRESULT CCamera::Init()
{
	// m_pCameraStrategy��nullpre�Ȃ�X�g���e�W�[�𐶐�
	if (!m_pCameraStrategy)
	{
		m_pCameraStrategy = new ProjectionPerspectiveStrategy();	// �`��X�g���e�W�[
	}

	return S_OK;
}
/// <summary>
/// �I������
/// </summary>
void CCamera::Uninit()
{
	// m_pCameraStrategy��nullpre�łȂ���΃X�g���e�W�[�����
	if (m_pCameraStrategy)
	{
		delete m_pCameraStrategy ;	// �`��X�g���e�W�[
		m_pCameraStrategy = nullptr;	// �`��X�g���e�W�[
	}

}
/// <summary>
/// �X�V����
/// </summary>
void CCamera::Update()
{
	CManager* pManager = CManager::GetInstance();	// �S�̃}�l�[�W���[�擾
	CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���͎擾
#if _DEBUG
	if (pKey->GetTrigger(DIK_F2))
	{
		m_bCumeraController = m_bCumeraController ? false : true;
	}
#endif // _Debug
	if (m_bCumeraController)
	{
		// ���͏���
		Controller();

		// �l���␳��]����
		if (m_bRotTarget == true)
		{
			// ���݂̉�]�p�ƖڕW�̉�]�p�̍������v�Z
			float fRotY = (m_rotTarget.y - m_rot.y);	// �ڕW�Ƃ̍���

			// ������ �}�΁i180�x�j�𒴂���ꍇ�ATAU�i360�x�j�␳�ōŒZ��]�ɒ���
			if (fRotY >= D3DX_PI)
			{
				fRotY -= TAU; // -360�x���ċt��]
			}
			else if (fRotY <= -D3DX_PI)
			{
				fRotY += TAU; // +360�x���ċt��]
			}

			// ������10%������]�i�C�[�W���O�̂悤�Ȋɂ₩�ȕ␳�j
			m_rot.y += fRotY * 0.1f;

			// ��]�p�� -�� �` �� �͈̔͂Ɏ��߂�i�I�[�o�[�t���[�΍�j
			if (m_rot.y >= D3DX_PI)
			{
				m_rot.y -= TAU;
			}
			else if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}

			// ��]�����̔���i���������ȉ��Ȃ犮���Ƃ݂Ȃ��j
			if (m_rot.y - m_rotTarget.y <= ROT_ERRER &&
				m_rot.y - m_rotTarget.y >= ROT_ERRER)
			{
				m_rot.y = m_rotTarget.y;	// �ڕW�p�Ƀs�^���ƍ��킹��
				m_bRotTarget = false;		// �␳�I��
			}
		}
	}
	CameraSetR();

	// �f�o�b�O�r���h���̂ݗL��
#if _DEBUG
	// �J��������\������t���O���L���ȏꍇ
#if s_bCameraDataDraw
	// �f�o�b�O�e�L�X�g�`��p�I�u�W�F�N�g���擾
	CText* pDebugText = pManager->GetDebugText();

	char aStr[MAX_TXT];
	sprintf_s(aStr, sizeof(aStr), 
		"CameraV Pos:X%f Y%f Z%f\n"
		"CameraR Pos:X%f Y%f Z%f\n"
		"Camera Rot:X%f Y%f Z%f\n",
		m_posV.x, m_posV.y, m_posV.z, 
		m_posR.x, m_posR.y, m_posR.z, 
		m_rot.x, m_rot.y, m_rot.z);

	// ���`������������f�o�b�O�e�L�X�g�ɕ\��
	pDebugText->PrintText(aStr);
#endif // s_bCameraDataDraw
#endif // _DEBUG
}
/// <summary>
/// �`�揈��
/// </summary>
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
#if 0
	// �v���W�F�N�V�����}�g���N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	// ����p�iFOV�j
		(float)SCREEN_W / (float)SCREEN_H,	// �A�X�y�N�g��i�� / �c�j
		10,		// �߃N���b�v��
		10000);	// ���N���b�v��
#else
	m_pCameraStrategy->Projection(&m_mtxProjection);
#endif // 0


	//switch (m_CameraType)
	//{
	//case ProjectionType::Perspective:
	//	// ���ߓ��e
	//	Projection()
	//	break;
	//case ProjectionType::Orthographic:
	//	// �����e
	//	break;
	//default:
	//	break;
	//}
#if _DEBUG


#endif // _DEBUG
	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	// �r���[�}�g���N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);
	// �r���[�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
/// <summary>
/// �J�����R���g���[���[
/// </summary>
void CCamera::Controller()
{
	// �S�̃}�l�[�W���[�擾
	CManager* pManager = CManager::GetInstance();
	//�L�[�{�[�h���͎擾
	CInputKeyboard* pKey = pManager->GetInKey();

	//----------------------------------------------
	// ����]�L�[�iQ�j����
	//----------------------------------------------
	if (pKey->GetTrigger(DIK_Q))
	{
		// SHIFT ���������Ȃ�u�l���␳��]�v
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;	// �l���␳���[�h�L����

			// ���݂̊p�x�Ɋ�Â���90�x�P�ʂ̕␳�p������
			if (m_rot.y <= 0.0f + 0.005f &&
				m_rot.y > -(D3DX_PI * 0.5f) + 0.005f)
			{
				m_rotTarget.y = -(D3DX_PI * 0.5f);
			}
			else if (m_rot.y <= -(D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > -D3DX_PI + 0.005f)
			{
				m_rotTarget.y = -D3DX_PI;
			}
			else if (m_rot.y <= -D3DX_PI + 0.005f ||
				m_rot.y > (D3DX_PI * 0.5f) + 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y <= (D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > 0.0f + 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		// �ʏ�̍���]�i�g���K�[�j
		else
		{
			m_bRotTarget = false;	// �l���␳���[�h������
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	// ����]�̌p���i�z�[���h�j
	else if (pKey->GetRepeat(DIK_Q) &&
		m_bRotTarget == false)
	{
		m_rot.y -= 0.05f;
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y += TAU;
		}
	}
	//----------------------------------------------
	// �E��]�L�[�iE�j����
	//----------------------------------------------
	else if (pKey->GetTrigger(DIK_E))
	{
		// SHIFT ���������Ȃ�u�l���␳��]�v
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;	// �l���␳��]���[�hON

				// ���݂̊p�x�Ɋ�Â���90�x�P�ʂ̕␳�p������
			if (m_rot.y >= 0.0f - 0.005f &&
				m_rot.y < (D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= D3DX_PI * 0.5f - 0.005f &&
				m_rot.y < D3DX_PI - 0.005f)
			{
				m_rotTarget.y = D3DX_PI;
			}
			else if (m_rot.y >= D3DX_PI - 0.005f ||
				m_rot.y < -(D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = -D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= -(D3DX_PI * 0.5f) - 0.005f &&
				m_rot.y < 0.0f - 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		// �ʏ�̉E��]�i�g���K�[�j
		else
		{
			m_bRotTarget = false;
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	// �E��]�̌p���i�z�[���h�j
	else if (pKey->GetRepeat(DIK_E) &&
		m_bRotTarget == false)
	{
		m_rot.y += 0.05f;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y -= TAU;
		}
	}
	//----------------------------------------------
	// ���]�L�[�iR�j�z�[���h�ŏ�ɌX����
	//----------------------------------------------
	if (pKey->GetRepeat(DIK_R))
	{
		// ��������i�^��ȏ�Ɍ����Ȃ��j
		if (m_rot.x < D3DX_PI)
		{
			m_rot.x -= 0.05f;
		}
	}
	//----------------------------------------------
	// ����]�L�[�iF�j�z�[���h�ŉ��ɌX����
	//----------------------------------------------
	else if (pKey->GetRepeat(DIK_F))
	{
		// ���������i�^���ȉ��Ɍ����Ȃ��j
		if (m_rot.x > 0)
		{
			m_rot.x += 0.05f;
		}
	}

	// �ړ����x�i�ʏ� or �����j
	float speed = (pKey->GetRepeat(DIK_LSHIFT)) ? m_fMoveFastSpeed : m_fMoveSpeed;

	// �ړ������x�N�g���̏�����
	D3DXVECTOR3 moveVec(0, 0, 0);

	// �����t���O
	bool w = pKey->GetRepeat(DIK_W);
	bool s = pKey->GetRepeat(DIK_S);
	bool a = pKey->GetRepeat(DIK_A);
	bool d = pKey->GetRepeat(DIK_D);

	//----------------------------------------------
	// 8�����ړ������i���_��]�ɉ����ĕ�����ϊ��j
	//----------------------------------------------
	if (w && a)
	{   // ���O�i-45�x�j
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y - D3DX_PI * 0.25f) * speed,
			0.0f,
			cosf(m_rot.y - D3DX_PI * 0.25f) * speed
		);
	}
	else if (w && d)
	{   // �E�O�i+45�x�j
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y + D3DX_PI * 0.25f) * speed,
			0.0f,
			cosf(m_rot.y + D3DX_PI * 0.25f) * speed
		);
	}
	else if (w)
	{   // �O
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y) * speed,
			0.0f,
			cosf(m_rot.y) * speed
		);
	}
	else if (s && a)
	{   // ����i-135�x�j
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y - D3DX_PI * 0.75f) * speed,
			0.0f,
			cosf(m_rot.y - D3DX_PI * 0.75f) * speed
		);
	}
	else if (s && d)
	{   // �E��i+135�x�j
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y + D3DX_PI * 0.75f) * speed,
			0.0f,
			cosf(m_rot.y + D3DX_PI * 0.75f) * speed
		);
	}
	else if (s)
	{   // ��
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y + D3DX_PI) * speed,
			0.0f,
			cosf(m_rot.y + D3DX_PI) * speed
		);
	}
	else if (a)
	{   // ���i-90�x�j
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y - D3DX_PI * 0.5f) * speed,
			0.0f,
			cosf(m_rot.y - D3DX_PI * 0.5f) * speed
		);
	}
	else if (d)
	{   // �E�i+90�x�j
		moveVec += D3DXVECTOR3(
			sinf(m_rot.y + D3DX_PI * 0.5f) * speed,
			0.0f,
			cosf(m_rot.y + D3DX_PI * 0.5f) * speed
		);
	}

	// �ړ���K�p
	m_posV += moveVec;

	//----------------------------------------------
	// �㉺�ړ��iShift�̗L���ő��x�ύX�j
	//----------------------------------------------
	float verticalSpeed = (pKey->GetRepeat(DIK_LSHIFT)) ? speed : 10.0f;

	if (pKey->GetRepeat(DIK_SPACE))
	{   // �㏸
		m_posV.y += verticalSpeed;
	}
	else if (pKey->GetRepeat(DIK_LCONTROL))
	{   // ���~
		m_posV.y -= verticalSpeed;
	}
}
/// <summary>
/// �J�����̒����_�im_posR�j���A�J�����̈ʒu�im_posV�j�Ɖ�]�p�im_rot�j����Z�o���Đݒ肷��B
/// ��]�p��x���c�i�㉺�̌X���j�Ay�����i���E�̉�]�j������\���B
/// </summary>
void CCamera::CameraSetR()
{
	// �J�����̌����Ă�������i��]�p�j���璍���_�̑��΍��W���v�Z
	// �p�x�͏��������Ƃ������߁AX����90�x�iPI/2�j�������Ă���

	// �����_��X���W
	m_posR.x = m_posV.x
		+ cosf(m_rot.x - (D3DX_PI * 0.5f))  // �㉺�̌X���ɂ�鐅�����������iX�����j���W����
		* sinf(m_rot.y)                    // ���E�̊p�x��X����
		* POS_CAMERA;                      // ���_����
	// �����_��Y���W
	m_posR.y = m_posV.y
		+ sinf(m_rot.x - (D3DX_PI * 0.5f))  // �㉺�̌X���ō�������
		* POS_CAMERA;

	// �����_��Z���W
	m_posR.z = m_posV.z
		+ cosf(m_rot.x - (D3DX_PI * 0.5f))  // �㉺�̌X���ɂ�鐅�����������iZ�����j���W����
		* cosf(m_rot.y)                    // ���E�̊p�x��Z����
		* POS_CAMERA;
}
/// <summary>
/// �������e�R���X�g���N�^
/// </summary>
CCamera::ProjectionPerspectiveStrategy::ProjectionPerspectiveStrategy()
{
	// �f�t�H���g�̎���p�iFOV�j�E�߃N���b�v�ʁE���N���b�v�ʂ̏����l��ݒ�
	m_fFov = PERSPECTIVE_FOV;	// ����p�i��F60�x�Ȃǁj
	m_fNear = PERSPECTIVE_NEAR;	// �߂��̕`��͈́i��F1.0f�j
	m_fFar = PERSPECTIVE_FAR;	// �����̕`��͈́i��F1000.0f�j
}
/// <summary>
/// �������e�`��
/// </summary>
/// <param name="mtx"></param>
void CCamera::ProjectionPerspectiveStrategy::Projection(D3DXMATRIX* mtx)
{
	// �v���W�F�N�V�����}�g���N�X���쐬
	D3DXMatrixPerspectiveFovLH(mtx,
		D3DXToRadian(m_fFov),	// ����p�iFOV�j
		(float)SCREEN_W / (float)SCREEN_H,	// �A�X�y�N�g��i�� / �c�j
		m_fNear,		// �߃N���b�v��
		m_fFar);	// ���N���b�v��
}
/// <summary>
/// ���s���e�R���X�g���N�^
/// </summary>
CCamera::ProjectionOrthographicStrategy::ProjectionOrthographicStrategy()
{
	m_fNear = PERSPECTIVE_NEAR;
	m_fFar = PERSPECTIVE_FAR;
}
/// <summary>
/// ���s���e�`��
/// </summary>
/// <param name="mtx"></param>
void CCamera::ProjectionOrthographicStrategy::Projection(D3DXMATRIX* mtx)
{
	D3DXMatrixOrthoLH(
		mtx,
		(float)SCREEN_W,
		(float)SCREEN_H,
		m_fNear,
		m_fFar);
}
