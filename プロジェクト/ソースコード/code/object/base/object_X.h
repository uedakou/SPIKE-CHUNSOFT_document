//===========================================
// 
// �I�u�W�F�N�gX[renderer.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _OBJECT_X_H_
#define _OBJECT_X_H_

#include "object.h"

#define MAX_MODEL_X 1024
#define MAX_TEX_X 8	// 1���f���̃e�N�X�`���ő吔

class CModelX
{
public:
	CModelX();
	~CModelX();
	LPD3DXBUFFER GetBuffMtx() { return m_pBuffMat; }
	DWORD GetNumMat() { return m_dwNumMat; }
	LPD3DXMESH GetMesh() { return m_pMesh; }
	LPDIRECT3DTEXTURE9 GetTexture(int nCnt) { return m_pTexture[nCnt]; }

	static void ReleaseAll();
	static int Load(const char* aFileName);
	static CModelX* GetModel(int nID);
private:
	// ���X�g
	static CModelX* m_pTop;	// �g�b�v
	static CModelX* m_pCur;	// �Ō��
	CModelX* m_pNext;		// ��
	CModelX* m_pPrev;		// �O

	LPD3DXBUFFER m_pBuffMat;					// �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;							// �}�e���A���̐�
	LPD3DXMESH m_pMesh;							// ���b�V��(���_���)�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX_X];	// �v���C���[�̃e�N�X�`��[�e�N�X�`����]

};

class CObjectX :public CObject
{
public:
	enum class TYPE {
		TYPE_NULL = 0,
		MOTION_PARTS,	// ���[�V�����p�[�c
		OBSTACLES,	// ��Q��
		MAX,
	};
	CObjectX();
	CObjectX(int nPriority);
	virtual ~CObjectX()		override;
	virtual bool Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��

	void SetType(TYPE type) { m_type = type; }	// ��ސݒ�
	void SetMtxworld(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	// ���[���h�}�g���N�X
	void SetID(int nID) { m_nID = nID; }	// ���f��ID�ݒ�



	TYPE GetType() { return m_type; }	// ��ގ擾
	D3DXMATRIX GetMtx() { return m_mtxWorld; }	// ���[���h�}�g���N�X�擾
	int GetID() { return m_nID; }	// �擾



	static CObjectX* create(const char* aFileName);	// ����
	static CObjectX* create(string aFileName);	// ����
protected:
private:
	TYPE m_type;	// ���
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���N�X

	static int m_nNum;	// X�I�u�W�F�N�g��
	int m_nID;	// ���f��ID


};






#endif // !_OBJECT_X_H_