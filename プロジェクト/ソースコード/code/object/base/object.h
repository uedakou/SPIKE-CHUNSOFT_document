//============================================
//
// �I�u�W�F�N�g[object.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "../../base/pch.h"	//�v���R���p�C���w�b�_
#include "../../base/calculation.h"	// �v�Z�p


// �I�u�W�F�N�g
class CObject
{
public:
	CObject();
	CObject(const int nPriority);	// �D��x�t��
	virtual ~CObject();
	virtual bool Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��
	void Release();				// �������g�̉��

	// �S�̏���
	static void ReleaseScene();	// �S�I�u�W�F�N�g���
	static void ReleaseAll();	// �S�I�u�W�F�N�g���
	static void ReleaseDeathFlag();	// �S�I�u�W�F�N�g���
	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V
	static void DrawAll();		// �S�I�u�W�F�N�g�`��
	static void GetAllObject(CObject* object[MAX_PRIORITY]);	// �I�u�W�F�N�g�擾
	static CObject* GetMyObject(int nPriorty) { return m_pTop[nPriorty]; };	// �I�u�W�F�N�g�擾(�D��x��)
	static void Sort();

	static void CalculateDistanceToCamera();	// �J��������̋����Ń\�[�g
	void CalculateDistance(D3DXVECTOR3 pos);	/// �J��������̋������v�Z
	// ���X�g
	virtual void SetNext(CObject* pNext) { m_pNext = pNext; }	// ���ݒ�
	virtual void SetPrev(CObject* pPrev) { m_pPrev = pPrev; }	// �O�ݒ�
	virtual CObject* GetNext() { return m_pNext; }//	���擾
	virtual CObject* GetPrev() { return m_pPrev; }//	���擾

	// �ʒu
	virtual void SetX(X x) { m_x = x; }
	virtual void SetX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) {
		m_x.pos = pos;
		m_x.rot = rot;
		m_x.scl = siz;
	}
	virtual void SetPos(const D3DXVECTOR3 pos) { m_x.pos = pos; }	// �ʒu�ݒ�
	virtual void SetPosX(const float x) { m_x.pos.x = x; }	// �ʒu�ݒ�
	virtual void SetPosY(const float y) { m_x.pos.y = y; }	// �ʒu�ݒ�
	virtual void SetPosZ(const float z) { m_x.pos.z = z; }	// �ʒu�ݒ�
	virtual void SetRot(const D3DXVECTOR3 rot) { m_x.rot = rot; }	// �����ݒ�
	virtual void SetRotX(const float x) { m_x.rot.x = x; }	// �����ݒ�
	virtual void SetRotY(const float y) { m_x.rot.y = y; }	// �����ݒ�
	virtual void SetRotZ(const float z) { m_x.rot.z = z; }	// �����ݒ�
	virtual void SetScl(const D3DXVECTOR3 siz) { m_x.scl = siz; }	// �傫���ݒ�
	virtual void SetSclX(const float x) { m_x.scl.x = x; }	// �傫���ݒ�
	virtual void SetSclY(const float y) { m_x.scl.y = y; }	// �傫���ݒ�
	virtual void SetSclZ(const float z) { m_x.scl.z = z; }	// �傫���ݒ�

	// �g�����X�t�H�[�����Z
	virtual void AddX(X x) { m_x += x; }
	virtual void AddX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz) {
		m_x.pos += pos;
		m_x.rot += rot;
		m_x.scl += siz;
	}														// �g�����X�t�H�[���ݒ�
	virtual void AddPos(const D3DXVECTOR3 pos) { m_x.pos += pos; }	// �ʒu�ݒ�
	virtual void AddPosX(const float x) { m_x.pos.x += x; }	// �ʒu�ݒ�
	virtual void AddPosY(const float y) { m_x.pos.y += y; }	// �ʒu�ݒ�
	virtual void AddPosZ(const float z) { m_x.pos.z += z; }	// �ʒu�ݒ�
	virtual void AddRot(const D3DXVECTOR3 rot) { m_x.rot += rot; }	// �����ݒ�
	virtual void AddRotX(const float x) { m_x.rot.x += x; }	// �����ݒ�
	virtual void AddRotY(const float y) { m_x.rot.y += y; }	// �����ݒ�
	virtual void AddRotZ(const float z) { m_x.rot.z += z; }	// �����ݒ�
	virtual void AddScl(const D3DXVECTOR3 siz) { m_x.scl += siz; }	// �傫���ݒ�
	virtual void AddSclX(const float x) { m_x.scl.x += x; }	// �傫���ݒ�
	virtual void AddSclY(const float y) { m_x.scl.y += y; }	// �傫���ݒ�
	virtual void AddSclZ(const float z) { m_x.scl.z += z; }	// �傫���ݒ�
	// �g�����X�t�H�[���擾
	virtual X GetX() { return m_x; }					// �g�����X�t�H�[���ݒ�
	virtual D3DXVECTOR3 GetPos() { return m_x.pos; }	// �ʒu�ݒ�
	virtual float GetPosX() { return m_x.pos.x; }	// �ʒu�ݒ�
	virtual float GetPosY() { return m_x.pos.y; }	// �ʒu�ݒ�
	virtual float GetPosZ() { return m_x.pos.z; }	// �ʒu�ݒ�
	virtual D3DXVECTOR3 GetRot() { return m_x.rot; }	// �����ݒ�
	virtual float GetRotX() { return m_x.rot.x; }	// �����ݒ�
	virtual float GetRotY() { return m_x.rot.y; }	// �����ݒ�
	virtual float GetRotZ() { return m_x.rot.z; }	// �����ݒ�
	virtual D3DXVECTOR3 GetScl() { return m_x.scl; }	// �傫���ݒ�
	virtual float GetSclX() { return m_x.scl.x; }	// �傫���ݒ�
	virtual float GetSclY() { return m_x.scl.y; }	// �傫���ݒ�
	virtual float GetSclZ() { return m_x.scl.z; }	// �傫���ݒ�

	// ����
	virtual void SetDistance(float fDistance) { m_fDistance = fDistance; }	// ���ڂ炩��̋���
	virtual float GetDistance() { return m_fDistance; }	// ���ڂ炩��̋���

	// �t���O
	virtual void SetNormalUpdate(bool bUpdate) { m_bAllUpdate = bUpdate; }		// �S�̂ōX�V���邩�ݒ�
	virtual void SetPoseUpdate(bool bUpdate) { m_bPoseUpdate = bUpdate; }		// �|�[�Y���X�V���邩�ݒ�
	virtual void SetNormalDraw(bool bDraw) { m_bAllDraw = bDraw; }				// �S�̂ŕ`�悷�邩�ݒ�
	virtual void SetPoseDraw(bool bDraw) { m_bPoseDraw = bDraw; }				// �|�[�Y���`�悷�邩�ݒ�
	virtual void SetReleaseScene(bool bRelease) { m_bReleaseScene = bRelease; }	// �V�[���Ń����[�X���邩

	virtual bool IsAllUpdate() { return m_bAllUpdate; }			// �S�̂ōX�V���邩
	virtual bool IsPoseUpdate() { return m_bPoseUpdate; }		// �|�[�Y���X�V���邩
	virtual bool IsAllDraw() { return m_bAllDraw; }				// �S�̂ŕ`�悷�邩
	virtual bool IsPoseDraw() { return m_bPoseDraw; }			// �|�[�Y���`�悷�邩
	virtual bool IsReleaseScene() { return m_bReleaseScene; }	// �V�[���Ń����[�X���邩

	virtual void DeathFlag() { m_bDeath = true; }	// �������g�̎��S�t���O
	virtual bool IsDeathFlag() { return m_bDeath ; }		// �������g�̎��S�t���O

protected:
private:
	// ���X�g
	static CObject* m_pTop[MAX_PRIORITY];	// �g�b�v
	static CObject* m_pCur[MAX_PRIORITY];	// �Ō��
	CObject* m_pNext;						// ��
	CObject* m_pPrev;						// �O
	static int m_nNumObject[MAX_PRIORITY];	// �I�u�W�F�N�g��
	int m_ID;	// �I�u�W�F�N�gID
	int m_nPriority;
	// �ϐ�

	X m_x;	// �g�����X�t�H�[��
	float m_fDistance;	// �J��������̋���

	bool m_bAllUpdate;						// �S�̂ōX�V���邩
	bool m_bPoseUpdate;						// �|�[�Y���X�V���邩
	bool m_bAllDraw;						// �S�̂ŕ`�悷�邩
	bool m_bPoseDraw;						// �|�[�Y���`�悷�邩
	bool m_bReleaseScene;					// �V�[���Ń����[�X���邩

	bool m_bDeath;							// ��  �S�t���O
	static constexpr int s_nDefalut_Priority = 3;	// �D��x���ݒ莞�̗D��x
};

#endif // !_OBJECT_H_