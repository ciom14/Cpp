import matplotlib.pyplot as plt
import numpy as np
import subprocess

x0, y0 = [], []
x1, y1 = [], []

with open("points.txt", "r") as f:
    for line in f:
        parts = line.split()
        x = float(parts[0])
        y = float(parts[1])
        label = float(parts[2])
        if label == 1.0:
            x1.append(x)
            y1.append(y)
        else:
            x0.append(x)
            y0.append(y)

# Читаем предсказания сети для сетки точек
with open("grid.txt", "r") as f:
    grid_data = []
    for line in f:
        parts = line.split()
        grid_data.append((float(parts[0]), float(parts[1]), float(parts[2])))

gx = np.array([d[0] for d in grid_data])
gy = np.array([d[1] for d in grid_data])
gz = np.array([d[2] for d in grid_data])

n = int(np.sqrt(len(grid_data)))
GX = gx.reshape(n, n)
GY = gy.reshape(n, n)
GZ = gz.reshape(n, n)

plt.figure(figsize=(8, 8))
plt.contourf(GX, GY, GZ, levels=[0, 0.5, 1], alpha=0.3, colors=['blue', 'red'])
plt.contour(GX, GY, GZ, levels=[0.5], colors=['black'], linewidths=2)

plt.scatter(x0, y0, color='blue', label='Class 0', zorder=5)
plt.scatter(x1, y1, color='red', label='Class 1', zorder=5)

x_line = np.linspace(-2, 2, 100)
y_line = np.sin(x_line)
plt.plot(x_line, y_line, color='green', linewidth=2, label='sin(x)')

plt.legend()
plt.title('Binary Classification')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.savefig('result.png')
plt.show()