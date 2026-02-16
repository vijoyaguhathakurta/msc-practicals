import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Create synthetic travel data
np.random.seed(42)

n_solutions = 50
cost = np.random.randint(100, 1000, n_solutions)
time = np.random.randint(1, 20, n_solutions)

df = pd.DataFrame({
    "Cost": cost,
    "Time": time
})

print(df.head())


def dominates(p, q):
    return (p[0] <= q[0] and p[1] <= q[1]) and (p[0] < q[0] or p[1] < q[1])

def non_dominated_sort(data):
    pareto_front = []

    for i in range(len(data)):
        dominated = False
        for j in range(len(data)):
            if i != j and dominates(data[j], data[i]):
                dominated = True
                break
        if not dominated:
            pareto_front.append(i)

    return pareto_front




points = df[["Cost", "Time"]].values
pareto_indices = non_dominated_sort(points)
pareto_df = df.iloc[pareto_indices]

print("\nPareto Optimal Solutions:")
print(pareto_df)




plt.figure(figsize=(8,6))

# All solutions
plt.scatter(df["Cost"], df["Time"], label="All Solutions", alpha=0.6)

# Pareto optimal front
plt.scatter(
    pareto_df["Cost"],
    pareto_df["Time"],
    color="red",
    label="Pareto Front",
    s=80
)

plt.xlabel("Cost")
plt.ylabel("Time")
plt.title("NSGA-II Pareto Optimal Front (Cost vs Time)")
plt.legend()
plt.grid(True)
plt.show()
