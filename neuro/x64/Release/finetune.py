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

# Загружаем датасет d3
dataset_path = "D:\\visual studio\\projects\\neuro\\neuro\\dataset3.csv"
inputs, targets = load_dataset(dataset_path)

combined = list(zip(inputs, targets))
random.shuffle(combined)
inputs, targets = zip(*combined)

split = int(len(inputs) * 0.8)
train_inputs, train_targets = inputs[:split], targets[:split]
test_inputs, test_targets = inputs[split:], targets[split:]

# Определяем количество признаков
input_size = len(inputs[0])
print(f"Input size: {input_size}")

# Загружаем подходящую модель
if input_size == 2:
    net = neuro.Network([8, 4, 1], 2)
    net.load("model1.txt")
elif input_size == 4:
    net = neuro.Network([8, 4, 1], 4)
    net.load("model2.txt")

print(f"F1 до дообучения: {f1_score(net, test_inputs, test_targets):.4f}")

# Дообучаем
for epoch in range(100):
    if epoch % 10 == 0:
        print(f"Epoch {epoch} F1: {f1_score(net, test_inputs, test_targets):.4f}")
    for i in range(len(train_inputs)):
        net.train(train_inputs[i], train_targets[i], 0.1)

print(f"\nF1 после дообучения: {f1_score(net, test_inputs, test_targets):.4f}")