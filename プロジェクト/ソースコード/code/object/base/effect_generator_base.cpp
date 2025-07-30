//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_base.cpp]
// Author:Uedakou
// 
//============================================
#include "effect_generator_base.h"	// �G�t�F�N�g�W�F�l���[�^�[
//============================================
// �R���X�g
//============================================
CEffectGeneratorBase::CEffectGeneratorBase()
{
	m_nLife = -1;			// ���C�t
	m_nCntLifeTime = 0;		// �o�ߎ���
	SetNormalDraw(false);	// �ʏ�`������Ȃ�
	SetPoseDraw(false);		// �|�[�Y���`�悵�Ȃ�

}
//============================================
// �f�X�g��
//============================================
CEffectGeneratorBase::~CEffectGeneratorBase()
{
}
//============================================
// ������
//============================================
bool CEffectGeneratorBase::Init()
{
	return true;
}
//============================================
// �I��
//============================================
void CEffectGeneratorBase::Uninit()
{
}
//============================================
// �X�V
//============================================
void CEffectGeneratorBase::Update()
{
	// �o�ߎ��Ԃ��J�E���g
	m_nCntLifeTime++;

	// �o�ߎ��Ԃ��������z�����玀�S�t���O�𗧂Ă�
	// �i-1�̏ꍇ�̂ݎ��������j
	if (m_nLife != -1 &&
		m_nCntLifeTime >= m_nLife)
	{
		DeathFlag();
	}
}
//============================================
// �`��
//============================================
void CEffectGeneratorBase::Draw()
{
}