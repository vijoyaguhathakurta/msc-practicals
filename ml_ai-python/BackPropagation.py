import numpy as np
import matplotlib.pyplot as plt

# Network
ARCH = [4, 3, 2, 2]   # Network architecture

X_train = np.array([        # Training dataset(XOR)
    [1, 1, 0, 1],
    [1, 0, 1, 0],
    [0, 1, 1, 1],
    [0, 0, 1, 0]
])
y_train = np.array([        # Expected Output
    [1, 0],
    [0, 1],
    [1, 1],
    [0, 0]
])



learning_rate = 0.1
epochs = 20000


# Activation Function
def sigmoid(x):
    return 1 / (1 + np.exp(-x))
def sigmoid_derivative(y):
    return y * (1 - y)


# Initialisation
np.random.seed(1)
weights = []
biases = []
for i in range(len(ARCH) - 1):
    weights.append(np.random.randn(ARCH[i], ARCH[i + 1]) * 0.5)
    biases.append(np.random.randn(ARCH[i + 1]))


# Forward Propagation
def forward_propagation(X):
    activations = [X]

    for i in range(len(weights)):
        net = np.dot(activations[-1], weights[i]) + biases[i]
        activations.append(sigmoid(net))

    return activations


# Back Propagation
def backpropagation(activations, y_true):
    deltas = [None] * len(weights)

    # Output layer
    error = y_true - activations[-1]
    deltas[-1] = error * sigmoid_derivative(activations[-1])

    # Hidden layers
    for i in reversed(range(len(deltas) - 1)):
        deltas[i] = (
            np.dot(deltas[i + 1], weights[i + 1].T)
            * sigmoid_derivative(activations[i + 1])
        )

    return deltas


# Training Loop with Early Stopping
loss_history = []
tolerance = 1e-6          # convergence threshold
prev_loss = float('inf')

for epoch in range(epochs):
    total_loss = 0

    for i in range(len(X_train)):
        X = X_train[i]
        y = y_train[i]

        # Forward pass
        activations = forward_propagation(X)

        # Loss (MSE)
        loss = np.mean((y - activations[-1]) ** 2)
        total_loss += loss

        # Backpropagation
        deltas = backpropagation(activations, y)

        # Update weights and biases
        for j in range(len(weights)):
            weights[j] += learning_rate * np.outer(activations[j], deltas[j])
            biases[j] += learning_rate * deltas[j]

    loss_history.append(total_loss)

    # Print progress
    if epoch % 200 == 0:
        print(f"Epoch {epoch}, Total Loss: {total_loss:.6f}")

    if abs(prev_loss - total_loss) < tolerance:
        print(f"Training converged at epoch {epoch}")
        break

    prev_loss = total_loss
    


# Testing
'''
print("\nFinal Predictions:")
for x in X_train:
    output = forward_propagation(x)[-1]
    pred = 1 if output >= 0.5 else 0
    print(f"Input: {x} -> Output: {pred}")
'''

# Testing (Generalised)
print("\nFinal Predictions:")
for x in X_train:
    output = forward_propagation(x)[-1]
    # Threshold each output neuron
    pred = (output >= 0.5).astype(int)
    print(f"Input: {x} -> Output: {pred}")



# Visualization (Loss)
plt.figure()
plt.plot(loss_history)
plt.xlabel("Epochs")
plt.ylabel("Total Loss (MSE)")
plt.title("Backpropagation Training Loss")
plt.grid(True)
plt.show()
