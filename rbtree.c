//check the rotatae functions

#include<stdio.h>
#include<stdlib.h>

struct node {
    int value;         
    struct node *p;   
    struct node *lc;
    struct node *rc;
    int color;
};
typedef struct node node;
 node* root = NULL;

node* bstinsert(struct node* root, struct node* temp)
{
    if (root == NULL) //empty tree
        return temp;
 
    // Otherwise recur down the tree
    if (temp->value < root->value)
    {
       // printf("hi lc  %d\n",temp->value);
        root->lc = bstinsert(root->lc, temp);
        root->lc->p = root;
    }
    else if (temp->value > root->value)
    {
       // printf("hi rc  %d\n",temp->value);
        root->rc = bstinsert(root->rc, temp);
        root->rc->p = root;
    }
 
    // Return the (unchanged) node pointer
    return root;
}
 
// Function performing right rotation of the passed node
void rightrotate(struct node* temp)
{
    struct node* left = temp->lc;
    temp->lc = left->rc;
    if (temp->lc)
        temp->lc->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->lc)
        temp->p->lc = left;
    else
        temp->p->rc = left;
    left->rc = temp;
    temp->p = left;
}
 
// Function performing left rotation of the passed node
void leftrotate(struct node* temp)
{
    struct node* right = temp->rc;
    temp->rc = right->lc;
    if (temp->rc)
        temp->rc->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->lc)
        temp->p->lc = right;
    else
        temp->p->rc = right;
    right->lc = temp;
    temp->p = right;
}

node* createRBTNode(int key)
{   
    
    node* temp = (struct node*)malloc(sizeof(struct node));
    temp->rc = NULL;
    temp->lc = NULL;
    temp->p = NULL;
    temp->value = key;
    temp->color = 1;  //red
    return temp;
}

void fixup(struct node* root, struct node* x)
{
    node* px = NULL;
    node* ppx = NULL;
    node* ux = NULL;
 
    while ((x != root) && (x->color != 0) && (x->p->color == 1))
    {
        px = x->p;
        ppx = x->p->p;
 
        //Case A: Parent of x is left child of Grand-parent of x
        if (px == ppx->lc)
        {
            ux = ppx->rc;
 
            //Case 1: The uncle of x is also red. Only Recoloring required 
            if (ux != NULL && ux->color == 1)
            {
                px->color = 0;
                ux->color = 0;
                ppx->color = 1;
                x = ppx;
            }
 
            //uncle is black both rotation and recoloring required
            else { 
                //Case 2: x is right child of its parent. Left-rotation required 
                if (x == px->rc) {
                   /* x = px;
                    px = x->p;
                    leftrotate(x);*/
                    leftrotate(px);
					x = px;
					px = x->p;

                }

                // Case 3: x is left child of its parent. Right-rotation required 
               px->color=0;
               ppx->color=1;
                rightrotate(ppx);
              
                x = px;
            }
        }
 
        //Case B: Parent of x is right child of Grand-parent of x 
        else {
            ux = ppx->lc;
 
            //Case 1: The uncle of x is also red. Only Recoloring required 
            if ((ux != NULL) && (ux->color == 1))
            {
                px->color = 0;
                ux->color = 0;
                ppx->color = 1;
                x = ppx;
            }

            //uncle is black both rotation and recoloring required
            else { 
                // Case 2: x is left child of its parent. Right-rotation required 
                if (x == px->lc) {
                   /* x = px;
                    px = x->p;
                    rightrotate(x);*/

                    rightrotate(px);
					x = px;
					px = x->p;
                }
 
                //Case 3: x is right child of its parent. Left-rotation required 
                px->color=0;
                ppx->color=1;
                leftrotate(ppx);

                x = px;
            }
        }
    }
}
node* RBTinsert(int key, struct node* root)
{
    node* x = createRBTNode(key);
    root = bstinsert(root, x);
    fixup(root,x);
    root->color = 0;
    return root;
}

void postorder(node* root)
{
    if(root!=NULL)
    {
        postorder(root->lc);
        postorder(root->rc);
        printf("%d ",root->value);
    }
    return;
}

int blk_hgt(node* root)
{
    int count=1;
    node* x = root;
    while(x->lc!=NULL)
    {
        if(x->color==0) count++;
        x=x->lc;
    }
    return count;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++)
    { 
        scanf("%d",&a[i]);
        //root = RBTinsert(a[i], root);
        node* x = createRBTNode(a[i]);
        root = bstinsert(root, x);
        fixup(root,x);
        root->color = 0;
    }
    postorder(root);
    printf("\n");
    printf("%d",blk_hgt(root));


}