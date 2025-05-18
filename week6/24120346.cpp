#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Company {
    string name;
    string profit_tax;
    string address;
};

vector<Company> readCompanyList(string file_name) {
    ifstream file(file_name);
    vector<Company> companies;
    string line;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, tax, address;

        getline(ss, name, '|');
        getline(ss, tax, '|');
        getline(ss, address);

        companies.push_back({name, tax, address});
    }

    return companies;
}

long long hashString(string company_name) {
    const int p = 31;
    const int m = 2000;
    long long hash_value = 0;
    long long power = 1;

    string s = company_name;
    if (s.length() > 20) {
        s = s.substr(s.length() - 20);
    }

    for (char c : s) {
        hash_value = (hash_value + (c * power) % m) % m;
        power = (power * p) % m;
    }

    return hash_value;
}

struct HashTable {
    vector<Company> table[2000];
};

HashTable* createHashTable(vector<Company> list_company) {
    HashTable* ht = new HashTable();
    for (const auto& company : list_company) {
        long long index = hashString(company.name);
        ht->table[index].push_back(company);
    }
    return ht;
}

void insert(HashTable* hash_table, Company company) {
    long long index = hashString(company.name);
    hash_table->table[index].push_back(company);
}

Company* search(HashTable* hash_table, string company_name) {
    long long index = hashString(company_name);
    for (auto& company : hash_table->table[index]) {
        if (company.name == company_name) {
            return &company;
        }
    }
    return nullptr;
}

int main() {
    string mst_path = "MST.txt";
    vector<Company> companies = readCompanyList(mst_path);
    HashTable* hash_table = createHashTable(companies);

    ifstream input_file("input.txt");
    ofstream output_file("output.txt");

    string company_name;
    while (getline(input_file, company_name)) {
        Company* result = search(hash_table, company_name);
        if (result) {
            output_file << result->name << "|" << result->profit_tax << "|" << result->address << "\n";
        }
    }

    delete hash_table;
    return 0;
}

