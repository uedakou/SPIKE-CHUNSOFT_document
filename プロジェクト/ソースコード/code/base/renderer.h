//===========================================
// 
// �����_���[[renderer.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _RCNDRERE_H_
#define _RCNDRERE_H_
#include "main.h"

#define B_SORT true

class CText;
// �����_���[
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND nWnd, BOOL bWindow);	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	void DrawFPS(void);	// FPS�`�揈��
	LPDIRECT3DDEVICE9 GetDevice();	// Direct3D�f�o�C�X�擾
private:
	LPDIRECT3D9 m_pD3D;				// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Direct3D�f�o�C�X
	D3DXCOLOR m_BGColor;	// �w�i�F
	static const D3DXCOLOR s_BGColor;	// �w�i�F
};

#endif // !_RCNDRERE_H_
