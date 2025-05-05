#include "graph.h"
#include <iostream>

int main() {
    try {
        Graph graph = readGraphFromFile("TestGraph.txt");
        
        auto components = graph.findConnectedComponents();

        std::cout << "Found " << components.size() << " connected components\n";

        int index = 1;
        for (const auto& component : components) {
            saveComponentToFile(component, index++);
            std::cout << "Saved component " << index << " with " << component.size() << " nodes\n";
        } //Сохранение в файл

        graph.clear(); //Реализовал ручное удаление вместо умных указателей 
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
