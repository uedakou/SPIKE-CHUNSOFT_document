//============================================
//
// �G�t�F�N�g[effect_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_particle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CEffectParticle::CEffectParticle()
{
	m_move = { 0.0f, 0.0f, 0.0f };			// ������������
	m_cor = { 1.0f, 1.0f, 1.0f , 1.0f };	// �F��������
	m_nLife = 0;							// ������������
	//SetSiz(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CEffectParticle::~CEffectParticle()
{
}
/// <summary>
/// �X�V
/// </summary>
void CEffectParticle::Update()
{
	// �r���{�[�h�X�V
	CObjectBillbord::Update();

	// �ړ��ʉ��Z
	AddPos(m_move);

	// ���������炷
	m_nLife--;
	// ������0�Ȃ玀�S�t���O�𗧂Ă�
	if (m_nLife <= 0)
	{
		DeathFlag();
	}
}
void CEffectParticle::Draw()
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();// �o�[�e�b�N�X�o�b�t�@�擾
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();		// �e�N�X�`��
	D3DXMATRIX mtxWorld = GetMaxWorld();	// ���[���h�}�g���N�X
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���N�X
	D3DXMATRIX matView;	// �r���[�}�g���N�X

	// �g�����X�t�H�[�����擾
	X x = GetX();
	if (!pDevice) {
		// �f�o�C�X�������ȏꍇ�̃G���[�n���h�����O
		return;
	}

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �r���[�}�g���N�X�̎擾
	if (FAILED(pDevice->GetTransform(D3DTS_VIEW, &matView))) {
		// �r���[�}�g���N�X�擾���s���̏���
		return;
	}

	// �r���[�}�g���N�X�̋t�s����v�Z
	if (D3DXMatrixInverse(&mtxWorld, NULL, &matView) == NULL) {
		// �t�s��v�Z���s���̏���
		return;
	}
	// ���[���h�}�g���N�X�̈ʒu��������
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;
	// �I�u�W�F�N�g�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// ���_�o�b�t�@��ݒ�
	if (pVtxBuff) {
		pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));
	}
	else {
		// ���_�o�b�t�@�������ȏꍇ�̏���
		return;
	}
	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���u�����f�B���O
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �e�N�X�`��
	pDevice->SetTexture(0, pTexture);
	//	�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
/// <summary>
/// �p�[�e�B�N���G�t�F�N�g����
/// </summary>
/// <param name="pos">�ʒu</param>
/// <param name="move">����</param>
/// <param name="cor">�F</param>
/// <param name="tex">�e�N�X�`��</param>
/// <param name="nLife">����</param>
/// <returns>���������|�C���^</returns>
CEffectParticle* CEffectParticle::create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR cor, string tex, int nLife)
{
	// �C���f�b�N�X���m��
	CEffectParticle* p = new CEffectParticle();

	p->SetPos(pos);	// �ʒu�ݒ�
	p->Init();		// ������
	p->SetColor(cor);	// �F�ݒ�
	p->SetTexture(tex.c_str());	// �e�N�X�`��
	p->m_move = move;	// �����ݒ�
	p->m_nLife = nLife;	// ����

	// �C���f�b�N�X��Ԃ�
	return p;
}
