def DFS(Graph, time):
    for i in range(num):
        prop.append([False, 0, 0, -1])
    
    for u in range(0, num):
        if prop[u][0] == False:
            DFS_visit(Graph, u)
                
def DFS_visit(Graph, u, time):
    time += 1
    prop[u][1] = time
    prop[u][0] = 0.5
    
    for ver in Graph[u]:
        if prop[ver][0] == False:
            prop[ver][3] = u 
            DFS_visit(Graph, ver)
            
    prop[u][0] = True
    time += 1
    prop[u][2] = time


if __name__ == '__main__':
    num = int(input())
    time = 0
    Graph = []
    prop = []
    for i in range(num):
        Graph.append(list(map(int, input().split())))
    DFS(Graph, time)
