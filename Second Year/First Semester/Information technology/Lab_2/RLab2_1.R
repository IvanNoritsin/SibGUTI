install.packages("nycflights13")
library(nycflights13)

data("flights")

install.packages("dplyr")
library(dplyr)
flights_december = flights %>% filter(month == 12)

flights_sorted = flights_december %>% arrange(desc(dep_delay))

dep_delay10 = flights_sorted[10, "dep_delay"]
print(dep_delay10)
