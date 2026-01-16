import pandas as pd
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# Load data
df = pd.read_csv('lucas_gmp_results.csv')
n = df['n'].values
time_ns = df['Time_ns'].values

# Power law function: T(n) = c * n^α
def power_law(n, c, alpha):
    return c * n**alpha

# Fit
params, _ = curve_fit(power_law, n, time_ns, p0=[1, 1.5])
c, alpha = params

print(f"T(n) = {c:.2f} * n^{alpha:.5f}")

# R² calculation
residuals = time_ns - power_law(n, c, alpha)
ss_res = np.sum(residuals**2)
ss_tot = np.sum((time_ns - np.mean(time_ns))**2)
r_squared = 1 - (ss_res / ss_tot)
print(f"R² = {r_squared:.4f}")

# Plot
plt.figure(figsize=(8, 5))
plt.scatter(n, time_ns, alpha=0.6, s=20, label='Measured')
plt.plot(n, power_law(n, c, alpha), 'r-', linewidth=2, 
         label=f'Fit: T(n) = {c:.2f}n^{{{alpha:.2f}}}')
plt.xlabel('n (Fibonacci Index)', fontsize=12)
plt.ylabel('Execution Time (ns)', fontsize=12)
plt.legend()
plt.grid(alpha=0.3)
plt.tight_layout()
plt.savefig('e_lucas_gmp_graph.png', dpi=300)
plt.show()
