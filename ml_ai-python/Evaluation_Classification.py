from sklearn.metrics import (
    confusion_matrix,
    classification_report,
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    ConfusionMatrixDisplay
)

import matplotlib.pyplot as plt

# ====================================
# Evaluation Function (Classification)
# ====================================

def evaluate_model(y_true, y_pred, class_names):

    # -------- Accuracy --------
    acc = accuracy_score(y_true, y_pred)
    print("\nAccuracy :", round(acc, 4))


    # -------- Precision, Recall, F1 (Macro Avg) --------
    prec = precision_score(y_true, y_pred, average="macro")
    rec = recall_score(y_true, y_pred, average="macro")
    f1 = f1_score(y_true, y_pred, average="macro")

    print("Precision:", round(prec, 4))
    print("Recall   :", round(rec, 4))
    print("F1-Score :", round(f1, 4))


    # -------- Full Report --------
    print("\nClassification Report:")
    print(classification_report(y_true, y_pred))


    # -------- Confusion Matrix --------
    cm = confusion_matrix(y_true, y_pred)

    print("Confusion Matrix:")
    print(cm)


    # -------- Colorful CM --------
    disp = ConfusionMatrixDisplay(
        confusion_matrix=cm,
        display_labels=class_names
    )

    disp.plot(cmap=plt.cm.Blues)

    plt.title("Confusion Matrix")
    plt.show()
