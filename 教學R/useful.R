####usefull packages for data wrangling 
install.packages("dplyr")
install.packages("tidyr")
install.packages("stringr")
install.packages("data.table")
install.packages("ggplot2")
install.packages("ggploty")



for(i in 2:4){
  
  x=lm(iris[,1]~iris[,i])
  
  y[[i-1]]=summary(x)
}


