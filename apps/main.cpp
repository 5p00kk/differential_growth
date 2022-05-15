#include <stdio.h>
#include "node.h"
#include "path.h"
#include "visualizer.h"

int main(int argc, char const *argv[])
{
    printf("diff_growth\n");
    
    dg::c_path path;
    dg::c_visualizer visualizer;

    printf("Creating ptr\n");
    for(int i=0;i<100;i++)
    {
        printf("Created ptr\n");
        path.add_node(std::make_shared<dg::c_node>(i, i));
    }
    printf("added %ld nodes\n", path.kdtree_get_point_count());
    path.print_path();

    cv::Mat output_image;
    visualizer.visualize(path.m_first_node, output_image);

    return 0;
}