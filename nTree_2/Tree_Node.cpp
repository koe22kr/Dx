#include "Tree_Node.h"

void Tree_Node::Release()
{
    for (auto nodes : m_Child_List)
    {
        nodes->Release();
        delete nodes; 
    }
#pragma message (TODO("이거 머리 맑을때 맞는지 다시 생각한번하기"))

}


Tree_Node::Tree_Node()
{
}


Tree_Node::~Tree_Node()
{

}
