//===========================================
// 
// �X�e�[�W001[stage_001.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_001_H_
#define _STAGE_001_H_
#include "stage_base.h"	// �V�[���Q�[���x�[�X
#include "./../../../base/pch.h"	// �v���R���p�C��
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_001 : public CStage_Base
		{
		public:
			CStage_001(CBase* game);
			virtual ~CStage_001();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		protected:

		private:
			// �����o�ϐ��̏����l
			static const float s_fGool;			// �S�[������
			static const string s_aStage;		// �X�e�[�W�p�X
			static const D3DXVECTOR3 s_PlayerFirstPos;		// �X�e�[�W�p�X

		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
