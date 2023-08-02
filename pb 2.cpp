#include <iostream>
#include <queue>
#include<vector>
struct NOD {
	int key, height;
	NOD* st, * dr, * p;
	NOD(int val) {
		key = val;
		height = 1;
		st = nullptr;
		dr = nullptr;
		p = nullptr;
	}
};
struct searchTree {
	NOD* root = nullptr;
	NOD* minim(NOD* root) {
		NOD* x = root;
		NOD* y = x;
		while (x != nullptr) {
			y = x;
			x = x->st;
		}
		return y;
	}
	NOD* maxim(NOD* root) {
		NOD* x = root;
		NOD* y = x;
		while (x != nullptr) {
			y = x;
			x = x->dr;
		}
		return y;
	}
	NOD* succesor(NOD* x) {
		NOD* y;
		if (x->dr != nullptr)
			y = minim(x->dr);
		else {
			y = x->p;
			while (y != nullptr && x == y->dr) {
				x = y;
				y = y->p;
			}
		}
		return y;
	}
	NOD* predecesor(NOD* x) {
		NOD* y;
		if (x->st != nullptr)
			y = maxim(x->st);
		else {
			y = x->p;
			while (y != nullptr && x == y->st) {
				x = y;
				y = y->p;
			}
		}
		return y;
	}
	NOD* find(int val) {
		if (root == nullptr)
			return nullptr;
		NOD* x = root;
		while (x != nullptr && x->key != val) {
			if (x->key < val)
				x = x->dr;
			else
				x = x->st;
		}
		return x;
	}
	void transplant(NOD* z, NOD* y) {
		y = succesor(z);
		if (z->p == nullptr)
			root = y;
		else {
			if (z == z->p->st)
				z->p->st = y;
			else
				z->p->dr = y;
		}
		if (y != nullptr)
			y->p = z->p;
	}
	void Delete(NOD* z) {
		if (z->st == nullptr)
			transplant(z, z->dr);
		else
			if (z->dr == nullptr)
				transplant(z, z->st);
			else {
				NOD* y = succesor(z);
				if (y != z->dr) {
					transplant(y, y->dr);
					y->dr = z->dr;
					z->dr->p = y;
				}
				transplant(z, y);
				y->st = z->st;
				z->st->p = y;
			}
	}
	void construct(std::vector<int>keys) {
		for (int key : keys)
			insert(key);
	}
	bool empty() {
		if (root == nullptr)
			return true;
		return false;
	}
	void clear(NOD* node) {
		if (node == nullptr)
			return;
		clear(node->st);
		clear(node->dr);
		delete node;
	}
	void RSD(NOD* root) {
		if (root == nullptr)
			return;
		std::cout << root->key << " ";
		RSD(root->st);
		RSD(root->dr);
	}
	void SRD(NOD* root) {
		if (root == nullptr)
			return;
		SRD(root->st);
		std::cout << root->key << " ";
		SRD(root->dr);
	}
	void SDR(NOD* root) {
		if (root == nullptr)
			return;
		SDR(root->st);
		SDR(root->dr);
		std::cout << root->key << " ";
	}
	void afisarePeNiveluri(NOD* root) {
		if (root == nullptr)
			return;
		std::queue<NOD*> queue;
		queue.push(root);
		while (!queue.empty()) {
			int size = queue.size();
			for (int i = 0; i < size; i++) {
				NOD* current = queue.front();
				std::cout << current->key << " ";
				queue.pop();
				if (current->st)
					queue.push(current->st);
				if (current->dr)
					queue.push(current->dr);
			}
			std::cout << std::endl;
		}
	}
	void printTree(int opt) {
		switch (opt) {
		case 1:
			RSD(root);
			break;
		case 2:
			SRD(root);
			break;
		case 3:
			SDR(root);
			break;
		case 4:
			afisarePeNiveluri(root);
			break;
		default:
			break;
		}
	}
	int height(NOD* node) {
		if (node == nullptr)
			return 0;
		return node->height;
	}
	int max(int a, int b) {
		return (a > b) ? a : b;
	}
	NOD* createNode(int key) {
		NOD* newNode = new NOD(key);
		return newNode;
	}
	int getBalance(NOD* node) {
		if (node == nullptr)
			return 0;
		return height(node->dr) - height(node->st);
	}
	NOD* rightRotate(NOD* x) {
		NOD* y = x->st;
		NOD* T2 = y->dr;
		y->dr = x;
		x->st = T2;
		y->p = x->p;
		x->p = y;
		x->height = max(height(x->st), height(x->dr)) + 1;
		y->height = max(height(y->st), height(y->dr)) + 1;
		return y;
	}
	NOD* leftRotate(NOD* x) {
		NOD* y = x->dr;
		NOD* T2 = y->st;
		y->st = x;
		x->dr = T2;
		y->p = x->p;
		x->p = y;
		x->height = max(height(x->st), height(x->dr)) + 1;
		y->height = max(height(y->st), height(y->dr)) + 1;
		return y;
	}
	NOD* insert(NOD* node, int key, NOD* parent) {
		if (node == nullptr) {
			NOD* newNode = createNode(key);
			newNode->p = parent;
			return newNode;
		}
		if (key < node->key)
			node->st = insert(node->st, key, node);
		else if (key > node->key)
			node->dr = insert(node->dr, key, node);
		else
			return node;
		node->height = 1 + max(height(node->st), height(node->dr));
		int balance = getBalance(node);
		if (balance < -1 && key < node->st->key)
			return rightRotate(node);
		if (balance > 1 && key > node->dr->key)
			return leftRotate(node);
		if (balance < -1 && key > node->st->key) {
			node->st = leftRotate(node->st);
			return rightRotate(node);
		}
		if (balance > 1 && key < node->dr->key) {
			node->dr = rightRotate(node->dr);
			return leftRotate(node);
		}
		return node;
	}
	void insert(int key) {
		root = insert(root, key, nullptr);
	}
	NOD* balanceAfterDeletion(NOD* node) {
		if (node == nullptr)
			return nullptr;
		node->height = 1 + max(height(node->st), height(node->dr));
		int balance = getBalance(node);
		if (balance > 1 && getBalance(node->st) >= 0)
			return rightRotate(node);
		if (balance > 1 && getBalance(node->st) < 0) {
			node->st = leftRotate(node->st);
			return rightRotate(node);
		}
		if (balance < -1 && getBalance(node->dr) <= 0)
			return leftRotate(node);
		if (balance < -1 && getBalance(node->dr) > 0) {
			node->dr = rightRotate(node->dr);
			return leftRotate(node);
		}
		return node;
	}
	void erase(NOD* z) {
		NOD* found = find(z->key);
		if (found == nullptr)
			return;
		if (found->st == nullptr) {
			if (found->p == nullptr)
				root = found->dr;
			else if (found == found->p->st)
				found->p->st = found->dr;
			else
				found->p->dr = found->dr;
			if (found->dr != nullptr)
				found->dr->p = found->p;
			delete found;
			root = balanceAfterDeletion(root);
			return;
		}
		if (found->dr == nullptr) {
			if (found->p == nullptr)
				root = found->st;
			else if (found == found->p->st)
				found->p->st = found->st;
			else
				found->p->dr = found->st;
			if (found->st != nullptr)
				found->st->p = found->p;
			delete found;
			root = balanceAfterDeletion(root);
			return;
		}
		NOD* succ = succesor(found);
		NOD* succParent = succ->p;
		if (succParent != found) {
			if (succ->dr != nullptr)
				succ->dr->p = succParent;
			succParent->st = succ->dr;
			succ->dr = found->dr;
			found->dr->p = succ;
		}
		if (found->p == nullptr)
			root = succ;
		else if (found == found->p->st)
			found->p->st = succ;
		else
			found->p->dr = succ;
		succ->p = found->p;
		if (succ->st != nullptr)
			succ->st->p = succ;
		succ->st = found->st;
		delete found;
		root = balanceAfterDeletion(root);
		return;
	}
};
int main()
{
	searchTree sT;
	int optiune;
	std::cout << "Optiunea 1 pentru inserarea unui nod nou" << std::endl;
	std::cout << "Optiunea 2 pentru cautarea unui nod" << std::endl;
	std::cout << "Optiunea 3 pentru stergerea u+nui nod" << std::endl;
	std::cout << "Optiunea 4 pentru maximul subarborelui cu radacina intr-un nod dat" <<
		std::endl;
	std::cout << "Optiunea 5 pentru minimul subarborelui cu radacina intr-un nod dat" <<
		std::endl;
	std::cout << "Optiunea 6 pentru a afla succesorul unui nod dat" << std::endl;
	std::cout << "Optiunea 7 pentru a afla predecesorul unui nod dat" << std::endl;
	std::cout << "Optiunea 8 pentru a afisa arborele (exista 4 modalitati)" << std::endl;
	std::cout << "Optiunea 0 pentru a parasi meniul" << std::endl;
	do {
		int x;
		std::cout << "Alegeti optiunea: ";
		std::cin >> optiune;
		switch (optiune) {
		case 0:
			break;
		case 1:
			std::cout << "Ce nod doriti sa inserati? ";
			std::cin >> x;
			sT.insert(x);
			break;
		case 2:
			std::cout << "Ce nod doriti sa cautati? ";
			std::cin >> x;
			std::cout << "Se afla la adresa: " << sT.find(x) << std::endl;
			break;
		case 3:
			std::cout << "Ce nod doriti sa stergeti? ";
			std::cin >> x;
			sT.erase(sT.find(x));
			break;
		case 4:
			std::cout << "Subarborele cu radacina in nodul ";
			std::cin >> x;
			std::cout << "Maximul subarborelui: " << sT.maxim(sT.find(x))->key <<
				std::endl;
			break;
		case 5:
			std::cout << "Subarborele cu radacina in nodul ";
			std::cin >> x;
			std::cout << "Minimul subarborelui: " << sT.minim(sT.find(x))->key <<
				std::endl;
			break;
		case 6:
			std::cout << "Succesorul nodului: ";
			std::cin >> x;
			std::cout << "Este: " << sT.succesor(sT.find(x))->key << std::endl;
			break;
		case 7:
			std::cout << "Predecesorul nodului: ";
			std::cin >> x;
			std::cout << "Este: " << sT.predecesor(sT.find(x))->key << std::endl;
			break;
		case 8:
			std::cout << "Cum doriti sa afisati arborele? (1: RSD 2: SRD 3: SDR 4: Pe
				niveluri) ";
				std::cin >> x;
			sT.printTree(x);
			break;
		default:
			std::cout << "Optiune invalida" << std::endl;
			break;
		}
	} while (optiune != 0);
	return 0;
}