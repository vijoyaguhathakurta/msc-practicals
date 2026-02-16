import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier, plot_tree
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
print("\nMissing values after handling:")
print(df.isna().sum())

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

# Split the data into Test and Train
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# STEP 1: ID3 Algorithm (Entropy)
model = DecisionTreeClassifier(criterion="entropy")     # Create Decision Tree using entropy (ID3)
model.fit(X_train, y_train) # Train the model

# STEP 2: Prediction
y_pred = model.predict(X_test)
print("\nTESTING:\nPredicted Values:",y_pred)
print("Actual Values:",y_test.values)

# STEP 3: Evaluation
accuracy = accuracy_score(y_test, y_pred)
cm = confusion_matrix(y_test, y_pred)
print("\nEvaluation Metrics:")
print("Accuracy:", accuracy)
print("\nConfusion Matrix:")
print(cm)
print("\nClassification Report:")
print(classification_report(y_test, y_pred))

# STEP 4: Decision Tree Visualization
plt.figure(figsize=(8, 12))
plot_tree(
    model,
    feature_names=X.columns,
    class_names=["No", "Yes"],
    filled=True
)
plt.title("Decision Tree using ID3 Algorithm")
plt.show()

# Line 15: D14,Rain,Mild,High,Strong,No
new_sample = pd.DataFrame(
    [["Rain", "Mild", "High", "Strong"]],
    columns=X.columns
)

for col in new_sample.columns:
    new_sample[col] = label_encoders[col].transform(new_sample[col])
prediction = model.predict(new_sample)
print(f"\n\nInput: {["Rain", "Mild", "High", "Strong"]}\nPrediction: {le.inverse_transform(prediction)}")
