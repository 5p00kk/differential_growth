#pragma once

#include <memory>

namespace dg
{

struct pt2
{
    double x, y;
};

class c_node
{
public:
    c_node(double x, double y);
    void update_position();
    std::weak_ptr<c_node> p_node;
    std::weak_ptr<c_node> n_node;
    pt2 curr_pos;
    pt2 next_pos;
};

}