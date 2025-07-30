//============================================
//
// �G[enemy.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "../object/base/character.h"

class CEnemy : public CCharacter
{
public:
	CEnemy();
	virtual ~CEnemy()		override;
	virtual bool Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��
	virtual int GetNextMotion() override { return 0; }	// �����[�V����
	virtual void Hit(int nCntInvincible, int nDamage);	// �q�b�g
protected:
	void SetSearch(bool bSearch) { m_bSearch = bSearch; }	// �����ς݂���ݒ�
	void SetTarget(CObject* pTarget) { m_pTarget = pTarget; }// �^�[�Q�b�g��ݒ�

	CObject* GetTarget() { return m_pTarget; }	// �^�[�Q�b�g���擾

private:
	bool m_bSearch;	// �����ς݂�
	CObject* m_pTarget;
};







#endif // _ENEMY_H_