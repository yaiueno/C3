#!/usr/bin/env python3
import heapq
import sys

INT_MAX = 2**31 - 1


def read_graph(path: str):
    with open(path, "r", encoding="ascii") as f:
        first = f.readline().strip()
        if not first:
            raise ValueError("empty input")
        n = int(first)
        graph = [[] for _ in range(n)]
        for line in f:
            line = line.strip()
            if not line:
                continue
            p, q, w = map(int, line.split())
            graph[p].append((q, w))
            graph[q].append((p, w))
    return graph


def dijkstra(graph, source: int):
    n = len(graph)
    dist = [INT_MAX] * n
    dist[source] = 0
    pq = [(0, source)]
    visited = [False] * n

    while pq:
        d, u = heapq.heappop(pq)
        if visited[u]:
            continue
        visited[u] = True
        for v, w in graph[u]:
            nd = d + w
            if not visited[v] and nd < dist[v]:
                dist[v] = nd
                heapq.heappush(pq, (nd, v))

    return dist


def main():
    if len(sys.argv) < 3:
        print("usage: compare_dijkstra.py <graph_file> <target> [source]", file=sys.stderr)
        return 1

    graph_file = sys.argv[1]
    target = int(sys.argv[2])
    source = int(sys.argv[3]) if len(sys.argv) >= 4 else 0

    graph = read_graph(graph_file)
    if not (0 <= source < len(graph)):
        raise ValueError("source out of range")
    if not (0 <= target < len(graph)):
        raise ValueError("target out of range")

    dist = dijkstra(graph, source)
    print(dist[target])
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
