//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_base.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFECT_GENERATOR__BASE_H_
#define _EFFECT_GENERATOR__BASE_H_
#include "object.h"	// �I�u�W�F�N�g
class CEffectGeneratorBase : public CObject
{
public:
	CEffectGeneratorBase();
	virtual ~CEffectGeneratorBase();
	bool Init()		override;	// ������
	void Uninit()	override;	// �I��	
	void Update()	override;	// �X�V
	void Draw()		override;	// �`��

	// ����
	void SetLife(int nSpan) { m_nLife = nSpan; }	// �����ݒ�
	int GetLife() { return m_nLife; }	// �����擾
	int GetCntTime() { return m_nCntLifeTime; }	// �o�ߎ��Ԏ擾

private:
	// ���ԊǗ�
	int m_nLife;	// �G�t�F�N�g�̎���
	int m_nCntLifeTime;	// ���݂̌o�ߎ���

};
#endif // !_EFFECT_GENERATOR__BASE_H_