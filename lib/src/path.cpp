#include "path.h"

dg::c_path::c_path()
{
    m_nodes.reserve(1000);
}

void dg::c_path::add_node(c_node node)
{
    m_nodes.push_back(node);
}
