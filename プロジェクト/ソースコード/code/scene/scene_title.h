//===========================================
// 
// �^�C�g���V�[��[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_
#include "scene_base.h"
#include "../object/base/object_3D.h"	// �RD

class CObject;
class CObject2D;
namespace Scene{
	enum class SELECT_TYPE {
		STATE = 0,
		END,
		MAX
	};
	class CTitle : public CBase
	{
	private:
	public:
		CTitle(CBase* scene);
		virtual ~CTitle();
		virtual CBase* Update()	override;	// �X�V
		virtual void Draw() const override;	// �`��
		bool GetPose()override;		// �|�[�Y��Ԏ擾
	private:
		CObject2D* m_pTitle;	// �^�C�g��
		CObject2D* m_pBG;			// �w�i
		CObject2D* m_pOptions[static_cast<unsigned int>(SELECT_TYPE::MAX)];	// �I����
		CObject2D* m_pSelectedOption;		// �I�𒆂�

		int m_nSelect;	// ���݃Z���N�g
		bool m_bNext;	// 
		const int m_nCntMax;	// 
		int m_nCnt;

		static const D3DXCOLOR m_Selected;		// �I��
		static const D3DXCOLOR m_NotSelected;	// ��I��
	};
}



#endif // _SCENE_TITLE_H_