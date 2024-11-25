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
	avlnode* root;
	
	// INITIALIZATION
	avltree(avlnode *root = NULL) {
		this->root = root;
	}
	
	
	// INSERTION
	avlnode* internal_insert(avlnode* cur, string& key, string& value) {
		if (cur == NULL) {
			flag = INS_SUCC;
			return new avlnode(key, value);
		}
		else if (cur->key == key) {
			flag = INS_DUP;
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
		flag = INS_ERROR;
		this->root = internal_insert(this->root, key, value);
	}
	
	
	// DELETION
	avlnode* internal_delete(avlnode* cur, string& key) {
		if (cur == NULL) {
			flag = DEL_NTFND;
		}
		
		// Node found condition
		else if (cur->key == key) {
			flag = DEL_SUCC;

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
		flag = DEL_ERROR;
		this->root = internal_delete(this->root, key);
	}
	
	// SEARCHING
	avlnode* search(string& key) {
		flag = SER_NTFND;
		avlnode* temp = root;
		while (temp != NULL) {
			if (temp->key == key) {
				flag = SER_SUCC;
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
		res.push_back({cur->key, cur->value});
		internal_inorder(cur->right);
	}
	void inorder() {
		internal_inorder(root);
		cout << endl;
	}

};
