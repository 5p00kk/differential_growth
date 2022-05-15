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
    for(int step=0; step<1000; step++)    
    {
        
        path.apply_brownian();
        path.update_path();
        path.print_path();
        visualizer.visualize(path.m_first_node, output_image);
        cv::imshow("output", output_image);
        cv::waitKey(10);
    }

    return 0;
}