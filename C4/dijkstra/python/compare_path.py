#!/usr/bin/env python3
import subprocess
import sys

INT_MAX = 2**31 - 1
ARROW = "\u2192"


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
            # Match C's adjacency order: insert at head.
            graph[p].insert(0, (q, w))
            graph[q].insert(0, (p, w))
    return graph


def dijkstra_with_prev(graph, source: int):
    n = len(graph)
    dist = [INT_MAX] * n
    prev = [-1] * n
    visited = [False] * n

    dist[source] = 0

    for _ in range(n):
        u = -1
        best = INT_MAX
        for i in range(n):
            if not visited[i] and dist[i] < best:
                best = dist[i]
                u = i
        if u < 0:
            break
        visited[u] = True

        for v, w in graph[u]:
            if visited[v]:
                continue
            nd = dist[u] + w
            if nd < dist[v]:
                dist[v] = nd
                prev[v] = u

    return dist, prev


def reconstruct_path(prev, source: int, target: int):
    if target == source:
        return [source]
    if prev[target] < 0:
        return []
    path = [target]
    curr = target
    while curr != source:
        curr = prev[curr]
        if curr < 0:
            return []
        path.append(curr)
    path.reverse()
    return path


def format_path(path):
    if not path:
        return ""
    out = str(path[0])
    for node in path[1:]:
        out += f" {ARROW} {node}"
    return out


def run_c_lines(binary_path: str, graph_path: str, target: int):
    result = subprocess.run(
        [binary_path, graph_path, str(target)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    lines = [line.strip() for line in result.stdout.splitlines() if line.strip()]
    if len(lines) >= 2:
        return lines[-2], lines[-1]
    if len(lines) == 1:
        return lines[0], ""
    return "", ""


def main():
    if len(sys.argv) < 3:
        print("usage: compare_path.py <graph_file> <target> [target ...]", file=sys.stderr)
        return 1

    graph_file = sys.argv[1]
    targets = [int(t) for t in sys.argv[2:]]

    graph = read_graph(graph_file)
    dist, prev = dijkstra_with_prev(graph, 0)

    for t in targets:
        if not (0 <= t < len(graph)):
            print(f"t={t} OUT_OF_RANGE")
            continue
        path = reconstruct_path(prev, 0, t)
        py_dist = str(dist[t])
        py_path = format_path(path)
        c_dist, c_path = run_c_lines("./mydijkstra", graph_file, t)
        if c_dist == py_dist and c_path == py_path:
            print(f"t={t} OK ({py_dist} | {py_path})")
        else:
            print(f"t={t} MISMATCH")
            print(f"  C:  {c_dist} | {c_path}")
            print(f"  Py: {py_dist} | {py_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
