#pragma once

namespace dg
{

struct pt2
{
    double x, y;
};

class c_node
{
    void update_position();
public:
    c_node* p_node;
    c_node* n_node;
    pt2 curr_pos;
    pt2 next_pos;
};

}