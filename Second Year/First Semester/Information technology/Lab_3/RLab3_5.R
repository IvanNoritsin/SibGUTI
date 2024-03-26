install.packages("data.table")
library(data.table)

url <- "https://d396qusza40orc.cloudfront.net/getdata%2Fdata%2Fss06pid.csv"
temp_file <- tempfile()
download.file(url, temp_file, mode = "wb")
DT <- fread(temp_file)
unlink(temp_file) 

time1 <- 0
time2 <- 0
time3 <- 0
time4 <- 0
time5 <- 0

for(i in 1:100) {
  
  time1 <- time1 + system.time({mean(DT[DT$SEX == 1, ]$pwgtp15); mean(DT[DT$SEX == 2, ]$pwgtp15)})[['elapsed']]
  time2 <- time2 + system.time(mean(DT$pwgtp15, by = DT$SEX))[['elapsed']]
  time3 <- time3 + system.time(tapply(DT$pwgtp15, DT$SEX, mean))[['elapsed']]
  time4 <- time4 + system.time(sapply(split(DT$pwgtp15, DT$SEX), mean))[['elapsed']]
  time5 <- time5 + system.time(DT[, mean(pwgtp15), by = SEX])[['elapsed']]
  
}

cat("способ 1: ", time1, "\n")
cat("способ 2: ", time2, "\n")
cat("способ 3: ", time3, "\n")
cat("способ 4: ", time4, "\n")
cat("способ 5: ", time5, "\n")
