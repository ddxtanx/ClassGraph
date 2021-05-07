#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
class Graph{
    public:     
        Graph();                                                                         //constructors
        Graph(std::vector<Vertex*> vertices);
        Graph(std::vector<Vertex*> vertices, std::vector<Edge> edges);
        Graph(const Graph& ot);
        ~Graph();

        std::vector<Vertex*> & getVertices();   //used for printing and whole graph representation
        std::vector<Edge> & getEdges();

        std::vector<Edge> getEdgesFrom(Vertex* from) const;

        bool vertexInGraph(Vertex* v) const;
        
        double getWeightBetweenVertices(Vertex from, Vertex to) const;              //used in algorithms
        double getWeightBetweenVertices(Edge edge) const;

        //ColoredGraph minimalPrerecChainBetween(ColoredVertex from, ColoredVertex to);          //main function to use for output
        size_t getVerticiesSize() const;
        size_t getEdgesSize() const;
        //iterator for BFS?

        void addVertex(Vertex* vert);
        void addEdge(Vertex* from, Vertex* to, double weight);
        void addEdge(Edge e);
        void makeAcyclic(Vertex* source, bool backwards = false, Vertex* necessaryVertex = nullptr);


        Graph& operator=(const Graph& other);

    private:
        template <typename T>
        class Matrix{
            public:
                Matrix();
                Matrix(int rows, int cols);

                T getVal(int row, int col) const;
                void setVal(int row, int col, T val);

                void resizeMatrix(int rows, int cols);
                
                std::pair<int, int> getDims() const;
            private:
                int getCoordinate(int row, int col) const;
                std::vector<T> matrix_;
                int rows_;
                int cols_;
        };          
        
        Matrix<double> adjacencyMatrix_;

        void copy(const Graph& other);
        void clear();

    protected:
        void resizeAdjMatrix(size_t size);
        std::vector<Vertex*> vertices_;
        std::vector<Edge> edges_;     
};