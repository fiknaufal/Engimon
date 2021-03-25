#include "Inventory.hpp"
using namespace std;

template <typename T>
Inventory<T>::Inventory(){}

template <typename T>
Inventory<T>::~Inventory(){}

template <typename T>
vector<T>& Inventory<T>::getVector(){
    return this->list;
}

template <typename T>
void Inventory<T>::add(T t){
    this->list.push_back(t);
}

template <typename T>
void Inventory<T>::removeAtIdx(int n){
    this->list.erase(this->list.begin()+n);
}

template <typename T>
int Inventory<T>::getSize(){
    return this->list.size();
}
