##產生 exponential random variable ，以樣本平均檢查大數法則的性質

rexp(30)
x=array();
for(i in 1:10000){
  x[i]=mean(rexp(30)) 
}

hist(x,xlim=c(0.5,1.5))

##產生 normal random variable ，檢查信賴區間的性質

ci=data.frame()
upper=array()
lower=array()
(1>2)*(1>2)

for(i in 1:10000){
  upper[i]=mean(rnorm(30))+1/sqrt(30)*1.96;
  lower[i]=mean(rnorm(30))-1/sqrt(30)*1.96;
  contain[i]=(upper[i]>0)*(0>lower[i]);
}

ci=data.frame(upper,lower,contain)

