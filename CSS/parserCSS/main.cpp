#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string.h>
#include "MyString.h"
#include "MyList.h"
#include "MyList.cpp"
#include "Node.h"

#define TRUE 1
#define FALSE 0
#define SIZE 17

///////////////////////////////////////////////////////////////////structs

struct couple {
	MyList<MyString> Znaczniki{};
	MyList<MyString> Atrybuty{};
};

struct listNode {
	couple array[SIZE];
	bool isSet[SIZE];
	short int size = 0;
};

struct position {
	int listIndex;
	int arrayIndex;
};

///////////////////////////////////////////////////////////////////help functions

std::ostream& operator<< (std::ostream& os, couple& couple) {

	os << "Znaczniki:\n";
	couple.Znaczniki.writeList();
	os << "Atrybuty:\n";
	couple.Atrybuty.writeList();
	return os;
}

std::ostream& operator<< (std::ostream& os, listNode& listNode) {

	for (int i = 0; i < SIZE; i++) {
		if ((listNode.array[i].Znaczniki.size() > 0) && (listNode.array[i].Atrybuty.size() > 0))
			std::cout << listNode.array[i] << std::endl;
	}
	return os;
}

bool checkForDuplicates(MyString buffor, couple& Couple1) {
	if (Couple1.Atrybuty.size() <= 0) {
		return true;
	}

	Node<MyString>* current = Couple1.Atrybuty.first;
	if (current->value.attributeName() == buffor.attributeName()) {
		current->value = buffor;
		return false;
	}

	for (int i = 0; i < Couple1.Atrybuty.size(); i++) {
		if (current->value.attributeName() == buffor.attributeName()) {
			current->value = buffor;
			return false;
		}
		current = current->next;
	}
	return true;
}

couple* getSection(MyList<listNode>& list, int section) {
	int i = section;
	Node<listNode>* current = list.first;
	i -= current->value.size;
	while (i >= 0) {
		current = current->next;
		i -= current->value.size;
	}
	i += current->value.size;
	for (int j = 0; j < SIZE; j++) {
		if ((i == 0) && (current->value.isSet[j]))
			return &current->value.array[j];
		else {
			if (current->value.isSet[j])
				i--;
		}
	}
	return nullptr;
}

void deleteWholeList(MyList<listNode>& list) {
	int counter = list.size();
	if (counter > 0) {
		Node<listNode>* temp = list.first;
		while (temp->next) {
			temp = list.first->next;
			for (int i = 0; i < SIZE; i++) {
				temp->value.array[i].Atrybuty.deleteList();
				temp->value.array[i].Znaczniki.deleteList();
			}
			delete list.first;
			list.first = temp;
		}
	}
}

///////////////////////////////////////////////////////////////////main

void inputCSS(MyList<listNode>& list, int& counterOfNodes);
void inputCommands(MyList<listNode>& list, int& counterOfNodes);

void clearListNode(listNode* listnode) {
	couple emptyCouple;
	for (int i = 0; i < SIZE; i++) {
		listnode->array[i] = emptyCouple;
	}
}
////main
int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	MyList<listNode> list{};
	int counterOfNodes = 0;
	inputCSS(list, counterOfNodes);
	//list.writeList();
	deleteWholeList(list);
	return 0;
}

///////////////////////////////////////////////////////////////////inputs CSS and read commands

void inputCSS(MyList<listNode>& list, int& counterOfNodes) {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	MyString buffor;
	MyString bufforForComplexSelectors = "";
	bool selectorTurn = true;
	int counter = 0;
	listNode Couples;
	clearListNode(&Couples);
	couple* Couple1 = new couple;
	MyString bufforForAtributes = "";
	while (std::cin >> buffor) {
		buffor.removeWhiteSpaces();
		///////////////////////////////////////////////////////////////////start reading commands
		if (buffor == "????")
			inputCommands(list, counterOfNodes);
		///////////////////////////////////////////////////////////////////beggingin of attributes
		else if (buffor.contains('{')) {
			selectorTurn = false;
			if (buffor != "{") {
				if (buffor.doesEndWith("{")) {
					buffor.removeLast('{');
					buffor.removeLast(',');
					bufforForComplexSelectors += buffor;
					if ((bufforForComplexSelectors != ""))
						Couple1->Znaczniki.insert_last(bufforForComplexSelectors);
					bufforForComplexSelectors = "";
				}
				else {
					bufforForComplexSelectors.removeLast(' ');
					Couple1->Znaczniki.insert_last(bufforForComplexSelectors);
					bufforForComplexSelectors = "";
					buffor.removeFirst('{');
					if (buffor.contains(';')) {
						buffor.removeLast(';');
						bufforForAtributes += buffor;
						if (checkForDuplicates(bufforForAtributes, *Couple1))
							Couple1->Atrybuty.insert_last(bufforForAtributes);
						bufforForAtributes = "";
					}
					else {
						bufforForAtributes += buffor;
						bufforForAtributes += " ";
					}
				}
			}
			else {
				bufforForComplexSelectors.removeLast(' ');
				if (bufforForComplexSelectors != "")
					Couple1->Znaczniki.insert_last(bufforForComplexSelectors);
				bufforForComplexSelectors = "";
			}
		}
		///////////////////////////////////////////////////////////////////end of a section
		else if (buffor.contains('}')) {
			if (buffor != "}") {
				buffor.removeLast('}');
				if (buffor.contains(';')) {
					buffor.removeLast(';');
					bufforForAtributes += buffor;
					if (checkForDuplicates(bufforForAtributes, *Couple1))
						Couple1->Atrybuty.insert_last(bufforForAtributes);
					bufforForAtributes = "";
				}
				else {
					bufforForAtributes += buffor;
					bufforForAtributes += " ";
				}
			}
			if ((counter % SIZE == 0) || list.size() < 1) {
				clearListNode(&Couples);
				list.insert_last(Couples);
				counter = 0;
			}
			if (Couple1 != nullptr) {
				list.last->value.array[counter] = *Couple1;
				list.last->value.isSet[counter] = true;
				list.last->value.size++;
				counterOfNodes++;
				counter++;
				selectorTurn = true;
			}
			couple* Couple2 = new couple;
			delete Couple1;
			Couple1 = Couple2;
		}
		///////////////////////////////////////////////////////////////////getting selectors
		else if (selectorTurn) {
			if (buffor.doesEndWith(",")) {
				buffor.removeLast(',');
				if (buffor != "") {
					bufforForComplexSelectors += buffor;
					Couple1->Znaczniki.insert_last(bufforForComplexSelectors);
					bufforForComplexSelectors = "";
				}
			}
			else {
				bufforForComplexSelectors += buffor;
				bufforForComplexSelectors += " ";
			}
		}
		///////////////////////////////////////////////////////////////////getting attributes
		else {
			if (buffor.contains(';')) {
				buffor.removeLast(';');
				bufforForAtributes += buffor;
				if (checkForDuplicates(bufforForAtributes, *Couple1))
					Couple1->Atrybuty.insert_last(bufforForAtributes);
				bufforForAtributes = "";
			}
			else {
				bufforForAtributes += buffor;
				bufforForAtributes += " ";
			}
		}
	}
	delete Couple1;
}

///////////////////////////////////////////////////////////////////zEs command

void zEs(MyString attribute, MyString selector, MyString buffor, MyList<listNode>& list) {
	Node<listNode>* current = list.last;
	for (int i = list.size() - 1; i >= 0; i--) {
		for (int j = SIZE - 1; j >= 0; j--) {
			if (current->value.isSet[j]) {
				Node<MyString>* currentSelector = current->value.array[j].Znaczniki.last;
				for (int k = current->value.array[j].Znaczniki.size() - 1; k >= 0; k--) {
					if (currentSelector->value == selector) {
						Node<MyString>* currentAttribute = current->value.array[j].Atrybuty.last;
						for (int l = current->value.array[j].Atrybuty.size() - 1; l >= 0; l--) {
							if (currentAttribute->value.attributeName() == attribute) {
								std::cout << buffor << " == " << currentAttribute->value.attributeValue() << std::endl;
								return;
							}
							currentAttribute = currentAttribute->prev;
						}
					}
					currentSelector = currentSelector->prev;
				}
			}
		}
		current = current->prev;
	}
}
///////////////////////////////////////////////////////////////////

void inputCommands(MyList<listNode>& list, int& counterOfNodes) {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	MyString buffor;
	while (std::cin >> buffor) {
		if (buffor == "****")
			return;
		else if (buffor == "?") {
			std::cout << buffor << " == " << counterOfNodes << std::endl;
		}
		else {
			MyString input[3];
			int iterator = 0;
			MyString inputt;
			inputt = buffor;
			while (inputt.countChar(',') < 2) {
				std::cin >> buffor;
				inputt += " ";
				inputt += buffor;
			}
			if (inputt.countChar(',') > 2)
				continue;
			for (int i = 0; i < inputt.size(); i++) {
				if (inputt[i] == ',')
					iterator++;
				else
					input[iterator] += inputt[i];
			}
			if (iterator == 2) {
				//////////////////////////////////////////////i,S,?
				if ((input[0].isDigit()) && (input[1] == "S" || input[1] == "s") && (input[2] == "?")) {
					if ((input[0].strtoint() - 1) < counterOfNodes) {
						couple* section = getSection(list, input[0].strtoint() - 1);
						std::cout << inputt << " == " << section->Znaczniki.size() << std::endl;
					}
				}
				//////////////////////////////////////////////i,S,j
				else if ((input[0].isDigit()) && (input[1] == "S") && (input[2].isDigit())) {
					if ((input[0].strtoint() - 1) < counterOfNodes) {
						couple* section = getSection(list, input[0].strtoint() - 1);
						int selector = input[2].strtoint() - 1;
						if (section->Znaczniki.size() > selector)
							std::cout << inputt << " == " << section->Znaczniki.get(selector)->value << std::endl;
					}
				}
				//////////////////////////////////////////////i,A,?
				else if ((input[0].isDigit()) && (input[1] == "A" || input[1] == "a") && (input[2] == "?")) {
					if ((input[0].strtoint() - 1) < counterOfNodes) {
						couple* section = getSection(list, input[0].strtoint() - 1);
						std::cout << inputt << " == " << section->Atrybuty.size() << std::endl;
					}
				}
				//////////////////////////////////////////////i,A,n
				else if ((input[0].isDigit()) && (input[1] == "A" || input[1] == "a")) {
					MyString attribute = input[2];
					if ((input[0].strtoint() - 1) < counterOfNodes) {
						couple* section = getSection(list, input[0].strtoint() - 1);
						int numberOfAttributes = section->Atrybuty.size();
						Node<MyString>* currentAttribute = section->Atrybuty.first;
						for (int i = 0; i < numberOfAttributes; i++) {
							if (currentAttribute->value.attributeName() == attribute) {
								std::cout << inputt << " == " << currentAttribute->value.attributeValue() << std::endl;
								break;
							}
							currentAttribute = currentAttribute->next;
						}
					}
				}
				//////////////////////////////////////////////i,D,*
				else if ((input[0].isDigit()) && (input[1] == "D" || input[1] == "d") && (input[2] == "*")) {
					int section = input[0].strtoint() - 1;
					int i = section;
					if (section < counterOfNodes) {
						int arrIndex = 0;
						Node<listNode>* current = list.first;
						i -= current->value.size;
						while (i >= 0) {
							current = current->next;
							arrIndex++;
							i -= current->value.size;
						}
						i += current->value.size;
						for (int j = 0; j < SIZE; j++) {
							if ((i == 0) && (current->value.isSet[j])) {
								current->value.isSet[j] = false;
								current->value.size--;
								counterOfNodes--;
								if (current->value.size == 0)
									list.remove(arrIndex);
								std::cout << inputt << " == deleted" << std::endl;
								break;
							}
							else {
								if (current->value.isSet[j])
									i--;
							}
						}
					}
				}
				//////////////////////////////////////////////i,D,n
				else if ((input[0].isDigit()) && (input[1] == "D" || input[1] == "d")) {
					int sectionIndex;
					int section = input[0].strtoint() - 1;
					int i = section;
					if (section < counterOfNodes) {
						int arrIndex = 0;
						Node<listNode>* current = list.first;
						i -= current->value.size;
						while (i >= 0) {
							current = current->next;
							arrIndex++;
							i -= current->value.size;
						}
						i += current->value.size;
						for (int j = 0; j < SIZE; j++) {
							if ((i == 0) && (current->value.isSet[j])) {
								MyString attribute = input[2];
								Node<MyString>* currentAttribute = current->value.array[j].Atrybuty.first;
								for (int k = 0; k < current->value.array[j].Atrybuty.size(); k++) {
									if (currentAttribute->value.attributeName() == attribute) {
										if (current->value.array[j].Atrybuty.size() <= 1) {//checking if we need to delete whole section list of attributes contains just one attribute
											current->value.isSet[j] = false;
											current->value.size--;
											counterOfNodes--;
											if (current->value.size == 0)
												list.remove(arrIndex);
										}
										else
											current->value.array[j].Atrybuty.remove(k);
										std::cout << inputt << " == deleted" << std::endl;
									}
									currentAttribute = currentAttribute->next;
								}
							}
							else {
								if (current->value.isSet[j])
									i--;
							}
						}
					}
				}
				//////////////////////////////////////////////n,A,?
				else if ((input[1] == "A" || input[1] == "a") && (input[2] == "?")) {
					int counterOfAttributes = 0;
					MyString attribute = input[0];
					Node<listNode>* current = list.first;
					for (int i = 0; i < list.size(); i++) {
						for (int j = 0; j < SIZE; j++) {
							if (current->value.isSet[j]) {
								Node<MyString>* currentAttribute = current->value.array[j].Atrybuty.last;
								for (int k = current->value.array[j].Atrybuty.size() - 1; k >= 0; k--) {
									if (currentAttribute->value.attributeName() == attribute) {
										counterOfAttributes++;
										break;
									}
									currentAttribute = currentAttribute->prev;
								}
							}
						}
						current = current->next;
					}
					std::cout << inputt << " == " << counterOfAttributes << std::endl;
				}
				//////////////////////////////////////////////z,S,?
				else if ((input[1] == "S" || input[1] == "s") && (input[2] == "?")) {
					int counterOfSelectors = 0;
					MyString selector = input[0];
					Node<listNode>* current = list.first;
					for (int i = 0; i < list.size(); i++) {
						for (int j = 0; j < SIZE; j++) {
							if (current->value.isSet[j]) {
								Node<MyString>* currentSelector = current->value.array[j].Znaczniki.last;
								for (int k = current->value.array[j].Znaczniki.size() - 1; k >= 0; k--) {
									if (currentSelector->value == selector) {
										counterOfSelectors++;
										break;
									}
									currentSelector = currentSelector->prev;
								}
							}
						}
						current = current->next;
					}
					std::cout << inputt << " == " << counterOfSelectors << std::endl;
				}
				//////////////////////////////////////////////z,E,n
				else if ((input[1] == "E" || input[1] == "e")) {
					MyString attribute = input[2];
					MyString selector = input[0];
					zEs(attribute, selector, inputt, list);
				}
				///////////////////////////////////////////////////
			}
		}
	}
}