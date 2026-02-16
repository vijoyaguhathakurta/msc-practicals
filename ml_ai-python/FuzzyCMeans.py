import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
import skfuzzy as fuzz
from sklearn.metrics import silhouette_score

# Load Dataset
dataset = "Datasets/Mall_Customers.csv"
df = pd.read_csv(dataset)
print(df.head())
print("Total samples:", len(df))

# Handle Missing Values 
num_cols = df.select_dtypes(include=[np.number]).columns            # Numerical columns
for col in num_cols:
    df[col] = df[col].fillna(df[col].mean())
cat_cols = df.select_dtypes(include=["object", "string"]).columns   # Categorical columns (explicit object + string)
for col in cat_cols:
    df[col] = df[col].fillna(df[col].mode()[0])
print("\nMissing values after handling:")
print(df.isna().sum())

# Encode Categorical Columns
label_encoders = {}
for col in cat_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le

# Separate Features & Target
drop_cols = ["CustomerID"]
X = df.drop(columns=drop_cols)

# Feature Scaling
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Transpose data (required by FCM library)
X_fcm = X_scaled.T

# STEP 1: Apply Fuzzy C-Means
c = 3   # Number of clusters
cntr, u, u0, d, jm, p, fpc = fuzz.cluster.cmeans(   # Apply FCM
    X_fcm,
    c=c,
    m=2,                 # Fuzziness coefficient smaller -> hard, higher -> soft
    error=0.005,
    maxiter=1000,
    init=None
)

# STEP 2: Membership Matrix
print("\nMembership values for first 5 samples:")
print(u[:, :5])

# STEP 3: Evaluation
sil_score = silhouette_score(X_scaled, np.argmax(u, axis=0))  # Silhouette Score (using hard labels)
print("\nEvaluation Metrics:")
print(f"Fuzzy Partition Coefficient (FPC):{fpc:.3f}")
print(f"Silhouette Score: {sil_score:.3f}")

# STEP 4: Visualization

# 1. Reduce dimensions for visualization
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

# 2. Create RGB Colors for the points based on membership
# Assume 'u' is  membership matrix from skfuzzy (shape: k, n_samples)
# We will assign a base color to each cluster (e.g., Red, Green, Blue)
base_colors = np.array([
    [1, 0, 0],  # Cluster 0: Red
    [1, 1, 0],  # Cluster 1: Green
    [0, 0, 1],  # Cluster 2: Blue
])
# Ensure we have enough base colors for  optimal_k
colors_to_use = base_colors[:u.shape[0]]
# Calculate point colors: Dot product of (n_samples, k) and (k, 3) 
# This blends the colors based on the membership percentages
point_colors = u.T @ colors_to_use

# 3. Plotting
plt.figure(figsize=(10, 7))
# Scatter plot using the blended colors
plt.scatter(
    X_pca[:, 0], 
    X_pca[:, 1], 
    c=point_colors,
    s=80, 
    edgecolors='white', 
    linewidth=0.5,
    alpha=0.8
)
plt.xlabel("PC1")
plt.ylabel("PC2")
plt.title(f"Fuzzy C-Means Membership (k={u.shape[0]})")
plt.grid(True, linestyle='--', alpha=0.6)
plt.show()