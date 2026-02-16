import numpy as np
import matplotlib.pyplot as plt

GATES = ["AND","OR","NAND","NOR"]   # AND, OR, NAND, NOR

X = np.array([      # Truth Table
    [0, 0],
    [0, 1],
    [1, 0],
    [1, 1]
])

for GATE in GATES:
      
    if GATE == "AND":
        y = np.array([0, 0, 0, 1])
    elif GATE == "OR":
        y = np.array([0, 1, 1, 1])
    elif GATE == "NAND":
        y = np.array([1, 1, 1, 0])
    elif GATE == "NOR":
        y = np.array([1, 0, 0, 0])
    else:
        raise ValueError("Invalid Gate")

    print(f"\nTraining Perceptron for {GATE} Gate")

    # Initialise Parameters
    weights = np.random.randn(2)
    bias = np.random.randn()
    learning_rate = 0.5
    epochs = 100

    # Activation Function
    def step(x):
        return 1 if x >= 0 else 0

    # Training Loop
    for epoch in range(epochs):
        total_error = 0
        print(f"\nEpoch {epoch + 1}")  
        for i in range(len(X)):
            net = np.dot(X[i], weights) + bias
            output = step(net)
            error = y[i] - output         
            # Update rule
            weights += learning_rate * error * X[i]
            bias += learning_rate * error
            total_error += abs(error)
            print(f"Input: {X[i]}, Output: {output}, Error: {error}")
        if total_error == 0:
            print("Training converged!")
            break
    print("\nFinal Weights:", weights)
    print("Final Bias:", bias)

    # Testing
    print(f"\nTesting {GATE} Gate:")
    for x in X:
        print(f"Input: {x}, Output:", step(np.dot(x, weights) + bias))

    # Visualization
    plt.figure()
    # Plot points
    for i in range(len(X)):
        if y[i] == 1:
            plt.scatter(X[i][0], X[i][1], color='green', s=100)
        else:
            plt.scatter(X[i][0], X[i][1], color='red', s=100)
    # Decision boundary: w1*x1 + w2*x2 + b = 0
    x_vals = np.array([-0.2, 1.2])
    y_vals = -(weights[0] * x_vals + bias) / weights[1]
    plt.plot(x_vals, y_vals, color='blue', label="Decision Boundary")
    plt.xlabel("Input X1")
    plt.ylabel("Input X2")
    plt.title(f"Perceptron Decision Boundary for {GATE} Gate")
    #plt.legend(["Decision Boundary", "Class 0 (RED)", "Class 1 (GREEN)"])
    plt.grid(True)
    plt.show()
