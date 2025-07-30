//===========================================
// 
// �Q�[���V�[���x�[�X[scene_game.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_
#include "../scene_base.h"	// �V�[���x�[�X
#include "game_data.h"	// �Q�[���f�[�^�ۑ��w�b�_
#include <thread>	// �}���`�X���b�h�𗧂Ă�̂ɕK�v
namespace Scene {
	namespace Game {
		class CGameManager;
		namespace nsPrev = Scene;
		class CBase : public nsPrev::CBase
		{
		protected:
			CBase(nsPrev::CBase* scene, CGameData* const gameData) :
				nsPrev::CBase(*scene),
				m_gameData(gameData)
			{
				CObject::ReleaseScene();
			}	// �V�[�������[�X}
			CBase(const CBase&) = default;

		public:
			virtual ~CBase() = default;
		protected:

			CGameData* const m_gameData;
		public:

			virtual  nsPrev::CBase* Update() override = 0;
			virtual void Draw() const override = 0;
			bool GetPose()override = 0;

			//���̐����p�֐�
			template<typename T>
			nsPrev::CBase* makeScene();
			// makeScene���X���b�h�������ďI��������
			// �Q�[���}�l�[�W���[�Ɏ��̃V�[���̃|�C���^��n��
			// 
			// 
			// 
		};
	}
}
#endif // !_SCENE_GAME_H_