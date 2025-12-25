#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

typedef struct n{
    int data;
    //int count;
    int bf;
    int h;
    struct n *left;
    struct n *right;
}node;

node * createNode(int v) {
    node *q=(node *)malloc(sizeof(node));
	q->data = v;
    //q->count = 1;
    q->left = NULL;
    q->right = NULL;
    q->bf = 0;
    q->h = 0;
    return q;
}

int height(node *root){
    if (root == NULL)
        return 0;
    return root->h + 1;    
}

node * leftRotation (node *root) {
    node *newroot = root->right;
    root->right = newroot->left;
    newroot->left = root;
    
    root->h = max(height(root->left), height(root->right));
    newroot->h = max(height(newroot->left), height(newroot->right));
    
    root->bf = height( root->left) - height(root->right);
    newroot->bf = height( newroot->left) - height(newroot->right); 
    
    return newroot;
}

node * rightRotation (node *root) {
    node *newroot = root->left;
    root->left = newroot->right;
    newroot->right = root;
    
    root->h = max(height(root->left), height(root->right));
    newroot->h = max(height(newroot->left), height(newroot->right));
    
    
    root->bf = height( root->left) - height(root->right);
    newroot->bf = height( newroot->left) - height(newroot->right); 
    
    return newroot;
}


node * balanceTree (node *root) {
    // Right heavy
    if (root->bf < -1) { 
        if (root->right->bf == -1)
            root = leftRotation(root);
        else {
            root->right = rightRotation(root->right);
            root = leftRotation(root);
        }
    }

    // Left heavy
    else if (root->bf > 1) {
        if (root->left->bf == 1)
            root = rightRotation(root);
        else {
            root->left = leftRotation(root->left);
            root = rightRotation(root);
        }
    }
    return root;
}

void preorder(node *root) {
    if (root == NULL)
        return;
    printf("\n%d [BF = %d] [H = %d] ; ",root->data, root->bf, root->h);
    preorder(root->left);
    preorder(root->right);
}

void inorder(node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("\n%d [BF = %d] [H = %d] ; ",root->data, root->bf, root->h);
    inorder(root->right);
}


node * insert(node *root, int val) {
    if (root == NULL)
        return createNode(val); 

    if (val < root->data) 
        root->left = insert(root->left, val);

    else if (val > root->data)
        root->right = insert(root->right, val);
    
    root->h = max(height(root->left),height(root->right));
    root->bf = height( root->left) - height(root->right);
    
    root = balanceTree(root);
    
    return root;
}

node * inorder_successor(node *root)
{   node *temp = NULL;
    if (root == NULL)
        temp = NULL;
    else
    {   temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
    }
    return temp;

}

node * delete(node *root, int d)
{   if (root==NULL)
        return root;
    else if (d < root->data )
        root->left = delete(root->left, d);
    else if (d > root->data)
        root->right = delete(root->right, d);
    else // root->data == d
    {   //delete root node

        // case 1 : root has no child
        if (root->left == NULL && root->right == NULL)
            return NULL;
        
        // case 2: root has only left child
        else if (root->right == NULL)
            return root->left;
        
        // case 3: root has only right child
        else if (root->left == NULL)
            return root->right;
        
        // case 4 : root has both left and right child
        else
        {   node * successor = inorder_successor(root);
            node * new = createNode(successor->data);
            new->left = root->left;
            new->right = delete(root->right, successor->data );
            new->h = max(height(new->left),height(new->right));
            new->bf = height( new->left) - height(new->right);
            return new;
        }
    }
    root->h = max(height(root->left),height(root->right));
    root->bf = height( root->left) - height(root->right);
    return balanceTree(root);

}

void main() {
    node *avl = NULL;
    int i;
    //int a[]= {44, 17, 78, 32, 50, 88, 48, 62, 84, 92, 80, 82}; 
    //int n= 12;
    //int a[] = {9,10,11,12};
    int a[] = {44, 17, 78, 32, 50, 88, 48, 62, 84, 92, 80, 82};
    int n= 12;
    for( i=0; i<n; i++)
    {   printf("\n\n\nINSERTING %d: \n",a[i]);
        avl = insert(avl,a[i]);
        printf("\nAVL(inorder) :: ");
        inorder(avl);
        printf("\n\nAVL(preorder) :: ");
        preorder(avl);
    }
    
    printf("\n\nDELETING %d",78);
    printf("\nAVL(inorder) :: ");
    avl = delete(avl, 78);
    inorder(avl);
    //printf("\n\nAVL(preorder) :: ");
    //preorder(avl);
    
    printf("\n\nDELETING %d",108);
    printf("\nAVL(inorder) :: ");
    avl = delete(avl, 108);
    inorder(avl);
    //printf("\n\nAVL(preorder) :: ");
    //preorder(avl);
    
    
}