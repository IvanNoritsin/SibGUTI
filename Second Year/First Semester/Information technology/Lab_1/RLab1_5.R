RNGkind(kind = "L'Ecuyer-CMRG",
        normal.kind = "Inversion",
        sample.kind = "Rounding"
)
set.seed(123)

myFun = function(n = 5000) {
  a = do.call(paste0, replicate(5, sample(LETTERS, n, TRUE), FALSE))
  paste0(a, sprintf("%04d", sample(9999, n, TRUE)), sample(LETTERS, n, TRUE))
}

x = myFun(3000)

count = sum(grepl("AZ", x))
print(count)
