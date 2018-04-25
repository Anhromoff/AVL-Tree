#include <cstdio>

typedef int Balance;
struct Node;
typedef Node* Ptr; // pointer to the node

// tree element
struct Node 
{
	int key;		 // some data
	Ptr left, right; // pointers to the left and right subtrees
	Balance bal;	 // balance indicator:
					 // -1 means that left subtree is higher than the right one
					 // 0 means that left subtree is as high as the right one,
					 // 1 means that right subtree is higher than the left one
};

// Inserting to the tree
void search(int x, Ptr &p, bool &h)
{
	Ptr p1, p2;

	// If the tree is empty
	if (p==nullptr)
	{
		p = new Node; // creating new node
		h = true;	  // we indicate that balancing is needed

		// Initialising	new node
		p->key = x;
		p->left = nullptr;
		p->right = nullptr;
		p->bal = 0;
	}
	else if (p->key > x)
	{
		search(x, p->left, h); // moving to the left subtree
		// If we need balancing
		if (h == true)
		{
			switch (p->bal)
			{
			// Right subtree was higher
			case 1:
			{
				p->bal = 0; // subtrees now have the same height
				h = false;  // we don't need balancing anymore
				break;
			}
			// Subtrees had the same height
			case 0:
			{
				p->bal = -1; // left subtree became higher
				break;
			}
			// Left subtree was higher
			// In this case we must perform balancing
			case -1:
			{
				p1 = p->left;
				// Single LL rotation
				if (p1->bal == -1)
				{
					p->left = p1->right;
					p1->right = p;
					p->bal = 0;
					p = p1;
				}
				// Double LR rotation
				else
				{
					p2 = p1->right;
					p1->right = p2->left;
					p2->left = p1;
					p->left = p2->right;
					p2->right = p;
					if (p2->bal == -1) p->bal = 1;
					else p->bal = 0;
					if (p2->bal == 1) p1->bal = -1;
					else p1->bal = 0;
					p = p2;
				}
				p->bal = 0; // subtrees now have the same height
				h = false;  // we don't need balancing anymore
				break;
			}
			}
		}
	}
	else if (p->key < x)
	{
		search(x, p->right, h); // moving to the right subtree
		// If we need balancing
		if (h == true)
		{
			switch (p->bal)
			{
			// If left subtree was higher
			case -1:
			{
				p->bal = 0; // subtrees now have the same height
				h = false;  // we don't need balancing anymore
				break;
			}
			// Subtrees had the same height
			case 0:
			{
				p->bal = 1; // right subtree became higher
				break;
			}
			// If right subtree was higher, we need balancing
			case 1:
			{
				p1 = p->right;
				// Single RR rotation
				if (p1->bal == 1)
				{
					p->right = p1->left;
					p1->left = p;
					p->bal = 0;
					p = p1;
				}
				// Double RL rotation
				else
				{
					p2 = p1->left;
					p1->left = p2->right;
					p2 ->right = p1;
					p->right = p2->left;
					p2->left = p;
					if (p2->bal == 1) p->bal = -1;
					else p->bal = 0;
					if (p2->bal == -1) p1->bal = 1;
					else p1->bal = 0;
					p = p2;
				}
				p->bal = 0; // subtrees now have the same height
				h = false;  // we don't need balancing anymore
				break;
			}
			}
		}
	}
}

// Balancing when left subtree became lower
void balanceL(Ptr &p, bool &h)
{
	Ptr p1, p2;
	Balance b1, b2;

	switch (p->bal)
	{
	case -1:
	{
		p->bal = 0;
		break;
	}
	case 0:
	{
		p->bal = 1; 
		h = false;  
		break;
	}
	case 1:
	{
		p1 = p->right;
		b1 = p1->bal;
		if (b1 >= 0)
		{
			p->right = p1->left;
			p1->left = p;
			if (b1 == 0)
			{
				p->bal = 1;
				p1->bal = -1;
				h = false;
			}
			else
			{
				p ->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else
		{
			p2 = p1->left;
			b2 = p2->bal;
			p1->left = p2->right;
			p2->right = p1;
			p->right = p2->left;
			p2->left = p;
			if (b2 == 1) p->bal = -1;
			else p->bal = 0;
			if (b2 == -1) p1->bal = 1;
			else p1->bal = 0;
			p = p2;
			p2->bal = 0;
		}
		break;
	}
	}
}

// Balancing when right subtree became lower
void balanceR(Ptr &p, bool &h)
{
	Ptr p1, p2;
	Balance b1, b2;

	switch (p->bal)
	{
	case 1:
	{
		p->bal = 0; 
		break;
	}
	// Ветви были равны
	case 0:
	{
		p->bal = -1; 
		h = false;   
		break;
	}
	case -1:
	{
		p1 = p->left;
		b1 = p1->bal;
		if (b1 <= 0)
		{
			p->left = p1->right;
			p1->right = p;
			if (b1 == 0)
			{
				p->bal = -1;
				p1->bal = 1;
				h = false;
			}
			else
			{
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else
		{
			p2 = p1->right;
			b2 = p2->bal;
			p1->right = p2->left;
			p2->left = p1;
			p->left = p2->right;
			p2->right = p;
			if (b2 == -1) p->bal = 1;
			else p->bal = 0;
			if (b2 == 1) p1->bal = -1;
			else p1->bal = 0;
			p = p2;
			p2->bal = 0;
		}
		break;
	}
	}
}

// Additional function for deleting
void del(Ptr &r, Ptr &q, bool &h)
{
	if (r->right != nullptr)
	{
		del(r->right, q, h);
		if (h == true) balanceR(r, h);
	}
	else
	{
		q->key = r->key;
		q = r;
		r = r->left;
		h = true;
	}
}

// Deleteng from tree
void Delete(int x, Ptr &p, bool &h)
{
	Ptr q;

	if (p == nullptr) return; 
	else if (p->key > x)
	{
		Delete(x, p->left, h);			// going to the left subtree
		if (h == true) balanceL(p, h);  // perform balancing if needed
	}
	else if (p->key < x)
	{
		Delete(x, p->right, h);        // going to the right subtree
		if (h == true) balanceR(p, h); // perform balancing if needed
	}
	// We found the node
	else
	{
		q = p;
		// node has no right child
		if (q->right == nullptr)
		{
			p = q->left; // left child replaces the node
			h = true;    // now we need balancing
		}
		// node has no left child
		else if (q->left == nullptr)
		{
			p = q->right; // right child replaces the node
			h = true;     // now we need balancing
		}
		// either node has 2 children or has none
		else
		{
			// we search for the most right element in left subtree and replace our node with it
			del(q->left, q, h);			   
			if (h == true) balanceL(p, h); // perform balancing if needed
		}
		delete q; // free memory
	}
}

// Tree visualisation
void PrintTree(Ptr p) 
{
	static int level = 0; 
	level++;
	if (p)
	{
		PrintTree(p->right); 
		for (int i = 0; i<level; i++) printf("   ");
		printf("\\__%d\n", p->key);
		PrintTree(p->left); 
	}
	level--;
}