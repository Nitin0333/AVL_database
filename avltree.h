struct avlnode {
	int bfactor, dpth;
	string key, value;
	struct avlnode *left, *right;
	
	avlnode(string key = "", string value = "", avlnode * left = NULL, avlnode* right = NULL, int bfactor = 0, int dpth = 0) {
		this->bfactor = bfactor;
		this->dpth = dpth;
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

	// calculating balance factor and depth
	void calc(avlnode* node) {
		int lft = 0, rht = 0;
		if (node->left) {
			lft = node->left->dpth;
		}
		if (node->right) {
			rht = node->right->dpth;
		}

		node->dpth = 1 + max(lft, rht);
		node->bfactor = lft - rht;
	}

	// INSERTION
	avlnode* internal_insert(avlnode* cur, string& key, string& value) {
		if (cur == NULL) {
			flag = INS_SUCC;
			return new avlnode(key, value, NULL, NULL, 0, 1);
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

		calc(cur);
		// BALANCING
		if (cur->bfactor == 2) {
			avlnode* temp = cur->left;
			if (temp->bfactor == 1) {
				cur->left = temp->right;
				temp->right = cur;

				calc(cur);
				calc(temp);
				cur = temp;
			}
			else {
				avlnode* temp2 = temp->right;
				temp->right = temp2->left;
				temp2->left = temp;
				cur->left = temp2->right;
				temp2->right = cur;

				calc(cur);
				calc(temp);
				calc(temp2);
				cur = temp2;
			}
		}
		else if (cur->bfactor == -2) {
			avlnode* temp = cur->right;
			if (temp->bfactor == -1) {
				cur->right = temp->left;
				temp->left = cur;

				calc(cur);
				calc(temp);
				cur = temp;
			}
			else {
				avlnode* temp2 = temp->left;
				cur->right = temp2->left;
				temp2->left = cur;
				temp->left = temp2->right;
				temp2->right = temp;

				calc(temp);
				calc(cur);
				calc(temp2);
				cur = temp2;
			}
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
		
		if (cur != NULL) {
			// BALANCING
			calc(cur);
			if (cur->bfactor == 2) {
				avlnode* temp = cur->left;
				if (temp->bfactor == 1) {
					cur->left = temp->right;
					temp->right = cur;

					calc(cur);
					calc(temp);
					cur = temp;
				}
				else {
					avlnode* temp2 = temp->right;
					temp->right = temp2->left;
					temp2->left = temp;
					cur->left = temp2->right;
					temp2->right = cur;

					calc(cur);
					calc(temp);
					calc(temp2);
					cur = temp2;
				}
			}
			else if (cur->bfactor == -2) {
				avlnode* temp = cur->right;
				if (temp->bfactor == -1) {
					cur->right = temp->left;
					temp->left = cur;

					calc(cur);
					calc(temp);
					cur = temp;
				}
				else {
					avlnode* temp2 = temp->left;
					cur->right = temp2->left;
					temp2->left = cur;
					temp->left = temp2->right;
					temp2->right = temp;

					calc(temp);
					calc(cur);
					calc(temp2);
					cur = temp2;
				}
			}

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
