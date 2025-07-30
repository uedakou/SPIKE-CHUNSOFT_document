//===========================================
// 
// �Q�[���f�[�^�ێ�[game_data.cpp]
// Auther:UedaKou
// 
//===========================================
#include "game_data.h"
#include <fstream>	// �t�@�C���̓ǂݍ��݂ɕK�v
#include <iostream>	// �t�@�C���̓ǂݍ��݂ɕK�v


// �I�u�W�F�N�g�ۑ�
namespace Scene
{
	namespace Game
	{
		CGameData::CGameData()
		{
			m_player = nullptr;	// �v���C���[
			// �X�e�[�W�]��������
			for (int nCnt = 0; nCnt < static_cast<int>(Stage::MAX); nCnt++)
			{
				m_nScore[nCnt] = 0;
			}
			// �X�e�[�W�]���ǂݍ���
			ifstream file("data/SaveData/StageEvaluation.txt");  // �ǂݍ��ރt�@�C���̃p�X���w��
			if (file.fail()) {
				MessageBoxA(nullptr, "�J���܂���ł���", "�G���[", MB_OK);
				return;
			}
			string str0, str1, str2, str3;	// ������i�[�p
			string _;	// �X�L�b�v�p�i�[
			string aModelFile[MAX_MOTION_MODEL];	// ���f���t�@�C��

			// ���o���Z�q>>���g���ăf���~�^�ŋ�؂�ꂽ�P��C�l��ǂݍ���
			while (file >> str0)
			{
				// �R�����g�A�E�g
				if (str0[0] == '#')
				{
					getline(file, _);	// ��s�X�L�b�v
				}
				// ��Q��TALL
				else if (str0.compare("STAGESET") == 0)
				{
					int nStage = 0;
					while (file >> str1 &&
						str1.compare("END_STAGESET") != 0)
					{
						// �R�����g�A�E�g
						if (str1[0] == '#')
						{
							getline(file, _);	// ��s�X�L�b�v
						}
						else if (str1.compare("STAGE") == 0)
						{
							file >> str1;	// �X�e�[�W�擾
							nStage = atoi(str1.c_str());
							getline(file, _);	// ��s�X�L�b�v
						}
						else if (str1.compare("EVALUATION") == 0)
						{
							file >> str1;	// �X�e�[�W�]���擾
							m_nScore[nStage] = atoi(str1.c_str());
						}
					}
				}
			}
			// �t�@�C�������
			file.close();

		}
		CGameData::~CGameData()
		{
			// �X�e�[�W�]���ǂݍ���
			ofstream file("data/SaveData/StageEvaluation.txt");  // �ǂݍ��ރt�@�C���̃p�X���w��
			if (!file) {
				MessageBoxA(nullptr, "�J���܂���ł���", "�G���[", MB_OK);
				return;
			}
			string str0, str1, str2, str3;	// ������i�[�p
			string _;	// �X�L�b�v�p�i�[
			string aModelFile[MAX_MOTION_MODEL];	// ���f���t�@�C��

			file << "STAGESET" << endl;
			for (int nCnt = 0; nCnt < static_cast<int>(Stage::MAX); nCnt++)
			{
				file << "	STAGE " << nCnt << endl;
				file << "	EVALUATION " << m_nScore[nCnt] << endl;
				
			}
			file << "END_STAGESET" << endl;

			// �t�@�C�������
			file.close();
		}
	}
}