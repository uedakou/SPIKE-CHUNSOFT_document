//===========================================
// 
// �|���S��2[object_2D.cpp]
// Auther:UedaKou
// 
//===========================================
#include "object_2D.h"	// �I�u�W�F�N�g�QD
#include "../../base/manager.h"	// �}�l�[�W���[
#include "../../base/main.h"	// ���C��

// �ÓI�����o�萔
const D3DXCOLOR CObject2D::s_colDef = { 1.0f, 1.0f, 1.0f, 1.0f };	// �F�����ݒ�
const int CObject2D::s_nNumVertices = 4;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CObject2D::CObject2D()
{
	m_pVtxBuff = nullptr;				// �o�[�e�b�N�X������
	m_pTexture = nullptr;				// �e�N�X�`��������
	m_col = s_colDef;					// �F������
	m_nNumVertices = s_nNumVertices;	// ���_��
}
/// <summary>
/// �R���X�g���N�^(�D��x�t��)
/// </summary>
/// <param name="nPriority">�D��x</param>
CObject2D::CObject2D(int nPriority):
	CObject(nPriority)
{
	m_pVtxBuff = nullptr;				// �o�[�e�b�N�X������
	m_pTexture = nullptr;				// �e�N�X�`��������
	m_col = s_colDef;					// �F������
	m_nNumVertices = s_nNumVertices;	// ���_��
}
//============================================
// �f�X�g���N�g
//============================================
CObject2D::~CObject2D()
{
	// ����������
	Uninit();
}
//============================================
// ������
//============================================
bool CObject2D::Init()
{
	// �S�̃}�l�[�W���[�擾
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �g�����X�t�H�[���擾
	X x = GetX();

	// �f�o�C�X�̎擾
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Unlock();
	return true;

}
//============================================
// �I��
//============================================
void CObject2D::Uninit()
{
	// �S�̃}�l�[�W���[
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�ւ̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//============================================
// �X�V
//============================================
void CObject2D::Update()
{
}
//============================================
// �`��
//============================================
void CObject2D::Draw()
{
	// �S�̃}�l�[�W���[
	CManager* pManager = CManager::GetInstance();
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�Ƀf�[�^���X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`��
	pDevice->SetTexture(0, m_pTexture);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}
/// <summary>
/// �g�����X�t�H�[����ݒ�
/// </summary>
/// <param name="x">�ݒ肷��g�����X�t�H�[��</param>
void CObject2D::SetX(X x)
{
	// �g�����X�t�H�[���ݒ�
	CObject::SetX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �g�����X�t�H�[����ݒ�
/// </summary>
/// <param name="pos">�ݒ肷��ʒu</param>
/// <param name="rot">�ݒ肷�����</param>
/// <param name="siz">�ݒ肷��X�P�[��</param>
void CObject2D::SetX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scl)
{
	// �g�����X�t�H�[���ݒ�
	CObject::SetPos(pos);
	CObject::SetRot(rot);
	CObject::SetScl(scl);

	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �ʒu��ݒ肵�܂�
/// </summary>
/// <param name="pos">�ݒ肷����W</param>
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject::SetPos(pos);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �ʒu�ix���̂݁j��ݒ�
/// </summary>
/// <param name="x">�ݒ肷����W</param>
void CObject2D::SetPosX(const float x)
{
	CObject::SetPosX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �ʒu�iy���̂݁j�ݒ�
/// </summary>
/// <param name="y">�ݒ肷����W</param>
void CObject2D::SetPosY(const float y)
{
	CObject::SetPosY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �ʒu�iz���̂݁j��ݒ�
/// </summary>
/// <param name="z">�ݒ肷����W</param>
void CObject2D::SetPosZ(const float z)
{
	CObject::SetPosZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// ������ݒ肷��
/// </summary>
/// <param name="rot">�ݒ肵�����p�x</param>
void CObject2D::SetRot(const D3DXVECTOR3 rot)
{
	CObject::SetRot(rot);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �����ix���̂݁j��ݒ肷��
/// </summary>
/// <param name="x">�ݒ肵�����p�x</param>
void CObject2D::SetRotX(const float x)
{
	CObject::SetRotX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �����iy���̂݁j��ݒ肷��
/// </summary>
/// <param name="y">�ݒ肵�����p�x</param>
void CObject2D::SetRotY(const float y)
{
	CObject::SetRotY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �����iz���̂݁j��ݒ肷��
/// </summary>
/// <param name="z">�ݒ肵�����p�x</param>
void CObject2D::SetRotZ(const float z)
{
	CObject::SetRotZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �g�嗦��ݒ�
/// </summary>
/// <param name="siz">�ݒ肵�����g�嗦</param>
void CObject2D::SetScl(const D3DXVECTOR3 siz)
{
	CObject::SetScl(siz);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �g�嗦(x���̂�)��ݒ�
/// </summary>
/// <param name="x">�ݒ肵�����g�嗦</param>
void CObject2D::SetSclX(const float x)
{
	CObject::SetSclX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �g�嗦(x���̂�)��ݒ�
/// </summary>
/// <param name="y">�ݒ肵�����g�嗦</param>
void CObject2D::SetSclY(const float y)
{
	CObject::SetSclY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// �g�嗦(x���̂�)��ݒ�
/// </summary>
/// <param name="z">�ݒ肵�����g�嗦</param>
void CObject2D::SetSclZ(const float z)
{
	// �g�嗦�ݒ�
	CObject::SetSclZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	// �ʒu���璸�_��ݒ�
	SetVtxPos();
}
/// <summary>
/// UV�ݒ�
/// </summary>
/// <param name="UV">�ݒ肵����UV�i�㉺���E�j</param>
void CObject2D::SetUV(D3DXVECTOR4 UV)
{
	VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(UV.z, UV.x);
	pVtx[1].tex = D3DXVECTOR2(UV.w, UV.x);
	pVtx[2].tex = D3DXVECTOR2(UV.z, UV.y);
	pVtx[3].tex = D3DXVECTOR2(UV.w, UV.y);

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Unlock();
}
/// <summary>
/// ���_�J���[�ݒ�
/// </summary>
/// <param name="col">�ݒ肵�������_�J���[</param>
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;


	VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^
	if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// ���_�o�b�t�@�����b�N
		m_pVtxBuff->Unlock();
	}
}
/// <summary>
/// �e�N�X�`����ݒ肷��
/// �O������擾����Direct3D�e�N�X�`���𒼐ړo�^����
/// </summary>
/// <param name="ptex">Direct3D�e�N�X�`���|�C���^</param>
void CObject2D::SetTexture(const LPDIRECT3DTEXTURE9 ptex)
{
	// �e�N�X�`���|�C���^��ݒ�
	m_pTexture = ptex;
}
/// <summary>
/// �e�N�X�`���t�@�C����ǂݍ���Őݒ肷��
/// </summary>
/// <param name="aName">�e�N�X�`���t�@�C���p�X</param>
void CObject2D::SetTexture(const char aName[MAX_TXT])
{
	// Direct3D�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�擾

	LPDIRECT3DTEXTURE9 ptex;

	// �e�N�X�`���t�@�C����ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		aName,
		&ptex);

	// �ǂݍ��񂾃e�N�X�`����ݒ�
	SetTexture(ptex);
}
/// <summary>
/// �e�N�X�`���t�@�C����ǂݍ���Őݒ肷��istd::string�Łj
/// </summary>
/// <param name="aName">�e�N�X�`���t�@�C���p�X</param>
void CObject2D::SetTexture(std::string aName)
{
	// Direct3D�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�擾

	LPDIRECT3DTEXTURE9 ptex;

	// �e�N�X�`���t�@�C����ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		aName.c_str(),
		&ptex);

	// �ǂݍ��񂾃e�N�X�`����ݒ�
	SetTexture(ptex);
}
/// <summary>
/// �g�����X�t�H�[�����Z
/// </summary>
/// <param name="x">���Z������W�E��]�E�X�P�[���̃Z�b�g</param>
void CObject2D::AddX(X x)
{
	CObject::AddX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// �g�����X�t�H�[���Ɏw��l�����Z����
/// </summary>
/// <param name="x">���Z������W�E��]�E�X�P�[���̃Z�b�g</param>
void CObject2D::AddX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz)
{
	CObject::AddX(pos, rot, siz);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// ���W���Z
/// </summary>
/// <param name="pos">���Z���������W</param>
void CObject2D::AddPos(const D3DXVECTOR3 pos)
{
	CObject::AddPos(pos);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// X���W�����Z
/// </summary>
/// <param name="x">���Z���������W</param>
void CObject2D::AddPosX(const float x)
{
	CObject::AddPosX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// Y���W�����Z
/// </summary>
/// <param name="y">���Z���������W</param>
void CObject2D::AddPosY(const float y)
{
	CObject::AddPosY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// Z���W�����Z
/// </summary>
/// <param name="z">���Z���������W</param>
void CObject2D::AddPosZ(const float z)
{
	CObject::AddPosZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// ��]�����Z�i�S���j
/// </summary>
/// <param name="rot">���Z��������]�i���W�A���P�ʁj</param>
void CObject2D::AddRot(const D3DXVECTOR3 rot)
{
	CObject::AddRot(rot);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// X����]�����Z
/// </summary>
/// <param name="x">���Z������X����]�i���W�A���P�ʁj</param>
void CObject2D::AddRotX(const float x)
{
	CObject::AddRotX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// Y����]�����Z
/// </summary>
/// <param name="y">���Z������Y����]�i���W�A���P�ʁj</param>
void CObject2D::AddRotY(const float y)
{
	CObject::AddRotY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// Z����]�����Z
/// </summary>
/// <param name="z">���Z������Z����]�i���W�A���P�ʁj</param>
void CObject2D::AddRotZ(const float z)
{
	CObject::AddRotZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// �X�P�[�������Z
/// </summary>
/// <param name="siz">���Z�������X�P�[��</param>
void CObject2D::AddScl(const D3DXVECTOR3 siz)
{
	CObject::AddScl(siz);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// X���X�P�[�������Z
/// </summary>
/// <param name="x">���Z������X���X�P�[��</param>
void CObject2D::AddSclX(const float x)
{
	CObject::AddSclX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// Y���X�P�[�������Z
/// </summary>
/// <param name="y">���Z������X���X�P�[��</param>
void CObject2D::AddSclY(const float y)
{
	CObject::AddSclY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// Z���X�P�[�������Z
/// </summary>
/// <param name="z">���Z������X���X�P�[��</param>
void CObject2D::AddSclZ(const float z)
{
	CObject::AddSclZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// ����
/// </summary>
/// <param name="pos">�����������ʒu</param>
/// <param name="siz">�����������傫��</param>
/// <returns>���������I�u�W�F�N�g</returns>
CObject2D* CObject2D::create(D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	// �C���X�^���X���m��
	CObject2D* pObject = new CObject2D;
	// �C���X�^���X���m�ۂ����s���Ă�����
	if (!pObject)
	{
		return nullptr;
	}

	pObject->SetPos(pos);	// �ʒu��ݒ�
	pObject->SetSiz(siz);	// �傫���ݒ�
	if (!pObject->Init())	// ������
	{
		delete pObject;
		pObject = nullptr;
		return nullptr;
	}	

	// �C���X�^���X��Ԃ�
	return pObject;
}
/// <summary>
/// �����D��x�t��
/// </summary>
/// <param name="nPriority">�D��x</param>
/// <param name="pos">�����������ʒu</param>
/// <param name="siz">�����������傫��</param>
/// <returns>���������I�u�W�F�N�g</returns>
CObject2D* CObject2D::create(int nPriority, D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	// �C���X�^���X���m��
	CObject2D* pObject = new CObject2D(nPriority);

	pObject->SetPos(pos);	// �ʒu��ݒ�
	pObject->SetSiz(siz);	// �傫���ݒ�
	if (!pObject->Init())	// ������
	{
		delete pObject;
		pObject = nullptr;
		return nullptr;
	}

	// �C���X�^���X��Ԃ�
	return pObject;
}
/// <summary>
/// ���_����ݒ�
/// </summary>
void CObject2D::SetVtxPos()
{
	//�ʒu��ݒ�
	X x = GetX();

	VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Unlock();
}