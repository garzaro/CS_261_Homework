//
//  worksheet_31.h
//  Worksheets_AVL_Heaps
//
//  Created by R G on 7/26/17.
//  Copyright © 2017 Romano Garza. All rights reserved.
//

#ifndef worksheet_31_h
#define worksheet_31_h

#ifndef TYPE
#define TYPE  int
#endif

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct AVLnode {
    TYPE value;
    struct AVLnode *left;
    struct AVLnode *right;
    int height;
};

int _h(struct AVLnode * current);
void _setHeight(struct AVLnode * current);
struct AVLnode * _AVLnodeAdd(struct AVLnode* current, TYPE newValue);
int _bf (struct AVLnode * current);
struct AVLnode * _balance(struct AVLnode * current);
struct AVLnode * _rotateLeft(struct AVLnode * current);
struct AVLnode * _rotateRight(struct AVLnode * current);

#endif /* worksheet_31_h */
