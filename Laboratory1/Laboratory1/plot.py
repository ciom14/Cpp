import matplotlib.pyplot as plt

epochs = []
losses = []

with open("D:\\visual studio\\projects\\Laboratory1\\Laboratory1\\loss.txt", "r") as f:
    for line in f:
        parts = line.split()
        epochs.append(int(parts[0]))
        losses.append(float(parts[1]))

plt.figure(figsize=(10, 6))
plt.plot(epochs, losses)
plt.title("Training Loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.grid(True)
plt.savefig("loss.png")
plt.show()