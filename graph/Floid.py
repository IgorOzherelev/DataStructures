num = int(input())
magic_matrix = []
for i in range(0, num):
    magic_matrix.append(list(map(int, input().split())))

for i in range(len(magic_matrix)):
    for j in range(len(magic_matrix[i])):
        if magic_matrix[i][j] == 0:
            magic_matrix[i][j] = 10**10

for k in range(num):
    for i in range(num):
        for j in range(num):
            if magic_matrix[i][k] + magic_matrix[k][j] < magic_matrix[i][j]:
                magic_matrix[i][j] = magic_matrix[i][k] + magic_matrix[k][j]

for i in range(num):
    if magic_matrix[i][i] != 10 ** 10:
        print(1)
        break
else:
    print(0)