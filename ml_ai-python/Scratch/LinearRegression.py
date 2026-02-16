import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

# Load Dataset
dataset = "/Users/samratdutta/Desktop/Sem 3/AI Assignment/Generalised/Dataset/house_loan.csv"
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
# X = df[["Dependents", "ApplicantIncome", "CoapplicantIncome"]] # Multi Polynomial
X = df[["ApplicantIncome"]]
y = df["LoanAmount"]



# Split the data into Test and Train
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)




# STEP 1: Linear Regression Model
x_train = X_train["ApplicantIncome"].values                     # Convert to NumPy arrays
y_train = y_train.values

x_mean = np.mean(x_train)                                       # Mean of X and Y
y_mean = np.mean(y_train)

numerator = np.sum((x_train - x_mean) * (y_train - y_mean))     # Calculate slope (m)
denominator = np.sum((x_train - x_mean) ** 2)
m = numerator / denominator

c = y_mean - m * x_mean                                         # Calculate intercept (c)
print("Slope (m):", m)
print("Intercept (c):", c)



# STEP 5: Prediction
x_test = X_test["ApplicantIncome"].values
y_pred = m * x_test + c
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
plt.scatter(x_test, y_test, label="Actual")
plt.plot(x_test, y_pred, color="red", label="Regression Line")
plt.xlabel("Applicant Income")
plt.ylabel("Loan Amount")
plt.legend()
plt.title("Simple Linear Regression")
plt.show()


new_income = 1853
prediction = m * new_income + c
print(f"\nPredicted Loan Amount for income {new_income} is {prediction}")
