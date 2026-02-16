# ====================================
# PRACTICAL 11 : Apriori Algorithm
# WITHOUT Using Any Library
# Dataset : market.csv
# ====================================

import pandas as pd
from itertools import combinations


# -------------------------------
# STEP 1 : Load Dataset
# -------------------------------

data = pd.read_csv("market.csv")

print("Original Dataset:")
print(data)


# -------------------------------
# STEP 2 : Convert to Transactions
# -------------------------------
# Each row -> one transaction list

transactions = []

for i in range(len(data)):

    # Drop NaN and convert row to list
    items = data.iloc[i].dropna().tolist()

    transactions.append(items)


print("\nTransactions:")
print(transactions)


# -------------------------------
# STEP 3 : Set Minimum Support
# -------------------------------

min_support = 0.3   # 30%

total_trans = len(transactions)


# -------------------------------
# STEP 4 : Find C1 (Single Items)
# -------------------------------

item_count = {}

# Count each item
for trans in transactions:

    for item in trans:

        if item in item_count:
            item_count[item] += 1
        else:
            item_count[item] = 1


# Calculate support for C1
C1 = {}

for item in item_count:

    support = item_count[item] / total_trans

    if support >= min_support:
        C1[frozenset([item])] = support


print("\nL1 (Frequent 1-itemsets):")
print(C1)


# -------------------------------
# STEP 5 : Generate Higher Itemsets
# -------------------------------

def generate_Lk(L_prev, k):

    candidates = {}

    # Combine previous itemsets
    for i in L_prev:
        for j in L_prev:

            union = i | j

            if len(union) == k:

                count = 0

                # Count support
                for trans in transactions:

                    if union.issubset(trans):
                        count += 1

                support = count / total_trans

                if support >= min_support:
                    candidates[union] = support

    return candidates


# -------------------------------
# STEP 6 : Find All Frequent Itemsets
# -------------------------------

L = []
L.append(C1)

k = 2

while True:

    Lk = generate_Lk(L[k-2], k)

    if len(Lk) == 0:
        break

    L.append(Lk)

    k += 1


# Print all frequent itemsets
print("\nAll Frequent Itemsets:")

for i in range(len(L)):
    print(f"\nL{i+1}:")
    for item in L[i]:
        print(set(item), "Support =", L[i][item])


# -------------------------------
# STEP 7 : Generate Association Rules
# -------------------------------

min_confidence = 0.6

print("\nAssociation Rules:")

for level in L[1:]:

    for itemset in level:

        for i in range(1, len(itemset)):

            subsets = combinations(itemset, i)

            for s in subsets:

                A = frozenset(s)
                B = itemset - A

                support_AB = level[itemset]

                # Find support of A
                for l in L:
                    if A in l:
                        support_A = l[A]

                confidence = support_AB / support_A

                if confidence >= min_confidence:

                    print(set(A), "->", set(B),
                          "Confidence =", round(confidence,2))
