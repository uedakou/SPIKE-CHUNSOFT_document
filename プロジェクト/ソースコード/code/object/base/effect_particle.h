//============================================
//
// �G�t�F�N�g[effect_paeticle.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFCTO_PARTICLE_H_
#define _EFFCTO_PARTICLE_H_
#include "object_billboard.h"

class CEffectParticle : public CObjectBillbord
{
public:
	CEffectParticle();
	virtual ~CEffectParticle();

	void Update()override;	// �X�V
	void Draw()override;	// �`��

	// ����
	static CEffectParticle* create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR cor, string tex, int nLife);
private:
	// ��{���
	D3DXVECTOR3 m_move;	// ����
	D3DXCOLOR m_cor;		// �F
	// ���ԊǗ�
	int m_nLife;	// ����
};



#endif // !_EFFCTO_PARTICLE_H_