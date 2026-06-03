import sys

sys.path.insert(0, ".")
import neuro
import csv
import random


def load_dataset(path):
    inputs = []
    targets = []
    with open(path, "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            features = [float(v) for k, v in row.items() if k.startswith("feature")]
            target = float(row["target"])
            inputs.append(features)
            targets.append(target)
    return inputs, targets


def f1_score(net, inputs, targets):
    tp = fp = fn = 0
    for i in range(len(inputs)):
        pred = 1 if net.forward(inputs[i]) >= 0.5 else 0
        label = int(targets[i])
        if pred == 1 and label == 1: tp += 1
        if pred == 1 and label == 0: fp += 1
        if pred == 0 and label == 1: fn += 1
    if tp + fp == 0 or tp + fn == 0:
        return 0.0
    precision = tp / (tp + fp)
    recall = tp / (tp + fn)
    if precision + recall == 0:
        return 0.0
    return 2 * precision * recall / (precision + recall)


def train_and_eval(dataset_path, layer_sizes, input_size, epochs=100, lr=0.1):
    inputs, targets = load_dataset(dataset_path)

    combined = list(zip(inputs, targets))
    random.shuffle(combined)
    inputs, targets = zip(*combined)

    split = int(len(inputs) * 0.8)
    train_inputs, train_targets = inputs[:split], targets[:split]
    test_inputs, test_targets = inputs[split:], targets[split:]

    net = neuro.Network(layer_sizes, input_size)

    for epoch in range(epochs):
        if epoch % 1 == 0:
            f1 = f1_score(net, test_inputs, test_targets)
            print(f"Epoch {epoch} F1: {f1:.4f}")
        for i in range(len(train_inputs)):
            net.train(train_inputs[i], train_targets[i], lr)


    return net, f1_score(net, test_inputs, test_targets), test_inputs, test_targets


print("Training on dataset 1...")
net1, f1_d1, test_inputs1, test_targets1 = train_and_eval(
    "D:\\visual studio\\projects\\neuro\\neuro\\dataset1.csv",
    [8, 4, 1], 2
)
net1.save("D:\\visual studio\\projects\\neuro\\x64\\Release\\model1.txt")

print("\nTraining on dataset 2...")
net2, f1_d2, test_inputs2, test_targets2 = train_and_eval(
    "D:\\visual studio\\projects\\neuro\\neuro\\dataset2.csv",
    [8, 4, 1], 4
)
net2.save("D:\\visual studio\\projects\\neuro\\x64\\Release\\model2.txt")

print(f"\nF1 d1: {f1_d1:.4f}")
print(f"F1 d2: {f1_d2:.4f}")
print(f"Final score: {0.5 * f1_d1 + 0.5 * f1_d2:.4f}")
print("\nМодели сохранены в model1.txt и model2.txt")
