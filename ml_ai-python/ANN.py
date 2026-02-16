import pandas as pd
import numpy as np
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

# Load Dataset
dataset = "Datasets/Iris.csv"
df = pd.read_csv(dataset)
print(df.head())
print("Total samples:", len(df))

cat_cols = df.select_dtypes(include=["object", "string"]).columns   # Categorical columns (explicit object + string)
# Encode Categorical Columns
label_encoders = {}
for col in cat_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le

# Separate Features & Target
target = "Species"
drop_cols = ["Species","Id"]
X = df.drop(columns=drop_cols)
X_ = X
y = df[target]
print("\nFeatures:")
print(X.head())
print("\nTarget:")
print(y.head())

num_classes = len(np.unique(y))
y_onehot = np.eye(num_classes)[y]

# Feature Scaling (NOT required for ID3, CART, Naive Bayes)
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Split the data into Test and Train
X_train, X_test, y_train, y_test = train_test_split(
    X_scaled, y_onehot, test_size=0.2, random_state=42)

# Architecture
ARCH = [X_train.shape[1], 3, num_classes]
learning_rate = 0.5
epochs = 2000

# Activation Functions
def sigmoid(x):
    return 1 / (1 + np.exp(-x))
def sigmoid_derivative(y):
    return y * (1 - y)

# Intialisation
np.random.seed(1)
weights = []
biases = []
for i in range(len(ARCH) - 1):
    weights.append(np.random.randn(ARCH[i], ARCH[i+1]) * 0.5)
    biases.append(np.zeros(ARCH[i+1]))

# Forward Propagation
def forward(X):
    activations = [X]
    for i in range(len(weights)):
        net = np.dot(activations[-1], weights[i]) + biases[i]
        activations.append(sigmoid(net))
    return activations

# Back Propagation
def backward(activations, y_true):
    deltas = [None] * len(weights)
    deltas[-1] = (y_true - activations[-1]) * sigmoid_derivative(activations[-1])
    for i in reversed(range(len(deltas) - 1)):
        deltas[i] = np.dot(deltas[i+1], weights[i+1].T) * sigmoid_derivative(activations[i+1])
    return deltas

# Training
print("\nTRAINING STARTED:")
loss_history = []
tolerance = 1e-3          # convergence threshold
prev_loss = float('inf')

for epoch in range(epochs):
    total_loss = 0
    for i in range(len(X_train)):
        X = X_train[i]
        y = y_train[i]
        activations = forward(X)
        loss = np.mean((y - activations[-1]) ** 2)
        total_loss += loss
        deltas = backward(activations, y)
        for j in range(len(weights)):
            weights[j] += learning_rate * np.outer(activations[j], deltas[j])
            biases[j] += learning_rate * deltas[j]
    loss_history.append(total_loss)

    if epoch % 50 == 0:
        print(f"Epoch {epoch}, Loss: {total_loss:.4f}")
    if abs(prev_loss - total_loss) < tolerance:
        print(f"Training converged at epoch {epoch}")
        break
    prev_loss = total_loss

# Testting and Accuracy
def predict(X):
    outputs = []
    for x in X:
        out = forward(x)[-1]
        outputs.append(np.argmax(out))
    return np.array(outputs)
y_test_labels = np.argmax(y_test, axis=1)
y_pred = predict(X_test)

cm = confusion_matrix(y_test_labels, y_pred)
print("\nEvaluation Metrics:")
print("\nConfusion Matrix:")
print(cm)
print("\nClassification Report:")
print(classification_report(y_test_labels, y_pred))

# Visualisation (Loss)
plt.figure()
plt.plot(loss_history)
plt.xlabel("Epochs")
plt.ylabel("Total Loss (MSE)")
plt.title("MLP Backpropagation Training Loss (IRIS)")
plt.grid(True)
plt.show()

# Visualization(CM)
plt.figure()
plt.imshow(cm)
plt.title("Confusion Matrix - MLP Backpropagation IRIS")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.colorbar()
plt.show()

# Testing unknown data
new_sample = np.array([[5.1, 3.5, 1.4, 0.2]])
new_sample_scaled = scaler.transform(new_sample)
output = forward(new_sample_scaled[0])[-1]

predicted_class = np.argmax(output)
predicted_species = label_encoders["Species"].inverse_transform([predicted_class])

print("\nNew Sample:", new_sample[0])
print("Network Output:", output)
print("Predicted Class Index:", predicted_class)
print("Predicted Species:", predicted_species[0])