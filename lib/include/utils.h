#pragma once

#include "node.h"

namespace dg
{
double node_distance(const c_node& first, const c_node& second);
pt2 nodes_midpoint(const c_node& first, const c_node& second);
}