import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

# Load Dataset
dataset = "Dataset/house_loan.csv"
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
#X = df[["ApplicantIncome", "CoapplicantIncome", "Loan_Amount_Term", "Credit_History"]] # Multi Polynomial
X = df[["ApplicantIncome"]]
y = df["LoanAmount"]


# Feature Scaling (NOT required for ID3, CART, Naive Bayes)
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# Split the data into Test and Train
X_train, X_test, y_train, y_test = train_test_split(
    X_scaled, y, test_size=0.2, random_state=42
)




# STEP 1: Linear Regression Model
model = LinearRegression()
model.fit(X_train, y_train) # Train the model


# STEP 5: Prediction
y_pred = model.predict(X_test)
print("\nPredicted Values:")
print(y_pred[:5])
print("\nActual Values:")
print(y_test.values[:5])


# STEP 6: Evaluation
mae = mean_absolute_error(y_test, y_pred)
mse = mean_squared_error(y_test, y_pred)
rmse = np.sqrt(mse)
r2 = r2_score(y_test, y_pred)

print("\nEvaluation Metrics:")
print("Mean Absolute Error (MAE):", mae)
print("Mean Squared Error (MSE):", mse)
print("Root Mean Squared Error (RMSE):", rmse)
print("R2 Score:", r2)


# Step 7: Visualization
plt.figure()
plt.scatter(X_test, y_pred, label = "Actual")
#plt.plot(X_test, y_pred, color="red", label="Regression Line")
plt.xlabel("Actual Loan Amount")
plt.ylabel("Predicted Loan Amount")
plt.title("Simple Linear Regression: Actual vs Predicted")
plt.show()



'''
new_sample = pd.DataFrame(
    [[1853]],
    columns=X.columns
)
prediction = model.predict(new_sample)
print("Prediction: ", prediction)
'''