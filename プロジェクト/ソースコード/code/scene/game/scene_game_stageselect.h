//===========================================
// 
// �Q�[���X�e�[�W�I��[scene_game_stageselect.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_GAME_STAGESELECT_H_
#define _SCENE_GAME_STAGESELECT_H_
#include "scene_game.h"
#include "../../base/pch.h"
class CObject2D;

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect : public CBase
		{
		public:
			enum class Select {
				STAGE_000 = 0,	// �X�e�[�W�`���[�g���A��
				STAGE_001,	// �X�e�[�W1
				STAGE_002,	// �X�e�[�W2
				MAX
			};		// ���Ɉڍs����V�[���̑I����

			CScen_Game_StageSelect(CBase* scene);
			virtual ~CScen_Game_StageSelect();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			bool m_bPose;
			bool m_bNext;	// ���̃V�[���Ɉڍs�����ǂ���
			int m_nSetlect;	// ���ݑI�𒆂̎��V�[��
			int m_nCntPressHold;	// ����������
			CObject2D* m_pStage[static_cast<int>(Select::MAX)];	// �I�����I�u�W�F�N�g
			CObject2D* m_pStageEvaluation;	// �X�e�[�W�]��

			static const D3DXVECTOR3 s_SelectSiz;	// �I�����傫��
			static const D3DXVECTOR3 s_SelectEvaluationSiz;	// �I��]���傫��
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
