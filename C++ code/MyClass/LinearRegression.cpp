#include "stdio.h"
#include "iostream"
#include "math.h"
#include "cstdlib"
#include "Matrix.cpp"

class LinearModel{
	public:
		int n,p;
		Matrix:: X(n,p);

		int isColinear(){
			return 0;
		}

		Matrix getHatMatrix(){
			return this->X;
		}

		Matrix estimateByLS(){
			Matrix:: beta(1,p);
			return (this->X.transpose().MatrixMul(this->X)).inverseMatrix_Partial();
		}

		Matrix estimateByRidge(){
			return this->X;
		}

		Matrix estimateByShrinkage(){
			return this->X;
		}

		void summary(){

		}

};


int main(int argc, char const *argv[])
{
	Matrix::Matrix a(2,2);
	// a.setMatrixELement();
	// a.showMatrixElement();
	return 0;
}