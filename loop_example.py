import numpy as np
from timeit import default_timer as timer

iterations = 10000
sum = 0

start = timer()
for r in range(0, iterations):
    for c in range(0, iterations):
        sum += c * 3.1415

end = timer()

print(end - start)





