#include "Tree_Node.h"

void Tree_Node::Release()
{
    for (auto nodes : m_Child_List)
    {
        nodes->Release();
        delete nodes; 
    }
#pragma message (TODO("�̰� �Ӹ� ������ �´��� �ٽ� �����ѹ��ϱ�"))

}


Tree_Node::Tree_Node()
{
}


Tree_Node::~Tree_Node()
{

}
