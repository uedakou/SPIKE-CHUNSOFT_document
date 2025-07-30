//===========================================
// 
// �Q�[���f�[�^�ێ�[game_data.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_
#include "../../object/player.h"			// �v���C���[

class CPlayer;
namespace Scene {
	namespace Game {
		class CGameData
		{
		public:
			CGameData();
			virtual ~CGameData();
			// �ݒ�
			void SetPlayer(CPlayer* player) { m_player = player; }	// �v���C���[�ݒ�
			// �擾
			CPlayer* GetPlayer() { return m_player; }	// �v���C���[�擾
			enum class Stage {
				STAGE_000 = 0,	// �X�e�[�W�`���[�g���A��
				STAGE_001,	// �X�e�[�W1
				STAGE_002,	// �X�e�[�W2
				MAX
			};		// ���Ɉڍs����V�[���̑I����
			int m_nScore[static_cast<int>(Stage::MAX)];
		private:
			CPlayer* m_player;	// �v���C���[


		};
	}
}



#endif //_GAME_DATA_H_