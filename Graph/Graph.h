#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <unordered_map>
#include <map>
class Graph{
    public:     
        /**
         * @brief Construct a new empty graph object
         * 
         */
        Graph();                                                                         //constructors
        /**
         * @brief Construct a new Graph object with only vertices.
         * 
         * @param vertices: Vertices to include in the graph
         * @info: Graph is totally disconnected
         */
        Graph(std::vector<Vertex*> vertices);
        /**
         * @brief Construct a new Graph object via vertices and edges
         * 
         * @param vertices:Vertices to include
         * @param edges:Edges to include
         */
        Graph(std::vector<Vertex*> vertices, std::vector<Edge> edges);
        /**
         * @brief Construct a new Graph object from another graph object
         * 
         * @param ot: Graph object to copy
         */
        Graph(const Graph& ot);
        /**
         * @brief Destroy the Graph object
         * 
         */
        ~Graph();
        /**
         * @brief Get the Vertices object, with reference
         * 
         * @return std::vector<Vertex*>& Reference to list of vertices
         */
        std::vector<Vertex*> & getVertices();   //used for printing and whole graph representation
        /**
         * @brief Get the Edges object
         * 
         * @return std::vector<Edge>& Reference to list of edges 
         */
        std::vector<Edge> & getEdges();
        /**
         * @brief Get the Layer Counts_ object
         * 
         * @return std::vector<int>& Reference to layer counts
         */
        std::vector<int> & getLayerCounts_();
        /**
         * @brief Get the Edges From a given vertex
         * 
         * @param from: Vertex to get edges from
         * @return std::vector<Edge>: List of all edges e such that e.getFrom = from
         */
        std::vector<Edge> getEdgesFrom(Vertex* from) const;

        /**
         * @brief Tests whether or not vertex is in graph
         * 
         * @param v Vertex to test
         * @return true: vertex is in graph
         * @return false: Vertex is not in graph
         */
        bool vertexInGraph(Vertex* v) const;

        /**
         * @brief Get the size of vertices list
         * 
         * @return size_t Number of vertices in graph
         */
        size_t getVerticesSize() const;
        /**
         * @brief Get the size of edges list
         * 
         * @return size_t Number of edges in graph
         */
        size_t getEdgesSize() const;

        /**
         * @brief Add vertex to graph
         * 
         * @param vert Vertex to add to graph
         */
        void addVertex(Vertex* vert);
        /**
         * @brief Add edge to graph via vertices
         * 
         * @param from Vertex to start edge from
         * @param to Vertex to end edge at
         */
        void addEdge(Vertex* from, Vertex* to);
        /**
         * @brief Add edge to graph
         * 
         * @param e Edge to add
         */
        void addEdge(Edge e);
        
        /**
         * @brief Initialize the vertex layers
         * 
         */
        void initLayers();
        /**
         * @brief Increase the layer count
         * 
         * @param layer 
         */
        void increaseLayerCount(unsigned layer);
        /**
         * @brief Get the Layers object
         * 
         * @return std::vector<int> 
         */
        std::vector<int> getLayers();

        /**
         * @brief Generate the betweennessCentrality map for ALL vertices
         * 
         * @param backwards Whether or not to traverse the graph forwards or backwards (default: false, so forwards)
         * @param normalize Whether or not to normalize the betweenness centralities between [0,1] (default: true, so normalize)
         */
        void generateBetweennessCentrality(bool backwards=false, bool normalize=true);
        /**
         * @brief Get the Betweenness Centrality of a given vertex
         * 
         * @param v The vertex to get the betweenness centrality of
         * @return double the betweenness centrality (possibly normalized)
         * @details You MUST run generateBetweennessCentrality before running this
         */
        double getBetweennessCentrality(Vertex* v);
        /**
         * @brief Get the Betweenness Centrality map
         * 
         * @return std::unordered_map<Vertex, double>* Pointer to the betweenness centrality map
         * @details You MUST run generateBetweennessCentrality before running this 
         */
        std::unordered_map<Vertex, double>* getBetweennessCentrality();

        /**
         * @brief Assignment operator
         * 
         * @param other Graph to assign value of
         * @return Graph& Next graph for assignment chaining
         */
        Graph& operator=(const Graph& other);
        
        /**
         * @brief Transform the graph into a form enterable into Wolfram Mathematica
         * 
         * @param backwards Whether or not to traverse the graph forwards or backwards (default: false, so forwards)
         * @return std::string The mathematica form of the graph
         */
        std::string toMathematicaForm(bool backwards = false);

    private:
    /**
     * @brief Matrix class to provide quick and efficient 2D array storage
     * 
     * @tparam T printable and default valuable type of matrix entries
     */
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