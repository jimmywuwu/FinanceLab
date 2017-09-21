#include "stdio.h"
#include "iostream"
#include "math.h"
#include "cstdlib"

void hw1();
void hw2();
void hw31();
void hw32();
void hw4();
void clear_screen();
void pressAnyKey();
// void getMatrixElement(M);
class Matrix{
	public:
		int COL,ROW;
		double** data;

		Matrix(int row,int col){
				 ROW=row;
				 COL=col;
				this->data=new double*[ROW];
				for (int i = 0; i < this->ROW; i++)
				{
					data[i]=new double[COL];
				}
			}

		void setMatrixElement(){
			for (int i = 0; i < this->ROW; ++i)
			{
				for (int j = 0; j < this->COL; ++j)
				{
					printf("Please enter [%d][%d]",i+1,j+1);
					scanf("%lf", &this->data[i][j]);
				}
			}
		}

		void showMatrixElement(){
			for (int i = 0; i <  ROW; ++i)
			{
				for (int j = 0; j <  COL; ++j)
				{
					printf("%lf ", data[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}

		Matrix MatrixMul(Matrix a){

			if(this->COL != a.ROW){
				printf("%d , %d",this->COL,a.ROW);
				printf("The dimension is wrong\n");
				return *this;
			}else{
				int tmp=this->COL;
				Matrix b(2,3);
				b.copyMatrix(*this);
				Matrix c(b.ROW,a.COL);			
				
				for (int i = 0; i < b.ROW; i++)
				{
					
					for (int j = 0; j < a.COL; j++)
					{
						double sum=0;
						for (int k = 0; k< tmp; k++)
						{
							sum=sum+b.data[i][k]*a.data[k][j];	
						}
						
						c.data[i][j]=sum;					
					}
						
				}
				return c;

			}
		}

		void freeMatrix(){
			for(int i = 0; i < this->ROW; i++){
				delete [] this->data[i];
			}
        	delete [] this->data;
		}

		void copyMatrix(Matrix a){
			this->COL=a.COL;
			this->ROW=a.ROW;
			this->data=new double*[ROW];
			for (int i = 0; i < this->ROW; i++)
			{
				data[i]=new double[COL];
			}
			for (int i = 0; i < this->ROW; ++i)
			{
				for (int j = 0; j < this->COL; ++j)
				{
					this->data[i][j]=a.data[i][j];
				}
			}

		}

		Matrix addMatrix(Matrix a){
			Matrix b(this->ROW,this->COL);
			if(a.COL!=this->COL || a.ROW!=this->ROW){
				printf("dimension is wrong");
				return *this;
			}else{
				for (int i = 0; i < this->ROW; i++)
				{
					for (int j = 0; j < this->COL;j++)
					{
						b.data[i][j]=this->data[i][j]+a.data[i][j];
					}
				}
				return b;
			}
		}

		Matrix scalarToMatrix(double r){
			Matrix b(this->ROW,this->COL);
				for (int i = 0; i < this->ROW; i++)
				{
					for (int j = 0; j < this->COL;j++)
					{
						b.data[i][j]=this->data[i][j]*r;
					}
				}
			return b;
		}

		int isSquare(){
			if(this->ROW!=this->COL){
				return 0;
			}else{
				return 1;
			}
		}

		void permuteRow(int p,int q){
			double tmp=0;
			
			for (int i = 0; i < this->COL; i++)
			{
				tmp=this->data[p][i];
				this->data[p][i]=this->data[q][i];
				this->data[q][i]=tmp;
			}
		}

		void toIdentity(){
			for (int i = 0; i < this->ROW; ++i)
			{
				for (int j = 0; j < this->COL; ++j)
				{
					if(i==j){
						this->data[i][j]=1;
					}else{
						this->data[i][j]=0;
					}
				}
			}
		}

		Matrix lowerElimination(int a){
				Matrix C(this->ROW,this->COL);
				Matrix I(this->ROW,this->COL);
				I.toIdentity();
				C.copyMatrix(*this);

				Matrix p((this->ROW),2);
				
				for(int i=0;i<(this->ROW);i++){
					p.data[i][0]=i;
					p.data[i][1]=i;
				}

				p.data[(this->ROW)-1][1]=(this->ROW)-1;


				for (int i = 0; i < this->ROW; i++)
				{
					for (int j = i+1; j < this->COL; j++)
					{
						
						double tmp1=-C.data[j][i]/C.data[i][i];//消去所需的係數
						
						for (int k = 0; k < this->COL; k++)
						{
							C.data[j][k]=C.data[j][k]+tmp1*C.data[i][k];
							I.data[j][k]=I.data[j][k]+tmp1*I.data[i][k];
						}
						
						
					}	
				}
				if(a==1){
					return C;
				}else if(a==0){
					return I;
				}else{
					return p;
				}
		}

		Matrix lowerElimination_Partial(int a){
				Matrix C(this->ROW,this->COL);
				Matrix I(this->ROW,this->COL);
				I.toIdentity();
				C.copyMatrix(*this);

				Matrix p((this->ROW),2);
				
				for(int i=0;i<(this->ROW);i++){
					p.data[i][0]=i;
					p.data[i][1]=i;
				}

				p.data[(this->ROW)-1][1]=(this->ROW)-1;


				for (int i = 0; i < this->ROW; i++)
				{

					double max=C.data[i][i];
					int max_j=i;
					// Partial Pivoting
					for (int j = i+1; j < this->ROW; j++)
					{
						if (C.data[j][i]>max)
						{
							max_j=j;
						}
					}
					p.data[i][1]=max_j;
					// p.showMatrixElement();
					C.permuteRow(p.data[i][1],p.data[i][0]);
					I.permuteRow(p.data[i][1],p.data[i][0]);
					// 
					for (int j = i+1; j < this->COL; j++)
					{
						
						double tmp1=-C.data[j][i]/C.data[i][i];//消去所需的係數
						
						for (int k = 0; k < this->COL; k++)
						{
							C.data[j][k]=C.data[j][k]+tmp1*C.data[i][k];
							I.data[j][k]=I.data[j][k]+tmp1*I.data[i][k];
						}
						
						
					}	
				}
				if(a==1){
					return C;
				}else if(a==0){
					return I;
				}else{
					return p;
				}
		}

		Matrix upperElimination(int a){
			Matrix I(this->ROW,this->COL);
			Matrix C(this->ROW,this->COL);
			I.toIdentity();
			C.copyMatrix(*this);
			for(int i=0;i<this->ROW;i++){

				for(int j=i+1;j<this->COL;j++){

					double tmp2=-C.data[this->ROW-1-j][this->COL-1-i]/C.data[this->ROW-1-i][this->COL-1-i];

					for(int k=0;k<this->COL;k++){
						C.data[this->ROW-1-j][this->COL-1-k]=C.data[this->ROW-1-j][this->COL-1-k]+tmp2*C.data[this->ROW-1-i][this->COL-1-k];
						I.data[this->ROW-1-j][this->COL-1-k]=I.data[this->ROW-1-j][this->COL-1-k]+tmp2*I.data[this->ROW-1-i][this->COL-1-k];
					}
				}
			}
			if(a==1){
				return C;
			}else{
				return I;
			}
		}

		Matrix diagToOne(int a){
			Matrix I(this->ROW,this->COL);
			Matrix C(this->ROW,this->COL);
			I.toIdentity();
			C.copyMatrix(*this);
			
			for(int i=0;i<this->ROW;i++){
				for(int j=0;j<this->COL;j++){
					I.data[i][j]=I.data[i][j]/C.data[i][i];
					C.data[i][j]=C.data[i][j]/C.data[i][i];
				}
			}
			if(a==1){
				return C;
			}else {
				return I;
			}
		}

		Matrix inverseMatrix_Partial(){
			if (this->isSquare())
			{
				Matrix C(this->ROW,this->COL);
				Matrix C2(this->ROW,this->COL);
				Matrix I1(this->ROW,this->COL);
				Matrix I2(this->ROW,this->COL);
				Matrix D(this->ROW,this->COL);
				Matrix p(this->ROW,2);
				Matrix P(this->ROW,this->COL);
				P.toIdentity();

				p=this->lowerElimination_Partial(2);
				for (int i = 0; i < this->ROW; ++i)
				{
					P.permuteRow(p.data[i][0],p.data[i][1]);
				}
				
				C2=P.MatrixMul(*this);
				C=C2.lowerElimination_Partial(1);
				if(C.data[(this->ROW)-1][(this->COL)-1]==0){
					printf("Matrix is not invertible");
					return *this;
				}			
				I1=C2.lowerElimination_Partial(0);			
				I2=C.upperElimination(0);			
				C=C.upperElimination(1);			
				D=C.diagToOne(0);
				I1=D.MatrixMul(I2).MatrixMul(I1).MatrixMul(P);
				
				return I1;
			}else{
				printf("the Matrix is not Sqare \n");
				return *this;
			}
		}

		Matrix inverseMatrix(){
			if (this->isSquare())
			{
				Matrix C(this->ROW,this->COL);
				Matrix I1(this->ROW,this->COL);
				Matrix I2(this->ROW,this->COL);
				Matrix D(this->ROW,this->COL);

				C=this->lowerElimination(1);
				if(C.data[(this->ROW)-1][(this->COL)-1]==0){
					printf("Matrix is not invertible");
					return *this;
				}			
				I1=this->lowerElimination(0);			
				I2=C.upperElimination(0);			
				C=C.upperElimination(1);			
				D=C.diagToOne(0);
				I1=D.MatrixMul(I2).MatrixMul(I1);
				
				return I1;
			}else{
				printf("the Matrix is not Sqare \n");
				return *this;
			}
		}

		Matrix getMatrixByCOL(int a){
			if (a<this->COL && a>=0)
			{
				Matrix c(1,this->COL);
				for (int i = 0; i < this->COL; ++i)
				{
					c.data[1][i]=this->data[a][i];
				}
				return c;
			}else{
				Matrix c(0,0);
				printf("Out of the Matrix Size");
				return c;
			}
			
		}

		Matrix MaxElementPosition(){
			double min=data[0][0];
			double max=data[0][0];
			int max_1=0,max_2=0;
			for(int i = 0; i < ROW; i++){
			    for(int j = 0; j < COL; j++){
				    if(data[i][j] > max){
					    max = data[i][j];
					    max_1 = i; max_2 = j;
					    }
				    }
			}
			Matrix c(1,2);
			c.data[0][0]=max_1;
			c.data[0][1]=max_2;
			return c;
		}

		int rank(){
			Matrix C=this->lowerElimination(1);
			int rnk=0;
			for (int i = 0; i < this->ROW; ++i)
			{
				if(C.data[i][this->COL-1]!=0 && !isnan(C.data[i][this->COL-1])){
					rnk+=1;
				}
			}
			return rnk;

		}

		double det(){
			if(this->isSquare()){
				Matrix	 b=this->lowerElimination_Partial(1);
				Matrix P=this->lowerElimination_Partial(2);
				int sign=1;
				for (int i = 0; i < this->ROW; ++i)
				{
					if(P.data[i][i]==0){
						sign=sign*-1;
					}
				}

				double dt=1;
				for(int i=0;i<this->ROW;i++){
					dt=dt*b.data[i][i];
				}
				return dt*sign;
			}else{
				printf("Matrix must be square !");
				return 0;
			}
		}

		Matrix transpose(){
			Matrix M(this->COL,this->ROW);
			
			for (int i = 0; i < this->ROW; i++)
			{
				double tmp=0;
				for (int j = 0; j < this->COL; j++)
				{
	
					M.data[j][i]=this->data[i][j];
					
				}
			}

			return M;
		}

		Matrix operator+(Matrix c){
			return this->addMatrix(c);
		}

		Matrix operator*(Matrix c){
			return this->MatrixMul(c);
		}

};



int main(int argc, char const *argv[])
	{	
		
		int a;
		int b;
		while(1){

			printf("\n1.Computed by Matrix Multiplication \n2.Computed by nested for loop \n\nEnter the number (enter 3 to quit)  :");
			scanf("%d",&a);
			clear_screen();
			switch(a){
				case 1:
				hw1();
				clear_screen();
				break;

				case 2:
				hw2();
				clear_screen();
				break;

				default:
				break;

			}
			if(a==3){
				break;
			}
		}
		
		return 0;
	}	

void hw1(){
	int n1;
	printf("1. Computed by Matrix Multiplication \n");
	printf("Enter size of lambda n : ");
	scanf("%d",&n1);
	Matrix lambda(1,n1);
	Matrix W(n1,n1);
	printf("Enter element of lambda : \n");
	lambda.setMatrixElement();
	printf("Enter element of Covariance Matrix : \n");
	W.setMatrixElement();
	printf("Variance is ： ");
	((lambda*W)*lambda.transpose()).showMatrixElement();
	pressAnyKey();
}

void hw2(){
	int n1;
	printf("1. Computed by Matrix Multiplication \n");
	printf("Enter size of lambda n : ");
	scanf("%d",&n1);
	Matrix lambda(1,n1);
	Matrix W(n1,n1);
	printf("Enter element of lambda : \n");
	lambda.setMatrixElement();
	printf("Enter element of Covariance Matrix : \n");
	W.setMatrixElement();

	double sum=0;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			sum=sum+lambda.data[0][i]*lambda.data[0][j]*W.data[i][j];
		}
	}
	printf("Variance is：%lf ",sum);
	
}



void clear_screen(){
	#ifdef WINDOWS
	    std::system("cls");
	#else
	    // Assume POSIX
	    std::system ("clear");
	#endif
}
void pressAnyKey(){
	#ifdef WINDOWS
	    std::system("pause");
	#else
	    // Assume POSIX
	    std::system ("read");
	#endif
}

