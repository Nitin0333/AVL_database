#include <bits/stdc++.h>

using namespace std;

#define start ">db "
#define INS_SUCC 200
#define INS_DUP 300
#define INS_ERROR 401
#define DEL_SUCC 201
#define DEL_NTFND 301
#define DEL_ERROR 402
#define SER_SUCC 202
#define SER_NTFND 404
#define WRNG_KEY 405

vector<pair<string, string>> res;

int flag = 0;
#include "avltree.h"

void query_result() {
	if (flag == INS_SUCC) {
		cout << "    Successfully inserted key";
	}
	else if (flag == INS_DUP) {
		cout << "    Key already exists select different key";
	}
	else if (flag == INS_ERROR) {
		cout << "    Could not enter into database";
	}
	else if (flag == DEL_SUCC) {
		cout << "    Successfully deleted the key";
	}
	else if (flag == DEL_NTFND) { 
		cout << "    Key does not exist";
	}
	else if (flag == DEL_ERROR) {
		cout << "    Could not delete the key";
	}
	else if (flag == SER_NTFND) {
		cout << "    Key was not found in the database";
	}
	else if (flag == SER_SUCC) {
		cout << "    Successfully found the key";
	}
	else if (flag == WRNG_KEY) {
		cout << "    The key voilates rules";
	}
}

string inbuff, buffer;

vector<string> commands;
deque<string> db;

avltree *tree = new avltree();

// if the database.txt doesnot exists this will create it
fstream database("database.txt", ios::app);
fstream logfile("log.txt", ios::app);

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
	database.open("database.txt", ios::out | ios::trunc);
	// To ensure the identity of the database
	database << "NITIN" << endl;
	write_node(tree->root);
	cout << start << "Successfully saved your data" << endl;
	database.close();
}

avlnode* load_node(avlnode* node) {
	if (!db.empty() && db.front() != "NULL") {
		string key = "";
		buffer = db.front();
		db.pop_front();
		int j = 0;
		while (buffer[j] != '_') {
			key += buffer[j];
			j++;
		}
		j++;
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
	tree->root = load_node(tree->root);
}

void space_sep(string& s) {
	// separating commands on the basis of space
	commands.clear();
	stringstream ss(s);
	while (getline(ss, buffer, ' ')) {
		commands.push_back(buffer);
	}
}


int main() {
	// Is useful only for first time or when the database file doesnot exists
	database.close();
	logfile.close();

	// Opening file for reading data
	database.open("database.txt", ios::in);
	logfile.open("log.txt", ios::in);

	// If the database correctly loads
	if (database) {

		// Loading the database 
		while (getline(database, buffer)) {
			db.push_back(buffer);
		}

		// checking if the database file is correct
		if (db.front() == "NITIN") {
			db.pop_front();
			load_database();
		}
		database.close();

		while (getline(logfile, buffer)) {
			db.push_back(buffer);
		}

		// If the log file is not empty
		if (!db.empty()) {
			cout << start << "There are some unsaved changes do you want to restore them [y]" << endl;
			getline(cin, inbuff);
			
			// If the user want to save the unsaved changes
			if (inbuff == "y") {
				while (!db.empty()) {
					string s = db.front();
					db.pop_front();

					space_sep(s);

					if (commands[0] == "insert") {
						tree->insert(commands[1], commands[2]);
					}
					else {
						tree->remove(commands[1]);
					}
				}
				save_database();
			}
		}

		logfile.close();
		logfile.open("log.txt", ios::out | ios::trunc);

		// Main program Loop
		while (true) {
			// Taking commands
			cout << start;
			getline(cin, inbuff);

			space_sep(inbuff);
			
			flag = 0;

			auto srt = chrono::high_resolution_clock::now();

			// Select command
			if (commands[0] == "select") {
				int sz = commands.size();

				flag = SER_NTFND;

				res.clear();
				if (sz == 2 && commands[1] == "all") {
					tree->inorder();
					flag = SER_SUCC;
				}
				else {
					for (int i = 1; i < sz; i++) {
						if (commands[i] == "all" || commands[i] == "NITIN") {
							flag = WRNG_KEY;
							break;
						}
						avlnode* temp = tree->search(commands[i]);

						if (flag == SER_NTFND) {
							break;
						}
						res.push_back({temp->key, temp->value});
					}
				}

				if (flag == SER_SUCC) {
					cout << start << endl;
					for (auto x : res) {
						cout << "    {" << x.first << ", " << x.second << '}' << endl;
					}
				}
			}

			// Insert command
			else if (commands.size() == 3 && commands[0] == "insert") {
				if (commands[1] != "all" && commands[1] != "NITIN")
					tree->insert(commands[1], commands[2]);
				else {
					flag = WRNG_KEY;
				}
			}

			// Remove command 
			else if (commands.size() == 2 && commands[0] == "remove") {
				if (commands[1] != "all" && commands[1] != "NITIN") {
					tree->remove(commands[1]);
				}
				else {
					flag = WRNG_KEY;
				}
			}

			// Save command
			else if (commands.size() == 1 && commands[0] == "save") {
				logfile.close();
				logfile.open("log.txt", ios::out | ios::trunc);
				save_database();
			}

			// Exit command
			else if (commands.size() == 1 && commands[0] == "exit") {
				cout << start << "Successfully exited the database" << endl;
				break;
			}

			// Help command
			else if (commands.size() == 1 && commands[0] == "help") {
				cout << start << "\t\t\tHelp Menu" << endl;
				cout << "\t1. Select command : select <key1> <key2> <key3> ....   key should not be all and NITIN" << endl;
				cout << "\t2. Insert command : insert <key> <value> key should not be all and NITIN" << endl;
				cout << "\t3. Remove command : remove <key> key should not be all and NITIN" << endl;
				cout << "\t3. Save command : save" << endl;
				cout << "\t3. Exit command : exit" << endl;
			}

			// Wrong command
			else {
				cout << start << "Unknown command. Type help to know the commands" << endl;
			}

			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::milliseconds>(stop - srt);
			query_result();	
			cout << " [query executed in " << duration.count() << "ms]" << endl;

			if (flag == INS_SUCC) {
				logfile << inbuff << endl;
			}
			else if (flag == DEL_SUCC) {
				logfile << inbuff << endl;
			}
		}
		database.close();
		logfile.close();
	}

	// If the database doesnot opens correctly
	else {
		cout << start << "Cannot access database" << endl; 
	}
	
	return 0;
}
