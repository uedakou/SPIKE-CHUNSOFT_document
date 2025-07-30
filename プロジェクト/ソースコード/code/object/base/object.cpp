//============================================
//
// �I�u�W�F�N�g[object.cpp]
// Author:Uedakou
// 
//============================================
#include "object.h"	// �I�u�W�F�N�g
#include "object_billboard.h"	// �r���{�[�h

// �ÓI�����o�ϐ�
CObject* CObject::m_pTop[MAX_PRIORITY] = {};	// �I�u�W�F�N�g�f�[�^
CObject* CObject::m_pCur[MAX_PRIORITY] = {};	// �I�u�W�F�N�g�f�[�^
int CObject::m_nNumObject[MAX_PRIORITY] = {};	// �K�w���ƃI�u�W�F�N�g��

/// <summary>
/// �R���X�g���N�^
/// </summary>
CObject::CObject()
{
	m_pNext = nullptr;		// ���I�u�W�F�N�g
	m_pPrev = nullptr;		// �O�I�u�W�F�N�g
	m_nNumObject[s_nDefalut_Priority]++;	// �I�u�W�F�N�g�����Z
	m_ID = m_nNumObject[s_nDefalut_Priority];	// ID���L�^

	m_nPriority = s_nDefalut_Priority;		// �I�u�W�F�N�g�v���C�I���e�B

	// �g�����X�t�H�[���ݒ�
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_fDistance = 0.0f;	// �J��������̋���

	m_bAllUpdate = true;	// �S�̂ōX�V���邩
	m_bPoseUpdate = false;	// �|�[�Y���X�V���邩
	m_bAllDraw = true;		// �S�̂ŕ`�悷�邩
	m_bPoseDraw = true;		// �|�[�Y���`�悷�邩
	m_bReleaseScene = true;	// �V�[���Ń����[�X���邩

	m_bDeath = false;		// �f�X�t���O

	// �擪���Ȃ�������擪�ݒ�
	if (m_pTop[s_nDefalut_Priority] != nullptr)
	{
		m_pCur[s_nDefalut_Priority]->m_pNext = this;
		m_pPrev = m_pCur[s_nDefalut_Priority];
		m_pCur[s_nDefalut_Priority] = this;
	}
	else
	{
		m_pTop[s_nDefalut_Priority] = this;
		m_pCur[s_nDefalut_Priority] = this;
	}
}
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="nPriority">�D��x</param>
CObject::CObject(const int nPriority)
{
	m_pNext = nullptr;		// ���I�u�W�F�N�g
	m_pPrev = nullptr;		// �O�I�u�W�F�N�g
	m_nNumObject[nPriority]++;	// �I�u�W�F�N�g�����Z
	m_ID = m_nNumObject[nPriority];	// ID���L�^

	m_nPriority = nPriority;	// �I�u�W�F�N�g�v���C�I���e�B

	// �g�����X�t�H�[��
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_fDistance = 0.0f;		// �J��������̋���

	m_bAllUpdate = true;		// �S�̂ōX�V���邩
	m_bPoseUpdate = false;	// �|�[�Y���X�V���邩
	m_bAllDraw = true;			// �S�̂ŕ`�悷�邩
	m_bPoseDraw = true;		// �|�[�Y���`�悷�邩
	m_bReleaseScene = true;	// �V�[���Ń����[�X���邩

	m_bDeath = false;		// �f�X�t���O

	// �擪���L�����疖���ɒǉ�
	if (m_pTop[nPriority] != nullptr)
	{
		m_pCur[nPriority]->m_pNext = this;
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority] = this;
	}
	// �擪���Ȃ�������擪�ݒ�
	else
	{
		m_pTop[nPriority] = this;
		m_pCur[nPriority] = this;
	}
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CObject::~CObject()
{
	// �I�u�W�F�N�g�������炷�ݒ�
	m_nNumObject[m_nPriority]--;
}
/// <summary>
/// ���S�t���O
/// </summary>
void CObject::Release()
{
	m_bDeath = true;
}
/// <summary>
/// �V�[���`�F���W���ɉ��
/// </summary>
void CObject::ReleaseScene()
{
	// �D��x���J��Ԃ�
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		// �g�b�v���I�u�W�F�N�g�ɓ����
		CObject* pObjact = m_pTop[nCntPriority];
		// �I�u�W�F�N�g�������Ȃ�܂ő�����
		while (pObjact != nullptr)
		{	
			CObject* pNext = pObjact->GetNext();	//	���ۊ�
			// �V�[�������[�X�ŉ�����邩�ǂ���
			if (pObjact->m_bReleaseScene)
			{
				CObject* pNext = pObjact->m_pNext;	// ���ۊ�
				CObject* pPrev = pObjact->m_pPrev;	// �O�ۊ�
				// �����L���
				if (pNext != nullptr)
				{// ���ɑO������
					pNext->SetPrev(pPrev);
				}
				// �O���L���
				if (pPrev != nullptr)
				{// �O�Ɏ�������
					pPrev->SetNext(pNext);
				}

				// �g�b�v�����̃I�u�W�F�N�g�Ȃ�
				if (m_pTop[nCntPriority] == pObjact)
				{
					// ����擪�ɓ����
					m_pTop[nCntPriority] = pNext;
				}
				// ���[�����̃I�u�W�F�N�g�Ȃ�
				if (m_pCur[nCntPriority] == pObjact)
				{
					// �O�𖖒[�ɓ����
					m_pCur[nCntPriority] = pPrev;
				}
				// �I�u�W�F�N�g�̏I������
				pObjact->Uninit();

				// ���
				delete pObjact;
			}
			// ���Ɉڍs
			pObjact = pNext;

		}
	}
}
/// <summary>
/// �S�I�u�W�F�N�g���
/// </summary>
void CObject::ReleaseAll()
{
	// �D��x���J��Ԃ�
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		// �g�b�v���I�u�W�F�N�g�ɓ����
		CObject* pObjact = m_pTop[nCntPriority];
		// �I�u�W�F�N�g�������Ȃ�܂ő�����
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext;	// ���ۊ�
			CObject* pPrev = pObjact->m_pPrev;	// �O�ۊ�
			// �����L���
			if (pNext != nullptr)
			{// ���ɑO������
				pNext->SetPrev(pPrev);
			}
			// �O���L���
			if (pPrev != nullptr)
			{// �O�Ɏ�������
				pPrev->SetNext(pNext);
			}

			// �g�b�v�����̃I�u�W�F�N�g�Ȃ�
			if (m_pTop[nCntPriority] == pObjact)
			{
				// ����擪�ɓ����
				m_pTop[nCntPriority] = pNext;
			}
			// ���[�����̃I�u�W�F�N�g�Ȃ�
			if (m_pCur[nCntPriority] == pObjact)
			{
				// �O�𖖒[�ɓ����
				m_pCur[nCntPriority] = pPrev;
			}
			// �I�u�W�F�N�g�̏I������
			pObjact->Uninit();
			// ���
			delete pObjact;
			// ���Ɉڍs
			pObjact = pNext;
		}
	}
}
/// <summary>
/// ���S�t���O�������Ă�������
/// </summary>
void CObject::ReleaseDeathFlag()
{
	// �D��x���J��Ԃ�
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		// �g�b�v���I�u�W�F�N�g�ɓ����
		CObject* pObjact = m_pTop[nCntPriority];
		// �I�u�W�F�N�g�������Ȃ�܂ő�����
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext;	//	���ۊ�
			CObject* pPrev = pObjact->m_pPrev;	// �O�ۊ�
			// ���S�t���O�������Ă�����
			if (pObjact->m_bDeath == true)
			{
				// �����L���
				if (pNext != nullptr)
				{// ���ɑO������
					pNext->SetPrev(pPrev);
				}
				// �O���L���
				if (pPrev != nullptr)
				{// �O�Ɏ�������
					pPrev->SetNext(pNext);
				}

				// �g�b�v�����̃I�u�W�F�N�g�Ȃ�
				if (m_pTop[nCntPriority] == pObjact)
				{
					// ����擪�ɓ����
					m_pTop[nCntPriority] = pNext;
				}
				// ���[�����̃I�u�W�F�N�g�Ȃ�
				if (m_pCur[nCntPriority] == pObjact)
				{
					// �O�𖖒[�ɓ����
					m_pCur[nCntPriority] = pPrev;
				}
				// �I�u�W�F�N�g�̏I������
				pObjact->Uninit();
				// ���
				delete pObjact;
			}
			// ���Ɉڍs
			pObjact = pNext;
		}
	}
}
/// <summary>
/// �I�u�W�F�N�g�X�V
/// </summary>
void CObject::UpdateAll()
{
	// �|�[�Y��Ԏ擾
	const bool bPose = CManager::GetInstance()->GetSceneManager()->GetPose();
	// �v���C�I���e�B���J��Ԃ�
	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		// �g�b�v���I�u�W�F�N�g�ɓ����
		CObject* pObjact = m_pTop[nCntPriority];
		// �I�u�W�F�N�g�������Ȃ�܂ő�����
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	���ۊ�
			// �|�[�Y��ԂȂ�
			if (bPose)
			{
				// �|�[�Y���X�V����Ȃ�
				if (pObjact->IsPoseUpdate())
				{
					pObjact->Update();
				}
			}
			// �ʏ펞
			else
			{
				// �ʏ펞�X�V����Ȃ�
				if (pObjact->IsAllUpdate())
				{
					pObjact->Update();
				}
			}
			// ���Ɉڍs
			pObjact = pNext;
		}
	}
	
}
/// <summary>
/// �I�u�W�F�N�g�`��
/// </summary>
void CObject::DrawAll()
{
	// �|�[�Y��Ԏ擾
	const bool bPose = CManager::GetInstance()->GetSceneManager()->GetPose();
	// �v���C�I���e�B���J��Ԃ�
	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		// �g�b�v���I�u�W�F�N�g�ɓ����
		CObject* pObjact = m_pTop[nCntPriority];
		// �I�u�W�F�N�g�������Ȃ�܂ő�����
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	���ۊ�
			// �|�[�Y��ԂȂ�
			if (bPose)
			{
				// �|�[�Y���X�V����Ȃ�
				if (pObjact->IsPoseDraw())
				{
					pObjact->Draw();
				}
			}
			// �ʏ펞
			else
			{
				// �ʏ펞�X�V����Ȃ�
				if (pObjact->IsAllDraw())
				{
					pObjact->Draw();
				}
			}
			// ���Ɉڍs
			pObjact = pNext;
		}
	}

}
/// <summary>
/// �I�u�W�F�N�g�擾
/// </summary>
/// <param name="object">�擪������I�u�W�F�N�g���X�g</param>
void CObject::GetAllObject(CObject* object[MAX_PRIORITY])
{

	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		object[nCnt] = m_pTop[nCnt];
	}
}
/// <summary>
/// �J��������̋����Ń\�[�g
/// </summary>
void CObject::Sort()
{
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		CObject* headUnsorted;	// �O
		CObject* headSorted;	// �擪
		CObject* max;			// ���ɑ傫��
		CObject* prevMax;		// �O�̍ő�
		CObject* prevComp;		// 
		//printf("���X�g�������\�[�g���܂�\n");
		headUnsorted = m_pTop[nCnt];    // ���\�[�g���X�g
		headSorted = nullptr;			// �\�[�g�σ��X�g 

		//------------------------------------------------------------
		// �I���\�[�g
		//------------------------------------------------------------
		// 
		while (headUnsorted != nullptr)
		{
			max = headUnsorted;				// �ő�l�v�f�������� 
			prevMax = nullptr;			// �ő�l�v�f�̑O�̗v�f�������� 
			prevComp = headUnsorted;	// 
			//------------------------------------------------------------
			// ���\�[�g���X�g��������𖞂����ő�l��T��
			//------------------------------------------------------------
			// ��������łȂ����
			while (prevComp->m_pNext != nullptr) {
				// �����𖞂����ꍇ�̂ݔ�r

				// �r���{�[�h�Ȃ�
				if (dynamic_cast<CObjectBillbord*>(prevComp->m_pNext)) {
					// �\�[�g����
					//
					if ((prevComp->m_pNext)->m_fDistance < max->m_fDistance) {
						max = prevComp->m_pNext;			// �ő�l���X�V
						prevMax = prevComp;				// �ő�l�̑O�̗v�f���L�^
					}
				}
				prevComp = prevComp->m_pNext;		// ���̗v�f�ɐi��
			}
			// �ő�l��������Ȃ��ꍇ�A�c��̃��X�g�̓\�[�g�ΏۊO
			if (max == nullptr) {//max��NULL�ɂȂ�Ȃ�
				break;
			}

			// �ő�l�𖢃\�[�g���X�g����폜
			if (prevMax == nullptr) {
				// �ő�l�����X�g�̐擪�̏ꍇ
				headUnsorted = max->m_pNext;
			}
			else {
				// �ő�l�����X�g���珜�O
				prevMax->m_pNext = max->m_pNext;
			}

			// �ő�l�v�f���\�[�g�σ��X�g�̐擪�ɒǉ�
			if (headSorted == NULL) {
				// �\�[�g�σ��X�g����̏ꍇ
				headSorted = max;
				m_pCur[nCnt] = max;
				max->m_pNext = NULL;
				max->m_pPrev = NULL;
			}
			else {
				// �\�[�g�σ��X�g�̐擪�ɒǉ�
				max->m_pNext = headSorted;
				headSorted->m_pPrev = max;
				max->m_pPrev = NULL;
				headSorted = max;

			}
		}
		m_pTop[nCnt] = headSorted;
	}
}
/// <summary>
/// �J��������̋����Ń\�[�g
/// </summary>
void CObject::CalculateDistanceToCamera()
{
	CManager* instance = CManager::GetInstance();
	CCamera* pCamera = instance->GetCamera();
	D3DXVECTOR3 pos = pCamera->GetPosR();

	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	���ۊ�

			pObjact->CalculateDistance(pos);

			pObjact = pNext;
		}
	}
}
/// <summary>
/// �J��������̋������v�Z
/// </summary>
/// <param name="pos"></param>
void CObject::CalculateDistance(D3DXVECTOR3 pos)
{
	// �J�����Ƃ̍����v�Z�iVec3�j
	D3DXVECTOR3 diff = m_x.pos - pos;
	// �x�N�^�[���狗��(float)
	m_fDistance = D3DXVec3LengthSq(&diff); // �����̓����v�Z
}