import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score

# Load Dataset
dataset = "Datasets/HousingData.csv"
df = pd.read_csv(dataset)
print("Dataset Loaded:\n ",df.head())
print("Total samples:", len(df))

# Handle Missing Values 
num_cols = df.select_dtypes(include=[np.number]).columns            # Numerical columns
for col in num_cols:
    df[col] = df[col].fillna(df[col].mean())
df.isna().sum()

# Feature Scaling
scaler = StandardScaler()
X_scaled = scaler.fit_transform(df)

# STEP 1: Elbow Method
wcss = []
for k in range(1, 11):
    model = KMeans(n_clusters=k, random_state=1)
    model.fit(X_scaled)
    wcss.append(model.inertia_)
plt.figure()
plt.plot(range(1, 11), wcss, marker='o')
plt.xlabel("Number of Clusters (K)")
plt.ylabel("WCSS")
plt.title("Elbow Method")
plt.show()

# Automatic Elbow Detection
wcss_diff = np.diff(wcss)   # Compute differences between consecutive WCSS values
print("\nWCSS Differences:")
for i, diff in enumerate(wcss_diff, start=1):
    print(f"k={i}, WCSS drop={abs(diff):.3f}")
optimal_k = np.argmax(np.abs(wcss_diff)) + 2    # Find elbow point (maximum drop)
print("\nOptimal number of clusters (Elbow Method):", optimal_k)

# STEP 2: Apply K-Means
model = KMeans(n_clusters=optimal_k, random_state=1)
clusters = model.fit_predict(X_scaled)
df["Cluster"] = clusters
print("\nClustered Data Preview:")
print(df.head())

# STEP 3: Evaluation
sil_score = silhouette_score(X_scaled, clusters)
print(f"\nSilhouette Score: {sil_score:.3f}")

# STEP 4: Visualization
from sklearn.decomposition import PCA
pca = PCA(2)
X_pca = pca.fit_transform(X_scaled)
plt.scatter(
    X_pca[:,0],
    X_pca[:,1],
    c=clusters
)
plt.xlabel("PC1")
plt.ylabel("PC2")
plt.title("K-Means with Optimal K (PCA View)")
plt.show()