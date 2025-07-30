//============================================
//
// �v���C���[[player.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "base/character.h"	// �L�����N�^�[
#include "base/effect_generator_particle.h"	// �G�t�F�N�g�W�F�l���[�^�[�p�[�e�B�N��

#define PLAYER_MOTIONFILE_A "data\\CHARACTER\\motion_Humimaru.txt"	// �v���C���[���[�V�����t�@�C���p�X
#define PLAYER_RESISTANCE 0.01f		// �ړ�����

class CPlayer:public CCharacter
{
public:
	class ActivityStrategy;
	// ���[�V����
	enum class Motion{
		ACTIVITY_NEUTRAL = 0,//	�j���[�g����
		ACTIVITY_MOVE,		// ����
		ACTIVITY_SLIDING,	// �X���C�f�B���O
		ACTIVITY_JANP,		// �W�����v
		ACTIVITY_DEATH,		// ���S
		ACTIVITY_MAX,
	};


	// �p�u���b�N�֐�
	// ��{����
	CPlayer();
	virtual ~CPlayer()		override;

	// ��{����
	bool Init()		override;	// ������
	void Uninit()	override;	// �I��
	void Update()	override;	// �X�V
	void Draw()		override;	// �`��

	// �擾
	float GetSpeed() { return m_fSpeed; }	// ���x�擾
	bool IsMove() { return m_bMove; }		// �����ňړ����邩�ǂ������擾
	float GetLaneSiz() { return m_fLane; }	// ���݂�1���[���̕��̎擾
	bool IsJanp() { return m_bJanp; }		// �W�����v�����ǂ����ݒ�
	bool IsSliding() { return m_bSliding; }	// �X���C�f�B���O����������

	ActivityStrategy* GetActivity() { return m_pActivityStrategy; }	// �X�g���e�W�[�擾

	// �ݒ�
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }	// ���x�ݒ�
	void SetSpeedNomal() { m_fSpeed = s_fSpeed; }		// ���x�ݒ�
	void SetMove(bool bMove) { m_bMove = bMove; }		// �����ňړ����邩�ǂ�����ݒ�
	void SetLaneSiz(float fLane) { m_fLane = fLane; }	// ���݂�1���[���̕��̐ݒ�

	void SetActivity(ActivityStrategy* pActivityStrategy) { m_pActivityStrategy = pActivityStrategy; }	// �X�g���e�W�[�ݒ�

	virtual int GetNextMotion() override;	// ���[�V�������擾

	// �����֐�
	void Hit(int nDamage)override;
	void Hit(int nCntInvincible, int nDamage) override;
	void Hit(D3DXVECTOR3 ShockRot,int nCntInvincible, int nDamage)override;

	// ����
	static CPlayer* create();

	// �X�g���e�W�[
	// �v���e�N�e�b�h�X�g���e�W�[
	class ActivityStrategy
	{
	public:
		enum class Type {
			Null = 0,	// �ύX���Ȃ�
			Ran,		// ����
			LaneChangeL,	// ���[���`�F���W
			LaneChangeR,	// ���[���`�F���W
			Janp,		// �W�����v
			Sliding,	// �X���C�f�B���O
		}m_type;	//�@���X�g���e�W�[

		ActivityStrategy() = delete;
		ActivityStrategy(CPlayer* player) : m_pPrimary(player), m_type(Type::Null),
			m_bInUP(true), m_bInDown(true), m_bInLeft(true), m_bInRight(true) {}
		virtual ~ActivityStrategy() {}

		virtual ActivityStrategy* Update(); // �X�V

		// ����
		virtual void InputUP() {}		// �����
		virtual void InputDown() {}		// ������
		virtual void InputLeft() {}		// ������
		virtual void InputRight() {}	// �E����

		// �擾
		bool GetInUP() { return m_bInUP; }	// �����
		bool GetInDown() { return m_bInDown; }// ������
		bool GetInLeft() { return m_bInLeft; }// ������
		bool GetInRight() { return m_bInRight; }// �E����

		// �ݒ�
		void SetInUP(bool bIn) { m_bInUP = bIn; }// �����
		void SetInDown(bool bIn) { m_bInDown = bIn; }// ������
		void SetInLeft(bool bIn) { m_bInLeft = bIn; }// ������
		void SetInRight(bool bIn) { m_bInRight = bIn; }// �E����

		virtual void Hit() {};

	protected:
		CPlayer* m_pPrimary;	// �v���C���[

		bool m_bInUP;		// �����
		bool m_bInDown;		// ������
		bool m_bInLeft;		// ������
		bool m_bInRight;	// �E����
	};
	// �ʏ���
	class PlayerNomarActivity :public ActivityStrategy
	{
	public:
		PlayerNomarActivity() = delete;
		PlayerNomarActivity(CPlayer* player);
		~PlayerNomarActivity();
		void InputUP()		override;	// �����
		void InputDown()	override;	// ������
		void InputLeft()	override;	// ������
		void InputRight()	override;	// �E����
	};
	// ���C���`�F���W���
	class PlayerLaneChangeActivity :public ActivityStrategy
	{
	public:
			enum class LR {
			L = 0,
			R,
		} m_LR;
		PlayerLaneChangeActivity() = delete;
		PlayerLaneChangeActivity(CPlayer* player, LR lr);
		~PlayerLaneChangeActivity();
		virtual ActivityStrategy* Update();	// �X�V
		void InputUP()		override;	// �����
		void InputDown()	override;	// ������
		void InputLeft()	override;	// ������
		void InputRight()	override;	// �E����
		int m_nCnt;					// �ړ��J�E���g
		static const int s_nCnt = 10;	// ���[���ړ��J�E���g
	};
	// �W�����v���
	class PlayerJanpActivity :public ActivityStrategy
	{
	public:
		PlayerJanpActivity() = delete;
		PlayerJanpActivity(CPlayer* player);
		~PlayerJanpActivity();
		virtual ActivityStrategy* Update();	// �X�V
		void InputUP()		override;	// �����
		void InputDown()	override;	// ������
		void InputLeft()	override;	// ������
		void InputRight()	override;	// �E����
	};
	// �X���C�f�B���O���
	class PlayerSlidingActivity :public ActivityStrategy
	{
	public:
		PlayerSlidingActivity() = delete;
		PlayerSlidingActivity(CPlayer* player);
		~PlayerSlidingActivity();
		virtual ActivityStrategy* Update();	// �X�V
		void InputUP()		override;	// �����
		void InputDown()	override;	// ������
		void InputLeft()	override;	// ������
		void InputRight()	override;	// �E����
		int m_nCnt;						// �X���C�f�B���O�J�E���g
		static const int s_nCnt = 30;	// �X���C�f�B���O�J�E���g�ő�
	};

private:
	// �v���C�x�[�g�֐�
	void MoveAttenuation();	// �ړ�����

private:
	// �v���C�x�[�g�ϐ�
	float m_fSpeed;	// �X�s�[�h
	bool m_bMove;	// �����œ������ǂ���
	float m_fLane;	// 1���[���̕�
	bool m_bSliding;	// �X���C�f�B���O���Ă��邩�ǂ���
	bool m_bJanp;	// �W�����v���Ă��邩�ǂ���

	ActivityStrategy* m_pActivityStrategy;	// �s���X�g���e�W
	CEffectGeneratorParticle* m_pEffect;	// �G�t�F�N�g

	// �萔
	static const int s_nLife = 1;		// �̗͏����l
	static const float s_fSpeed;	// ���x�����l
	static const bool s_bMove;		// �����ړ����邩�ǂ���
	static const float s_fLane;		// ��{��1���[���̕�
	static const X s_Collision;	// �����蔻�菉���l
	static const float s_fGravity;	// �����蔻�菉���l
	static const float s_fJanp;	// �����蔻�菉���l
};

#endif // !_PLAYER_H_