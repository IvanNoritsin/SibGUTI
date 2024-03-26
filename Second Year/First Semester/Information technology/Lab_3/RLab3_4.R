install.packages("XML")
library(XML)

url <- "https://d396qusza40orc.cloudfront.net/getdata%2Fdata%2Frestaurants.xml"
temp_file <- tempfile()

download.file(url, temp_file, mode = "wb")

xml_data <- xmlParse(file = temp_file)

zip_codes <- xpathSApply(xml_data, "//zipcode", xmlValue)

count_21231 <- sum(zip_codes == "21231")

print(count_21231)

unlink(temp_file)
