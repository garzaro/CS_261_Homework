//
//  worksheet_31.c
//  Worksheets_AVL_Heaps
//
//  Created by R G on 7/26/17.
//  Copyright © 2017 Romano Garza. All rights reserved.
//

#include "worksheet_31.h"

int _h(struct AVLnode * current){
    if (current == 0) return -1;
    return current->height;
}


void _setHeight (struct AVLnode * current) {
    int lch = _h(current->left);
    int rch = _h(current->right);
    if (lch < rch) current->height = 1 + rch;
    else current->height = 1 + lch;
}


struct AVLnode * _AVLnodeAdd (struct AVLnode* current, TYPE newValue){
    struct AVLnode * newnode;
    if(current == 0){
        newnode = (struct AVLnode*) malloc(sizeof(struct AVLnode));
        assert(newnode!=0);
        newnode->value = newValue;
        newnode->left =newnode ->right = 0;
        return newnode;
    }
    else if(newValue < current->value){
        current->left = _AVLnodeAdd(current->left, newValue);
    }
    else current->right = _AVLnodeAdd(current->right, newValue);
    return _balance(current);
}


int _bf(struct AVLnode * current){
    return _h(current->right) - _h(current->left);
}


struct AVLnode * _balance(struct AVLnode * current){
    int cbf = _bf(current);
    if(cbf < -1){
        if(_bf(current->left) > 0) {
            current->left = _rotateLeft(current->left);
        }
        return _rotateRight(current);
    }
    else if (cbf > 1) {
        if (_bf(current->left) > 0){
            current->right = _rotateRight(current->right);
        }
        return _rotateLeft(current);
    }
    _setHeight(current);
    return current;
}



struct AVLnode * _rotateLeft(struct AVLnode * current){
 
// Set new top node to the current node's right child
    struct AVLnode * newTop = current->right;
// Set current nodes new right child to the new top nodes _left_ child
    current->right = newTop->left;
// Set new top's left child to current node
    newTop->left = current;
// Set height of current node and new top node
    _setHeight(current);
    _setHeight(newTop);
// Return new top node
    return newTop;
}


 
struct AVLnode * _rotaterRight(struct AVLnode * current){
 
 // Set new top node to the current node's left child
    struct AVLnode * newTop = current->left; 
 // Set current nodes new left child to the new top nodes _right_ child
    current->left = newTop->right;
 // Set new top's right child to current node
    newTop->right = current;
 // Set height of current node and new top node
    _setHeight(current);
    _setHeight(newTop);
 // Return new top node
    return newTop;
}
 

