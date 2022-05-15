#include "path.h"
#include <stdio.h>

dg::c_path::c_path()
{
    m_nodes.reserve(1000);
}

void dg::c_path::add_node(std::shared_ptr<c_node> node)
{
    m_nodes.push_back(node);
    if(m_last_node == nullptr)
    {
        m_first_node = node;
        m_last_node = node;
    }
    else
    {
        m_last_node->n_node = node;
        node->p_node = m_last_node;
        m_last_node = node;
    }
}

void dg::c_path::print_path() const
{
    if(m_first_node != nullptr)
    {
        std::shared_ptr<c_node> curr_node = m_first_node;
        while(curr_node != nullptr)
        {
            printf("%f %f\n", curr_node->curr_pos.x, curr_node->curr_pos.y);
            curr_node = curr_node->n_node.lock();
        }
    }
    else
    {
        printf("No nodes!\n");
    }
}