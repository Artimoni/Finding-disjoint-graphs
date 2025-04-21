#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <string>
#include <sstream>
#include <memory>

class Node {
public:
    std::string name;
    std::set<std::shared_ptr<Node>> neighbours;
    Node(const std::string& name) : name(name) {}
};

class Graph {
private:
    std::set<std::shared_ptr<Node>> nodes;
public:
    void addEdge(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);
    std::shared_ptr<Node> getOrCreateNode(const std::string& name);
    std::vector<std::set<std::shared_ptr<Node>>> findConnectedComponents();
    void clear();
};

Graph readGraphFromFile(const std::string& filename);
void saveComponentToFile(const std::set<std::shared_ptr<Node>>& component, int index);

#endif