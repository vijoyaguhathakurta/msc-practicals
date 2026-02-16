import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

from sklearn.svm import SVC as SVM
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# Load Dataset
dataset = "Datasets/play_tennis.csv"
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

# Encode Categorical Columns
label_encoders = {}
for col in cat_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le

# Separate Features & Target
target = "play"
drop_cols = ["play", "day"]
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

# STEP 1: SVM Model
# kernel options: 'linear', 'rbf', 'poly', 'sigmoid'
model = SVM(kernel="sigmoid")    # Create SVM classifier with sigmoid kernel
model.fit(X_train, y_train)     # Train the model

# STEP 2: Prediction
y_pred = model.predict(X_test)
print("\nPredicted Values:",y_pred)
print("\nActual Values:", y_test.values)

# STEP 3: Evaluation
accuracy = accuracy_score(y_test, y_pred)
cm = confusion_matrix(y_test, y_pred)
print("\nEvaluation Metrics:")
print("Accuracy:", accuracy)
print("\nConfusion Matrix:")
print(cm)
print("\nClassification Report:")
print(classification_report(y_test, y_pred))


# STEP 4: Visualization
plt.figure()
plt.imshow(cm)
plt.title("Confusion Matrix - SVM")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.colorbar()
plt.show()

# D10,Rain,Mild,Normal,Weak,Yes
new_sample = pd.DataFrame(
    [["Rain", "Mild", "Normal", "Weak"]],
    columns=X.columns
)
print("Testing Sample",new_sample)
# Label encode
for col in new_sample.columns:
    new_sample[col] = label_encoders[col].transform(new_sample[col])

new_sample_scaled = scaler.transform(new_sample)
# Predict
prediction = model.predict(new_sample_scaled)
print("Prediction:", prediction)
