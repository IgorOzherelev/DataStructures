#BFS adjency-list 

def BFS(Graph, source, num):
    
    prop = []
    
    for i in range(num):    
        prop.append([True, 0, 0])
        
     #ver is closed/white, dist, pred
        
    prop[source][0] = 0.5 #source is gray/checked
    prop[source][1] = 0
    prop[source][2] = -1
    
    queue = []
    queue.append(source)
    
    while len(queue)!= 0:
        cur = queue[-1]
        del queue[-1:]
        
        for ver in Graph[cur]:
            if prop[ver][0] == False:
                prop[ver][0] == 0.5
                prop[ver][1] += 1
                prop[ver][2] = cur
                queue.append(ver)
        
        prop[cur][0] = True
    
    return prop[num - 1][1] #returns distance between source and last vertice
        
if __name__ == '__main__':
    source = 0
    num = int(input())
    Graph = []
    for i in range(num):
        Graph.append(list(map(int, input().split())))
        
    print(BFS(Graph, source, num))
