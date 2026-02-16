import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report


# Load Dataset
dataset = "Dataset/iris.csv"
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
target = "Species"
drop_cols = ["Species"]
X = df.drop(columns=drop_cols)
y = df[target]
print("\nFeatures:")
print(X.head())
print("\nTarget:")
print(y.head())



# Feature Scaling (NOT required for ID3, CART, Naive Bayes)
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)



# Split the data into Test and Train
X_train, X_test, y_train, y_test = train_test_split(
    X_scaled, y, test_size=0.2, random_state=42
)



# K-value vs Accuracy
k_values = range(1, 21)
accuracies = []
for k in k_values:
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(X_train, y_train)
    y_pred_k = knn.predict(X_test)
    acc = accuracy_score(y_test, y_pred_k)
    accuracies.append(acc)
# Plot
plt.figure()
plt.plot(k_values, accuracies, marker='o')
plt.xlabel("K value")
plt.ylabel("Accuracy")
plt.title("K Value vs Accuracy (KNN)")
plt.grid(True)
plt.show()





# Step 1: KNN Model
k = 5   # Choose value of K
model = KNeighborsClassifier(n_neighbors=k) # Create KNN classifier
model.fit(X_train, y_train) # Train the model


# STEP 2: Prediction
y_pred = model.predict(X_test)
print("\nPredicted Values:")
print(y_pred)
print("\nActual Values:")
print(y_test)


# STEP 3: Evaluation
accuracy = accuracy_score(y_test, y_pred)
cm = confusion_matrix(y_test, y_pred)
print("\nEvaluation Metrics:")
print("Accuracy:", accuracy)
print("\nConfusion Matrix:")
print(cm)
#print("\nClassification Report:")
#print(classification_report(y_test, y_pred))


# STEP 7: Visualization
plt.figure()
plt.imshow(cm)
plt.title("Confusion Matrix - KNN")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.colorbar()
plt.show()





# Prediction (Numeric Dataset like "iris.csv")
# Line 31: 4.7,3.2,1.6,0.2,Iris-setosa
new_sample = pd.DataFrame(
    [[4.7,3.2,1.6,0.2]],
    columns=X.columns
)
new_sample_scaled = scaler.transform(new_sample)
prediction = model.predict(new_sample_scaled)
print("Prediction: ", prediction)