#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cctype>


using namespace std;

struct Car {
    string plate; // LLL-NLNN | L = letter, N = number
    string brand;
    int year;
    Car *next;
};

class List {
    private: Car *first_car;

    public: 
        List() { first_car = nullptr; }

    // requisite 2 and 1
    void insert(string plate, string brand, int year) {
        Car *new_car = new Car();
        new_car->plate = plate; 
        new_car->brand = brand; 
        new_car->year = year; 
        new_car->next = NULL;

        if(first_car == nullptr || !(first_car->plate < plate)) {
            new_car->next = first_car;
            first_car = new_car;
            } else {
                Car *temp = first_car;
                while (temp->next != NULL && (temp->next->plate < plate)) {
                    temp = temp->next;
                }
                new_car->next = temp->next;
                temp->next = new_car;
            }
    }

    // requisite 2
    void remove(string plate) {
        Car *current = first_car;
        Car *previous = nullptr;

        while(current != nullptr && current->plate != plate) {
            previous = current;
            current = current->next;
        }

        if(current != nullptr) {
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                first_car = current->next;
            }

            delete current;
        } else {
            cout << "Carro não encontrado." << endl;
        }
    }

    // requisite 1 and 7
    void display() {
        Car* temp = first_car;
        cout << "\nLista de carros ordenada por placa:" << endl;
        while (temp != NULL) {
            cout << "Placa: " << temp->plate << ", Marca: " << temp->brand << ", Ano: " << temp->year << endl;
            temp = temp->next;
        }
    }

    Car* getFirstCar() {
        return first_car;
    }

    List* deepCopyList(List &carList) {
        List* copyList = new List();
        Car* currentCar = carList.getFirstCar();
        while (currentCar != nullptr) {
            copyList->insert(currentCar->plate, currentCar->brand, currentCar->year);
            currentCar = currentCar->next;
        }
        return copyList;
    }

    List* sortByBrands(List &carList) {
        List* sortedList = new List();
        List* copyList = deepCopyList(carList);

        Car* currentCar = copyList->getFirstCar();
        while (currentCar != nullptr) {
            Car* minBrandCar = currentCar;
            Car* tempCar = currentCar->next;
            while (tempCar != nullptr) {
                if (tempCar->brand < minBrandCar->brand) {
                    minBrandCar = tempCar;
                }
                tempCar = tempCar->next;
            }

            sortedList->insert(minBrandCar->plate, minBrandCar->brand, minBrandCar->year);

            copyList->remove(minBrandCar->plate);

            currentCar = copyList->getFirstCar();
        }

        delete copyList; 
        return sortedList;
    }


    List* sortByYears(List &carList) {
        List* sortedList = new List();
        List* copyList = deepCopyList(carList);

        Car* currentCar = copyList->getFirstCar();
        while (currentCar != nullptr) {
            Car* minYearCar = currentCar;
            Car* tempCar = currentCar->next;
            while (tempCar != nullptr) {
                if (tempCar->year < minYearCar->year) {
                    minYearCar = tempCar;
                }
                tempCar = tempCar->next;
            }

            sortedList->insert(minYearCar->plate, minYearCar->brand, minYearCar->year);
            
            copyList->remove(minYearCar->plate);

            currentCar = copyList->getFirstCar();
        }

        return sortedList;
    }
};

struct NodeCar {
    Car car;
    NodeCar *left;
    NodeCar *right;
};

class TreePlates {
    private: 
        NodeCar *root;

        NodeCar* insertNode(NodeCar* node, const Car& car) {
            if (node == nullptr) {
                NodeCar* newNode = new NodeCar();
                newNode->car = car;
                newNode->left = nullptr;
                newNode->right = nullptr;
                return newNode;
            }

            if (car.plate < node->car.plate) {
                node->left = insertNode(node->left, car);
            } else if (car.plate > node->car.plate) {
                node->right = insertNode(node->right, car);
            }

            return node;
        }

    public: 
        TreePlates() { root = nullptr; }

        // requisite 3
        void createTreePlates(List& carList) {
            Car* currentCar = carList.getFirstCar();
            root = nullptr; 

            while (currentCar != nullptr) {
                root = insertNode(root, *currentCar);
                currentCar = currentCar->next;
            }

            cout << "\nÁrvore binária relativa à placa dos carros criada." << endl;
        }

        // requisite 6
        void searchCar(const string& plate) {
            NodeCar* currentNode = root;
            while (currentNode != nullptr) {
                if (plate == currentNode->car.plate) {
                    cout << "\nCarro encontrado - Placa: " << currentNode->car.plate << ", Marca: " << currentNode->car.brand << ", Ano: " << currentNode->car.year << endl;
                    return;
                } else if (plate < currentNode->car.plate) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
            }

            cout << "Carro com a placa " << plate << " não encontrado." << endl;
        }
};

class TreeBrands {
    private: 
        NodeCar *root;

        NodeCar* insertNode(NodeCar* node, const Car& car) {
            if (node == nullptr) {
                NodeCar* newNode = new NodeCar();
                newNode->car = car;
                newNode->left = nullptr;
                newNode->right = nullptr;
                return newNode;
            }

            string carBrandLower = car.brand;
            transform(carBrandLower.begin(), carBrandLower.end(), carBrandLower.begin(), ::tolower);

            string nodeBrandLower = node->car.brand;
            transform(nodeBrandLower.begin(), nodeBrandLower.end(), nodeBrandLower.begin(), ::tolower);

            if (carBrandLower < nodeBrandLower) {
                node->left = insertNode(node->left, car);
            } else if (carBrandLower > nodeBrandLower) {
                node->right = insertNode(node->right, car);
            }

            return node;
        }

    public:
        TreeBrands() { root = nullptr; }

        // requisite 4
        void createTreeBrands(List& carList) {
            List* sortedByBrandsList = carList.sortByBrands(carList);
            Car* currentCar = sortedByBrandsList->getFirstCar();
            root = nullptr; 

            while (currentCar != nullptr) {
                root = insertNode(root, *currentCar);
                currentCar = currentCar->next;
            }

            cout << "\nÁrvore binária relativa à marca dos carros criada." << endl;
        }

        // requisite 8
        void display() {
            cout << "\nCarros ordenados por marca:" << endl;
            inOrderTraversal(root);
        }

        void inOrderTraversal(NodeCar* node) {
            if (node != nullptr) {
                inOrderTraversal(node->left);
                cout << "Placa: " << node->car.plate << ", Marca: " << node->car.brand << ", Ano: " << node->car.year << endl;
                inOrderTraversal(node->right);
            }
        }
};

class TreeYears {
    private: 
        NodeCar *root;

        NodeCar* insertNode(NodeCar* node, const Car& car) {
            if (node == nullptr) {
                NodeCar* newNode = new NodeCar();
                newNode->car = car;
                newNode->left = nullptr;
                newNode->right = nullptr;
                return newNode;
            }

            if (car.year < node->car.year) {
                node->left = insertNode(node->left, car);
            } else if (car.year > node->car.year) {
                node->right = insertNode(node->right, car);
            }

            return node;
        }

    public:
        TreeYears() { root = nullptr; }

        // requisite 5
        void createTreeYears(List& carList) {
            List* sortedByYearsList = carList.sortByYears(carList);
            Car* currentCar = sortedByYearsList->getFirstCar();
            root = nullptr; 

            while (currentCar != nullptr) {
                root = insertNode(root, *currentCar);
                currentCar = currentCar->next;
            }

            cout << "\nÁrvore binária relativa ao ano dos carros criada." << endl;
        }

        // requisite 9
        void display() {
            cout << "\nCarros ordenados por ano:" << endl;
            inOrderTraversal(root);
        }

        void inOrderTraversal(NodeCar* node) {
            if (node != nullptr) {
                inOrderTraversal(node->left);
                cout << "Placa: " << node->car.plate << ", Marca: " << node->car.brand << ", Ano: " << node->car.year << endl;
                inOrderTraversal(node->right);
            }
        }
};


int main() {
    List carList;

    carList.insert("ABC-1B12", "honda", 2012);
    carList.insert("ABC-1A13", "civic", 2011);
    carList.insert("ABC-1A12", "toyota", 2013);
    carList.insert("ABC-1A11", "Ford", 2018);

    carList.display();

    TreePlates treePlates;

    treePlates.createTreePlates(carList);
    treePlates.searchCar("ABC-1A11");
    treePlates.searchCar("CCC-9C99");

    TreeBrands treeBrands;

    treeBrands.createTreeBrands(carList);
    treeBrands.display();

    TreeYears treeYears;

    treeYears.createTreeYears(carList);
    treeYears.display();

    return 0;
}