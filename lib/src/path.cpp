#include "path.h"
#include "utils.h"
#include <stdio.h>
#include <random>

dg::c_path::c_path()
: m_search_index{2, *this, {10}}
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

void dg::c_path::apply_brownian(double scale)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(0.0, 0.1);

    if(m_first_node == nullptr)
    {
        return;
    }

    std::shared_ptr<c_node> curr_node = m_first_node;
    while(curr_node != nullptr)
    {
        curr_node->next_pos.x += scale * dis(gen);
        curr_node->next_pos.y += scale * dis(gen);
        curr_node = curr_node->n_node.lock();
    }
}


void dg::c_path::apply_split(double split_distance)
{
    if(m_first_node == nullptr)
    {
        return;
    }

    std::shared_ptr<c_node> node_1 = m_first_node;
    std::shared_ptr<c_node> node_2 = node_1->n_node.lock();;
    while(node_1 != nullptr && node_2 != nullptr)
    {
        if(dg::node_distance(*node_1, *node_2) > split_distance)
        {
            dg::pt2 midpoint = dg::pts_midpoint(node_1->curr_pos, node_2->curr_pos);
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

void dg::c_path::apply_alignment(double aligment_force)
{
    if(m_first_node == nullptr)
    {
        return;
    }
    
    std::shared_ptr<c_node> prev_node = nullptr;
    std::shared_ptr<c_node> curr_node = m_first_node;
    std::shared_ptr<c_node> next_node = curr_node->n_node.lock();

    while(curr_node != nullptr)
    {
        /* Apply aligment "force" */
        if(prev_node != nullptr && next_node != nullptr)
        {
            pt2 midpoint = pts_midpoint(prev_node->next_pos, next_node->next_pos);
            pt2 direction = get_force_dir(curr_node->next_pos, midpoint);
            curr_node->next_pos.x += aligment_force * direction.x;
            curr_node->next_pos.y += aligment_force * direction.y;
        }

        if(next_node == nullptr)
        {
            break;
        }

        /* Get next trio */
        prev_node = curr_node;
        curr_node = next_node;
        next_node = next_node->n_node.lock();
    }
}

void dg::c_path::apply_attraction_repulsion(double att_rep_crossing, double low_thresh, double high_thresh)
{
    if(m_first_node == nullptr)
    {
        return;
    }

    m_search_index.buildIndex();

    std::shared_ptr<c_node> curr_node = m_first_node;
    while(curr_node != nullptr)
    {
        const double query_pt[2] = {curr_node->next_pos.x, curr_node->next_pos.y};
        const double search_radius = high_thresh*high_thresh;
        std::vector<std::pair<uint32_t, double>> ret_matches;
        nanoflann::SearchParams params;

        const size_t n_matches = m_search_index.radiusSearch(&query_pt[0], search_radius, ret_matches, params);

        for (size_t i=0; i<n_matches; i++)
        {
            size_t match_idx = ret_matches[i].first;

            if(m_nodes[match_idx] == curr_node)
                continue;
            
            if(sqrt(ret_matches[i].second) < low_thresh)
                continue;

            if(sqrt(ret_matches[i].second) > high_thresh)
                continue;

            dg::pt2 force{};
            if(sqrt(ret_matches[i].second) > att_rep_crossing)
            {
                force = dg::get_force(curr_node->curr_pos, m_nodes[match_idx]->curr_pos, att_rep_crossing);
            }
            else
            {
                force = dg::get_force_dir(curr_node->curr_pos, m_nodes[match_idx]->curr_pos);
                force.x *= -1 * (sqrt(ret_matches[i].second) - att_rep_crossing);
                force.y *= -1 * (sqrt(ret_matches[i].second) - att_rep_crossing);
            }

            curr_node->next_pos.x += force.x;
            curr_node->next_pos.y += force.y;
        }

        curr_node = curr_node->n_node.lock();
    }
}

void dg::c_path::apply_pruning(double min_distance)
{
    for(auto it = m_nodes.begin(); it != m_nodes.end();)
    {
        bool flag_remove = false;

        std::shared_ptr<c_node> curr_node = *it;
        std::shared_ptr<c_node> next_node = curr_node->n_node.lock();
        std::shared_ptr<c_node> prev_node = curr_node->p_node.lock();

        if(prev_node != nullptr && dg::node_distance(*curr_node, *prev_node) < min_distance)
        {
            flag_remove = true;
        }

        if(next_node != nullptr && dg::node_distance(*curr_node, *next_node) < min_distance)
        {
            flag_remove = true;
        }

        if(flag_remove)
        {
            if(curr_node == m_first_node)
            {
                m_first_node = next_node;
            }

            if(prev_node == nullptr)
            {
                next_node->p_node = curr_node->p_node;
            }
            else if(next_node == nullptr)
            {
                prev_node->n_node = curr_node->n_node;
            }
            else
            {
                prev_node->n_node = curr_node->n_node;
                next_node->p_node = curr_node->p_node;
            }
            it = m_nodes.erase(it);
        }
        else
        {
            ++it;
        }
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
        curr_node->update_position();
        curr_node = curr_node->n_node.lock();
    }
}