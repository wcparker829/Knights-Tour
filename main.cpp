/*
 * Student Name: Will Parker
 * Student NetID: wcp133
 * Compiler Used: CLion using MinGW
 * Program Description:
 *      This program implements a modified version of Djikstra's where weights of edges are changing and
 *      edges become directed after they are traversed and a vertex sheds all edges except for one after it is left
 *      this is used to simulate the knight's tour on a 4x3 board
 */

#include "Vertex.h"

using std::cout;
using std::endl;

List tour_4x3(Vertex board[4][3], int adj_matrix[12][12], Vertex *vertices_list[12], int start, bool last);

int main() {
    Vertex board [4][3] = {Vertex(0), Vertex(1), Vertex(2),
                           Vertex(3), Vertex(4), Vertex(5),
                           Vertex(6), Vertex(7), Vertex(8),
                           Vertex(9), Vertex(10), Vertex(11)};

    Vertex *vertices_list[12] = {&board[0][0], &board[0][1], &board[0][2],
                                 &board[1][0], &board[1][1], &board[1][2],
                                 &board[2][0], &board[2][1], &board[2][2],
                                 &board[3][0], &board[3][1], &board[3][2]};

    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<4; k++) {
                for (int l=0; l<3; l++) {
                    if ((i+2 == k && j+1 == l) ||
                        (i+1 == k && j+2 == l) ||
                        (i+2 == k && j-1 == l) ||
                        (i+1 == k && j-2 == l) ||
                        (i-2 == k && j+1 == l) ||
                        (i-1 == k && j+2 == l) ||
                        (i-2 == k && j-1 == l) ||
                        (i-1 == k && j-2 == l)) {
                        board[i][j].adjacent.insert(board[k][l].name);
                    }
                }
            }
        }
    }


    int adj_matrix[12][12];
    for (int i=0; i<4; i++) {
        for(int j=0; j<3; j++) {
            Vertex *v = &board[i][j];
            for (int k=0; k<12; k++) {
                if (v->adjacent.find(k)) {
                    adj_matrix[v->name][k] = vertices_list[k]->adjacent.length;
                }
                else {
                    adj_matrix[v->name][k] = 999;
                }
            }
        }
    }

    cout << "      0 1 2 3 4 5 6 7 8 9 X 11" << endl;
    cout << "------------------------------" << endl;
    for (int i=0;i<12;i++) {
        cout << *vertices_list[i] << " |   ";
        for (int j=0;j<12;j++) {
            cout << adj_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "The knight's tour of a 4x3 board starting in cell 0 is: ";
    cout << tour_4x3(board, adj_matrix, vertices_list, 0, false) << endl << endl;

    cout << "      0 1 2 3 4 5 6 7 8 9 X 11" << endl;
    cout << "------------------------------" << endl;
    for (int i=0;i<12;i++) {
        cout << *vertices_list[i] << " |   ";
        for (int j=0;j<12;j++) {
            cout << adj_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}

List tour_4x3(Vertex board[4][3], int adj_matrix[12][12], Vertex *vertices_list[12],  int start, bool last) {

    List list;
    Vertex *temp = &board[0][0];
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j].name == start) {
                temp = &board[i][j];

            }
        }
    }

    list.insert(temp->name);

    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            board[i][j].adjacent.remove(temp->name);
        }
    }
    for (int i=0; i<4; i++) {
        for (int j = 0; j < 3; j++) {
            Vertex *v = &board[i][j];
            for (int k = 0; k < 12; k++) {
                if (v->adjacent.find(k)) {
                    adj_matrix[v->name][k] = vertices_list[k]->adjacent.length;
                } else {
                    adj_matrix[v->name][k] = 999;
                }
            }
        }
    }

    int next_weight = 1000;
    int next = temp->name;
    for (int i=0; i<12; i++) {
        if (adj_matrix[temp->name][i] < next_weight) {
            next_weight = adj_matrix[temp->name][i];
            next = i;
        }
    }

    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j].name == next) {
                temp = &board[i][j];
            }
        }
    }

    if (temp->adjacent.length > 0) {
        list.insert(tour_4x3(board, adj_matrix, vertices_list, temp->name, false));
    }
    else if (temp->adjacent.length == 0 && last == false) {
        list.insert(tour_4x3(board, adj_matrix, vertices_list, temp->name, true));
    }
        return list;
}