#include <stdio.h>
#include "node.h"
#include "path.h"
#include "visualizer.h"
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char const *argv[])
{
    printf("diff_growth\n");
    
    dg::c_path path;
    dg::c_visualizer visualizer;

    printf("Creating ptr\n");
    for(int i=0;i<300;i++)
    {
        printf("Created ptr\n");
        path.add_node(std::make_shared<dg::c_node>(i+300, i+300));
    }
    printf("added %ld nodes\n", path.kdtree_get_point_count());
    path.print_path();

    cv::Mat output_image;
    cv::Mat cumulative = cv::Mat::zeros(900, 900, CV_8UC1);

    for(int step=0; step<10000; step++)    
    {
        path.apply_brownian();
        path.apply_attraction(2.0, 0.2);
        path.apply_repulsion(15.0, 0.1);
        path.update_path();
        path.apply_split(10.0);
        //path.print_path();
        visualizer.visualize(path.m_first_node, output_image);
        cumulative = (output_image/255)+cumulative;
        cv::imshow("cumulative", cumulative);
        cv::imshow("output", output_image);
    }

    return 0;
}