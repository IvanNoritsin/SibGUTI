install.packages("readxl")
library("readxl")

url <- "https://d396qusza40orc.cloudfront.net/getdata%2Fdata%2FDATA.gov_NGAP.xlsx"
download.file(url, destfile = "DATA.gov_NGAP.xlsx", mode = "wb")
dat <- read_excel("DATA.gov_NGAP.xlsx", range = "R18C7:R23C15")

result <- sum(dat$Zip * dat$Ext, na.rm = TRUE)

print(result)
