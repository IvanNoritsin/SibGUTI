RNGkind(kind = "L'Ecuyer-CMRG",
        normal.kind = "Inversion",
        sample.kind = "Rounding"
)
set.seed(123)
x = sample(seq(-1000, 1000), 1000, replace=T)
m = matrix(x,250,40,byrow = T)
x = sample(seq(2000, 4000), 1000, replace=T)
n = matrix(x,40,250,byrow = T)

result = m %*% n

determinant = det(result)
print(determinant)

diagonal_sum = sum(diag(result))
print(diagonal_sum)
