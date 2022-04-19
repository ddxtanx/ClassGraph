#pragma once
#include "Vertex.h"
class Edge{
    public:
        /**
         * @brief Construct a new Edge object
         * 
         * @details The to and from nodes are null
         */
        Edge();                                                      //constructors
        /**
         * @brief Construct a new Edge object
         * 
         * @param from: Vertex edge starts from
         * @param to: Vertex edge points to
         */
        Edge(Vertex* from, Vertex* to);

        /**
         * @brief Gets the vertex the edge points from
         * 
         * @return Vertex*: Initial vertex
         */
        Vertex* getFrom() const;           //getter and setter functions
        
        /**
         * @brief Gets the vertex the edge points to
         * 
         * @return Vertex*: Terminal vertex
         */
        Vertex* getTo() const;

        /**
         * @brief Set the from vertex
         * 
         * @param newFrom: New initial vertex
         */
        void setFrom(Vertex* newFrom);
        
        /**
         * @brief Set the to vertex
         * 
         * @param newTo: New terminal vertex
         */
        void setTo(Vertex* newTo);

        /**
         * @brief Returns if the edge points to valid vertices
         * 
         * @return true: The edge's initial and terminal vertex pointers are non-null
         * @return false: There is one null initial or terminal point
         */
        bool isValidEdge() const; //checks to see if from and too point places

        /**
         * @brief Edge equality: if edges start and finish at same vertices
         * 
         * @param ot: Other edge
         * @return true: The edges start and end at the same vertices
         * @return false: The edges differ
         */
        bool operator==(const Edge& ot) const;

        bool operator<(const Edge& ot) const;
        /**
         * @brief Inserts the edge into a string stream
         * 
         * @param os: Stream to insert to
         * @param e: Edge to insert
         * @return std::ostream&: Stream with edge inserted
         */
        friend std::ostream& operator<<(std::ostream& os, const Edge& e){
            os << "{" << e.from_ << "," << e.to_ << "}";
            return os;
        }

    private:
        /**
         * @brief From vertex
         * 
         */
        Vertex* from_;       //edge data
        /**
         * @brief To vertex
         * 
         */
        Vertex* to_;
};

namespace std{
    /**
     * @brief Hashes a edge for use in unordered_map
     * 
     * @tparam None 
     */
    template<>
    struct hash<Edge>{
        /**
         * @brief Hashes edge
         * 
         * @param e Edge to hash
         * @return size_t Hash value of edge
         */
        size_t operator()(const Edge& e) const{
            size_t h1 = e.getFrom() -> getId();
            size_t h2 = e.getTo() -> getId();
            return (h1 ^ (h2 << 1)) >> 1; //Edge is hashed by combining hashes of the vertices in the edge
        }
    };
};