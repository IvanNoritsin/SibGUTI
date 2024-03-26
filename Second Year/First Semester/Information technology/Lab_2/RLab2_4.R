library(nycflights13)
library(dplyr)

# столбцы faa (код аэропорта), name (название аэропорта) и alt (высота аэропорта)
location = airports %>% select(faa, name, alt) %>%
  rename(dest = faa)

flights_grouped = flights %>%
  group_by(dest)

flights_cleaned = flights_grouped %>%
  filter(!is.na(air_time))

#среднее время полета (mean_air_time) 
#общее количество рейсов (count_flights)
flights_summary = flights_cleaned %>%
  summarize(mean_air_time = mean(air_time), count_flights = n())

flights_sorted = flights_summary %>%
  arrange(desc(mean_air_time))

result = left_join(flights_sorted, location, by = "dest")

print(result$name[1])
