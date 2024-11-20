# Efficient Fibonacci N-th Term Calculation

This code and formula (below) provide an optimized method for directly computing the N-th Fibonacci term, eliminating unnecessary calculations and improving efficiency.

### Main Formula
To compute the Fibonacci number directly, use the following formula. Copy it into a LaTeX editor to render the math beautifully:

--------
\documentclass{article}
\usepackage{amsmath}

\begin{document}

\[
F_n = \sum_{k=1}^{s} \frac{(n-k-1)!}{(k-1)!(n-2k)!}, \quad n > 1
\]
where 
\[
s = 
\begin{cases} 
\frac{n-1}{2} & \text{if } \; n \; \text{ is odd}, \\
\frac{n}{2} & \text{if } \;  n \; \text{ is even}.
\end{cases}
\]

\end{document}
--------

### Note on Fibonacci Term Calculation

For Fibonacci terms **above the 45th term**:

- The result of the summation (`sum`) exceeds the maximum value that can be stored in a 32-bit `int` (2,147,483,647). 

#### How to Handle Larger Terms:
1. **Change `sum` to `double`**:
   - This allows the program to accommodate the exponential growth of Fibonacci numbers beyond the 45th term.
   - However, note that using `double` may introduce small precision errors for very large terms.

2. **Use `long long`**:
   - For exact integer representation, switch to `long long`. This will handle Fibonacci terms up to the 93rd term, as it can store values up to 9,223,372,036,854,775,807 (64-bit integer maximum).

3. **Beyond the 93rd Term**:
   - If Fibonacci terms beyond the 93rd are required, consider using arbitrary-precision libraries like **GMP** or **Boost.Multiprecision** for exact results.

### Additional Resources

For a detailed explanation of the formula and its derivation, visit my blog:

[Efficient Fibonacci Computation: Instantly Calculate the Exact N-th Number Directly](https://medium.com/@aadeshtikhe24/efficient-fibonacci-computation-instantly-calculate-the-exact-nth-number-directly-no-recursion-ed13bb284c71)
