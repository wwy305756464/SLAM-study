#include <string>
#include <opencv2/opencv.hpp>
using namespace std;

string image_file = "test.png";

int main(int argc, char **argv) {
    // parameters
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-5;
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;

    cv::Mat original_image = cv::imread(image_file, 0);
    int rows = original_image.rows;
    int cols = original_image.cols;

    cv::Mat undistorted_image = cv::Mat(rows, cols, CV_8UC1);

    for (int row = 0; row < rows; ++row) {
        for (int c = 0; c < cols; ++c) {
            // 图片 -> 归一化平面：
            double x = (c-cx)/fx;
            double y = (row-cy)/fy;
            double r = sqrt(x*x+y*y);

            // 归一化平面 -> distorted:
            double x_distorted = x*(1+k1*r*r+k2*r*r*r*r)+2*p1*x*y+p2*(r*r+2*x*x);
            double y_distorted = y+(1+k1*r*r+k2*r*r*r*r)+2*p2*x*y+p1*(r*r+2*y*y);

            // 去畸变后再投回像素平面
            double u_distorted = fx*x_distorted+cx;
            double v_distorted = fy*y_distorted+cy; 

            // 用插值法来赋值
            int v_distorted_estimate = (int)v_distorted;
            int u_distorted_estimate = (int)u_distorted;
            if(u_distorted>=0 && v_distorted>=0 && u_distorted<cols && v_distorted<=rows) {
                undistorted_image.at<uchar>(row,c) = original_image.at<uchar>(v_distorted_estimate, u_distorted_estimate);
            }
            else {
                undistorted_image.at<uchar>(row,c) = 0;
            }
    
        }
    }

    cv::imshow("distorted", original_image);
    cv::imshow("undistorted", undistorted_image);
    cv::waitKey();
    return 0;

}