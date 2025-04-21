#include "graph.h"

void Graph::addEdge(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
    a->neighbours.insert(b);
    b->neighbours.insert(a);
}

std::shared_ptr<Node> Graph::getOrCreateNode(const std::string& name) {
    for (const auto& node : nodes) {
        if (node->name == name) return node;
    }
    auto newNode = std::make_shared<Node>(name);
    nodes.insert(newNode);
    return newNode;
}

std::vector<std::set<std::shared_ptr<Node>>> Graph::findConnectedComponents() {
    std::vector<std::set<std::shared_ptr<Node>>> components;
    std::set<std::shared_ptr<Node>> visited;

    for (const auto& node : nodes) {
        if (visited.find(node) == visited.end()) {
            std::set<std::shared_ptr<Node>> component;
            std::queue<std::shared_ptr<Node>> q;
            q.push(node);
            visited.insert(node);

            while (!q.empty()) {
                auto current = q.front();
                q.pop();
                component.insert(current);

                for (const auto& neighbour : current->neighbours) {
                    if (visited.find(neighbour) == visited.end()) {
                        visited.insert(neighbour);
                        q.push(neighbour);
                    }
                }
            }
            components.push_back(component);
        }
    }
    return components;
}

void Graph::clear() {
    nodes.clear();
}

Graph readGraphFromFile(const std::string& filename) {
    Graph graph;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return graph;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string source, target;

        if (!(ss >> source >> target)) {
            std::cerr << "Warning: Invalid line format: " << line << std::endl;
            continue;
        }

        auto srcNode = graph.getOrCreateNode(source);
        auto tgtNode = graph.getOrCreateNode(target);
        graph.addEdge(srcNode, tgtNode);
    }

    return graph;
}

void saveComponentToFile(const std::set<std::shared_ptr<Node>>& component, int index) {
    std::string filename = "subgraph_" + std::to_string(index) + ".txt";
    std::ofstream out(filename);

    if (!out.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }

    out << "Source\tTarget\n";
    std::set<std::pair<std::string, std::string>> edges;

    for (const auto& node : component) {
        for (const auto& neighbour : node->neighbours) {
            if (node->name <= neighbour->name) {
                edges.insert({ node->name, neighbour->name });
            }
        }
    }

    for (const auto& edge : edges) {
        out << edge.first << "\t" << edge.second << "\n";
    }
}