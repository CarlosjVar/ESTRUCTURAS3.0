#include "Rojinegro.h"
void RBTree::rellenarGondolaRN (NodePtr raiz, int codigoPasillo, int codigoProducto, AA inventario){
    if (raiz==NULL){
        return;
    }
    rellenarGondolaRN(raiz->right,codigoPasillo,codigoProducto, inventario);
    rellenarGondolaRN(raiz->left,codigoPasillo,codigoProducto, inventario);
    if (raiz->cantidadGondola>2){
        return;
    }
    int recarga;
    string opcion;
    cout<<"Quedan ";
    cout<<raiz->cantidadGondola;
    cout<<" unidades en gondola de la marca "+raiz->nombre<<endl;
    while (true){
        cout<<"Digite la cantidad de existencias a tomar del inventario para colocar en gondola: ";
        cin>>recarga;
        if(cin.fail())
        {
            cout<<"La cantidad de existencias a tomar debe ser un numero entero"<<endl;
            cin.clear();
            cin.ignore(256,'\n');
        }else
        {
            break;
        }
    }
    pnodoAA aux = inventario.buscarNodoAA(stoi(to_string(codigoPasillo)+to_string(codigoProducto)+to_string(raiz->data)));
    if (aux!=NULL){
        if (aux->cantidadStock>=recarga){
            raiz->cantidadGondola+=recarga;
            aux->cantidadStock-=recarga;
            cout<<"Recarga completa"<<endl;
            return;
        }else{
            if (aux->cantidadStock==0){
                cout<<"No quedan existencias de esta marca en el inventario"<<endl;
                return;
            }else{
                string opcion2;
                cout<<"Solo quedan ";
                cout<<aux->cantidadStock;
                cout<<" existencias en inventario de esta marca"<<endl;
                cout<<"Digite 1 para mover dichas unidades a la gondola u otra tecla para salir: ";
                cin>>opcion2;
                if (opcion2=="1"){
                    raiz->cantidadGondola+=aux->cantidadStock;
                    aux->cantidadStock=0;
                    cout<<"Recarga completa"<<endl;
                    return;
                }else{
                    return;
                }
            }
        }
    }else{
        cout<<"No se ha encontrado en el inventario la informacion correspondiente a esta marca"<<endl;
    }
}




void RBTree::initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
}

void  RBTree::preOrderHelper(NodePtr node) {
    if (node != NULL) {
        cout<<node->data<<","<<node->nombre<<" - ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

void  RBTree::inOrderHelper(NodePtr node) {
    if (node != NULL) {
        inOrderHelper(node->left);
        cout<<node->data<<","<<node->nombre<<" - ";
        inOrderHelper(node->right);
    }
}

void  RBTree::postOrderHelper(NodePtr node) {
    if (node != NULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout<<node->data<<","<<node->nombre<<" - ";
    }
}

NodePtr  RBTree::searchTreeHelper(NodePtr node, int key) {
    if (node == NULL || key == node->data) {
        return node;
    }
    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

// fix the rb tree modified by the delete operation
void  RBTree::fixDelete(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == 1) {
                // case 3.1
                s->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == 0 && s->right->color == 0) {
                // case 3.2
                s->color = 1;
                x = x->parent;
            } else {
                if (s->right->color == 0) {
                    // case 3.3
                    s->left->color = 0;
                    s->color = 1;
                    rightRotate(s);
                    s = x->parent->right;
                }

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == 1) {
                // case 3.1
                s->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == 0 && s->right->color == 0) {
                // case 3.2
                s->color = 1;
                x = x->parent;
            } else {
                if (s->left->color == 0) {
                    // case 3.3
                    s->right->color = 0;
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}


void  RBTree::rbTransplant(NodePtr u, NodePtr v){
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void  RBTree::deleteNodeHelper(NodePtr node, int key) {
    // find the node containing key
    NodePtr z = NULL;
    NodePtr x, y;
    while (node != NULL){
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == NULL) {
        cout<<"Couldn't find key in the tree"<<endl;
        return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == NULL) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == 0){
        fixDelete(x);
    }
}

// fix the red-black tree
void  RBTree::fixInsert(NodePtr k){
    NodePtr u;
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle
            if ((u!=NULL) && (u->color == 1)) {
                // case 3.1
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    // case 3.2.2
                    k = k->parent;
                    rightRotate(k);
                }
                // case 3.2.1
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle

            if ((u!=NULL) && (u->color == 1)) {
                // mirror case 3.1
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    // mirror case 3.2.2
                    k = k->parent;
                    leftRotate(k);
                }
                // mirror case 3.2.1
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 0;
}

void  RBTree::printHelper(NodePtr root, string indent, bool last) {
    // print the tree structure on the screen
    if (root != NULL) {
       cout<<indent;
       if (last) {
          cout<<"R----";
          indent += "     ";
       } else {
          cout<<"L----";
          indent += "|    ";
       }

       string sColor = root->color?"RED":"BLACK";
       cout<<root->data<<","<<root->nombre<<"("<<sColor<<")"<<endl;
       printHelper(root->left, indent, false);
       printHelper(root->right, indent, true);
    }
    // cout<<root->left->data<<endl;
}



 RBTree::RBTree() {
    root = NULL;
}

 RBTree::RBTree(NodePtr raiz) {
    root = raiz;
}

// Pre-Order traversal
// Node->Left Subtree->Right Subtree
void  RBTree::preorder() {
    preOrderHelper(this->root);
}

// In-Order traversal
// Left Subtree -> Node -> Right Subtree
void  RBTree::inorder() {
    inOrderHelper(this->root);
}

// Post-Order traversal
// Left Subtree -> Right Subtree -> Node
void  RBTree::postorder() {
    postOrderHelper(this->root);
}

// search the tree for the key k
// and return the corresponding node
NodePtr  RBTree::searchTree(int k) {
    return searchTreeHelper(this->root, k);
}

// find the node with the minimum key
NodePtr  RBTree::minimum(NodePtr node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// find the node with the maximum key
NodePtr  RBTree::maximum(NodePtr node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

// find the successor of a given node
NodePtr  RBTree::successor(NodePtr x) {
    // if the right subtree is not null,
    // the successor is the leftmost node in the
    // right subtree
    if (x->right != NULL) {
        return minimum(x->right);
    }

    // else it is the lowest ancestor of x whose
    // left child is also an ancestor of x.
    NodePtr y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// find the predecessor of a given node
NodePtr  RBTree::predecessor(NodePtr x) {
    // if the left subtree is not null,
    // the predecessor is the rightmost node in the
    // left subtree
    if (x->left != NULL) {
        return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }

    return y;
}

// rotate left at node x
void  RBTree::leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// rotate right at node x
void  RBTree::rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

// insert the key to the tree in its appropriate position
// and fix the tree
void  RBTree::insert(int key,string nombre, int precio, int cantidadGondola) {
    // Ordinary Binary Search Insertion
    NodePtr node = new Node;
    node->nombre = nombre;
    node->precio = precio;
    node->cantidadGondola = cantidadGondola;
    node->parent = nullptr;
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    node->color = 1; // new node must be red

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != NULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // y ics parent of x
    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    // if new node is a root node, simply return
    if (node->parent == nullptr){
        node->color = 0;
        return;
    }

    // if the grandparent is null, simply return
    if (node->parent->parent == nullptr) {
        return;
    }

    // Fix the tree
    fixInsert(node);
}

NodePtr  RBTree::getRoot(){
    return this->root;
}

// delete the node from the tree
void  RBTree::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}

// print the tree structure on the screen
void  RBTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
}
