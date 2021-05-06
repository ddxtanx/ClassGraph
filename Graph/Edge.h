#pragma once
#include "Vertex.h"
class Edge{
    public:
        Edge();                                                      //constructors
        Edge(Vertex* from, Vertex* to);
        Edge(Vertex* from, Vertex* to, double weight);

        Vertex* getFrom() const;           //getter and setter functions
        Vertex* getTo() const;
        double getWeight() const;
        void setFrom(Vertex* newFrom);
        void setTo(Vertex* newTo);
        void setWeight(double newWeight);

        bool isValidEdge() const; //checks to see if from and too point places

        bool operator<(const Edge& ot) const;
        bool operator==(const Edge& ot) const;

        friend std::ostream& operator<<(std::ostream& os, const Edge& e){
            os << "{" << e.from_ << "," << e.to_ << "," << e.weight_ << "}";
            return os;
        }

    private:
        Vertex* from_;       //edge data
        Vertex* to_;
        double weight_;
};

namespace std{
    template<>
    struct hash<Edge>{
        size_t operator()(const Edge& e) const{
            size_t h1 = e.getFrom() -> getId();
            size_t h2 = e.getTo() -> getId();
            return (h1 ^ (h2 << 1)) >> 1;
        }
    };
};