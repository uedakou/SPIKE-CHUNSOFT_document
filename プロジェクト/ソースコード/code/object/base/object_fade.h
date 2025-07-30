//===========================================
// 
// �t�F�[�h[object_fade.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "object_2D.h"	// �I�u�W�F�N�g2D
#include "../../base/manager.h"	// �}�l�[�W���[

class CFade: public CObject2D
{
public:
	enum class TYPE {
		WHITE_OUT = 0,	// ���h��
		WHITE_IN,
		BLACK_OUT,
		BLACK_IN,
		MAX
	};
	CFade();
	CFade(int nPriority);	// �D��x�t��
	virtual ~CFade()override;
	bool Init()		override;	// ������
	void Uninit()	override;	// �I��
	void Update()	override;	// �X�V
	void Draw()		override;	// �`��
	static CFade* create(TYPE type, int nCnt);
	static CFade* create(int nPriority, TYPE type, int nCnt);
private:
	int m_nCnt;
	int m_nCntMax;
	TYPE m_type;
};




#endif // !_FADE_H_