import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.cluster import AgglomerativeClustering
from scipy.cluster.hierarchy import dendrogram, linkage
from sklearn.metrics import silhouette_score

# Load Dataset
dataset = "Datasets/mtcars.csv"
df = pd.read_csv(dataset)
print(df.head())
print("Total samples:", len(df))

# Drop
drop_cols = ["model"]
X = df.drop(columns=drop_cols)

# Feature Scaling
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

methods = ["single","complete","average"]
# Agglomerative Clustering 
for x in methods:
    print(f"--------------------------------------------------------------------------------------\n{x.upper()} LINKAGE")
    linked = linkage(X_scaled, method=x)   # Create linkage matrix using Ward's method

    # Plot dendrogram
    plt.figure(figsize=(10, 6))
    dendrogram(linked)
    plt.title(f"Dendrogram {x} linkage")
    plt.xlabel("Data Points")
    plt.ylabel("Distance")
    plt.show()

    k = 3   # Number of clusters 
    agnes = AgglomerativeClustering(n_clusters=k, linkage=x)   # Apply Single linkage clustering
    clusters = agnes.fit_predict(X_scaled)  # Get cluster labels
    df["Cluster"] = clusters  # Add cluster labels to dataset
    print("\nClustered Data Preview:")
    print(df.head())

    # Evaluation
    sil_score = silhouette_score(X_scaled, clusters)    # Silhouette Score
    print("\nEvaluation Metrics:")
    print(f"Silhouette Score: {sil_score:.3f}")

    # Visualization
    pca = PCA(2)
    X_pca = pca.fit_transform(X_scaled)
    plt.scatter(
        X_pca[:,0],
        X_pca[:,1],
        c=clusters
    )
    plt.xlabel("PC1")
    plt.ylabel("PC2")
    plt.title(f"AGNES Clustering Visualization [PCA view] for {x} linkage")
    plt.show()