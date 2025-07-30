//============================================
//
// ����[light.cpp]
// Author:Uedakou
// 
//============================================
#include "light.h"
#include "manager.h"
#include "manager.h"
#include <strsafe.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
CLight::CLight()
{
	// ���C�g�\���̂��[��������
	//ZeroMemory(&m_light, sizeof(D3DLIGHT9));
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CLight::~CLight()
{
}
/// <summary>
/// ������
/// </summary>
/// <returns>����I���Ȃ�S_OK</returns>
HRESULT CLight::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^

	// ���C�g�̕����x�N�g���i�ꎞ�I�Ɏg�p�j
	D3DXVECTOR3 vecDir = { 0.0f, 0.0f,0.0f };

	// ���C�g�̏����N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g�̎�ނ��f�B���N�V���i�����C�g�ɐݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// �g�U���̐F�i���j��ݒ�
		m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���C�g�̕����x�N�g����ݒ�i�e���C�g���ƂɈقȂ�����j
		switch (nCntLight)
		{
		case 0:
			// ���C�g�̕����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, -1.0f);
			break;
		case 1:
			// ���C�g�̕����ݒ�
			vecDir = D3DXVECTOR3(-0.2f, 0.8f, 0.4f);
			break;
		case 2:
			// ���C�g�̕����ݒ�
			vecDir = D3DXVECTOR3(0.8f, -0.8f, -0.4f);
			break;
		}

		// �����x�N�g���𐳋K��
		D3DXVec3Normalize(&vecDir, &vecDir);

		// ���C�g�ɕ�����ݒ�
		m_light[nCntLight].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);

		// ���̃��[�v�p�Ƀx�N�g�����������i���͕s�v�A�㏑������邽�߁j
		vecDir = { 0.0f, 0.0f,0.0f };
	}
	
	return S_OK;
}
void CLight::Uninit()
{}
void CLight::Update()
{}