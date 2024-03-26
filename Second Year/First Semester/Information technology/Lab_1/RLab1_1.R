RNGkind(kind = "L'Ecuyer-CMRG",
        normal.kind = "Inversion",
        sample.kind = "Rejection"
)

set.seed(123)
x = rnorm(10000, mean = 6, sd = 2)

sumx = sum(x > 3)
meanx = mean(x)

print(sumx)
print(meanx)
