library(nycflights13)
library(dplyr)

flights_cleaned = flights %>% filter(!is.na(arr_delay))

result = flights_cleaned %>%
  group_by(month) %>%
  summarize(median_arr_delay = median(arr_delay, na.rm = TRUE),
            count_delayed_flights =a n()) %>% 
  arrange(desc(count_delayed_flights))

max_median_month = result %>%
  mutate(abs_median_arr_delay = abs(median_arr_delay)) %>%
  filter(abs_median_arr_delay == max(abs_median_arr_delay)) %>%
  select(month)

print(max_median_month$month)
