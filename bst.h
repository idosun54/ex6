#ifndef BST_H
#define BST_H

typedef struct BSTNode {
    void* data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct {
    BSTNode* root;
    int (*compare)(void*, void*);
    void (*print)(void*);
    void (*freeData)(void*);
} BST;

BST* createBST(int (*cmp)(void*, void*), void (*print)(void*), void (*freeData)(void*));
BSTNode* bstInsert(BSTNode* root, void* data, int (*cmp)(void*, void*));
void* bstFind(BSTNode* root, void* data, int (*cmp)(void*, void*));
void bstInorder(BSTNode* root, void (*print)(void*));
void bstPreorder(BSTNode* root, void (*print)(void*));
void bstPostorder(BSTNode* root, void (*print)(void*));
void bstFree(BSTNode* root, void (*freeData)(void*));

#endif


BST* createBST(int (*cmp)(void*, void*), void (*print)(void*), void (*freeData)(void*))
{
  BST* tree= (BST*)malloc(sizeof(BST));
  tree->root=NULL;
  tree->compare= cmp;
  tree->print= print;
  tree->freeData= freeData;
}

BSTNode* bstInsert(BSTNode* root, void* data, int (*cmp)(void*, void*))
{
 if(root==NULL)
  {
  BSTNode* node= (BSTNode*)malloc(sizeof(BSTNode));
  node->data= data;
  node->left=NULL;
  node->right=NULL;
  return node;
 }

 int comp= cmp(data, root->data);

 if(comp<0)
  root->left= bstInsert(root->left, data, cmp);
 if(comp>0)
  root->right= bstInsert(root->right, data, cmp);

 return root;
}