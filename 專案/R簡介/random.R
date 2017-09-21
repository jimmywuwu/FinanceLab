### random variable生成

a=rnorm(100) #生成100個N(0,1) Random Variable
mean(a)
var(a)

b=rexp(100,1/2)
mean(b)
var(b)

### quantile 計算

qnorm(0.975)


### pdf

dnorm(0)

### cdf

pnorm(0)


### Monte Carlo Simulation 例子
### Normal Random Variable 的CDF 無法用一個close form表達，但是我們可以用Monte Carlo Simulation 
### 求得Normal CDF在某一點的值

#1.用N(0)=0.5確認

a=rnorm(10000) 
mean(a<0)

#2.用N(1.96)=0.975 確認

mean(a<1.96)

#自訂函數 myPNorm 計算N(0,1) CDF 預設simulation1000次

myPNorm=function (x,simul=1000){
  a=rnorm(simul)
  mean(a<x)
}



A = c(1:10)
