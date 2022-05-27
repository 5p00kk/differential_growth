#pragma once

#include "node.h"

namespace dg
{
double node_distance(const c_node& first, const c_node& second);
pt2 nodes_midpoint(const c_node& first, const c_node& second);
pt2 lerp(pt2 first, pt2 second, double t);
pt2 lerp_diff(pt2 first, pt2 second, double t);
}