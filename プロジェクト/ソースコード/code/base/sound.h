//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"
#include "xaudio2.h"

class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		SOUND_TITLE_000 = 0,		// �^�C�g�����y
		SOUND_STAGE_SELECT_000,	// ���U���g
		SOUND_STAGE_00,			// �X�e�[�W000
		SE_CHOICE_000,		// �I��
		SE_DECISION_000,	// ����
		SE_FOOTSTEPS_000,	// ����
		SE_GET_ITEM_000,	// ����
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	//*****************************************************************************
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;
	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);		// ����������
	void UninitSound(void);				// �I������
	HRESULT PlaySound(SOUND_LABEL label);	// �Đ�
	void StopSound(SOUND_LABEL label);		// ��~
	void StopSound(void);					// ��~(�S��)
	bool IsPlaySound(SOUND_LABEL label);	// �Đ���Ԏ擾
protected:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
	// �T�E���h�̏��
	SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX];
};

#endif
