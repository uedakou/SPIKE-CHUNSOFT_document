//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_paeticle.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFECT_GENERATOR_PAETICLE_H_
#define _EFFECT_GENERATOR_PAETICLE_H_
#include "effect_generator_base.h"	// �G�t�F�N�g�W�F�l���[�^�[

class CEffectGeneratorParticle : public CEffectGeneratorBase
{
public:
	CEffectGeneratorParticle();
	virtual ~CEffectGeneratorParticle();
	bool Init()		override;	// ������
	void Uninit()	override;	// �I��
	void Update()	override;	// �X�V
	void Draw()		override;	// �`��
	// �������
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						// ����
	void SetLength(float fLength) { m_fLength = fLength; }				// ����
	void SetDiffusion(float fDiffusion) { m_fDiffusion = fDiffusion; }	// �g�U��(�p�x)
	void SetCole(D3DXCOLOR Cor) { m_pCor = Cor; }						// �F
	void SetTexture(const char* aFileName);		// �e�N�X�`���ݒ�

	// ����
	static CEffectGeneratorParticle* create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan);	// ����(����,����, �g�U�p�x,�F,�p�[�e�B�N����������, �Ԋu)
	static CEffectGeneratorParticle* create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan, int nLife);	// ����(����,����, �g�U�p�x,�F,�p�[�e�B�N����������, �Ԋu,�W�F�l���[�^�[��������)
private:
	// �������
	D3DXVECTOR3 m_rot;	// ����
	float m_fLength;	// �^����
	float m_fDiffusion;	// �g�U��(�p�x)
	D3DXCOLOR m_pCor;	// �F
	int m_nLifeParticle;	// �p�[�e�B�N���̃��C�t
	string m_aTexture;	// �e�N�X�`��
	// ���ԊǗ�
	int m_nCreatSpan;		// �����Ԋu
	int m_nCntCreatTime;	// ��������
	static const string s_aDefltTexture;

};

#endif // !_EFFECT_GENERATOR__PAETICLE_H_