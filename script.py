import matmul
import timeit
import numpy as np
import random

MAT_SIZE = 200
first = [[random.randint(1, 100)] * MAT_SIZE for _ in range(MAT_SIZE)]
second = [[random.randint(1, 100)] * MAT_SIZE for _ in range(MAT_SIZE)]

def python_matmul(X, Y):
    result = [
        [0]*len(X)
        for _ in range(len(X))
    ]
    for i in range(len(X)):
        for j in range(len(Y[0])):
           for k in range(len(Y)):
               result[i][j] += X[i][k] * Y[k][j]
    return result


time_took_python_ms = timeit.timeit(lambda: python_matmul(first, second), number=1) * 1000
time_took_matmul_ms = timeit.timeit(lambda: matmul.matmul(first, second), number=1) * 1000

first = np.asarray(first)
second = np.asarray(second)
time_took_numpy_ms = timeit.timeit(lambda: first @ second, number=1000) * 1000

print(f"Python took {time_took_python_ms} ms.")
print(f"Numpy took {time_took_numpy_ms} ms.")
print(f"Simple C extension took {time_took_matmul_ms} ms.")
