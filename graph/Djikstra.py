Num, source, finish = map(int, input().split())
source = source - 1
finish = finish - 1
Wei = []
for i in range(0, Num):
    Wei.append(list(map(int, input().split())))
for i in range(len(Wei)):
    for j in range(len(Wei[i])):
        if Wei[i][j] == -1:
            Wei[i][j] = 10 ** 10

dist = [10**10] * Num
dist[source] = 0
mark = [False] * Num
INF = 10**10
while True:
    min_dist = INF
    for i in range(Num):
        if not mark[i] and dist[i] < min_dist:
            min_dist = dist[i] 
            min_vertex = i 
    if min_dist == INF: 
        break
    i = min_vertex 
    mark[i] = True 
    for j in range(Num): 
        if dist[i] + Wei[i][j] < dist[j]: 
            dist[j] = dist[i] + Wei[i][j] 

if dist[finish] >= 10**10:
    print(-1)
else:
    print(dist[finish])
