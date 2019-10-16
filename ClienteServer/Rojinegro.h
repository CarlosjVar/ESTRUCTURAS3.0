#ifndef ROJINEGRO_H_INCLUDED
#define ROJINEGRO_H_INCLUDED
#include "AA.h"
#include <iostream>
#include <string>
using namespace std;


struct Node {
    string nombre;
    int cantidadGondola;
    int precio;
	int data; // holds the key
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;


class RBTree {

private:
	NodePtr root;

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer
    void initializeNULLNode(NodePtr node, NodePtr parent) ;

    void preOrderHelper(NodePtr node) ;

    void inOrderHelper(NodePtr node) ;

    void postOrderHelper(NodePtr node) ;

    NodePtr searchTreeHelper(NodePtr node, int key) ;

	// fix the rb tree modified by the delete operation
    void fixDelete(NodePtr x) ;

    void rbTransplant(NodePtr u, NodePtr v);

    void deleteNodeHelper(NodePtr node, int key) ;

	// fix the red-black tree
    void fixInsert(NodePtr k);

    void printHelper(NodePtr root, string indent, bool last) ;

public:

    RBTree() ;
    RBTree(NodePtr raiz) ;
	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
    void preorder() ;

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
    void inorder() ;
	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
    void postorder() ;

	// search the tree for the key k
	// and return the corresponding node
    NodePtr searchTree(int k) ;

	// find the node with the minimum key
    NodePtr minimum(NodePtr node) ;
	// find the node with the maximum key
    NodePtr maximum(NodePtr node) ;

	// find the successor of a given node
    NodePtr successor(NodePtr x) ;
	// find the predecessor of a given node
    NodePtr predecessor(NodePtr x) ;

	// rotate left at node x
    void leftRotate(NodePtr x) ;

	// rotate right at node x
    void rightRotate(NodePtr x) ;

	// insert the key to the tree in its appropriate position
	// and fix the tree
    void insert(int key,string nombre, int precio, int cantidadGondola);
    void rellenarGondolaRN (NodePtr raiz, int codigoPasillo, int codigoProducto, AA inventario);

    NodePtr getRoot();
    void prettyPrint();
    void deleteNode(int s);
	friend class Binario;

};

#endif
