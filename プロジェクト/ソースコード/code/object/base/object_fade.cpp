//===========================================
// 
// �t�F�[�h[object_fade.cpp]
// Auther:UedaKou
// 
//===========================================
#include "object_fade.h"


//============================================
// �R���X�g���N�^
//============================================
CFade::CFade() :
	CObject2D(10)
{
	m_nCnt = 0;
	m_nCntMax = 0;
	m_type = TYPE::WHITE_OUT;
}
CFade::CFade(int nPriority):
	CObject2D(nPriority)
{
	m_nCnt = 0;
	m_nCntMax = 0;
	m_type = TYPE::WHITE_OUT;
}
//============================================
// �f�X�g��
//============================================
CFade::~CFade()
{
}
//============================================
// ������
//============================================
bool CFade::Init()
{
	CObject2D::Init();
	return true;
}
//============================================
// �I��
//============================================
void CFade::Uninit()
{

}
//============================================
// �X�V
//============================================
void CFade::Update()
{
	if (m_nCnt < m_nCntMax)
	{
		m_nCnt++;
	}
	else
	{
		DeathFlag();
	}
	switch (m_type)
	{
	case TYPE::WHITE_OUT:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / m_nCntMax) *  m_nCnt));
		break;
	case TYPE::WHITE_IN:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f / m_nCntMax) * m_nCnt));
		break;
	case TYPE::BLACK_OUT:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / m_nCntMax) * m_nCnt));
		break;
	case TYPE::BLACK_IN:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f / m_nCntMax) * m_nCnt));
		break;
	}
	CObject2D::Update();
}
//============================================
// �`��
//============================================
void CFade::Draw()
{
	CObject2D::Draw();
}
//============================================
// �`��
//============================================
CFade* CFade::create(TYPE type, int nCnt)
{
	CFade* pFade = new CFade;
	pFade->m_nCnt = 0;
	pFade->m_nCntMax = nCnt;
	pFade->m_type = type;
	switch (type)
	{
	case TYPE::WHITE_OUT:
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case TYPE::WHITE_IN:
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case TYPE::BLACK_OUT:
		pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		break;
	case TYPE::BLACK_IN:
		pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	}
	pFade->SetSiz(D3DXVECTOR3(SCREEN_W, SCREEN_H, 0.0f));
	pFade->SetPos(D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f));
	pFade->Init();
	return pFade;
}

CFade* CFade::create(int nPriority, TYPE type, int nCnt)
{
	CFade* pFade = new CFade;
	pFade->m_nCnt = 0;
	pFade->m_nCntMax = nCnt;
	pFade->m_type = type;
	switch (type)
	{
	case TYPE::WHITE_OUT:
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case TYPE::WHITE_IN:
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case TYPE::BLACK_OUT:
		pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		break;
	case TYPE::BLACK_IN:
		pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	}
	pFade->SetSiz(D3DXVECTOR3(SCREEN_W, SCREEN_H, 0.0f));
	pFade->SetPos(D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f));
	pFade->Init();
	return pFade;
}
