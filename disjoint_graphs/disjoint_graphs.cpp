#include "graph.h"
#include <iostream>

int main() {
    try {
        Graph graph = readGraphFromFile("TestGraph.txt");
        auto components = graph.findConnectedComponents();

        std::cout << "Found " << components.size() << " connected components\n";

        for (size_t i = 0; i < components.size(); ++i) {
            saveComponentToFile(components[i], i + 1);
            std::cout << "Saved component " << (i + 1) << " with "
                << components[i].size() << " nodes\n";
        }

        graph.clear();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}