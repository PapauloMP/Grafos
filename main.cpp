#include <iostream>
#include <sstream>
#include <vector>
#include "Headers/Node.h"
#include "Headers/Graph.h"
#include "Headers/Menu.h"

vector<EdgeStruct>* readTxt(const string& path, bool isWeighted);
vector<EdgeStruct>* loadGraph(Graph* graph, const string& inputFilePath,bool isWeightedEdge);
void printGraph(Graph* grafo, vector<EdgeStruct>* ListEdge);

int main(int argc, char** argv) {

/*      TESTES BÁSICOS
    Node* no = new Node(0, "no1", 1);
    Node* no2 = new Node(1, "no2", 2);
    no->insertEdge(1, 5);
    cout << "No id:"<< no->getId() << endl;
    cout << "No id externo: "<< no->getIdExternal() << endl;
    cout << "No peso: "<< no->getWeight() << endl;

    cout << "No2 id:"<< no2->getId() << endl;
    cout << "No2 id externo: "<< no2->getIdExternal() << endl;
    cout << "No2 peso: "<< no2->getWeight() << endl;

    cout << "Aresta target_id (deve ser 1): " << no->getFirstEdge()->getTargetId() << endl;
    cout << "Aresta peso (5): " << no->getLastEdge()->getWeight() << endl;
    Node* no3 = new Node(2, "no3", 3);
    no->insertEdge(2, 3);
    //no->removeAllEdges();
    cout << "Aresta target_id (deve ser 2): " << no->getLastEdge()->getTargetId() << endl;
    cout << "Aresta peso (3): " << no->getLastEdge()->getWeight() << endl;
    cout << no->getFirstEdge()->getNextEdge()->getTargetId() << endl;
    cout << "Testes" << endl;
    cout << no->hasEdgeBetween(2)->getTargetId() << endl;
    cout << no->searchEdge(1) << endl;
    cout << "Teste 3" << endl;
    cout << no2->removeEdge(0, 0, no) << endl;
    cout << no->searchEdge(2) << endl;
    cout << no3->getIdExternal() << endl;*/
/*
    Graph* grafo = new Graph(false,false,false);
    grafo->insertEdge("Marcos", "Paulo", 33);
    cout << "Teste 1" << endl;
    cout << "NO 0: " << grafo->getFirstNode()->getIdExternal() << endl;
    cout << "NO 0 id: " << grafo->getFirstNode()->getId() << endl;
    cout << "NO 1: " << grafo->getLastNode()->getIdExternal() << endl;
    cout << "NO 1 id: " << grafo->getLastNode()->getId() << endl;
    cout << "Peso da primeira aresta: " << grafo->getFirstNode()->getFirstEdge()->getWeight() << endl;
    cout << "InsertionPosition: "<< grafo->getInsertionPosition() << endl; // privado, ta acrescentando 1 nele mesmo
    cout << "Ordem: "<< grafo->getOrder() << endl;
    cout << "Numero de arestas: " << grafo->getNumberEdges() << endl;
    grafo->removeNode(0);
    //grafo->removeNode(1);
    grafo->removeNode(0);
    cout << "Teste 2" << endl;
    cout << "NO 0: " << grafo->getFirstNode()->getIdExternal() << endl;
    cout << "NO 0 id: " << grafo->getFirstNode()->getId() << endl;
    cout << "NO 1: " << grafo->getLastNode()->getIdExternal() << endl;
    cout << "NO 1 id: " << grafo->getLastNode()->getId() << endl;
    cout << "Peso da primeira aresta: " << grafo->getFirstNode()->getFirstEdge()->getTargetId() << endl;
    cout << "InsertionPosition: "<< grafo->getInsertionPosition() << endl;
    cout << "Ordem: "<< grafo->getOrder() << endl;
    cout << "Numero de arestas: " << grafo->getNumberEdges() << endl;//*/
/*    cout << grafo->searchNode(1)<< endl;
    cout << grafo->searchNodeFromExternalId("Marcos")<< endl;
    cout << grafo->getNode(0)->getIdExternal() << endl;
    cout << grafo->getNodeFromExternalId("Marcos")->getIdExternal() << endl;
    grafo->indexId();
    cout << grafo->mapInternalIdToExternalId[0] << endl;
    cout << grafo->mapInternalIdToExternalId[1] << endl;*/
/*
    cout << "Ordem: " << grafo->getOrder() << endl;
    cout << "Arestas: " << grafo->getNumberEdges() << endl;
    //grafo->removeNode("1");
    cout << "Ordem: " << grafo->getOrder() << endl;
    cout << "Arestas: " << grafo->getNumberEdges() << endl;
*/

    if(argc != 6){
        cout << "ERRO: parametros nao correspondem com a sintaxe do comando" << endl;
        cout << "Sintaxe correta: ./exec <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>" << endl;
        abort();
    }

    string inputFilePath = argv[1];
    string outputFilePath = argv[2];
    bool isDirected = stoi(argv[3]);
    bool isWeightedEdge = stoi(argv[4]);
    bool isWeightedNode = stoi(argv[5]);
    auto* grafo = new Graph(isDirected, isWeightedEdge, isWeightedNode);

    loadGraph(grafo, inputFilePath, isWeightedEdge);

    Menu* menu = new Menu(grafo, outputFilePath);
    //menu->printGraph();
    menu->start();

    return 0;
}

vector<EdgeStruct>* loadGraph(Graph* graph, const string& inputFilePath, bool isWeighted){
    auto ListEdge = readTxt(inputFilePath, isWeighted);
    string edgeShape = graph->getDirected() ? "->" : "--";

    if(isWeighted) {
        for (auto &i: *ListEdge) {
            cout << i.fromNode << edgeShape << i.toNode << " = " << i.weight << endl;
            graph->insertEdge(i.fromNode, i.toNode, i.weight);
        }
    }
    else{
        for (auto& i : *ListEdge){
            cout << i.fromNode << edgeShape << i.toNode << " = " << 1 << endl;
            graph->insertEdge(i.fromNode, i.toNode, 1);
        }
    }
    return ListEdge;
}

vector<EdgeStruct>* readTxt(const string& path, bool isWeighted){
    try {
        auto ListEdge = new vector<EdgeStruct>();

        ifstream file;
        file.open(path);

        if(file.is_open()){

            string line;
            getline(file, line);

            auto edge = EdgeStruct();
            string toNode, fromNode, weight;
            while (getline(file, line)){

                stringstream ss(line);

                getline(ss, fromNode, ' ');
                getline(ss, toNode, ' ');

                if(isWeighted){
                    getline(ss, weight, ' ');
                    edge.weight = stof(weight);
                }

                edge.fromNode = fromNode;
                edge.toNode = toNode;

                ListEdge->push_back(edge);
            }

            return ListEdge;
        }else{
            cout << "Erro ao tentar abrir o arquivo: " << path;
            abort();
        }
    } catch (exception &e) {

    }
    return nullptr;
}

void printGraph(Graph* grafo, vector<EdgeStruct>* ListEdge){
    for (auto& i : *ListEdge){
        cout << i.fromNode << " -> " << i.toNode << " = " << i.weight << endl;
        grafo->insertEdge(i.fromNode, i.toNode, i.weight);
    }
}