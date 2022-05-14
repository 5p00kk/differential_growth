/* 
TODO

*/
#pragma once
#include "node.h"
#include <vector>
#include <memory>

namespace dg
{

class c_path
{
public:
    void add_node(c_node node);

    /* Get point count */
    inline size_t kdtree_get_point_count() const { return m_nodes.size(); }

    // Returns the dim'th component of the idx'th point in the class:
    // Since this is inlined and the "dim" argument is typically an immediate
    // value, the
    //  "if/else's" are actually solved at compile time.
    inline double kdtree_get_pt(const size_t idx, const size_t dim) const
    {
        if (dim == 0)
            return m_nodes[idx].pos.x;
        else
            return m_nodes[idx].pos.y;
    }

    /* Optional bounding-box computation */
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /* bb */) const {return false;}

    std::vector<c_node> m_nodes;
};

}