//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_generator_particle.h"	// �G�t�F�N�g�p�[�e�B�N���W�F�l���[�^�[
#include "effect_particle.h"	// �G�t�F�N�g�p�[�e�B�N��
#include <iostream>
#include <random>

const string CEffectGeneratorParticle::s_aDefltTexture = "data/TEXTURE/shadow000.jpg";	// �����G�t�F�N�g�p�[�e�B�N���e�N�X�`��
/// <summary>
/// �R���X�g���N�^
/// </summary>
CEffectGeneratorParticle::CEffectGeneratorParticle()
{
	// �������
	m_rot = { 0.0f, 0.0f, 0.0f };			// ����
	m_fLength = 0.0f;						// ����
	m_fDiffusion = 0.0f;					// �g�U��(�p�x)
	m_pCor = { 0.0f, 0.0f, 0.0f, 0.0f };	// �F
	m_aTexture = s_aDefltTexture;			// �e�N�X�`��
	m_nLifeParticle = 0;					// �p�[�e�B�N���̃��C�t
	// ���ԊǗ�
	m_nCreatSpan = 0;		// �����Ԋu
	m_nCntCreatTime = 0;	// ��������
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CEffectGeneratorParticle::~CEffectGeneratorParticle()
{
}
/// <summary>
/// ������
/// </summary>
/// <returns>true : ����������</returns>
bool CEffectGeneratorParticle::Init()
{
	// �G�t�F�N�g�W�F�l���[�^�[�x�[�X������
	CEffectGeneratorBase::Init();
	return true;
}
/// <summary>
/// �I������
/// </summary>
void CEffectGeneratorParticle::Uninit()
{
	// �G�t�F�N�g�W�F�l���[�^�[�x�[�X�I��
	CEffectGeneratorBase::Uninit();
}
/// <summary>
///  �X�V����
/// </summary>
void CEffectGeneratorParticle::Update()
{
	// ���S�t���O�������Ă��Ȃ����
	if (IsDeathFlag() != true)
	{
		// �G�t�F�N�g�W�F�l���[�^�[�x�[�X
		CEffectGeneratorBase::Update();

		// �����J�E���g���J�E���g�_�E������
		m_nCntCreatTime--;
		if (m_nCntCreatTime <= 0)
		{
			// �J�E���g��߂�
			m_nCntCreatTime = m_nCreatSpan;

			D3DXVECTOR3 RandRotA = {};	// �p�x�̌v�Z�p�i�[�ϐ�
			// �͈͓��ŗ����𐶐�
			// ����������i�V�[�h�t���j
			std::random_device rd;
			std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^
			// ����
			std::uniform_real_distribution<float> dist(-m_fDiffusion, m_fDiffusion);
			RandRotA.x = (dist(gen));
			RandRotA.y = (dist(gen));
			RandRotA.z = (dist(gen));

			RandRotA += m_rot;	// �W�F�l���[�^�[�̌��������Z
			D3DXVec3Normalize(&RandRotA, &RandRotA);	// �m�[�}���C�Y

			D3DXVECTOR3 move = RandRotA * m_fLength;	// �ړ��ʂ���Z
			//����
			CEffectParticle::create(GetPos(), move, m_pCor, m_aTexture, m_nLifeParticle);
		}
	}
}
/// <summary>
/// �`�揈��(�W�F�l���[�^�[�͕`�悵�Ȃ����ߋ�)
/// </summary>
void CEffectGeneratorParticle::Draw()
{}
/// <summary>
/// �e�N�X�`���ݒ�
/// </summary>
/// <param name="aFileName">�e�N�X�`���t�@�C���p�X</param>
void CEffectGeneratorParticle::SetTexture(const char* aFileName)
{
	// �f�X�t���O�������Ă��Ȃ����
	if (IsDeathFlag() != true)
	{
		m_aTexture = aFileName;
	}
}
/// <summary>
/// ����
/// </summary>
/// <param name="rot">�p�[�e�B�N���̃x�N�g��</param>
/// <param name="fLength">�^����</param>
/// <param name="Diffusion">�g�U��</param>
/// <param name="Cor">�F</param>
/// <param name="nParticleLife">�p�[�e�B�N���̂��ǂꂮ�炢�ؗ����邩</param>
/// <param name="nCreatSpan">�����Ԋu</param>
/// <returns>// �쐬�����I�u�W�F�N�g��Ԃ�</returns>
CEffectGeneratorParticle* CEffectGeneratorParticle::create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan)
{
	// �W�F�l���[�^�[�p�C���X�^���X�m��
	CEffectGeneratorParticle* p = new CEffectGeneratorParticle();

	// �C���X�^���X�m�ۂ����s���Ă�����
	if (!p)
	{
		return nullptr;
	}


	// ������
	if (!(p->Init()))// ���������s���͉������ null ��Ԃ�
	{
		delete p;
		p = nullptr;
		return nullptr;
	}

	// �������
	D3DXVec3Normalize(&(p->m_rot),&rot);		// ����
	p->m_fLength = fLength;						// ����
	p->m_fDiffusion = AngleToRadian(Diffusion);	// �g�U��(�p�x)
	p->m_pCor = Cor;							// �F
	p->m_nLifeParticle = nParticleLife;			// �p�[�e�B�N���̃��C�t
	// ���ԊǗ�
	p->m_nCreatSpan = nCreatSpan;	// �����Ԋu

	// �쐬�����I�u�W�F�N�g��Ԃ�
	return p;
}
/// <summary>
/// ����
/// </summary>
/// <param name="rot">�p�[�e�B�N���̃x�N�g��</param>
/// <param name="fLength">�^����</param>
/// <param name="Diffusion">�g�U��</param>
/// <param name="Cor">�F</param>
/// <param name="nParticleLife">�p�[�e�B�N���̂��ǂꂮ�炢�ؗ����邩</param>
/// <param name="nCreatSpan">�����Ԋu</param>
/// <param name="nLife">�W�F�l���[�^�[���̂̎���</param>
/// <returns></returns>
CEffectGeneratorParticle* CEffectGeneratorParticle::create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan, int nLife)
{
	// �W�F�l���[�^�[�p�C���X�^���X�m��
	CEffectGeneratorParticle* p = new CEffectGeneratorParticle();

	// ������
	p->Init();

	// �������
	D3DXVec3Normalize(&(p->m_rot), &rot);	// ����
	p->m_fLength = fLength;					// ����
	p->m_fDiffusion = AngleToRadian(Diffusion);	// �g�U��(�p�x)
	p->m_pCor = Cor;						// �F
	p->m_nLifeParticle = nParticleLife;		// �p�[�e�B�N���̃��C�t
	// ���ԊǗ�
	p->m_nCreatSpan = nCreatSpan;			// �����Ԋu
	p->SetLife(nLife);						// �����ݒ�

	// �C���X�^���X��Ԃ�
	return p;
}