download.file("https://d396qusza40orc.cloudfront.net/getdata%2Fdata%2Fss06hid.csv", "ss06hid.csv")

housing_data <- read.csv("ss06hid.csv")

idaho_houses <- subset(housing_data, ST == 16) 

expensive_idaho_houses <- subset(idaho_houses, VAL >= 24)

count_expensive_idaho_houses <- nrow(expensive_idaho_houses)

print(count_expensive_idaho_houses)
