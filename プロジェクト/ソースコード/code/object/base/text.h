//===========================================
// 
// �e�L�X�g[text.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _TEXT_H_
#define _TEXT_H_
#include "object.h"
#include "../../base/pch.h"	// �v���R���p�C��

class CText :public CObject
{
public:
	typedef enum {
		Terminal = 0,// �^�[�~�i��
		Max,
	}Type;	// �t�H���g�^�C�v
	CText();
	CText(int nPriorithi);
	virtual ~CText()		override;
	virtual bool Init()		override;	// ����������
	virtual void Uninit()	override;	// �I������
	virtual void Update()	override;	// �X�V����
	virtual void Draw()		override;	// �e�L�X�g���Œ�\��


	// �\���ݒ�
	void SetData();	// �ݒ蔽�f
	void SetAll(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, Type type);	// �S�ݒ�
	void SetHyde(int nHyde) { m_nHyde = nHyde; SetData(); }		// ����
	void SetWide(int nWide) { m_nWide = nWide; SetData(); }		// ��
	void SetBold(int nBold) { m_nBold = nBold; SetData(); }		// �Α�
	void SetMip(int nMip) { m_nMip = nMip; SetData(); }			// �~�b�v�}�b�v
	void SetItalic(bool bItalic) { m_bItalic = bItalic; SetData(); }// �Α̃t�H���g
	void SetFont(UINT nFont) { m_nFont = nFont; SetData(); }	// �t�H���g
	void SetSize(UINT nSize) { m_nSize = nSize; SetData(); }	// �傫��
	void SetPitch(UINT nPitch) { m_nPitch = nPitch; SetData(); }// �s�b�`
	void SetType(Type Type) { m_type = Type; SetData(); }		// ���
	void SetCol(D3DXCOLOR pCol) { m_pCol = pCol; }				// �F
	void SetSpace(int nSpaceSW, int nSpaceSH, int nSpaceBW, int nSpaceBH) {	// �̈�
		m_Space = { nSpaceSW, nSpaceSH, nSpaceBW, nSpaceBH };	//�̈�
	}
	void SetText(const char* text);	// �e�L�X�g�ݒ�
	void SetText(string text);		// �e�L�X�g�ݒ�

	void PrintText(string text) { m_aText += text; }	// �^����ꂽ�����������e�L�X�g�ɒǉ�

	LPD3DXFONT GetFont();	// �t�H���g�擾

	void ClearText() { m_aText = ""; }	// �e�L�X�g�N���A
	// ����
	static CText* create();
	static CText* create(int nHyde, UINT nWide, UINT nBold, UINT nMip, bool bItalic);
	static CText* create(int nHyde, UINT nWide, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, Type type);
protected:
	static string m_aFontList[Max];	// �t�H���g��

	int		m_nHyde;	// ��������	
	UINT	m_nWide;	// ������
	UINT	m_nBold;	// ��������
	UINT	m_nMip;		// �~�b�v���x��	
	bool	m_bItalic;	// �������Α̂�
	DWORD	m_nFont;	// �t�H���g
	DWORD	m_nSize;	// �����T�C�Y(�ύX�s��)
	DWORD	m_nPitch;	// �s�b�`
	Type	m_type;		// ���̂��܂ޕ�����
	RECT	m_Space;
	D3DXCOLOR m_pCol;	// �F
	LPD3DXFONT m_pFont;// �t�H���g�̃|�C���^
	string	m_aText;	// �e�L�X�g
public:
	static const int	s_nHyde;	// ��������	
	static const UINT	s_nWide;	// ������
	static const UINT	s_nBold;	// ��������
	static const UINT	s_nMip;		// �~�b�v���x��	
	static const bool	s_bItalic;	// �������Α̂�
	static const DWORD	s_nFont;	// �t�H���g
	static const DWORD	s_nSize;	// �����T�C�Y(�ύX�s��)
	static const DWORD	s_nPitch;	// �s�b�`
	static const Type	s_type;		// ���̂��܂ޕ�����
	static const RECT	s_Space;
	static const D3DXCOLOR s_pCol;	// �F
	static const LPD3DXFONT s_pFont;// �t�H���g�̃|�C���^
	static const string	s_aText;	// �e�L�X�g
};
#endif // !_TEXT_H_