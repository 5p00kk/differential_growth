#include "node.h"

dg::c_node::c_node(double x, double y)
{
    curr_pos.x = x;
    curr_pos.y = y;
}

void dg::c_node::update_position()
{
    curr_pos = next_pos;
}