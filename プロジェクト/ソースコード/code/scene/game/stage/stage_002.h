//===========================================
// 
// �X�e�[�W002[stage_002.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_002_H_
#define _STAGE_002_H_
#include "stage_base.h"	// �V�[���Q�[���x�[�X
#include "./../../../base/pch.h"	// �v���R���p�C��
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_002 : public CStage_Base
		{
		public:
			CStage_002(CBase* game);
			virtual ~CStage_002();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		protected:

		private:
			// �����o�ϐ��̏����l
			static const float s_fGool;			// �S�[������
			static const string s_aStage;		// �X�e�[�W�p�X

		};
	}
}
#endif // !_STAGE_002_H_
