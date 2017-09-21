// 值要算之前要初始化！！！！！！
#include "math.h"
#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include <time.h>
#include <vector>
#include <cstdlib>

using namespace std;
double EquityValue(double r,double T,double V,double K,double vol,double alpha);
double DebtValue(double r,double T,double V,double K,double vol,double alpha,double tau,double coupon,double Amount);
double BankruptcyCost(double r,double T,double V,double K,double vol,double alpha);
double TaxBenefit(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau);
double FirmValue(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau);
double Standard_Normal_Distribution(double d){
   int flag=0;   //Flag =1 if d<0
   if(d<0)
     {
      flag=1;
      d=fabs(d);
     }
   double rr=0.2316419;
   double a1=0.31938153;
   double a2=-0.356563782;
   double a3=1.781477937;
   double a4=-1.821255978;
   double a5=1.330274429;
   double k=1/(1+d*rr);
   double PI=3.14159265359;
   double value=1-exp(d*d/(-2))*(a1*k+a2*pow(k,2)+a3*pow(k,3)+a4*pow(k,4)
                  +a5*pow(k,5))/sqrt(2*PI);
   if(flag) return 1-value;
    else return value;
}
int comp_func(const void *a, const void *b) ;

class Chromosome{
public:
	int n;
	std::vector<int> gene;
	double left;
	double right;

	// 使用預設建構子，因為要在Population Class建立此物件的陣列
	void setParameter(int n,double left,double right){
		
		this->n=n;
		this->gene.resize(n);
		for (int i = 0; i < this->n; i++)
		{
			this->gene[i]=rand() & 1;
		}
		this->left=left;
		this->right=right;
	}

	double decoding(){
		int ans=0;
		for (int i = 0; i < this->n; ++i)
		{
			ans=ans+this->gene[i]*pow(2,i);
		}
		return this->left+ans*(this->right-this->left)/(pow(2,this->n)-1);
	}

	double fitness(){
		double a=(this->decoding())*100;
		double K=a+0.05*a*(1-0.1);
		return -FirmValue(0.1,1.0,100.0,K,0.3,0.1,0.05,a,0.1);
	}

	void showGene(){
		for (int i = 0; i < this->n; ++i)
		{
			printf("%d",this->gene[i]);
		}
		printf("\n");
	}

	void mutation(){
		int point_mutation=rand()%this->n;
		if(this->gene[point_mutation]==1){
			this->gene[point_mutation]=0;
		}else{
			this->gene[point_mutation]=1;
		}
	}

	Chromosome crossover(Chromosome p){
		Chromosome child;
		child.setParameter(this->n,this->left,this->right);
		int crossover_point=rand()%this->n;
		
		int tmp=0;
		for (int i = 0; i < crossover_point; ++i)
		{
			child.gene[i]=this->gene[i];
		}
		for (int i = crossover_point; i < this->n; ++i)
		{
			child.gene[i]=p.gene[i];
		}
		
		return child;
	}

	void reproduct(Chromosome p){
		for (int i = 0; i < this->n; ++i)
		{
			this->gene[i]=p.gene[i];
		}
		
	}

};

// 此class 用來排序並取得order
class X_arr {
	public:
		int index;
		double value;
};

class Population{
public:
	int size;
	int BestN;
	Chromosome *chromosomes;
	double left;
	double right;
	double GeneLength;
	int MutationNumber;
	Population(int size,int GeneLength,double left,double right,int BestN,int MutationNumber){
		this->size=size;
		this->left=left;
		this->right=right;
		this->GeneLength=GeneLength;
		this->chromosomes=new Chromosome[size];
		this->MutationNumber=MutationNumber;
		for (int i = 0; i < size; ++i)
		{
			this->chromosomes[i].setParameter(GeneLength,left,right);
		}
		this->BestN=BestN;
	}

	~Population(){

	}

	X_arr* getFitnessOrder(){
		double *gene_fitness=new double[this->size];
		
		for (int i = 0; i < size; ++i)
		{
			gene_fitness[i]=this->chromosomes[i].fitness();	
		}

		X_arr *X=new X_arr[size];
		for (int i=0; i<size; i++) {
			X[i].index = i;
			X[i].value = gene_fitness[i];
		}
		qsort(X, size, sizeof(X_arr), comp_func);

		return X;

	}

	Population getBestN(){
		Population p=Population(this->size,this->GeneLength,this->left,this->right,this->BestN,this->MutationNumber);
		X_arr* X=this->getFitnessOrder();
		for (int i = 0; i <= this->BestN; ++i)
		{
			p.chromosomes[i].reproduct(this->chromosomes[X[i].index]);
		}
		return p;
	}

	void crossoverToSize(){
		for (int i = this->BestN; i < size; ++i)
		{	
			int gene1=rand()%this->BestN;
			int gene2=rand()%this->BestN;
			this->chromosomes[i]=this->chromosomes[gene1].crossover(this->chromosomes[gene2]);
		}
	}

	void mutationGene(){
		for (int i = 0; i < this->MutationNumber; ++i)
		{
			int j=rand()%this->size;
			this->chromosomes[j].mutation();
		}
	}

	void showChromosomes(){
		for (int i = 0; i < size; ++i)
		{
			this->chromosomes[i].showGene();
		}
		printf("\n");
	}



};


int main(int argc, char const *argv[]){
	srand(time(0));
	

	Population p=Population(20,20,0,5,5,5);
	Population q=Population(20,20,0,5,5,5);
	int i=0;
	while(i<100){
		q=p.getBestN();
		q.crossoverToSize();
		q.mutationGene();
		printf("%d th result : \n",i);
		p.showChromosomes();
		q.showChromosomes();
		p=q;

		i++;
	}

	printf("the answer is %lf ",p.getBestN().chromosomes[0].decoding());

	return 0;

		
}	



int comp_func(const void *a, const void *b) {
			X_arr x, y;
			x = *(X_arr *)(a);
			y = *(X_arr *)(b);
			if (x.value > y.value) return 1;
			else if (x.value == y.value) return 0;
			else return -1;
}

double FirmValue(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau){
	return EquityValue(r,T,V,K,vol,alpha)+DebtValue(r,T,V,K,vol,alpha,tau,coupon,Amount);
}

double EquityValue(double r,double T,double V,double K,double vol,double alpha){
	  double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
    return V*Standard_Normal_Distribution(d1)-K*exp(-r*T)*Standard_Normal_Distribution(d2);
}

double DebtValue(double r,double T,double V,double K,double vol,double alpha,double tau,double coupon,double Amount){
	double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
    return (1-alpha)*V*Standard_Normal_Distribution(-d1)+(Amount+coupon*Amount)*exp(-r*T)*Standard_Normal_Distribution(d2);
}


double BankruptcyCost(double r,double T,double V,double K,double vol,double alpha){
	  double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
	return alpha*V*Standard_Normal_Distribution(-d1);
}

double TaxBenefit(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau){
	  double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
	return exp(-r*T)*(coupon*Amount*T*tau)*Standard_Normal_Distribution(d2);
}