import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.metrics import silhouette_score


# STEP 1: Load Dataset
dataset = "Dataset/iris.csv"
df = pd.read_csv(dataset)
print(df.head())
print("Total samples:", len(df))


# STEP 2: Handle Missing Values
num_cols = df.select_dtypes(include=[np.number]).columns
for col in num_cols:
    df[col] = df[col].fillna(df[col].mean())
cat_cols = df.select_dtypes(include=["object", "string"]).columns
for col in cat_cols:
    df[col] = df[col].fillna(df[col].mode()[0])


# STEP 3: Encode Categorical Columns
for col in cat_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])


# STEP 4: Separate Features
X = df.drop(columns=["Species"]).values


# STEP 5: Feature Scaling
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# STEP 6: K-Medoids (PAM)
def euclidean(a, b):
    return np.linalg.norm(a - b)

def k_medoids(X, k, max_iter=100):
    n = len(X)
    medoid_indices = np.random.choice(n, k, replace=False)
    medoids = X[medoid_indices]

    for _ in range(max_iter):
        clusters = [[] for _ in range(k)]

        # Assignment step
        for i, x in enumerate(X):
            distances = [euclidean(x, m) for m in medoids]
            clusters[np.argmin(distances)].append(i)

        new_medoids = []
        for cluster in clusters:
            cluster_points = X[cluster]
            costs = [
                sum(euclidean(p, q) for q in cluster_points)
                for p in cluster_points
            ]
            new_medoids.append(cluster_points[np.argmin(costs)])

        new_medoids = np.array(new_medoids)
        if np.array_equal(medoids, new_medoids):
            break
        medoids = new_medoids

    labels = np.zeros(n, dtype=int)
    for idx, cluster in enumerate(clusters):
        for point in cluster:
            labels[point] = idx

    return labels


# STEP 7: Apply K-Medoids
k = 3
clusters = k_medoids(X_scaled, k)
df["Cluster"] = clusters

print("\nClustered Data Preview:")
print(df.head())


# STEP 8: Evaluation
sil_score = silhouette_score(X_scaled, clusters)
print("\nSilhouette Score:", sil_score)


# STEP 9: Visualization
plt.figure()
plt.scatter(X_scaled[:, 0], X_scaled[:, 1], c=clusters)
plt.xlabel("Feature 1 (scaled)")
plt.ylabel("Feature 2 (scaled)")
plt.title("K-Medoids (PAM) Clustering")
plt.show()
