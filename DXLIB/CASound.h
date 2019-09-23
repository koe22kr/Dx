#pragma once

#include "CAStd.h"
#include "fmod.hpp"

class CASound
{
public:
    FMOD::Sound*    m_pSound;   //사운드 데이터 저장되는곳.  ////
                                     //배열숫자 변경요망
    
    //std::string     m_szBuffer;
    
    //int             m_iNumsound;                                          //필요 없을 것 이다.
    //int             m_iSE_Num; //m_pSound 배열 카운팅 //로드시            //필요 없을 것 이다.
    //int             m_iBGM_Num;//bgm 번호 카운팅                          //필요 없을 것 이다.

    CASound();
    virtual ~CASound();
};

//stl map.
//
//std::vector<T*> m_List;   //front<->back push    인덱싱
//std::list<T*> m_List;     //front<->back push 
//std::set<T*> m_List;      //front<->back push
//std::map<DWORD,T*> m_List;  기본저장 방식 - > BST , 인덱싱, 리스트관리-> 검색 최적화 STL     //키값은 DWORD , STR 맘대로 사용가능

//play에서 중복 재생 막는걸, 플레이 중이면 정지 시키고, 틀기 로 하자. 다른 브금으로 변경 할 경우가 존재.



