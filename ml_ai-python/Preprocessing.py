import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt


# Load Dataset
dataset = "Dataset/"
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
target = ""
drop_cols = [""]
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







# Prediction (Numeric Dataset like "iris.csv")
# Line 31: 4.7,3.2,1.6,0.2,Iris-setosa
new_sample = pd.DataFrame(
    [[4.7,3.2,1.6,0.2]],
    columns=X.columns
)
new_sample_scaled = scaler.transform(new_sample)
prediction = model.predict(new_sample_scaled)
print("Prediction: ", prediction)


# Prediction (String+Numeric like "play_tennis.csv")
# Line 15: D14,Rain,Mild,High,Strong,No
new_sample = pd.DataFrame(
    [["Rain", "Mild", "High", "Strong"]],
    columns=X.columns
)
for col in new_sample.columns:
    new_sample[col] = label_encoders[col].transform(new_sample[col])
prediction = model.predict(new_sample)
print("Prediction: ", prediction)