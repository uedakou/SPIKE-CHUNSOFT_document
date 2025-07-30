//===========================================
// 
// �L�����N�^�[[charactor.cpp]
// Auther:UedaKou
// 
//===========================================
#include "character.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CCharacter::CCharacter()
{
	m_nLife = 0;
	m_nCntInvincible = 0;
	m_nAttcak = 0;
	m_nDefense = 0;
	m_fSpeed = 0;
	m_Xcollision = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_xmove = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	bJump = false;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CCharacter::~CCharacter()
{
}
/// <summary>
///  ����������
/// </summary>
/// <returns>true : ����������</returns>
bool CCharacter::Init()
{
	// ���[�V�����I�u�W�F�N�g������
	CObjectMotion::Init();
	return true;
}
/// <summary>
/// �I������
/// </summary>
void CCharacter::Uninit()
{
	// ���[�V�����I�u�W�F�N�g�I������
	CObjectMotion::Uninit();
}
/// <summary>
/// �X�V����
/// </summary>
void CCharacter::Update()
{
	// �������Z
	CObjectMotion::AddPos(m_xmove.pos);
	CObjectMotion::AddRot(m_xmove.rot);

	// �ړ�����
	MoveAttenuation();

	// ���[�V�����I�u�W�F�N�g�X�V
	CObjectMotion::Update();
	// ���G���Ԃ��L������J�E���g�_�E������
	if (m_nCntInvincible > 0)
	{
		m_nCntInvincible--;
	}
}
/// <summary>
/// �`�揈��
/// </summary>
void CCharacter::Draw()
{
	// ���[�V�����I�u�W�F�N�g�`��
	CObjectMotion::Draw();
}
/// <summary>
/// �����[�V�����擾
/// </summary>
/// <returns>�����[�V������Ԃ��i�h���N���X�Őݒ肵�Ȃ����0�Ԗڂ�Ԃ��j</returns>
int CCharacter::GetNextMotion()
{
	return 0;
}
/// <summary>
/// �q�b�g����(�_���[�W�̂�)
/// </summary>
/// <param name="nDamage">�_���[�W</param>
void CCharacter::Hit(int nDamage)
{
	if (m_nCntInvincible <= 0)
	{
		m_nCntInvincible = 0;
		m_nLife -= nDamage;
	}
}
/// <summary>
/// �q�b�g����(���G���Ԃƃ_���[�W�̂�)
/// </summary>
/// <param name="nCntInvincible">���G����</param>
/// <param name="nDamage">�_���[�W</param>
void CCharacter::Hit(int nCntInvincible, int nDamage)
{
	if (m_nCntInvincible <= 0)
	{
		Hit(nDamage);
		m_nCntInvincible = nCntInvincible;
	}
}
/// <summary>
/// �q�b�g����(�m�b�N�o�b�N,���G���Ԃƃ_���[�W)
/// </summary>
/// <param name="ShockRot">�m�b�N�o�b�N</param>
/// <param name="nCntInvincible">���G����</param>
/// <param name="nDamage">�_���[�W</param>
void CCharacter::Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage)
{
	if (m_nCntInvincible <= 0)
	{
		Hit(nCntInvincible, nDamage);
		m_xmove.pos += ShockRot;
	}
}
/// <summary>
/// �ړ�����
/// </summary>
void CCharacter::MoveAttenuation()
{
	// yUp�n�ړ�����
	m_xmove.pos.x += (0 - m_xmove.pos.x) * s_fBase_Resistance;
	m_xmove.pos.z += (0 - m_xmove.pos.z) * s_fBase_Resistance;

	// �d�͉��Z
	m_xmove.rot.y += (0 - m_xmove.rot.y) * s_fBase_Gravity;

}