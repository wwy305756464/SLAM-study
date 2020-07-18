#include <iostream>
using namespace std;

#include<ctime>
#include<Eigen/Core>
#include<Eigen/Dense>
using namespace Eigen;

#define MATRIX_SIZE 100

int main(int argc, char **argv) {
    Matrix<double, Dynamic, Dynamic> matrix_100;

    matrix_100.resize(100, 100);
    matrix_100 = MatrixXd::Random(100,100);
    matrix_100 = matrix_100 * matrix_100.transpose();
    Matrix<double, 100, 1> v_Nd = MatrixXd::Random(100,1);

    // QR Decomposition
    Matrix<double, 100, 1> x = matrix_100.colPivHouseholderQr().solve(v_Nd);
    cout << "by QR, x = " << x.transpose() << endl;

    // Cholesky Decomposition
    x = matrix_100.ldlt().solve(v_Nd);
    cout << "by Cholesky, x = " << x.transpose() << endl;

return 0;
}


