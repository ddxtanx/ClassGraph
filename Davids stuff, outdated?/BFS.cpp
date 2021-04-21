#include "BFS.h"


BFS::Iterator::Iterator();
BFS::Iterator::Iterator(const ColoredGraph * graph, ColoredVertex startPoint, BFS * traversal);

FBS::Iterator & BFS::Iterator::operator++()
{}
ColoredVertex & BFS::Iterator::operator*()
{}
bool BFS::Iterator::operator!=(const Iterator &other)
{}
bool BFS::Iterator::isDone() const
{}

////////////////////////////////////////////////////////////////////////////////

BFS::BFS(const ColoredGraph * graph, ColoredVertex startPoint)
{}

Iterator BFS::begin()
{}
Iterator BFS::end()
{}

void BFS::add(const ColoredVertex & vert)
{}
ColoredVertex BFS::pop()
{}
ColoredVertex BFS::peek() const
{}
bool BFS::empty() const
{}