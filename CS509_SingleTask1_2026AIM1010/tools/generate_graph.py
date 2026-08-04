#!/usr/bin/env python3
"""
Generate a random undirected graph in the adjacency-list text format used
throughout CS509 Assignment 1 (sections 6.1 and 7.1).

Unweighted format:
    V E
    u0 degree n1 n2 ...
    ...
    SOURCE s

Weighted format (edge_weight follows each neighbour):
    V E
    u0 degree n1 w1 n2 w2 ...
    ...
    SOURCE s
"""
import random
import sys


def generate(V, avg_degree, path, weighted=False, seed=None, source=0,
             min_weight=1, max_weight=20):
    if seed is not None:
        random.seed(seed)

    adj = [set() for _ in range(V)]
    target_edges = max(V - 1, int(V * avg_degree / 2))

    # Start with a random spanning structure so the graph stays connected.
    for v in range(1, V):
        u = random.randint(0, v - 1)
        adj[v].add(u)
        adj[u].add(v)

    edges_so_far = sum(len(s) for s in adj) // 2
    attempts = 0
    while edges_so_far < target_edges and attempts < target_edges * 20:
        u = random.randint(0, V - 1)
        v = random.randint(0, V - 1)
        attempts += 1
        if u == v or v in adj[u]:
            continue
        adj[u].add(v)
        adj[v].add(u)
        edges_so_far += 1

    weight_of = {}
    if weighted:
        for u in range(V):
            for v in adj[u]:
                key = (min(u, v), max(u, v))
                if key not in weight_of:
                    weight_of[key] = random.randint(min_weight, max_weight)

    with open(path, "w") as f:
        f.write(f"{V} {edges_so_far}\n")
        for u in range(V):
            neighbours = sorted(adj[u])
            if weighted:
                parts = []
                for v in neighbours:
                    key = (min(u, v), max(u, v))
                    parts.append(f"{v} {weight_of[key]}")
                f.write(f"{u} {len(neighbours)} " + " ".join(parts) + "\n" if neighbours
                        else f"{u} 0\n")
            else:
                f.write(f"{u} {len(neighbours)} " + " ".join(map(str, neighbours)) + "\n" if neighbours
                        else f"{u} 0\n")
        f.write(f"SOURCE {source}\n")

    return V, edges_so_far


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: generate_graph.py <V> <output_path> <unweighted|weighted> [avg_degree] [seed]")
        sys.exit(1)
    V = int(sys.argv[1])
    out = sys.argv[2]
    weighted = sys.argv[3] == "weighted"
    avg_degree = float(sys.argv[4]) if len(sys.argv) > 4 else 4.0
    seed = int(sys.argv[5]) if len(sys.argv) > 5 else 42
    v, e = generate(V, avg_degree, out, weighted=weighted, seed=seed)
    print(f"Wrote {out}: V={v}, E={e}, weighted={weighted}")
