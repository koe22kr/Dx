#pragma once

#include "CAStd.h"
#include "fmod.hpp"

class CASound
{
public:
    FMOD::Sound*    m_pSound;   //���� ������ ����Ǵ°�.  ////
                                     //�迭���� ������
    
    //std::string     m_szBuffer;
    
    //int             m_iNumsound;                                          //�ʿ� ���� �� �̴�.
    //int             m_iSE_Num; //m_pSound �迭 ī���� //�ε��            //�ʿ� ���� �� �̴�.
    //int             m_iBGM_Num;//bgm ��ȣ ī����                          //�ʿ� ���� �� �̴�.

    CASound();
    virtual ~CASound();
};

//stl map.
//
//std::vector<T*> m_List;   //front<->back push    �ε���
//std::list<T*> m_List;     //front<->back push 
//std::set<T*> m_List;      //front<->back push
//std::map<DWORD,T*> m_List;  �⺻���� ��� - > BST , �ε���, ����Ʈ����-> �˻� ����ȭ STL     //Ű���� DWORD , STR ����� ��밡��

//play���� �ߺ� ��� ���°�, �÷��� ���̸� ���� ��Ű��, Ʋ�� �� ����. �ٸ� ������� ���� �� ��찡 ����.



