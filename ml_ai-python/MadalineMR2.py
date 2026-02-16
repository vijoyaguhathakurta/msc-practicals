import numpy as np
import matplotlib.pyplot as plt

# Network
ARCH = [4, 3, 2]        # Network architecture

X_train = np.array([
    [1, 1, 0, 1],
    [1, 0, 1, 0],
    [0, 1, 1, 1],
    [0, 0, 1, 0]
])
y_train = np.array([    # Bipolar outputs (-1, +1)
    [ 1, -1],
    [-1,  1],
    [ 1,  1],
    [-1, -1]
])



learning_rate = 0.1
epochs = 6000


# Activation Function
def sign(x):
    return np.where(x >= 0, 1, -1)


# Initialisation
np.random.seed(1)

W_hidden = np.random.randn(ARCH[0], ARCH[1])
b_hidden = np.random.randn(ARCH[1])

W_out = np.random.randn(ARCH[1], ARCH[2])
b_out = np.random.randn(ARCH[2])



# Training Loop
loss_history = []

for epoch in range(epochs):
    total_error = 0

    for i in range(len(X_train)):
        x = X_train[i]
        y = y_train[i]

        # ---- Hidden layer (linear ADALINEs)
        net_h = np.dot(x, W_hidden) + b_hidden
        h = net_h

        # ---- Output layer
        net_o = np.dot(h, W_out) + b_out
        y_pred = sign(net_o)

        error = y - y_pred
        total_error += np.sum(error ** 2)

        # ---- Update output layer (always)
        W_out += learning_rate * np.outer(h, error)
        b_out += learning_rate * error

        # ---- MR-II: update ONLY one hidden ADALINE
        if np.any(error != 0):
            j_star = np.argmin(np.abs(net_h))  # closest to zero

            W_hidden[:, j_star] += learning_rate * error.mean() * x
            b_hidden[j_star] += learning_rate * error.mean()

    loss_history.append(total_error)

    if epoch % 100 == 0:
        print(f"Epoch {epoch}, Total Error: {total_error}")
    
    if total_error == 0:
        print(f"Training converged at epoch {epoch}")
        break


# Testing
print("\nFinal MADALINE Predictions:")
for x in X_train:
    h = np.dot(x, W_hidden) + b_hidden
    out = sign(np.dot(h, W_out) + b_out)
    print(f"Input: {x} -> Output: {out}")


# Visualization (Loss)
plt.plot(loss_history)
plt.xlabel("Epochs")
plt.ylabel("Total Error")
plt.title("MADALINE Rule-II Training Error")
plt.grid(True)
plt.show()
