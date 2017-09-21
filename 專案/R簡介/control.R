# for 迴圈的各種用法
#(1)
for(i in 1:10){
  print(i^2)
}
#(2)
for(i in seq(1,9,2)){
  print(i)
}
#(3)
for(i in c(1,4,6,8,3)){
  print(i)
}
#(4)
for(i in c('i','am','fat')){
  print(i)
}




#while迴圈
#(1)
a=0
while(a<10){
  print(a)
  a=a+1
}

#(2)
while(a<-scan(n=1)){
  print(a)
}

#(3)
while(1){
  #這是無窮迴圈，請按esc終止
}

#if else elseif
#(1)
a=10
if(a==1){
  print("a is 1")
}else{
  sprintf('a is not 1,a is %d',a)
}

#(2)
if(a>3){
  sprintf("a is bigger than 3")
}else if(a==3){
  sprintf("a is equal to 3")
}else{
  sprintf("a is smaller than 3")  
}