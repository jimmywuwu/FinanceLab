#include "stdio.h"
#include <cmath>
#include <stdlib.h>

class TrinomialTree{
	public:
		double a,sigma,step,deltR;
		int n,jmax;
		double** FirstStage;
		double** SecondStage;
		double * ZeroRate;
		double * alpha;
		int zeroRate_isset;

		TrinomialTree(double a,double sigma,double step,int n){
			this->n=n;
			this->step=step;
			this->sigma=sigma;
			this->a=a;
			this->jmax=(int)(0.184/a) +1;
			this->deltR=sigma*sqrt(step*3);
			if (this->n<=this->jmax)
			{

				this->FirstStage=new double*[2*n+1];
				this->SecondStage=new double*[2*n+1];
				for (int i = 0; i < 2*jmax+1; ++i)
				{
					this->FirstStage[i]=new double[n+1];
					this->SecondStage[i]=new double[n+1];
				}

				// case1 初始化
				for(int i=0;i<n+1;i++){
					for(int j=0;j<2*n+1;j++){
						this->FirstStage[j][i]=0;
						this->SecondStage[j][i]=0;
					}	
				}
				// First Stage 賦值 直著填
				for (int i = 0; i < n+1; ++i){
					for(int j=0;j<2*i+1;j++){
						this->FirstStage[j][i]=this->deltR*i-j*deltR;
					}
				}


			}else{
				this->FirstStage=new double*[2*jmax+1];
				this->SecondStage=new double*[2*jmax+1];
				for (int i = 0; i < 2*jmax+1; ++i)
				{
					this->FirstStage[i]=new double[n+1];
					this->SecondStage[i]=new double[n+1];
				}
				// case2 初始化
				for(int i=0;i<n+1;i++){
					for(int j=0;j<2*jmax+1;j++){
						this->FirstStage[j][i]=0;
						this->SecondStage[j][i]=0;
					}	
				}
				// First Stage 賦值 直著填
				for (int i = 0; i < n+1; ++i){
						if(i<jmax){
							for(int j=0;j<2*i+1;j++){
								this->FirstStage[j][i]=this->deltR*i-j*deltR;
							}
						}
					
					else{
						for(int j=0;j<2*jmax+1;j++){
							this->FirstStage[j][i]=this->deltR*jmax-j*deltR;
						}
					}
				}
			}
						

			this->ZeroRate=new double[n+1];
			this->alpha=new double[n+1];

			this->setZeroRate();
			this->solve_alpha_m();
			
		}

		void showMatrix(int number){
			if (number==1)
			{
				if(this->n<=this->jmax){
					for (int i = 0; i < 2*this->n+1; ++i)
					{
						for(int j=0;j<this->n+1;j++){
							printf("%lf ",this->FirstStage[i][j]);
						}
						printf("\n");
					}

				}else{
					for (int i = 0; i < 2*this->jmax+1; ++i)
					{
						for(int j=0;j<this->n+1;j++){
							printf("%lf ",this->FirstStage[i][j]);
						}
						printf("\n");
					}
				}
				
			}else{
				if(this->n<=this->jmax){
					for (int i = 0; i < 2*this->n+1; ++i)
					{
						for(int j=0;j<this->n+1;j++){
							printf("%lf ",this->SecondStage[i][j]);
						}
						printf("\n");
					}

				}else{
					for (int i = 0; i < 2*this->jmax+1; ++i)
					{
						for(int j=0;j<this->n+1;j++){
							printf("%lf ",this->SecondStage[i][j]);
						}
						printf("\n");
					}
				}
				

			}

		}

		double getNodeValue_FirstStage(int i,int j){
			if(abs(j)>i||(abs(j)>jmax && i>jmax)){
				printf("Out of Bound!! return 0");
				return 0;
			}else{
				if(i<=jmax){
					return this->FirstStage[i-j][i];
				}else{
					return this->FirstStage[jmax-j][i];
				}
			}
		}

		double getNodeValue_SecondStage(int i,int j){
			if(abs(j)>i || (abs(j)>jmax && i>jmax)){
				printf("Out of Bound!! return 1\n");
				return 0;
			}else{
				if(i<=jmax){
					return this->SecondStage[i-j][i];
				}else{
					return this->SecondStage[jmax-j][i];
				}	
			}
		}

		void setSecondStage(int i,int j,double value){
			if(abs(j)>i || (abs(j)>jmax && i>jmax)){
				printf("Out of Bound!! return 2");
			}else{
				if(i<=jmax){
					this->SecondStage[i-j][i]=value;
				}else{
					this->SecondStage[jmax-j][i]=value;
				}
			}
		}

		double UpProb(int i ,int j){
			if(abs(j)<jmax){
				return 1.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)-this->a*j*step);
			}else if(j==jmax){
				return 7.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)-3*this->a*j*step);
				// return 1.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)+this->a*j*step);
			}else if(j==(-jmax)){
				return 1.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)+this->a*j*step);
				// return 7.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)-3*this->a*j*step);
			}else{
				printf("out of bound !!\n");
				return -1;
			}
		}

		double DownProb(int i,int j){
			if(abs(j)<jmax){
				return 1.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)+this->a*j*step);
			}else if(j==jmax){
				// return 7.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)-3*this->a*j*step);
				return 1.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)-this->a*j*step);
			}else if(j==(-jmax)){
				// return 1.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)+this->a*j*step);
				return 7.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)+3*this->a*j*step);
			}else{
				printf("out of bound !!\n");
				return -1;
			}

		}

		double MProb(int i,int j){
			if(abs(j)<jmax){
				return 2.0/3-pow(this->a,2)*pow(j,2)*pow(step,2);
			}else if(j==jmax){
				// return 7.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)-3*this->a*j*step);
				return -1.0/3-pow(this->a,2)*pow(j,2)*pow(step,2)+2*this->a*j*this->step;
			}else if(j==(-jmax)){
				// return 1.0/6+0.5*(pow(this->a,2)*pow(j,2)*pow(step,2)+this->a*j*step);
				return -1.0/3-pow(this->a,2)*pow(j,2)*pow(step,2)-2*this->a*j*this->step;
			}else{
				printf("out of bound !!\n");
				return -1;
			}
		}

		double correctInterestRate(int i,int j){
			if(i>n||j>jmax){
				printf("Out of Bound!! return 0");
				return 0;
			}else{
				return this->alpha[i]+this->getNodeValue_FirstStage(i,j);
			}	
		}

	private:
		void setZeroRate(){
			zeroRate_isset=1;
			for (int i = 0; i < n+1; ++i)
			{
				printf("please enter %lf year -zero rate : \n",this->step*i);
				scanf("%lf",&this->ZeroRate[i]);
			}
		}


	

		void solve_alpha_m(){
			if(zeroRate_isset){
				this->alpha[0]=this->ZeroRate[0];
				this->SecondStage[0][0]=1;
				this->SecondStage[0][1]=this->UpProb(0,0)*exp(-this->alpha[0]);
				this->SecondStage[1][1]=this->MProb(0,0)*exp(-this->alpha[0]);
				this->SecondStage[2][1]=this->DownProb(0,0)*exp(-this->alpha[0]);
				this->alpha[1]=log((this->SecondStage[0][1]*exp(-this->deltR)+this->SecondStage[1][1]+this->SecondStage[2][1]*exp(this->deltR))/exp(this->ZeroRate[1]*(-2)*step))/step;
				// double P_mplus1=exp(-this->alpha[0]*step);
				double a1,a2,a3,a4,a5,b1,b2,b3,b4,b5,b6,b7;
				for(int i=2;i<n+1;i++){
					// update Q
					if(i<=jmax){
					
						a1=this->getNodeValue_SecondStage(i-1,i-1)*this->UpProb(i-1,i-1)*exp(-(alpha[i-1]+(i-1)*deltR)*step);
						this->setSecondStage(i,i,a1);
						a2=this->getNodeValue_SecondStage(i-1,i-1)*this->MProb(i-1,i-1)*exp(-(alpha[i-1]+(i-1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,i-2)*this->UpProb(i-1,i-2)*exp(-(alpha[i-1]+(i-2)*deltR)*step);
						this->setSecondStage(i,i-1,a2);

						for(int j=-(i-2);j<=(i-2);j++){
							a3=this->getNodeValue_SecondStage(i-1,j)*this->MProb(i-1,j)*exp(-(alpha[i-1]+(j)*deltR)*step)+this->getNodeValue_SecondStage(i-1,j-1)*this->UpProb(i-1,j-1)*exp(-(alpha[i-1]+(j-1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,j+1)*this->DownProb(i-1,j+1)*exp(-(alpha[i-1]+(j+1)*deltR)*step);
							this->setSecondStage(i,j,a3);
						}

						a4=this->getNodeValue_SecondStage(i-1,-i+1)*this->MProb(i-1,-i+1)*exp(-(alpha[i-1]+(-i+1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,-i+2)*this->UpProb(i-1,-i+2)*exp(-(alpha[i-1]+(-i+2)*deltR)*step);
						this->setSecondStage(i,-i+1,a4);

						a5=this->getNodeValue_SecondStage(i-1,-i+1)*this->DownProb(i-1,-i+1)*exp(-(alpha[i-1]+(-i+1)*deltR)*step);
						this->setSecondStage(i,-i,a5);
						
					}else{
	
						b1=this->getNodeValue_SecondStage(i-1,jmax)*this->UpProb(i-1,jmax)*exp(-(alpha[i-1]+(jmax)*deltR)*step)+this->getNodeValue_SecondStage(i-1,jmax-1)*this->UpProb(i-1,jmax-1)*exp(-(alpha[i-1]+(jmax-1)*deltR)*step);
						this->setSecondStage(i,jmax,b1);

						b2=this->getNodeValue_SecondStage(i-1,jmax)*this->MProb(i-1,jmax)*exp(-(alpha[i-1]+(jmax)*deltR)*step)+this->getNodeValue_SecondStage(i-1,jmax-1)*this->MProb(i-1,jmax-1)*exp(-(alpha[i-1]+(jmax-1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,jmax-2)*this->UpProb(i-1,jmax-2)*exp(-(alpha[i-1]+(jmax-2)*deltR)*step);
						this->setSecondStage(i,jmax-1,b2);

						b3=this->getNodeValue_SecondStage(i-1,jmax)*this->DownProb(i-1,jmax)*exp(-(alpha[i-1]+(jmax)*deltR)*step)+this->getNodeValue_SecondStage(i-1,jmax-1)*this->DownProb(i-1,jmax-1)*exp(-(alpha[i-1]+(jmax-1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,jmax-2)*this->MProb(i-1,jmax-2)*exp(-(alpha[i-1]+(jmax-2)*deltR)*step)+this->getNodeValue_SecondStage(i-1,jmax-3)*this->UpProb(i-1,jmax-3)*exp(-(alpha[i-1]+(jmax-3)*deltR)*step);
						this->setSecondStage(i,jmax-2,b3);

						b4=0;
						for(int j=-(jmax-3);j<=(jmax-3);j++){
							// b4=this->getNodeValue_SecondStage(i-1,j)*this->MProb(i-1,j)*exp(-(alpha[i-1]+(j)*deltR)*step)+this->getNodeValue_SecondStage(i-1,j-1)*this->UpProb(i-1,j-1)*exp(-(alpha[i-1]+(j-1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,j+1)*this->DownProb(i-1,j+1)*exp(-(alpha[i-1]+(j+1)*deltR)*step);
							this->setSecondStage(i,j,b4);
						}

						b5=this->getNodeValue_SecondStage(i-1,-jmax)*this->UpProb(i-1,-jmax)*exp(-(alpha[i-1]+(-jmax)*deltR)*step)+this->getNodeValue_SecondStage(i-1,-jmax+1)*this->UpProb(i-1,-jmax+1)*exp(-(alpha[i-1]+(-jmax+1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,-jmax+2)*this->MProb(i-1,-jmax+2)*exp(-(alpha[i-1]+(-jmax+2)*deltR)*step)+this->getNodeValue_SecondStage(i-1,-jmax+3)*this->DownProb(i-1,-jmax+3)*exp(-(alpha[i-1]+(-jmax+3)*deltR)*step);
						this->setSecondStage(i,-jmax+2,b5);

						b6=this->getNodeValue_SecondStage(i-1,-jmax)*this->MProb(i-1,-jmax)*exp(-(alpha[i-1]+(-jmax)*deltR)*step)+this->getNodeValue_SecondStage(i-1,-jmax+1)*this->MProb(i-1,-jmax+1)*exp(-(alpha[i-1]+(-jmax+1)*deltR)*step)+this->getNodeValue_SecondStage(i-1,-jmax+2)*this->DownProb(i-1,-jmax+2)*exp(-(alpha[i-1]+(-jmax+2)*deltR)*step);
						this->setSecondStage(i,-jmax+1,b6);

						b7=this->getNodeValue_SecondStage(i-1,-jmax)*this->DownProb(i-1,-jmax)*exp(-(alpha[i-1]+(-jmax)*deltR)*step)+this->getNodeValue_SecondStage(i-1,-jmax+1)*this->DownProb(i-1,-jmax+1)*exp(-(alpha[i-1]+(-jmax+1)*deltR)*step);
						this->setSecondStage(i,-jmax,b7);
						printf("%d\n",this->jmax);
						
					}


					// update alpha
					double sum=0;
					if(i>=jmax){
						for(int j=-jmax;j<=jmax;j++){	
							sum=sum+this->getNodeValue_SecondStage(i,j)*exp(-j*this->deltR*this->step);
						}
					}else{
						for(int j=-i;j<=i;j++){	
							sum=sum+this->getNodeValue_SecondStage(i,j)*exp(-j*this->deltR*this->step);
						}
					}
		
					this->alpha[i]=(log(sum)-log(exp(this->ZeroRate[i]*(-i-1)*step)))/step;
					// printf("%lf",this->alpha[i]);		
				}
			}
			
		}

	
		
};


double OptionPricing(double X,TrinomialTree t){
	double *Price_T;
	double *tmp;
	if (t.jmax>t.n)
	{
		printf("case 1 ");
		Price_T=new double[(2*t.n)+1];	
		for (int i = 0; i <(2*t.n)+1 ; ++i)
		{
			Price_T[i]=fmax(100*(t.correctInterestRate(t.n,i-t.n)-X),0);
		}

		for (int i = (t.n-1); i >=0; i--)
		{
			for(int j=0;j<2*i+1;j++){
				Price_T[j]=exp(-1*t.correctInterestRate(i,j-i)*t.step)*(Price_T[j]*t.DownProb(i,j-i)+Price_T[j+1]*t.MProb(i,j-i)+Price_T[j+2]*t.UpProb(i,j-i));
			}	
		}
		return Price_T[0];

	}else{
		printf("case 2");
		Price_T=new double[2*t.jmax+1];	
		tmp=new double[2*t.jmax+1];	
		for (int i = 0; i <2*t.jmax+1 ; ++i)
		{
			Price_T[i]=fmax(100*(t.correctInterestRate(t.n,i-t.jmax)-X),0);
		}

		// i>jmax後 backward Induction
		double tmp1,tmp2;
		for (int i = t.n-1; i>=t.jmax ; i--)
		{
			tmp1=Price_T[0];
			tmp2=Price_T[1];
			Price_T[0]=exp(-1*t.correctInterestRate(i,-t.jmax)*t.step)*(Price_T[0]*t.DownProb(i,-t.jmax)+tmp1*t.MProb(i,-t.jmax)+tmp2*t.UpProb(i,-t.jmax));
			for(int j=1;j<2*t.jmax-1;j++){
				Price_T[j]=exp(-1*t.correctInterestRate(i,j-t.jmax)*t.step)*(tmp1*t.DownProb(i,j-t.jmax)+tmp2*t.MProb(i,j-t.jmax)+Price_T[j+1]*t.UpProb(i,j-t.jmax));
				tmp1=tmp2;
				tmp2=Price_T[j+1];
			}
			Price_T[2*t.jmax-1]=exp(-1*t.correctInterestRate(i,t.jmax-1)*t.step)*(tmp1*t.DownProb(i,t.jmax-1)+tmp2*t.MProb(i,t.jmax-1)+Price_T[2*t.jmax]*t.UpProb(i,t.jmax-1));
			Price_T[2*t.jmax]=exp(-1*t.correctInterestRate(i,t.jmax)*t.step)*(Price_T[0]*t.DownProb(i,t.jmax)+tmp1*t.MProb(i,t.jmax)+tmp2*t.UpProb(i,t.jmax));
		}
		// i<jmax前 backward Induction
		for (int i = t.jmax-1; i>=0 ; i--)
		{
			for(int j=0;j<2*i+1;j++){
				Price_T[j]=exp(-1*t.correctInterestRate(i,j-i)*t.step)*(Price_T[j]*t.DownProb(i,j-i)+Price_T[j+1]*t.MProb(i,j-i)+Price_T[j+2]*t.UpProb(i,j-i));
			}	
		}

		return Price_T[0];
	}
	
}
