library(nycflights13)
library(dplyr)

flights_cleaned = flights %>% filter(!is.na(arr_delay))

result = flights_cleaned %>%
  group_by(origin, month) %>%
  summarize(count_departures = n()) %>%
  arrange(desc(count_departures))

max_month_JFK = result %>%
  filter(origin == "JFK") %>%
  top_n(1, count_departures)

print(max_month_JFK$month)
