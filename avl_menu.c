#include<stdio.h>
#include<stdlib.h>
struct Node 
{
	int info;
	struct Node *left;
	struct Node *right;
	int height;
};
int height(struct Node *node)
{
	if (node == NULL)
		return 0;
	return node->height;
}
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
}
struct Node* New_Node(int val)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->info = val;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->height = 1;
	return(new_node);
}
struct Node *RRotate(struct Node *node)
{
	struct Node *L = node->left;
	struct Node *temp = L->right;
	L->right = node;
	node->left = temp;
	node->height = max(height(node->left), height(node->right))+1;
	L->height = max(height(L->left), height(L->right))+1;
	return L;
}
struct Node *LRotate(struct Node *node)
{
	struct Node *R = node->right;
	struct Node *T2 = R->left;
	R->left = node;
	node->right = T2;
	node->height = max(height(node->left), height(node->right))+1;
	R->height = max(height(R->left), height(R->right))+1;
	return R;
}
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 
struct Node* Insert(struct Node* node, int info)
{
	if (node == NULL)
		return(New_Node(info));
	if (info < node->info)
		node->left = Insert(node->left, info);
	else if (info > node->info)
		node->right = Insert(node->right, info);
	else
		return node;
	node->height = 1 + max(height(node->left), height(node->right));
	int balance = getBalance(node);
	if (balance > 1 && info < node->left->info)
		return RRotate(node);
	if (balance < -1 && info > node->right->info)
		return LRotate(node);
	if (balance > 1 && info > node->left->info)
	{
		node->left = LRotate(node->left);
		return RRotate(node);
	}
	if (balance < -1 && info < node->right->info)
	{
		node->right = RRotate(node->right);
		return LRotate(node);
	}
	return node;
}
struct Node* Delete(struct Node* root, int info) 
{
	if(root == NULL)
		return root;
	if(info < root->info)
		root->left = Delete(root->left, info);
	else if(info > root->info)
		root->right = Delete(root->right, info);
	else
	{
		if((root->left == NULL)||(root->right == NULL))
		{
			struct Node *temp = root->left ? root->left : root->right;
			if(temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			struct Node* temp = root->right;
			while(temp->left != NULL)
				temp = temp->left;
			root->info = temp->info;
			root->right = Delete(root->right, temp->info);
		}
	}
	if(root == NULL) 
		return root;
	root->height = 1 + max(height(root->left), height(root->right)); 
	int balance = getBalance(root);
	if(balance > 1 && getBalance(root->left) >= 0)
		return RRotate(root);
	if(balance > 1 && getBalance(root->left) < 0)
	{
		root->left = LRotate(root->left);
		return RRotate(root);
	}
	if (balance < -1 && getBalance(root->right) <= 0)
		return LRotate(root);
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = RRotate(root->right);
		return LRotate(root);
	}
	return root;
}
void Postorder(struct Node* node) 
{ 
     if (node == NULL) 
        return;
     Postorder(node -> left);
     Postorder(node -> right);
     printf("%d ", node -> info); 
}
void Inorder(struct Node* node) 
{ 
     if (node == NULL) 
          return;
     Inorder(node -> left);
     printf("%d ", node -> info);
     Inorder(node -> right); 
}
void Preorder(struct Node* node) 
{
     if (node == NULL) 
          return;
     printf("%d ", node -> info);
     Preorder(node -> left);
     Preorder(node -> right); 
}
void main()
{
	struct Node *root = NULL; 
	int ch,val;
	printf("=======Menu of AVL Tree======= \n");
	printf("1. Insert \n");
	printf("2. Delete \n");
	printf("3. Print PreOrder \n");
	printf("4. Print Inorder \n");
	printf("5. Print Postorder \n");
	printf("6. Exit \n");
	printf("============================== \n");
	loop:
	printf("Enter your choice = ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			po:
			printf("\nEnter the value you want to insert (To Stop Enter '-000') = ");
			scanf("%d",&val);
			if(val == -000)
				goto loop;
			else
				root = Insert(root,val);
			goto po;
			break;
		case 2:
				printf("\nEnter the value you want to delete = ");
				scanf("%d",&val);
				root = Delete(root,val);
			goto loop;
			break;
		case 3:
			printf("\nPreorder traversal of binary tree is \n"); 
			Preorder(root); 
			goto loop;
			break;
		case 4:
			printf("\nInorder traversal of binary tree is \n"); 
			Inorder(root);
			goto loop;
			break;
		case 5:
			printf("\nPostorder traversal of binary tree is \n"); 
			Postorder(root);
			goto loop;
			break;
		case 6:
			printf("==========Thank You========== \n");
			break;
		default:
			printf("\nWrong input please try again! :( \n");
			goto loop;
			break;
	}
}
