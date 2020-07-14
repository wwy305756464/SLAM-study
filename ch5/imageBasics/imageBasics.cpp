#include <iostream>
#include <chrono>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv) {
	cv::Mat image;  // 创建一个image的array class，用来储存图像array
	image = cv::imread(argv[1]);  // cv::imread函数用于读取指定路径下的图像，
								  // 这里的指定路径为 argv[1]

	// 判断图像文件的读取是否正确
	if (image.data == nullptr) {  // 判断如果数据不存在或者文件不存在
		cerr << "file" << argv[1] << "does not exist." << endl;
		// cerr: error for char
		return 0;
	}

	// 图像顺利读取后输出一些基本信息
	cout << "width of image is: " << image.cols << endl;   // num of cols
	cout << "height of image is: " << image.rows << endl;  // num of rows
	cout << "number of channels is: " << image.channels() << endl;  // num of channels
	cv::imshow("image", image);  // cv::imshow 来显示图像，这里将image显示为“image”
	cv::waitKey(0);  // waitKey用于暂停程序，等待一个按键的输入

	// 判断图片的类型
	// CV_8UC1, CV_8UC3 -> CV_<bit-depth>(S/U/F)C<number-of-channels>
	// bit-depth: 图像中每个像素点在内存空间内所占空间大小是多少个bite
	// S/U/F: S->signed int; U->unsigned int; F->float
	// C<number-of-channels>: 图片的通道数: 1->灰度图, 3->RGB图像, 4->带Alph通道的RGB图
	if (image.type() != CV_8UC1 && image.type() != CV_8UC3) {
		cout << "please insert a color image or gray image." << endl;
		return 0;
	}

	// 遍历图像，这个遍历方式也可以用于随机像素访问
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();、
	// std::chrono用于给算法计时
	for (size_t y = 0; y < image.rows; y++) {  // 遍历每行
		unsigned char *row_ptr = image.ptr<unsigned char>(y);
		// row_ptr代表了第y行的头指针
		for (size_t x = 0; x < image.cols; x++) {  // 遍历每列
			// 访问位于（x,y）处的像素
			unsigned char *data_ptr = &row_ptr[x * image.channels()];
			// data_ptr 指向待访问的像素数据
			// 输出该像素的每个通道，如果是灰度图的话就只有一个通道
			for (int c = 0; c != image.channels(); c++) {
				unsigned char data = data_ptr[c];  // data是I(x,y)第c个通道的值
			}
		}
	} 

	chorno::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> time_used = 
		chrono::duration_cast < chrono::duraction <double>>(t2-t1);
	cout >> "read all image data used: " << time_used.count() << " seconds." << endl;

	// CV 中的赋值与拷贝
	// 直接赋值并不会拷贝数据
	cv::Mat image_another = image;
	// 这里修改赋值后的image_another也会同时导致image发生变化
	image_another(cv::Rect(0, 0, 100, 100)).setTo(0); // 将图片左上角 100*100 的部分置零
	cv::imshow("image", image);
	cv::waitKey(0);

	// 使用clone后再修改，不会修改原来的图
	cv::Mat iamge_clone = image.clone();
	image_clone(cv::Rect(0, 0, 100, 100)).setTo(255);
	cv::imshow("image", image);
	cv::imshow("image_clone", image_clone);
	cv::waitKey(0);

	cv::destroyAllWindows();
	return 0;
}