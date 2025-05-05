#include "graph.h"

void Graph::addEdge(Node* a, Node* b) {
    a->neighbours.insert(b);
    b->neighbours.insert(a);
}

Node* Graph::getOrCreateNode(const std::string& name) {
    for (auto node : nodes) {
        if (node->name == name) return node;
    }
    
    Node* newNode = new Node(name);
    nodes.insert(newNode);
    return newNode;
}

std::set<std::set<Node*>> Graph::findConnectedComponents() {
    std::set<std::set<Node*>> components;  
    std::set<Node*> visited;

    for (auto node : nodes) {
        if (visited.find(node) == visited.end()) {
            std::set<Node*> component;  
            std::set<Node*> toVisit; 
            toVisit.insert(node);

            while (!toVisit.empty()) {
                Node* current = *toVisit.begin(); 
                toVisit.erase(current);  

                component.insert(current);  

                for (auto neighbour : current->neighbours) {
                    if (visited.find(neighbour) == visited.end()) {
                        visited.insert(neighbour);  
                        toVisit.insert(neighbour);  
                    }
                }
            }

            components.insert(component);  
        }
    }

    return components;
}

void Graph::clear() {
    for (auto node : nodes) {
        delete node;
    }
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

        Node* srcNode = graph.getOrCreateNode(source);
        Node* tgtNode = graph.getOrCreateNode(target);

        graph.addEdge(srcNode, tgtNode);
    }

    return graph;
}

void saveComponentToFile(const std::set<Node*>& component, int index) {
    std::string filename = "subgraph_" + std::to_string(index) + ".txt";
    std::ofstream out(filename);

    if (!out.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }

    out << "Source\tTarget\n";
    std::set<std::pair<std::string, std::string>> edges;  

    for (auto node : component) {
        for (auto neighbour : node->neighbours) {
            if (node->name <= neighbour->name) {  
                edges.insert({ node->name, neighbour->name });
            }
        }
    }

    for (const auto& edge : edges) {
        out << edge.first << "\t" << edge.second << "\n";
    }
}
