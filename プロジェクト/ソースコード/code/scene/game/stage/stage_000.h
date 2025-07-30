//===========================================
// 
// �`���[�g���A���X�e�[�W[stage_000.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_000_H_
#define _STAGE_000_H_
#include "stage_base.h"	// �V�[���Q�[���x�[�X
#include "./../../../base/pch.h"	// �v���R���p�C��
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_000 : public CStage_Base
		{
		public:
			// �`���[�g���A���C�x���g
			enum class TUTORIAL {
				Tutorial_000 = 0,	// ���E����
				Tutorial_001,		// ��щz��
				Tutorial_002,		// ���蔲��
				Tutorial_003,		// �A�C�e��
				MAX,
			};
			CStage_000(CBase* game);
			virtual ~CStage_000();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			// �����o�ϐ��ݒ�
			float m_fTutorialRange;	// �`���[�g���A���C�x���g�����͈̔�
			// �`���[�g���A��
			bool m_bCanShownTutorial_000;	// �C�x���g�t���O
			bool m_bCanShownTutorial_001;	// �C�x���g�t���O
			bool m_bCanShownTutorial_002;	// �C�x���g�t���O
			bool m_bCanShownTutorial_003;	// �C�x���g�t���O

			bool m_bHasShownTutorial_000;	// �C�x���g���s�������ǂ���
			bool m_bHasShownTutorial_001;	// �C�x���g���s�������ǂ���
			bool m_bHasShownTutorial_002;	// �C�x���g���s�������ǂ���
			bool m_bHasShownTutorial_003;	// �C�x���g���s�������ǂ���

			CObject2D* m_pTutorealPopup[static_cast<int>(TUTORIAL::MAX)];	// �`���[�g���A���|�b�v�A�b�v

			// �����o�ϐ��̏����l
			static const float s_fGool;			// �S�[������
			static const string s_aStage;	// �����`���[�g���A���̃|�b�v�A�b�v�̑傫��

			static const float s_fTutorialRange;	// �`���[�g���A���C�x���g�����͈̔�
			// �`���[�g���A��
			static const float s_fTutorial_000;	// �����`���[�g���A���̃C�x���g�����ʒu
			static const float s_fTutorial_001;	// �����`���[�g���A���̃C�x���g�����ʒu
			static const float s_fTutorial_002;	// �����`���[�g���A���̃C�x���g�����ʒu
			static const float s_fTutorial_003;	// �����`���[�g���A���̃C�x���g�����ʒu

			static const bool s_bCanShownTutorial_000;	// �����`���[�g���A���̃C�x���g�t���O
			static const bool s_bCanShownTutorial_001;	// �����`���[�g���A���̃C�x���g�t���O
			static const bool s_bCanShownTutorial_002;	// �����`���[�g���A���̃C�x���g�t���O
			static const bool s_bCanShownTutorial_003;	// �����`���[�g���A���̃C�x���g�t���O

			static const D3DXVECTOR3 s_TutorialPopupPos;	// �����`���[�g���A���̃|�b�v�A�b�v�̈ʒu
			static const D3DXVECTOR3 s_TutorialPopupSiz;	// �����`���[�g���A���̃|�b�v�A�b�v�̑傫��


		};
	}
}
#endif // !_STAGE_000_H_
