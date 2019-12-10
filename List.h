/*
 * Student Name: Will Parker
 * Student NetID: wcp133
 * Compiler Used: CLion using MinGW
 * Program Description:
 *      Implementation of Node and List Classes needed for the project, very simple;
 */
#include<iostream>
using std::ostream;

class Node {
public:
    int data;
    Node* next;
    explicit Node(int data): data(data), next(nullptr) {};
    Node(int data, Node* next): data(data), next(next) {};
    friend ostream& operator<<(ostream &os, const Node n) {
        os << n.data;
        return os;
    }
};

class List {
private:
public:
    Node *head;
    Node *end;

    int length;
    List(): head(nullptr), end(nullptr), length(0) {};

    void insert(int data) {
        if (head == nullptr) {
            head =  new Node(data);
            end = head;
        }
        else {
            end->next = new Node(data);
            end = end->next;
        }
        length++;
    }

    void insert(List list) {
        for (int i=0; i<list.length; i++) {
            insert(list[i].data);
        }
    }

    bool remove(int data) {
        Node *temp = head;
        Node *parent = nullptr;
        while (temp) {
            if (temp->data == data) {
                if (temp == head) {
                    head = head->next;
                    temp->next = nullptr;
                    delete temp;
                }
                else {
                    parent->next = temp->next;
                    temp->next = nullptr;
                    delete temp;
                }
                length--;
                return true;
            }
            else {
                parent = temp;
                temp = temp->next;
            }
        }
        return false;
    }

    bool find(int data) {
        Node *temp = head;
        while (temp) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    friend ostream& operator<<(ostream &os, const List list) {
        Node* temp = list.head->next;
        os << *list.head;
        while (temp) {
            os << ", " << *temp;
            temp = temp->next;
        }
        return os;
    }

    Node& operator[](int num) {
        if (num < 0 || num > this->length) {
            throw "ERROR: out of range";
        }
        else {
            Node *temp = this->head;
            for (int i=0; i<num; i++) {
                temp = temp->next;
            }
            return *temp;
        }
    }
};
