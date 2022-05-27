#include "path.h"
#include "utils.h"
#include <stdio.h>
#include <random>

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
    printf("\nPATH IS:\n");
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

void dg::c_path::apply_brownian()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(0.0, 1.0);
    const double scale = 1.0;

    if(m_first_node == nullptr)
    {
        return;
    }

    std::shared_ptr<c_node> curr_node = m_first_node;
    while(curr_node != nullptr)
    {
        curr_node->next_pos.x += dis(gen);
        curr_node->next_pos.y += dis(gen);
        curr_node = curr_node->n_node.lock();
    }
}


void dg::c_path::apply_split()
{
    if(m_first_node == nullptr)
    {
        return;
    }

    std::shared_ptr<c_node> node_1 = m_first_node;
    std::shared_ptr<c_node> node_2 = node_1->n_node.lock();;
    while(node_1 != nullptr && node_2 != nullptr)
    {
        if(dg::node_distance(*node_1, *node_2) > 100.0)
        {
            dg::pt2 midpoint = dg::nodes_midpoint(*node_1, *node_2);
            auto node = std::make_shared<dg::c_node>(midpoint.x, midpoint.y);
            /* Insert the node in between */
            m_nodes.push_back(node);
            node->p_node = node_1;
            node->n_node = node_2;
            node_1->n_node = node;
            node_2->p_node = node;
        }
        /* Get next pair */
        node_1 = node_2;
        node_2 = node_2->n_node.lock();;
    }
}


void dg::c_path::update_path()
{
    if(m_first_node == nullptr)
    {
        return;
    }

    std::shared_ptr<c_node> curr_node = m_first_node;
    while(curr_node != nullptr)
    {
        curr_node->curr_pos.x = curr_node->next_pos.x;
        curr_node->curr_pos.y = curr_node->next_pos.y;
        curr_node = curr_node->n_node.lock();
    }
}