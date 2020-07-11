#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "sophus/se3.hpp"

using namespace std;
using namespace Eigen;

int main(int argc, char ** argv) {
	Matrix3d R = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();

	Quaterniond q(R);
	Sophus::SO3d SO3_R(R); // 通过旋转矩阵构造
	Sophus::SO3d SO3_q(q); // 通过四元数构造

	cout << "SO(3) from matrix:\n" << SO3_R.matrix() << endl;
	cout << "SO(3) from quaternion:\n" << S03_q.matrix() << endl;
	cout << "they are equal" << endl;

	Vector3d so3 = SO3_R.log(); // 通过对数映射得到SO3的李代数
	cout << "so3 = " << so3.transpose() << endl;
	// 这里 hat 为向量到反对称矩阵
	cout << "so3 hat = \n" << Sophus::SO3d::hat(so3) << endl;
	// 这里 vee 为反对称矩阵到向量
	cout << "so3 hat vee = " << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl;

	// 增量扰动模型的更新
	Vector3d update_so3(1e-4, 0, 0); // 更新量为这么多
	Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R; // 更新后的matrix
	cout << "SO3 updated = \n" << SO3_updated.matrix() << endl;

	xout << "*********************************************" << endl;

	// 对SE(3)的操作
	Vector3d t(1, 0, 0);
	Sophus::SE3d SE3_Rt(R, t);
	Sophus::SE3d SE3_qt(q, t);
	cout << "SE3 from R,t = \n" << SE3_Rt.matrix() << endl;
	cout << "SE3 from q,t = \n" << SE3_qt.matrix() << endl;

	typedef Eigen::Matrix<double, 6, 1> Vector6d;  // 用typedef确保se(3)是六维向量
	Vector6d se3 = SE3_Rt.log();
	cout << "se3 = " << se3.transpose() << endl;

	cout << "se3 hat = \n" << Sophus::SE3d::hat(se3) << endl;
	cout << "se3 hat vee = " << Sophus::SE3d::vee(sophus::SE3d::hat(se3)).transpose() << endl;

	Vector6d update_se3;
	update_se3.setZero();
	update_Se3(0, 0) = 1e-4d;
	Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
	cout << "SE3 updated = " << endl << SE3_updated.matrix() << endl;

	return 0;
}