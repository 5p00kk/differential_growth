#include <stdio.h>
#include <cmath>
#include "node.h"
#include "path.h"
#include "visualizer.h"
#include "recorder.h"
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char const *argv[])
{
    printf("--diff_growth--\n");
    
    dg::c_path path;
    dg::c_visualizer visualizer;
    const int output_dim = 700;
    const double zero_cross = 4.0;
    const double lower_force_radius = 2.0;
    const double upper_force_radius = 10.0;
    const double pruning_radius = 2.0;
    const double split_length = 10.0;
    
    c_recorder m_recorder;
    m_recorder.new_recording(output_dim, output_dim, "");
    
    
    cv::Mat output_image = cv::Mat::zeros(output_dim, output_dim, CV_8UC1);
    cv::Mat cumulative = cv::Mat::zeros(output_dim, output_dim, CV_8UC1);

    /* Generate initial path (circle) */
    for(double step = 0; step<2*3.14; step+=0.1)
    {
        double x = 100*sin(step);
        double y = 100*cos(step);
        path.add_node(std::make_shared<dg::c_node>(350+x, 350+y));
    }

    /* Growtih iterate */
    for(int step=0; step<10000; step++)    
    {
        printf("Path contains %d nodes\n", (int)path.m_nodes.size());

        /* Path operations */
        path.apply_brownian(0.1);
        path.apply_attraction_repulsion(zero_cross, lower_force_radius, upper_force_radius);
        path.apply_alignment(0.01);
        path.update_path();
        path.apply_split(split_length);
        path.apply_pruning(pruning_radius);

        /* Visualize */
        visualizer.visualize(path.m_first_node, output_image);
        cumulative = (output_image/255)+cumulative;
        
        if(step%100 == 0)
        {
            printf("Step: %d\n", step);
        }

        if(step%5 == 0)
        {
            m_recorder.video_add_frame(output_image);
        }
        cv::imshow("cumulative", cumulative);
        cv::imshow("output", output_image);
        cv::waitKey(1);
    }

    cv::imwrite("cumulative.png", cumulative);
    cv::imwrite("output.png", output_image);

    m_recorder.stop_recording();
    return 0;
}