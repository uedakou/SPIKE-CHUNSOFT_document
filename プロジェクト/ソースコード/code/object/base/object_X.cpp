//===========================================
// 
// �I�u�W�F�N�gX[object_X.cpp]
// Auther:UedaKou
// 
//===========================================
#include "object_X.h"	// �I�u�W�F�N�gX
#include "../../base/manager.h"	// �}�l�[�W���[
//********************************************
// ���f��X
//********************************************
CModelX* CModelX::m_pTop;
CModelX* CModelX::m_pCur;

//============================================
// �R���X�g���N�^
//============================================
CModelX::CModelX()
{
	for (int nCnt = 0; nCnt < MAX_TEX_X; nCnt++)
	{
		m_pTexture[nCnt] = nullptr;
	}
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
}
//============================================
// �f�X�g��
//============================================
CModelX::~CModelX()
{
}
//============================================
// �����[�X����
//============================================
void CModelX::ReleaseAll()
{
	CModelX* pModel = m_pTop;
	CModelX* pNext;
	while (pModel != nullptr)
	{
		pNext = pModel;
		if (pModel->m_pBuffMat != nullptr)
		{
			pModel->m_pBuffMat->Release();
			pModel->m_pBuffMat = nullptr;
		}
		if (pModel->m_pMesh != nullptr)
		{
			pModel->m_pMesh->Release();
			pModel->m_pMesh = nullptr;
		}
		for (int nCntTex = 0; nCntTex < MAX_MODEL_X; nCntTex++)
		{
			if (pModel->m_pTexture[nCntTex] != nullptr)
			{
				pModel->m_pTexture[nCntTex]->Release();
				pModel->m_pTexture[nCntTex] = nullptr;
			}
		}
		delete pModel;
		pModel = pNext;
	}
}

//============================================
// �ǂݍ���
//============================================
int CModelX::Load(const char* aFileName)
{
	LPD3DXBUFFER pBuffMat = nullptr;	// �}�e���A���ւ̃|�C���^
	DWORD dwNumMat = 0;					// �}�e���A���̐�
	LPD3DXMESH pMesh = nullptr;			// ���b�V��(���_���)�ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�擾
	D3DXLoadMeshFromX(
		aFileName,				// ���f����
		D3DXMESH_SYSTEMMEM,
		pDevice,				// �f�o�C�X
		NULL,					// NULL
		&pBuffMat,				// �o�b�t�@�}�g���N�X
		NULL,					// NULL
		&dwNumMat,				// �}�e���A����
		&pMesh);				// ���b�V��

	if (pBuffMat == nullptr)
	{
		Beep(1200, 300);

		return -1;
	}

	CModelX* pModel = m_pTop;	// �I�u�W�F�N�g
	CModelX* pNext = nullptr;				// ���I�u�W�F�N�g
	int nCnt = 0;
	while (pModel != nullptr)
	{// �g�b�v���L����
		pNext = pModel->m_pNext;// �����i�[
		if (pModel->m_pMesh == pMesh &&
			pModel->m_pBuffMat == pBuffMat &&
			pModel->m_dwNumMat == dwNumMat)
		{// �����f�[�^����������
			return nCnt;
		}
		pModel = pNext;

		nCnt++;
	}
	// �f�[�^�̓����Ă��Ȃ����܂ŌJ��Ԃ�����
	if (m_pTop == nullptr)
	{// �g�b�v����Ȃ�g�b�v������
		pModel = new CModelX;
		m_pTop = pModel;
		m_pCur = pModel;
	}
	else
	{
		pModel = new CModelX;
		pModel->m_pPrev = m_pCur;
		m_pCur->m_pNext = pModel;
		m_pCur = pModel;
	}
	pModel->m_pBuffMat = pBuffMat;
	pModel->m_dwNumMat = dwNumMat;
	pModel->m_pMesh = pMesh;

	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pModel->m_pBuffMat->GetBufferPointer();	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	for (int nCntMat = 0; nCntMat < (int)pModel->m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{// �}�e���A���t�@�C�������݂���
			// �e�N�X�`��
			D3DXCreateTextureFromFile(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&pModel->m_pTexture[nCntMat]);
		}
	}
	return nCnt;
}
//============================================
// ���f���擾
//============================================
CModelX* CModelX::GetModel(int nID)
{
	int nCnt = 0;
	CModelX* pObject,* pNext;//	�I�u�W�F�N�g
	pObject = m_pTop;
	while (pObject != nullptr)
	{
		pNext = pObject->m_pNext;
		if (nCnt == nID)
		{
			return pObject;
		}
		pObject = pNext;
		nCnt++;
	}
	return nullptr;
}



int CObjectX::m_nNum = 0;
//============================================
// �R���X�g���N�^
//============================================
CObjectX::CObjectX()
{
	m_nNum++;
}
CObjectX::CObjectX(int nPriority): CObject(nPriority)
{
	m_nNum++;
}
//============================================
// �f�X�g���N�^
//============================================
CObjectX::~CObjectX()
{
	m_nNum--;
}
//============================================
// ������
//============================================
bool CObjectX::Init()
{
	return true;
}
//============================================
// �I��
//============================================
void CObjectX::Uninit()
{
}
//============================================
// �X�V
//============================================
void CObjectX::Update()
{
}
//============================================
// �`��
//============================================
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�擾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���N�X	
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	CModelX* pModel = CModelX::GetModel(m_nID);
	X x = GetX();

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, x.rot.y, x.rot.x, x.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pModel->GetBuffMtx()->GetBufferPointer();

	// �}�e���A���T�C�Y���J��Ԃ�
	for (int nCntMat = 0; nCntMat < (int)pModel->GetNumMat(); nCntMat++)
	{
		// �F
		//pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
		//pMat[nCntMat].MatD3D.Diffuse.a = 0.1f;

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pModel->GetTexture(nCntMat));

		//���f��(�p�[�c)�̕`��
		pModel->GetMesh()->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}
//============================================
// ����
//============================================
CObjectX* CObjectX::create(const char* aFileName)
{
	int nID = 0;
	nID = CModelX::Load(aFileName);
	if (nID != 0)
	{

	}
	CObjectX* pObjectX = new CObjectX;
	pObjectX->SetID(nID);
	pObjectX->Init();

	return pObjectX;
}
CObjectX* CObjectX::create(string aFileName)
{
	int nID = 0;
	nID = CModelX::Load(aFileName.c_str());
	if (nID != 0)
	{

	}
	CObjectX* pObjectX = new CObjectX;
	pObjectX->SetID(nID);
	pObjectX->Init();

	return pObjectX;
}