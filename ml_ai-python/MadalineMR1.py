from matplotlib import pyplot as plt
import numpy as np

# Sign Function
def sign(x):
    if x >= 0:
        return 1
    else:
        return -1

# Training Data (XOR)
# Bipolar {-1, +1}
X = np.array([
    [-1,-1],
    [-1, 1],
    [ 1,-1],
    [ 1, 1]
])
y = np.array([-1, 1, 1, -1])   # XOR

# Initialize Weights

np.random.seed(1)
# Input → Hidden (2 neurons)
W = np.random.randn(2,2) * 0.5
# Hidden biases
b = np.zeros(2)
# Hidden → Output weights
V = np.array([1.0, 1.0])   # Fixed as per theory

# Parameters
lr = 0.1
max_epochs = 1000

# Training (MR-I Rule)
print("Training Started (MR-I)...\n")
loss_history = []

for epoch in range(max_epochs):
    total_error = 0
    weight_changed = False

    for i in range(len(X)):
        # ----- Hidden Layer -----
        z_in = np.dot(X[i], W) + b
        z_out = np.array([sign(z) for z in z_in])
        # ----- Output Layer -----
        y_in = np.dot(z_out, V)
        y_pred = sign(y_in)
        # ----- Error -----
        if y_pred != y[i]:
            total_error += 1
            # Find hidden unit closest to zero
            j = np.argmin(np.abs(z_in))
            # Target for hidden unit
            t = y[i]
            # Update only selected neuron (MR-I)
            W[:,j] = W[:,j] + lr * (t - z_in[j]) * X[i]
            b[j] = b[j] + lr * (t - z_in[j])
            weight_changed = True
        loss_history.append(total_error)
    # Training log
    print(f"Epoch {epoch+1} | Error = {total_error}")
    # Stopping condition
    if not weight_changed:
        print("\nTraining Converged!")
        break

# Testing
print("\nFinal Predictions:\n")
for i in range(len(X)):
    z_in = np.dot(X[i], W) + b
    z_out = np.array([sign(z) for z in z_in])
    y_in = np.dot(z_out, V)
    y_pred = sign(y_in)
    print(X[i], "->", y_pred)

# Visualization (Loss)
plt.plot(loss_history)
plt.xlabel("Epochs")
plt.ylabel("Total Error")
plt.title("MADALINE Rule-I Training Error")
plt.grid(True)
plt.show()