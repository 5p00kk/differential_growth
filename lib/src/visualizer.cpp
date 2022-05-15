#include "visualizer.h"
#include <stdio.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

dg::c_visualizer::c_visualizer()
{}

void dg::c_visualizer::visualize(const std::shared_ptr<dg::c_node> first_node, cv::Mat& output_mat) const
{
    if(first_node == nullptr)
    {
        return;
    }

    /* TODO get this size from somewhere */
    /* Clear the array */
    output_mat = cv::Mat::zeros(900, 900, CV_8UC1);

    /* Draw lines */
    std::shared_ptr<c_node> curr_node = first_node;

    cv::Point2i p1(0, 0);
    cv::Point2i p2(0, 0);
    bool skip = true;

    while(curr_node != nullptr)
    {
        p2.x = int(curr_node->curr_pos.x);
        p2.y = int(curr_node->curr_pos.y);

        if(!skip)
        {
            cv::line(output_mat, p1, p2, 255, 1);
        }
        else
        {
            skip = false;
        }

        p1.x = p2.x;
        p1.y = p2.y;
        curr_node = curr_node->n_node.lock();
    }
}