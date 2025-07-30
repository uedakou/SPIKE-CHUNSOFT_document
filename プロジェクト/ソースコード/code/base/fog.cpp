//===========================================
// 
// �t�H�O[fog.h]
// Auther:UedaKou
// 
//===========================================
#include "fog.h"		// �t�H�O����
#include "manager.h"	// �Q�[���S�̂��Ǘ�����N���X
/// <summary>
/// �R���X�g���N�^
/// </summary>
CFog::CFog()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �t�H�O�L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	// �t�H�O�J���[
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// �t�H�O�p�����[�^
	m_type = EXP;
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);

	// �����w��

	m_fFogStartPos = 100.0f;
	m_fFogEndPos = 10000.0f;
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));

	// ���x�w��
	m_m_fFogDensity = 0.002f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_m_fFogDensity));
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CFog::~CFog()
{

}
/// <summary>
/// �t�H�O�ݒ�
/// </summary>
/// <param name="type">�t�H�O�̎��</param>
void CFog::SetFogType(FogType type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �t�H�O�p�����[�^
	m_type = type;
	switch (type)
	{
	case EXP:	
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
		break;
	case LINEAR:
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
		break;
	default:
		break;
	}
}
/// <summary>
/// ���`�t�H�O�̊J�n�����ƏI��������ݒ肵�܂��B
/// </summary>
/// <param name="fStart">�t�H�O���n�܂鋗��</param>
/// <param name="fEnd">�t�H�O�����S�ɂ����鋗��</param>
void CFog::SetFogLinear(float fStart, float fEnd)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �����w��
	m_fFogStartPos = fStart;
	m_fFogEndPos = fEnd;
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));

}
/// <summary>
/// �w���t�H�O�̖��x��ݒ肵�܂��B
/// �t�H�O���ǂꂾ���}���ɔZ���Ȃ邩�𐧌䂵�܂��B
/// </summary>
/// <param name="fDensity">�t�H�O�̖��x�i�ʏ��0.0�`1.0�j</param>
void CFog::SetFogDensity(float fDensity)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���x�w��
	m_m_fFogDensity = fDensity;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_m_fFogDensity));
}
/// <summary>
/// �t�H�O�̐���
/// </summary>
/// <returns>���������|�C���^�[</returns>
CFog* CFog::create()
{
	return new CFog;
}