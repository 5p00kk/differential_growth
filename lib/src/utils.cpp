#include "utils.h"
#include <cmath>

double dg::node_distance(const c_node& first, const c_node& second)
{
    return sqrt(pow((first.curr_pos.x - second.curr_pos.x), 2) + pow((first.curr_pos.y - second.curr_pos.y), 2));
}

dg::pt2 dg::nodes_midpoint(const c_node& first, const c_node& second)
{
    pt2 midpoint{};
    midpoint.x = std::min(first.curr_pos.x, second.curr_pos.x) + abs(first.curr_pos.x - second.curr_pos.x);
    midpoint.y = std::min(first.curr_pos.y, second.curr_pos.y) + abs(first.curr_pos.y - second.curr_pos.y);
    return midpoint;
}