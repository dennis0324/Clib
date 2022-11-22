#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <stdlib.h>

#ifndef BINARYTREE_ELEMENT
#define BINARYTREE_ELEMENT
typedef struct binarytree_element{
    int key;
}BT_Element;

#define BINARYTREE_ELEMENT BT_Element
#endif

typedef struct binarytree_node{
    BINARYTREE_ELEMENT element;
    struct binarytree_node * left,*right;
}BTNode;

BTNode * AddNode(BINARYTREE_ELEMENT element){
    BTNode * result = (BTNode *)malloc(sizeof(BTNode));
    result->element = element;
    result->left = result->right = NULL;
    return result;
}

void insert_BTNode(BTNode ** root,BINARYTREE_ELEMENT element){
    BTNode * c = *root;
    BTNode * p = NULL;
    while(c && c->element.key != element.key){
        p = c;
        if(c->element.key > element.key) c = c->left;
        else c = c->right;
    }
    if(p == NULL) *root = AddNode(element);
    if(p->element.key > element.key) p->left = AddNode(element);
    else p->right = AddNode(element);
}

BTNode * search_BTNode(BTNode * root,BINARYTREE_ELEMENT element){
    while(root){
        if(root->element.key == element.key) return root;
        if(root->element.key > element.key) root = root->left;
        else root = root->right;
    }
    return NULL;
}

void delete_BTNode(BTNode ** root, BINARYTREE_ELEMENT element){
    BTNode *p = NULL, *c = *root;
    BTNode * succ_p,*succ;
    while(c){
        p = c;
        c = c->left ? c->left : c->right;
    }
    if(!c) return;
    if(c->left == NULL && c->right == NULL){
        if(!p){
            if(p->left == c) p->left = NULL;
            else p->right = NULL;
        }
        else *root = NULL;
    }
    else if(c->left == NULL || c->right == NULL){
        BTNode * temp = c->left ? c->left : c->right;
        if(!p){
            if(p->left == c) p->left = temp;
            else p->right = temp;
        }
        else *root = temp;
    }
    else{
        succ_p = c;
        succ = c->right;
        while(succ->left){
            succ_p = succ;
            succ = succ->left;
        }
        if(succ_p->left == succ) succ_p->left = succ->right;
        else succ_p->right = succ->right;

        c->element = succ->element;
        c = succ;
    }
    free(c);
}

void destory_BTNode(BTNode * temp){
    if(!temp) return;
    destory_BTNode(temp->left);
    destory_BTNode(temp->right);
    free(temp);
}
#endif