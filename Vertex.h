/*
 * Student Name: Will Parker
 * Student NetID: wcp133
 * Compiler Used: CLion using MinGW
 * Program Description:
 *      Implementation of Vertex Class needed for the project, very simple;
 */

#include "List.h"

class Vertex {
public:
    int name;
    List adjacent;

    Vertex(int num) {
        name = num;
        adjacent = {};
    };

    friend ostream& operator<<(ostream &os, const Vertex &v) {
        os << v.name;
        return os;
    }
};
