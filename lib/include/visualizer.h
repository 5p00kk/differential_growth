#pragma once
#include "node.h"
#include <opencv2/core/mat.hpp>

namespace dg
{

class c_visualizer
{
public:
    c_visualizer();
    void visualize(const std::shared_ptr<dg::c_node> first_node, cv::Mat& output_mat) const;
};

}