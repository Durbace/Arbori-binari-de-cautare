#include <iostream>
#include <fstream>
#include <set>
void citeste_fisier(std::set<int>& cresc, std::set<int>& desc) {
	std::ifstream fin("Text.txt");
	int curent, anterior;
	fin >> anterior;
	while (fin >> curent) {
		if (anterior < curent) cresc.insert(anterior);
		else desc.insert(anterior);
		anterior = curent;
	}
	desc.insert(curent);
	auto penultim = desc.begin();
	std::advance(penultim, desc.size() - 2);
	for (auto it = desc.begin(); it != penultim; it++)
		cresc.insert(*it);
}
bool try_insert(int val, std::set<int>& cresc, std::set<int>& desc) {
	auto it = *(desc.rbegin());
	if (val == it)
		return 0;
	if (cresc.find(val) == cresc.end()) {
		cresc.insert(val);
		return 1;
	}
	else {
		if (desc.find(val) == desc.end()) {
			desc.insert(val);
			return 1;
		}
		else return 0;
	}
}
void afisare_sir(std::set<int>& cresc, std::set<int>& desc) {
	for (auto it = cresc.begin(); it != cresc.end(); it++) std::cout << *it << " ";
	for (auto it = desc.rbegin(); it != desc.rend(); it++) std::cout << *it << " ";
}
int main() {
	int k, val;
	std::set<int> cresc;
	std::set<int> desc;
	citeste_fisier(cresc, desc);
	std::cout << "Sir : ";
	afisare_sir(cresc, desc);
	std::cout << std::endl << "Introduceti K : ";
	std::cin >> k;
	for (int i = 0; i < k; i++) {
		std::cout << std::endl << "Valoare : ";
		std::cin >> val;
		bool succes = try_insert(val, cresc, desc);
		if (succes) {
			std::cout << std::endl << "Valoarea a fost inserata. Noul sir este ";
			afisare_sir(cresc, desc);
		}
		else std::cout << std::endl << " Valoarea nu a putut fi inserata";
	}
	return 0;
}
