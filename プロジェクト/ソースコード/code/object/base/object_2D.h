//===========================================
// 
// �|���S��2[object_2D.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"	// �I�u�W�F�N�g
#include "../../base/pch.h"	// �v���R���p�C��
#include <stdio.h>


class CObject2D : public CObject
{
public:
	CObject2D();
	CObject2D(int nPriority);
	virtual ~CObject2D()	override;
	virtual bool Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��

	// �ݒ�
	virtual void SetX(X x)		override;
	virtual void SetX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) override;
	virtual void SetPos(const D3DXVECTOR3 pos) override;	// �ʒu�ݒ�
	virtual void SetPosX(const float x) override;	// �ʒu�ݒ�
	virtual void SetPosY(const float y) override;	// �ʒu�ݒ�
	virtual void SetPosZ(const float z) override;	// �ʒu�ݒ�
	virtual void SetRot(const D3DXVECTOR3 rot) override;	// �����ݒ�
	virtual void SetRotX(const float x) override;	// �����ݒ�
	virtual void SetRotY(const float y) override;	// �����ݒ�
	virtual void SetRotZ(const float z) override;	// �����ݒ�
	virtual void SetScl(const D3DXVECTOR3 siz) override;	// �傫��(�{��)�ݒ�
	virtual void SetSclX(const float x) override;	// �傫��(�{��)�ݒ�
	virtual void SetSclY(const float y) override;	// �傫��(�{��)�ݒ�
	virtual void SetSclZ(const float z) override;	// �傫��(�{��)�ݒ�
	virtual void SetSiz(const D3DXVECTOR3 siz) { m_siz = siz; };	// �傫���ݒ�
	virtual void SetSizX(const float x) { m_siz.x = x; };	// �傫���ݒ�
	virtual void SetSizY(const float y) { m_siz.y = y; };	// �傫���ݒ�
	virtual void SetSizZ(const float z) { m_siz.z = z; };	// �傫���ݒ�
	virtual void SetUV(D3DXVECTOR4 UV);	// UV�ݒ�


	void SetColor(D3DXCOLOR col);	// �F�ݒ�
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtx) { m_pVtxBuff = pVtx; }	// �o�[�e�b�N�X�o�b�t�@�ݒ�
	void SetTexture(const LPDIRECT3DTEXTURE9 ptex);	// �e�N�X�`���ݒ�
	void SetTexture(const char aName[MAX_TXT]);		// �e�N�X�`���ݒ�
	void SetTexture(std::string aName);				// �e�N�X�`���ݒ�

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_pVtxBuff; }	// �o�b�t�@�擾
	D3DXCOLOR GetColor() { return m_col; }	// �F�擾
	const D3DXVECTOR3 GetSiz() { return m_siz; }	// �傫���擾

	// ���Z
	virtual void AddX(X x) override;	// �g�����X�t�H�[���ݒ�
	virtual void AddX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) override;	// �g�����X�t�H�[���ݒ�
	virtual void AddPos(const D3DXVECTOR3 pos) override;	// �ʒu�ݒ�
	virtual void AddPosX(const float x) override;	// �ʒu�ݒ�
	virtual void AddPosY(const float y) override;	// �ʒu�ݒ�
	virtual void AddPosZ(const float z) override;	// �ʒu�ݒ�
	virtual void AddRot(const D3DXVECTOR3 rot) override;	// �����ݒ�
	virtual void AddRotX(const float x) override;	// �����ݒ�
	virtual void AddRotY(const float y) override;	// �����ݒ�
	virtual void AddRotZ(const float z) override;	// �����ݒ�
	virtual void AddScl(const D3DXVECTOR3 siz) override;	// �傫���ݒ�
	virtual void AddSclX(const float x) override;	// �傫���ݒ�
	virtual void AddSclY(const float y) override;	// �傫���ݒ�
	virtual void AddSclZ(const float z) override;	// �傫���ݒ�

	static CObject2D* create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);					// ����
	static CObject2D* create(int nPriority, D3DXVECTOR3 pos, D3DXVECTOR3 siz);	// ����
private:
	// �v���C�x�[�g�֐�
	void SetVtxPos();	// �o�[�e�b�N�X�̈ʒu��ݒ�
private:
	// �v���C�x�[�g�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	D3DXCOLOR m_col;					// �F
	D3DXVECTOR3 m_siz;					// �傫��
	int m_nNumVertices;	// ���_��


	static const D3DXCOLOR s_colDef;	// �����F
	static const int s_nNumVertices;	// �������_��
};

#endif // !_OBJECT_H_