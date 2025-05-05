#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream> //Удалены нерабочие библиотеки(<queue>)

class Node {
public:
    std::string name;                     
    std::set<Node*> neighbours;

    Node(const std::string& name) : name(name) {}  
    ~Node() = default;  //Конструктор и Деконструктор
};

class Graph {
private:
    std::set<Node*> nodes;  //Все узлы
public:
    ~Graph() { clear(); }  //Ручная отчистка

    void addEdge(Node* a, Node* b);  
    Node* getOrCreateNode(const std::string& name);  
    std::set<std::set<Node*>> findConnectedComponents();  
    void clear(); 
};

Graph readGraphFromFile(const std::string& filename); 
void saveComponentToFile(const std::set<Node*>& component, int index); 

#endif
