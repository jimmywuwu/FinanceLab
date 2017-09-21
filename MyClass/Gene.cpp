// 值要算之前要初始化！！！！！！

#include "math.h"
#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include <time.h>
#include <vector>
#include <cstdlib>

using namespace std;


int comp_func(const void *a, const void *b) ;

class Chromosome{
public:

	int n;
	std::vector<int> gene;
	double left;
	double right;

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
		double a=this->decoding();
		return a*a-a+0.25;
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
	
	Population p=Population(10,10,0,5,5,5);
	Population q=Population(10,10,0,5,5,5);
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
	printf("the answer is %lf",p.getBestN().chromosomes[0].decoding());

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



