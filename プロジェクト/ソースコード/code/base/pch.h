//============================================
//
// �v���R���p�C��[pch.h]
// Author:Uedakou
// 
//============================================
#ifndef _PCH_H_
#define _PCH_H_

// �C���N���[�h
#include <Windows.h>
#include "d3dx9.h"	 // �`��ɕK�v

#include "dinput.h"
#include "Xinput.h"

// ���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		// �`��ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9,lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	// D�C���v�b�g
#pragma comment(lib,"Xinput.lib")	// X�C���v�b�g
//#pragma comment(lib,"x86")		// 
//#pragma comment(lib,"Redist")	// X�C���v�b�g

// C++ �e�L�X�g
#include <iostream>	// �C���A�E�g�X�g���[��
#include <string>
using namespace std;
//#include "../object/base/text.h"	// �e�L�X�g

// �}�N����`
#define SCREEN_W (1280)			// �E�B���h�E�̕�
#define SCREEN_H (720)			// �E�B���h�E�̍���

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define FPS (60)	// FPS

#define ANIM_SLEEP (5)	// �A�j���[�V�������x����

#define CLASS_NAME "CatasrtopheMobile"		// �E�B���h�E�N���X���O
#define WINDOW_NAME "CatasrtopheMobile"		// �E�B���h�E�̖��O

// ���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ύX�p�W���i1.0f�ŌŒ�j
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;
// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

#endif // !_PCH_H_