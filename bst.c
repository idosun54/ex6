#include <stdlib.h>
#include "bst.h"


BST* createBST(int (*cmp)(void*, void*), void (*print)(void*), void (*freeData)(void*))
{
  BST* tree= (BST*)malloc(sizeof(BST));
  tree->root=NULL;
  tree->compare= cmp;
  tree->print= print;
  tree->freeData= freeData;
  return tree;
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

 return NULL;
}

void* bstFind(BSTNode* root, void* data, int (*cmp)(void*, void*))
{
  if(root==NULL)
   return NULL;
  
 int result= cmp(data, root->data);
 if(result==0)
  return root->data;
 else if(result < 0)
  return bstFind(root->left, data, cmp);
 else
  return bstFind(root->right, data, cmp);
}

void bstInorder(BSTNode* root, void (*print)(void*))
{
 if(root==NULL)
  return;
 
 bstInorder(root->left, print);
 print(root->data);
 bstInorder(root->right, print);
}

void bstPreorder(BSTNode* root, void (*print)(void*))
{
 if(root==NULL)
  return;
 
 print(root->data);
 bstInorder(root->left, print);
 bstInorder(root->right, print);
}

void bstPostorder(BSTNode* root, void (*print)(void*))
{
 if(root==NULL)
  return;
 
 bstInorder(root->left, print);
 bstInorder(root->right, print);
 print(root->data);
}

void bstFree(BSTNode* root, void (*freeData)(void*))
{
  if(root==NULL)
   return;
  
  bstFree(root->right, freeData);
  bstFree(root->left, freeData);

  if(freeData)
   freeData(root->data);
  
 free(root);
}
