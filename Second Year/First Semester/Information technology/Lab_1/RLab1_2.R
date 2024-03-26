install.packages("ggplot2")
library(ggplot2)

tables_in_ggplot2 = data(package = "ggplot2")$results[, "Item"]
num_tables_in_ggplot2 = length(tables_in_ggplot2)
print(num_tables_in_ggplot2)

data("CO2", package = "datasets")
column_type = class(CO2$conc)
print(column_type)
