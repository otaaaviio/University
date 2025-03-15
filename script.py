import os
import random

path = '/home/otavio/Documents/vscode-folders/University/POD/files'

with open(os.path.join(path, 'file-3.txt'), 'w') as f:
    for i in range(1000000, 1, -1):
        f.write(str(i) + '\n')

numeros = list(range(1, 10000001))

random.shuffle(numeros)

with open(os.path.join(path, 'file-4.txt'), 'w') as f:
    for num in numeros:
        f.write(str(num) + '\n')