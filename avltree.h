#define NodeFound 200
#define Nodenotfound 404


struct avlnode {
	string key, value;
	struct avlnode *left, *right;
	
	avlnode(string key = "", string value = "", avlnode * left = NULL, avlnode* right = NULL) {
		this->key = key;
		this->value = value;
		this->left = left;
		this->right = right;
	}
	
};

struct avltree {
	avlnode * root;
	
	// INITIALIZATION
	avltree(avlnode *root = NULL) {
		this->root = root;
	}
	
	
	// INSERTION
	avlnode* internal_insert(avlnode* cur, string& key, string& value) {
		if (cur == NULL) {
			return new avlnode(key, value);
		}
		else if (cur->key == key) {
			cout << "Key already exists select different key" << endl;
		}
		else if (cur->key < key) {
			cur->right = internal_insert(cur->right, key, value);
		}
		else {
			cur->left = internal_insert(cur->left, key, value);
		}
		return cur;
	}
	void insert(string& key, string& value) {
		this->root = internal_insert(this->root, key, value);
	}
	
	
	// DELETION
	avlnode* internal_delete(avlnode* cur, string& key) {
		if (cur == NULL) {
			cout << key << " not found" << endl;
		}
		
		// Node found condition
		else if (cur->key == key) {
			// Node is leaf
			if (cur->left == NULL && cur->right == NULL) {
				delete(cur);
				cur = NULL;
			}
			
			// Node has a single child
			else if (cur->left == NULL ^ cur->right == NULL) {
				avlnode* temp = cur;
				if (cur->left == NULL) {
					cur = cur->right;	
				}
				else {
					cur = cur->left;
				}
				delete(temp);			
			}
			
			// Node has two child
			else {
				cur->key = insucc(cur);
				cur->right = internal_delete(cur->right, cur->key);
			}
		}
		
		// search right
		else if (cur->key < key) {
			cur->right = internal_delete(cur->right, key);
		}
		
		// search left
		else {
			cur->left = internal_delete(cur->left, key);
		}
		
		
		return cur;
	}
	void remove(string& key) {
		this->root = internal_delete(this->root, key);
	}
	
	// SEARCHING
	avlnode* search(string& key) {
		avlnode* temp = root;
		while (temp != NULL) {
			if (temp->key == key) {
				break;
			}
			else if (temp->key < key) {
				temp = temp->right;
			}
			else {
				temp = temp->left;
			}
		}
		
		return temp;
	}
	
	
	// INORDER SUCCESSOR
	string insucc(avlnode* cur) {
		avlnode* nxt = cur->right;
		
		while (nxt != NULL) {
			cur = nxt;
			nxt = nxt->left;
		}
		return cur->key;
	}
	
	
	// TRAVERSAL
	void internal_inorder(avlnode* cur) {
		if (cur == NULL)
			return;
		
		internal_inorder(cur->left);
		cout << '{' << cur->key << ", " << cur->value << '}' << " ";
		internal_inorder(cur->right);
	}
	void inorder() {
		internal_inorder(root);
		cout << endl;
	}

};