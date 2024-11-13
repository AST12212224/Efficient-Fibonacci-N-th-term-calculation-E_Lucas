# Efficient-Fibonacci-N-th-term-calculation
This code and formula (in Readme) help eliminate unnecessary calculations, providing an efficient method for directly computing the N'th Fibonacci term.

here is the main formula, put it in LaTex editor and run.
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
