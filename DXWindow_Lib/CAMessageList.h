#pragma once
#include "CAStd.h"

class CAMessageList :public CASingleton<CAMessageList>
{
    friend CASingleton<CAMessageList>;

public:
    vector<MSG> Msg_list;

    //void Pushback_msg(MSG dwkey);
private:
        CAMessageList();
public:
    virtual ~CAMessageList();
};

#define I_MSG CAMessageList::GetInstance()