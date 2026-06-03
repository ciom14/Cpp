import sys
sys.path.insert(0, ".")
import neuro

net = neuro.Network([8, 4, 1], 2)
result = net.forward([1.0, 0.5])
print("Result:", result)