#include "utils.h"
#include <cmath>

double dg::node_distance(const dg::c_node& first, const dg::c_node& second)
{
    return sqrt(pow((first.curr_pos.x - second.curr_pos.x), 2) + pow((first.curr_pos.y - second.curr_pos.y), 2));
}

dg::pt2 dg::nodes_midpoint(const dg::c_node& first, const dg::c_node& second)
{
    pt2 midpoint{};
    midpoint.x = std::min(first.curr_pos.x, second.curr_pos.x) + abs(first.curr_pos.x - second.curr_pos.x)/2;
    midpoint.y = std::min(first.curr_pos.y, second.curr_pos.y) + abs(first.curr_pos.y - second.curr_pos.y)/2;
    return midpoint;
}

dg::pt2 dg::lerp(dg::pt2 first, dg::pt2 second, double t)
{
    dg::pt2 retval{};
    retval.x = first.x + (second.x - first.x) * t;
    retval.y = first.y + (second.y - first.y) * t;
    return retval;
}

dg::pt2 dg::lerp_diff(dg::pt2 first, dg::pt2 second, double t)
{
    dg::pt2 retval{};
    retval.x = (second.x - first.x) * t;
    retval.y = (second.y - first.y) * t;
    return retval;
}