//===========================================
// 
// ���[�V����[motion.cpp]
// Auther:UedaKou
// 
//===========================================
#include "motion.h"
#include <fstream>
#include <iostream>
#include "../../base/pch.h"

//============================================
// �R���X�g���N�^(�p�[�c�f�[�^)
//============================================
CPartsData::CPartsData()
{
	// �g�����X�t�H�[��������
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
//============================================
// �f�X�g��(�p�[�c�f�[�^)
//============================================
CPartsData::~CPartsData()
{
}

//============================================
// �R���X�g���N�^(�L�[�t���[��)
//============================================
CKye::CKye()
{
	// �p�[�c�C���f�b�N�X��nullptr�ɂ���
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (m_pParts[nCntParts] != nullptr)
		{
			m_pParts[nCntParts] = nullptr;
		}
	}
	// �t���[����������
	m_nFrame = 0;
}
//============================================
// �f�X�g��(�L�[�t���[��)
//============================================
CKye::~CKye()
{
	// �p�[�c�폜
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		delete m_pParts[nCnt];
		m_pParts[nCnt] = nullptr;
	}
}
//============================================
// ����
//============================================
CPartsData* CKye::createPartsData()
{
	// �󂢂Ă��郊�X�g�ɓ����
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// �p�[�c�f�[�^���X�g���󂢂Ă�����
		if (m_pParts[nCnt] == nullptr)
		{
			// �p�[�c�f�[�^����
			m_pParts[nCnt] = new CPartsData;
			// �C���f�b�N�X��Ԃ�
			return m_pParts[nCnt];
		}
	}
	// ���X�g���S�Ė��܂��Ă�����0��Ԃ�
	return 0;
}

//============================================
// �R���X�g���N�^
//============================================
CMotion::CMotion()
{
	// Kye��S��nulptr�ɂ���
	for (int nCntkye = 0; nCntkye < MAX_KYE; nCntkye++)
	{
		m_pKye[nCntkye] = nullptr;
	}
	// �L�[����������
	m_nNumKye = 0;

	// ���[�v������
	m_bLoop = 0;
}
//============================================
// �f�X�g��
//============================================
CMotion::~CMotion()
{
	// �L�[��S�ĉ��
	for (int nCnt = 0; nCnt < MAX_KYE; nCnt++)
	{
		if (m_pKye[nCnt] != nullptr)
		{
			delete m_pKye[nCnt];
			m_pKye[nCnt] = nullptr;
		}
	}
}
//============================================
// �L�[�t���[������
//============================================
void CMotion::createKye()
{
	// ���X�g�̋󂢂Ă��鏊�ɐ���
	for (int nCntKye = 0; nCntKye < m_nNumKye; nCntKye++)
	{
		if (m_pKye[nCntKye] == nullptr)
		{
			m_pKye[nCntKye] = new CKye;
			return;
		}
	}
}


//============================================
// �R���X�g(���݃��[�V����)
//============================================
CNowMotion::CNowMotion()
{
	m_nCntMotion = 0;	// ���[�V������������
	m_nCntKye = 0;		// �L�[�J�E���g��������
	m_nCntFrame = 0;	// �t���[���J�E���g��������
}
//============================================
// �f�X�g��(���݃��[�V����)
//============================================
CNowMotion::~CNowMotion()
{
}

//============================================
// �R���X�g���N�^(�p�[�c)
//============================================
CParts::CParts()
{
	// ��{�ʒu
	m_xBasic.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	// �ǉ��ʒu
	m_xOffset.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ����
	m_xMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nParent = -1;	// �p�[�c��������

	m_bDisplay = 0;		// �\�����邩�ǂ���

	m_bDoMotion = true;	// ���[�V���������邩�ݒ�

	m_pNowMotion = new CNowMotion;	// ���[�V��������

	SetNormalUpdate(false);
}

CParts::CParts(int nPriority) : 
	CObjectX(nPriority)
{
	// ��{�ʒu
	m_xBasic.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xBasic.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	// �ǉ��ʒu
	m_xOffset.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xOffset.scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ����
	m_xMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_xMove.scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nParent = -1;	// �e

	//m_nIndex = 0;		// �p�[�c���// 
	m_bDisplay = 0;		// �\�����邩�ǂ���

	m_pNowMotion = new CNowMotion;
}
//============================================
// �f�X�g��(�p�[�c)
//============================================
CParts::~CParts()
{
	delete m_pNowMotion;
}
//============================================
// ������(�p�[�c)
//============================================
bool CParts::Init()
{
	SetNormalUpdate(false);	// �ʏ펞�X�V�ݒ�
	SetPoseUpdate(false);	// �ʏ펞�X�V�ݒ�
	SetNormalDraw(false);	// �ʏ펞�`��ݒ�
	SetPoseDraw(false);		// �|�[�Y���`��ݒ�
	CObjectX::Init();
	return true;
}
//============================================
// �I��(�p�[�c)
//============================================
void CParts::Uninit()
{
	CObjectX::Uninit();
}
//============================================
// �X�V(�p�[�c)
//============================================
void CParts::Update()
{
	// ���������Z
	//m_nID;
	m_xOffset.pos += m_xMove.pos;
	m_xOffset.rot += m_xMove.rot;
	m_xOffset.scl += m_xMove.scl;
	// ���Z�����v�Z
	D3DXVECTOR3 pos, rot, siz;
	pos = m_xOffset.pos + m_xBasic.pos;
	rot = m_xOffset.rot + m_xBasic.rot;
	siz = m_xOffset.scl + m_xBasic.scl;
	// �v�Z���𔽉f
	CObjectX::SetX(pos, rot, siz);
	CObjectX::Update();
}
//============================================
// �`��(�p�[�c)
//============================================
void CParts::Draw()
{
#if 0
	CObjectX::Draw();
#else
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�擾
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld, mtxParent;	// �v�Z�p�}�g���N�X	
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	
	CModelX* pModel = CModelX::GetModel(GetID());

	X x = GetX();

	mtxWorld = GetMtx();
	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, x.rot.y, x.rot.x, x.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	mtxRot = m_mtxParent;

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	SetMtxworld(mtxWorld);

	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

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
#endif // 0
}
void CParts::SetMotion(int nMotion)
{
	m_pNowMotion->SetMotion(nMotion);
	m_pNowMotion->SetKye(0);
	m_pNowMotion->SetFrame(0);
}

void CParts::SetMoveX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz, int nFrame)
{
	X x;
	x.pos = pos - m_xOffset.pos;
	x.rot = rot - m_xOffset.rot;
	x.scl = siz - m_xOffset.scl;


	if (x.rot.x > D3DX_PI)
	{
		x.rot.x -= TAU;
	}
	else if (x.rot.x < -D3DX_PI)
	{
		x.rot.x += TAU;
	}

	if (x.rot.y > D3DX_PI)
	{
		x.rot.y -= TAU;
	}
	else if (x.rot.y < -D3DX_PI)
	{
		x.rot.y += TAU;
	}

	if (x.rot.z > D3DX_PI)
	{
		x.rot.z -= TAU;
	}
	else if (x.rot.z < -D3DX_PI)
	{
		x.rot.z += TAU;
	}

	m_xMove.pos.x = x.pos.x / (float)nFrame;
	m_xMove.pos.y = x.pos.y / (float)nFrame;
	m_xMove.pos.z = x.pos.z / (float)nFrame;
	m_xMove.rot.x = x.rot.x / (float)nFrame;
	m_xMove.rot.y = x.rot.y / (float)nFrame;
	m_xMove.rot.z = x.rot.z / (float)nFrame;
	m_xMove.scl.x = x.scl.x / (float)nFrame;
	m_xMove.scl.y = x.scl.y / (float)nFrame;
	m_xMove.scl.z = x.scl.z / (float)nFrame;
	m_pNowMotion->SetFrame(nFrame);
}

const bool CObjectMotion::s_bMotion = true;
//============================================
// �R���X�g���N�^
//============================================
CObjectMotion::CObjectMotion()
{
	// ���f��
	m_nModel = 0;

	// ���[�V�����f�[�^
	m_nNumMotion = 0;
	for (int i = 0; i < MAX_MOTION; i++)
	{
		m_pMotion[i] = nullptr;
	}

	// �p�[�c
	m_nParts = 0;
	for (int i = 0; i < MAX_PARTS; i++)
	{
		m_pParts[i] = nullptr;
	}

	//	���݃��[�V����
	m_nNextMotion = 0;
	m_nNowMotion = 0;

	m_bMotion = s_bMotion;	// ���[�V�����𓮂������ǂ�����ݒ�
}

//============================================
// �f�X�g��
//============================================
CObjectMotion::~CObjectMotion()
{
	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (m_pMotion[nCnt])
		{
			delete m_pMotion[nCnt];
		}
	}
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{

		if (m_pParts[nCnt] != nullptr)
		{
			m_pParts[nCnt]->DeathFlag();
			m_pParts[nCnt] = nullptr;
		}
	}

}
//============================================
// ������
//============================================
bool CObjectMotion::Init()
{
	for (int nCnt = 0; nCnt < m_nNumMotion; nCnt++)
	{
		CPartsData* TargetMotion = m_pMotion[GetNextMotion()]->GetKye(0)->GetPartsData(nCnt);	// �ڕW���[�V�����擾
		// ������ݒ�
		m_pParts[nCnt]->SetOffsetX(
			TargetMotion->GetPosTarget(),	// �ʒu
			TargetMotion->GetRotTarget(),	// ����
			TargetMotion->GetSclTarget());	// �傫��
		m_pParts[nCnt]->GetNowMotion()->SetFrame(1);
		m_pParts[nCnt]->SetMoveX(
			TargetMotion->GetPosTarget(),	// �ʒu
			TargetMotion->GetRotTarget(),	// ����
			TargetMotion->GetSclTarget(),
			m_pMotion[GetNextMotion()]->GetKye(0)->GetFrame());	// �傫��
	}
	return true;
}
//============================================
// �I������
//============================================
void CObjectMotion::Uninit()
{
	for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
	{
		m_pParts[nCntParts]->Uninit();
	}
	CObject::DeathFlag();
}
//============================================
// �X�V����
//============================================
void CObjectMotion::Update()
{
	// ���[�V�����̓�����true�Ȃ�
	if (m_bMotion)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�擾
		D3DXMATRIX mtxRot0, mtxRot1, mtxTrans;	// �v�Z�p�}�g���N�X
		X x = GetX();
		// ���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);
		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot1, x.rot.y, x.rot.x, x.rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot1);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[�V����
		for (int nCntParts = 0; nCntParts < m_nParts; nCntParts++)
		{
			CNowMotion* pNowMotion = m_pParts[nCntParts]->GetNowMotion();
			CMotion* pTargetMotion0 = m_pMotion[pNowMotion->GetMotion()];

			pNowMotion->AddFrame(-1);	// �t���[�����P�i�߂�
			int nNowFrame = pNowMotion->GetFrame();
			if (nNowFrame <= 0)
			{// �L�[�̃t���[�����o�߂�����
				pNowMotion->AddKye(1);	// kye���P�i�߂�
				int nNowKye = pNowMotion->GetKye(),
					nTarget = pTargetMotion0->GetNumKye();
				if (nNowKye >= nTarget)
				{// ���[�V�����̃L�[���o�߂�����
					pNowMotion->SetKye(0);
					bool bLoop = pTargetMotion0->GetLoop();
					if (bLoop == false)
					{// ���[�v���Ȃ��Ȃ�
						pNowMotion->SetMotion(GetNextMotion());
					}
				}
				CPartsData* pTargetMotion1;	// ���[�V�����i�[�p
				pTargetMotion1 = m_pMotion[pNowMotion->GetMotion()]->GetKye(pNowMotion->GetKye())->GetPartsData(nCntParts);	// �ڕW���[�V�����擾
				// ������ݒ�
				m_pParts[nCntParts]->SetMoveX(
					pTargetMotion1->GetPosTarget(),	// �ʒu
					pTargetMotion1->GetRotTarget(),	// ����
					pTargetMotion1->GetSclTarget(),	// �傫��
					m_pMotion[pNowMotion->GetMotion()]->GetKye(0)->GetFrame());
			}
			m_pParts[nCntParts]->Update();
		}
	}
}
//============================================
// �`�揈��
//============================================
void CObjectMotion::Draw()
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (m_pParts[nCntParts] != nullptr)
		{
			int ParentID = m_pParts[nCntParts]->GetParentID();	// �eID�i�[�p
			// �e�����Ȃ�������
			if (ParentID == -1)
			{
				m_pParts[nCntParts]->SetParentMtx(m_mtxWorld);
			}
			// �e��������
			else
			{
				m_pParts[nCntParts]->SetParentMtx(m_pParts[ParentID]->GetMtx());
			}

			m_pParts[nCntParts]->Draw();
		}
	}
}

void CObjectMotion::SetReleaseScene(bool bRelease)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		m_pParts[nCnt]->SetReleaseScene(bRelease);
	}
	CObject::SetReleaseScene(bRelease);
}

CObjectMotion* CObjectMotion::create(const char* FileName)
{
	CObjectMotion* p = new CObjectMotion();

	p->Init();
	p->Load(FileName);

	return p;
}

CObjectMotion* CObjectMotion::create(string FileName)
{
	CObjectMotion* p = create(FileName.c_str());
	return p;
}

//============================================
// �ǂݍ��ݏ���
//============================================
bool CObjectMotion::Load(const char* aFileName)
{
	ifstream file(aFileName);  // �ǂݍ��ރt�@�C���̃p�X���w��
	if (file.fail()) {
		cerr << "�t�@�C�����J���܂���ł���\n";
		return false;
	}
	string str0, str1, str2 , str3;	// ������i�[�p
	string skip;			// �X�L�b�v�p�i�[
	string aModelFile[MAX_MOTION_MODEL];	// ���f���t�@�C��

	int nCntModel = 0;		// �ǂݍ��񂾃��f����
	int nCntPartsset0 = 0;	// �ǂݍ��񂾃p�[�c��(�x�[�X)
	int nCntPartsset1 = 0;	// �ǂݍ��񂾃p�[�c��
	int nCntMotion = 0;		// �ǂݍ��񂾃��[�V������
	int nCntKye = 0;		// �ǂݍ��񂾃L�[��


	// ���o���Z�q>>���g���ăf���~�^�ŋ�؂�ꂽ�P��C�l��ǂݍ���
	while (file >> str0)
	{
		// �R�����g�A�E�g
		if (str0[0] == '#')
		{
			getline(file, skip);	// ��s�X�L�b�v
		}
		// ���f����
		else if (str0.compare("NUM_MODEL") == 0)
		{
			file >> skip;	// �ꕶ�X�L�b�v
			file >> str1;	// ���f�������擾
			m_nModel = atoi(str1.c_str());
			getline(file, skip);	// ��s�X�L�b�v
		}
		// ���f���t�@�C�����O
		else if (str0.compare("MODEL_FILENAME") == 0 &&
			nCntModel < m_nModel &&
			m_nModel > 0)
		{
			file >> skip;	// �ꕶ�X�L�b�v
			file >> str1;	// ���f�������擾
			aModelFile[nCntModel] = str1;

			nCntModel++;
			getline(file, skip);	// ��s�X�L�b�v
		}
		// �L�����N�^�[���
		else if (str0.compare("CHARACTERSET") == 0)
		{
			while (file >> str1 &&
				str1.compare("END_CHARACTERSET") != 0)
			{
				// �p�[�c��
						// �R�����g�A�E�g
				if (str1[0] == '#')
				{
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("NUM_PARTS") == 0)
				{
					file >> skip;	// �ꕶ�X�L�b�v
					file >> str2;	// ���f�������擾
					m_nParts = atoi(str2.c_str());
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("MOVE") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("JUMP") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("RADIUS") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				else if (str1.compare("HEIGHT") == 0)
				{// ���g�p�̂��߃X�L�b�v
					getline(file, skip);	// ��s�X�L�b�v
				}
				// �p�[�c�f�[�^
				else if (str1.compare("PARTSSET") == 0)
				{
					if (nCntPartsset0 < MAX_PARTS)
					{
						m_pParts[nCntPartsset0] = new CParts(4);
						m_pParts[nCntPartsset0]->Init();
						while (file >> str2 &&
							str2.compare("END_PARTSSET") != 0)
						{
							// �R�����g�A�E�g
							if (str2[0] == '#')
							{
								getline(file, skip);	// ��s�X�L�b�v
							}
							// ���f�������擾
							else if (str2.compare("INDEX") == 0)
							{
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾

								int nID = CModelX::Load(aModelFile[atoi(str3.c_str())].c_str());
								m_pParts[nCntPartsset0]->CObjectX::SetID(nID);



								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("PARENT") == 0)
							{
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								int nParentID = atoi(str3.c_str());
								m_pParts[nCntPartsset0]->SetParentID(nParentID);

								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("POS") == 0)
							{
								D3DXVECTOR3 pos;// pos �i�[�p
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								pos.x = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								pos.y = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								pos.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicPos(pos);
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("ROT") == 0)
							{
								D3DXVECTOR3 rot;// rot �i�[�p
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								rot.x = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								rot.y = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								rot.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicRot(rot);
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("SIZ") == 0)
							{
								D3DXVECTOR3 siz;// siz �i�[�p
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// ���f�������擾
								siz.x = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								siz.y = stof(str3.c_str());
								file >> str3;	// ���f�������擾
								siz.z = stof(str3.c_str());
								m_pParts[nCntPartsset0]->SetBasicScl(siz);
								getline(file, skip);	// ��s�X�L�b�v
							}
						}
						nCntPartsset0++;
					}
				}
			}
		}
		else if (str0.compare("MOTIONSET") == 0)
		{
			if (nCntMotion < MAX_MOTION)
			{
				createMotion();
				while (file >> str1 &&
					str1.compare("END_MOTIONSET") != 0)
				{
					// �R�����g�A�E�g
					if (str1[0] == '#')
					{
						getline(file, skip);	// ��s�X�L�b�v
					}
					else if (str1.compare("LOOP") == 0)
					{
						file >> skip;	// �ꕶ�X�L�b�v
						file >> str2;	// ���f�������擾
						if (str2.compare("0") == 0)
						{ m_pMotion[nCntMotion]->SetLoop(false); }
						else
						{ m_pMotion[nCntMotion]->SetLoop(true); }
						getline(file, skip);	// ��s�X�L�b�v
					}
					else if (str1.compare("NUM_KEY") == 0)
					{
						file >> skip;	// �ꕶ�X�L�b�v
						file >> str2;	// ���f�������擾
						m_pMotion[nCntMotion]->SetNumKye(atoi(str2.c_str()));
						getline(file, skip);	// ��s�X�L�b�v
					}
					else if (str1.compare("KEYSET") == 0)
					{
						m_pMotion[nCntMotion]->createKye();
						while (file >> str2 &&
							str2.compare("END_KEYSET") != 0)
						{
							// �R�����g�A�E�g
							if (str2[0] == '#')
							{
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("FRAME") == 0)
							{
								file >> skip;	// �ꕶ�X�L�b�v
								file >> str3;	// �t���[�������擾
								m_pMotion[nCntMotion]->GetKye(nCntKye)->SetFrame(atoi(str3.c_str()));
								getline(file, skip);	// ��s�X�L�b�v
							}
							else if (str2.compare("KEY") == 0)
							{
								m_pMotion[nCntMotion]->GetKye(nCntKye)->createPartsData();
								while (file >> str3 &&
									str3.compare("END_KEY") != 0)
								{
									if (str3[0] == '#')
									{
										getline(file, skip);	// ��s�X�L�b�v
									}
									else if (str3.compare("POS") == 0)
									{
										D3DXVECTOR3 pos;// pos �i�[�p
										file >> skip;	// �ꕶ�X�L�b�v
										file >> str3;	// ���f�������擾
										pos.x = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										pos.y = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										pos.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetPosTarget(pos);
									}
									else if (str3.compare("ROT") == 0)
									{
										D3DXVECTOR3 rot;// pos �i�[�p
										file >> skip;	// �ꕶ�X�L�b�v
										file >> str3;	// ���f�������擾
										rot.x = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										rot.y = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										rot.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetRotTarget(rot);
									}
									else if (str3.compare("SIZ") == 0)
									{
										D3DXVECTOR3 siz;// pos �i�[�p
										file >> skip;	// �ꕶ�X�L�b�v
										file >> str3;	// ���f�������擾
										siz.x = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										siz.y = stof(str3.c_str());
										file >> str3;	// ���f�������擾
										siz.z = stof(str3.c_str());
										m_pMotion[nCntMotion]->GetKye(nCntKye)->GetPartsData(nCntPartsset1)->SetSclTarget(siz);
									}
								}
								nCntPartsset1++;
							}
						}
						nCntKye++;
						nCntPartsset1 = 0;
					}
				}
				nCntMotion++;
				nCntKye = 0;
			}
		}
	}
	// �t�@�C�������
	file.close();
	return true;
}
/// <summary>
/// ���[�V�����ݒ�
/// </summary>
/// <param name="nMotion">�����[�V����</param>
void CObjectMotion::SetMotion(int nMotion)
{
	m_nNowMotion = nMotion;
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		CParts* pParts = GetParts(nCnt);

		if (pParts->GetNowMotion()->GetMotion() != nMotion)
		{
			pParts->SetMotion(nMotion);

			CPartsData* pTarget = GetMotion(nMotion)->GetKye(0)->GetPartsData(nCnt);
			pParts->SetMoveX(
				pTarget->GetPosTarget(),	// �ʒu
				pTarget->GetRotTarget(),	// ����
				pTarget->GetSclTarget(),
				10);	// �傫��
		}
	}
}
/// <summary>
/// �ʏ펞�X�V�ݒ�
/// </summary>
/// <param name="bUpdate">�ʏ펞�X�V���邩�ǂ���</param>
void CObjectMotion::SetPartsNormalUpdate(bool bUpdate)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		CParts* pParts = GetParts(nCnt);
		if (pParts != nullptr)
		{
			pParts->SetNormalUpdate(bUpdate);
		}
	}
}
/// <summary>
/// �|�[�Y���X�V�ݒ�
/// </summary>
/// <param name="bUpdate">�|�[�Y���X�V���邩�ǂ���</param>
void CObjectMotion::SetPartsPoseUpdate(bool bUpdate)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		CParts* pParts = GetParts(nCnt);
		if (pParts != nullptr)
		{
			pParts->SetNormalUpdate(bUpdate);
		}
	}
}
/// <summary>
/// �ʏ펞�`��ݒ�
/// </summary>
/// <param name="bDraw">�ʏ펞�`�悷�邩�ǂ���</param>
void CObjectMotion::SetPartsNormalDraw(bool bDraw)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		CParts* pParts = GetParts(nCnt);
		if (pParts != nullptr)
		{
			pParts->SetNormalUpdate(bDraw);
		}
	}
}
/// <summary>
/// �|�[�Y���`��ݒ�
/// </summary>
/// <param name="bDraw">�|�[�Y���`�悷�邩�ǂ���</param>
void CObjectMotion::SetPartsPoseDraw(bool bDraw)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		CParts* pParts = GetParts(nCnt);
		if (pParts != nullptr)
		{
			pParts->SetNormalUpdate(bDraw);
		}
	}
}
//============================================
// ���[�V��������
//============================================
void CObjectMotion::createMotion()
{
	for (int nCntMotion = 0; nCntMotion < MAX_KYE; nCntMotion++)
	{
		if (m_pMotion[nCntMotion] == nullptr)
		{
			m_pMotion[nCntMotion] = new CMotion;
			return;
		}
	}
}