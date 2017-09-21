#include <iostream>
 
using namespace std;
 
class Matrix{
	public:
		Matrix(int col,int row){
			this->col=col;
			this->row=row; 
		}
		void setRow(int row){
			this->row=row;
		}
		int getRow(){
			return this->row;
		}
		void setCol(int col){
			this->col=col;
		}
		int getCol(){
			return this->col;
		}

		int isSquare(){
			if(this->col==this->row){
				return 1;
			}else{
				return 0;
			}
		}

		// void setMatrixElement(){
		// 	for(int i=0;i<this->col;i++){
		// 		for(int j=0;j<this->row;j++){
		// 			printf("Enter [%d][%d] : ",j,i);
		// 			scanf("%lf",&element[j][i]);
		// 		}	
		// 	}
		// }

	private:
		int row;
		int col;
		double element[];
};


int main(int argc, char const *argv[])
{
	Matrix a(3,3);
	printf("row %d",a.getRow());
	// a.setMatrixElement();
	return 0;
}