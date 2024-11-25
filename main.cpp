#include <bits/stdc++.h>

using namespace std;

#include "avltree.h"
#define start ">db "

string inbuff, buffer;

vector<string> commands;
deque<string> db;

avltree *tree = new avltree();

fstream database("database.txt", ios::app);
fstream logfile("log.txt", ios::out | ios::in);

void write_node(avlnode* node) {
	if (node == NULL) {
		database << "NULL" << endl;
		return;
	}
	database << node->key + "_" + node->value << endl;
	write_node(node->left);
	write_node(node->right);
}

void save_database() {
	// removing the previous database file

	// creating new database file and saving data in that file
	database.open("database.txt", ios::app);
	write_node(tree->root);
	cout << start << "Successfully saved your data" << endl;
	database.close();
}

avlnode* load_node(avlnode* node) {
	cout << "Hi" << endl;
	if (db.empty() || db.front() == "NULL") {
		string key = "";
		buffer = db.front();
		db.pop_front();
		int j = 0;
		while (buffer[j] != '_') {
			key += buffer[j];
		}
		node = new avlnode();
		node->key = key;
		node->value = buffer.substr(j);
		node->left = load_node(node->left);
		node->right = load_node(node->right);
	}
	else {
		if (!db.empty())
			db.pop_front();
	}
	return node;
}

void load_database() {
	//database.clear();
	tree->root = load_node(tree->root);
}


int main() {
	/*if (filesystem::exists("database.txt")) {
		cout << "YES" << endl;
		return 0;
	}
	else {
		fstream database("database.txt", ios::out);
	}*/

	// Main Program Loop
	if (database) {
		while (getline(database, buffer)) {
			db.push_back(buffer);
		}
		load_database();
		database.close();
		while (true) {
			// Taking commands
			cout << start;
			getline(cin, inbuff);
			
			// separating commands on the basis of space
			commands.clear();
			stringstream ss(inbuff);
			while (getline(ss, buffer, ' ')) {
				commands.push_back(buffer);
			}
			
			// Select command
			if (commands[0] == "select") {
				tree->inorder();
			}
			else if (commands[0] == "insert") {
				tree->insert(commands[1], commands[2]);
			}
			else if (commands[0] == "save") {
				save_database();
			}
			else if (commands[0] == "exit") {
				cout << start << "Successfully exited the database" << endl;
				break;
			}
			else {
				cout << start << "Unknown command" << endl;
			}	
		}
		database.close();
		if (logfile) {
			logfile.close();
		}
	}
	else {
		cout << start << "Cannot access database" << endl; 
	}
	
	return 0;
}
