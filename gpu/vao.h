#pragma once
#include <map>
#include "datastructures.h"

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void set(size_t binding, size_t vboId, size_t itemSize, size_t stride, size_t offset);

    std::map<uint32_t, BindingDescription> getBindingMap() const;

    void print();

private:
    std::map<uint32_t, BindingDescription> mBindingMap;
};