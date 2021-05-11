#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <unordered_map>
#include <map>
class Graph{
    public:     
        Graph();                                                                         //constructors
        Graph(std::vector<Vertex*> vertices);
        Graph(std::vector<Vertex*> vertices, std::vector<Edge> edges);
        Graph(const Graph& ot);
        ~Graph();

        std::vector<Vertex*> & getVertices();   //used for printing and whole graph representation
        std::vector<Edge> & getEdges();
        std::vector<int> & getLayerCounts_();
        std::vector<Edge> getEdgesFrom(Vertex* from) const;

        bool vertexInGraph(Vertex* v) const;

        //ColoredGraph minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);          //main function to use for output
        size_t getVerticesSize() const;
        size_t getEdgesSize() const;

        void addVertex(Vertex* vert);
        void addEdge(Vertex* from, Vertex* to);
        void addEdge(Edge e);
        void makeAcyclic(Vertex* source, bool backwards = false, Vertex* necessaryVertex = nullptr);
        void initLayers();
        void increaseLayerCount(unsigned layer);
        std::vector<int> getLayers();

        double getBetweennessCentrality(Vertex* v);
        std::unordered_map<Vertex, double>* getBetweennessCentrality();


        Graph& operator=(const Graph& other);
        void generateBetweennessCentrality(bool backwards=false, bool normalize=true);

    private:
        template <typename T>
        class Matrix{
            public:
                Matrix();
                Matrix(int rows, int cols, T defVal = T());

                T getVal(int row, int col) const;
                void setVal(int row, int col, T val);

                void resizeMatrix(int rows, int cols);
                
                std::pair<int, int> getDims() const;

                friend std::ostream& operator<<(std::ostream& os, const Matrix& mat){
                    auto dims = mat.getDims();
                    int rows = dims.first;
                    int cols = dims.second;
                    for(int i = 0; i<rows; i++){
                        for(int j = 0; j<cols; j++){
                            T v = mat.getVal(i,j);
                            os << v << ",";
                        }
                        os<<std::endl;
                    }
                    return os;
                }

                std::string toString() const;
            private:
                int getCoordinate(int row, int col) const;
                std::vector<T> matrix_;
                int rows_;
                int cols_;
        };          
        
        Matrix<double> adjacencyMatrix_;
        std::unordered_map<Vertex, double> betweennessCentrality_;


        void copy(const Graph& other);
        void clear();

    protected:
        void resizeAdjMatrix(size_t size);
        std::vector<Vertex*> vertices_;
        std::vector<Edge> edges_;  
        std::vector<int> layerCounts_;   
};