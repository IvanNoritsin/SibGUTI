factorial = function(n) {
  if (n == 0) {
    return(1)
  } else {
    return(n * factorial(n-1))
  }
}

sum_factorial = 0
for (i in 1:10) {
  sum_factorial = sum_factorial + factorial(i)
}

print(sum_factorial)
