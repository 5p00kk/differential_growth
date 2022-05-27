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

dg::pt2 dg::pts_midpoint(const dg::pt2& first, const dg::pt2& second)
{
    pt2 midpoint{};
    midpoint.x = std::min(first.x, second.x) + abs(first.x - second.x)/2;
    midpoint.y = std::min(first.y, second.y) + abs(first.y - second.y)/2;
    return midpoint;
}

dg::pt2 dg::lerp(const dg::pt2& first, const dg::pt2& second, double t)
{
    dg::pt2 retval{};
    retval.x = first.x + (second.x - first.x) * t;
    retval.y = first.y + (second.y - first.y) * t;
    return retval;
}

dg::pt2 dg::lerp_diff(const dg::pt2& first, const dg::pt2& second, double t)
{
    dg::pt2 retval{};
    retval.x = (second.x - first.x) * t;
    retval.y = (second.y - first.y) * t;
    return retval;
}

dg::pt2 dg::get_force(const dg::pt2& first, const dg::pt2& second, double zero_point)
{
    double distance = sqrt(pow(first.x - second.x,2)+pow(first.y - second.y,2));
    double lj_force = pow(zero_point/distance, 12) - pow(zero_point/distance, 6);

    dg::pt2 retval{};
    retval.x = ((second.x - first.x) / distance)*lj_force;
    retval.y = ((second.y - first.y) / distance)*lj_force;

    return retval;
}