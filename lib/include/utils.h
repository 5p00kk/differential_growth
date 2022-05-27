#pragma once

#include "node.h"

namespace dg
{
double node_distance(const dg::c_node& first, const dg::c_node& second);
dg::pt2 nodes_midpoint(const dg::c_node& first, const dg::c_node& second);
dg::pt2 pts_midpoint(const dg::pt2& first, const dg::pt2& second);
dg::pt2 lerp(const dg::pt2& first, const dg::pt2& second, double t);
dg::pt2 lerp_diff(const dg::pt2& first, const dg::pt2& second, double t);
dg::pt2 get_force(const dg::pt2& first, const dg::pt2& second, double zero_point);
}