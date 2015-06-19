#ifndef _BIN_TREE_H
#define _BIN_TREE_H

#include <iostream>

using namespace std;

template <class elemType>
struct binaryTreeNode
{
	elemType info;
	binaryTreeNode<elemType> *llink;
	binaryTreeNode<elemType> *rlink;
	
	binaryTreeNode(const elemType & v) : info(v), llink(nullptr), rlink(nullptr) {}
};

template <class elemType>
class binaryTree
{
	public:
		const binaryTree<elemType>& operator=(const binaryTree<elemType>&);
		bool isEmpty() const;
		void inorderTraversal() const;
		void preorderTraversal() const;
		void postorderTraversal() const;
		int treeHeight() const;
		void destroyTree();
		binaryTree(const binaryTree<elemType>& otherTree);
		binaryTree();
		~binaryTree();		
	protected:
		binaryTreeNode<elemType>*root;
	private:
		void copyTree(binaryTreeNode<elemType>* &copiedTreeRoot,binaryTreeNode<elemType>* otherTreeRoot);	
		void destroy(binaryTreeNode<elemType>* &p);
		void inorder(binaryTreeNode<elemType> *p) const;
		void preorder(binaryTreeNode<elemType> *p) const;
		void postorder(binaryTreeNode<elemType> *p) const;
		int height(binaryTreeNode<elemType> *p) const;
		int max(int x, int y) const;		
};


template <class elemType>
bool binaryTree<elemType>::isEmpty() const
{
	return (root == nullptr);
}

template <class elemType>
binaryTree<elemType>::binaryTree()
{
	root = nullptr;
}

template <class elemType>
void binaryTree<elemType>::inorderTraversal() const
{
	inorder(root);
}

template <class elemType>
void binaryTree<elemType>::preorderTraversal() const
{
	preorder(root);
}

template <class elemType>
void binaryTree<elemType>::postorderTraversal() const
{
	postorder(root);
}

template <class elemType>
int binaryTree<elemType>::treeHeight() const
{
	return height(root);
}

template <class elemType>
void binaryTree<elemType>::inorder(binaryTreeNode<elemType> *p) const
{
	if (p != nullptr)
	{
		inorder(p->llink);
		cout << p->info << " ";
		inorder(p->rlink);
	}
}

template <class elemType>
void binaryTree<elemType>::preorder(binaryTreeNode<elemType> *p) const
{
	if (p != nullptr)
	{
		cout << p->info << " ";
		preorder(p->llink);
		preorder(p->rlink);
	}
}

template <class elemType>
void binaryTree<elemType>::postorder(binaryTreeNode<elemType> *p) const
{
	if (p != nullptr)
	{
		postorder(p->llink);
		postorder(p->rlink);
		cout << p->info << " ";
	}
}

template <class elemType>
int binaryTree<elemType>::height(binaryTreeNode<elemType> *p) const
{
	if (p == nullptr)
		return 0;
	else
		return 1 + max(height(p->llink), height(p->rlink));
}

template <class elemType>
int binaryTree<elemType>::max(int x, int y) const
{
	if (x >= y)
		return x;
	else
		return y;
}

template <class elemType>
void binaryTree<elemType>::copyTree(binaryTreeNode<elemType>* &copiedTreeRoot,binaryTreeNode<elemType>* otherTreeRoot)
{
	if (otherTreeRoot == nullptr)
		copiedTreeRoot = nullptr;
	else
	{
		copiedTreeRoot = new binaryTreeNode<elemType>; 
		copiedTreeRoot->info = otherTreeRoot->info;
		copyTree(copiedTreeRoot->llink, otherTreeRoot->llink);
		copyTree(copiedTreeRoot->rlink, otherTreeRoot->rlink);
	}
}

template <class elemType>
void binaryTree<elemType>::destroy(binaryTreeNode<elemType>* &p)
{
	if (p != nullptr)
	{
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p = nullptr;
	}
}

template <class elemType>
void binaryTree<elemType>::destroyTree()
{
	destroy(root);
}

template <class elemType>
binaryTree<elemType>::binaryTree
(const binaryTree<elemType>& otherTree)
{
	if (otherTree.root == nullptr) 
		root = nullptr;
	else			
		copyTree(root, otherTree.root);
}

template <class elemType>
binaryTree<elemType>::~binaryTree()
{
	destroy(root);
}


template <class elemType>
const binaryTree<elemType>& binaryTree<elemType>::operator=(const binaryTree<elemType>& otherTree)
{
	if (this != &otherTree)
	{
		if (root != nullptr)
			destroy(root);
		if (otherTree.root == nullptr)
			root = nullptr;
		else
			copyTree(root, otherTree.root);
	}
return *this;
}


#endif
