
#ifndef MYPROJECT_H
#define MYPROJECT_H

#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void addElement(int data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    int searchByIndex(int index) {
        Node* curr = head;
        int count = 0;

        while (curr != nullptr) {
            if (count == index) {
                return curr->data;
            }
            count++;
            curr = curr->next;
        }

        // ≈сли индекс выходит за пределы списка, возвращаем -1 или бросаем исключение
        return -1;
    }

    void deleteByIndex(int index) {
        if (head == nullptr) {
            return;
        }

        Node* curr = head;
        if (index == 0) {
            head = head->next;
            delete curr;
            return;
        }

        Node* prev = nullptr;
        int count = 0;

        while (curr != nullptr && count != index) {
            prev = curr;
            curr = curr->next;
            count++;
        }

        if (curr == nullptr) {
            // ≈сли индекс выходит за пределы списка, ничего не удал€ем
            return;
        }

        prev->next = curr->next;
        delete curr;
    }
    int showlast() {


        int data = head->data;
        return data;
    }
    void lastdelete() {

        Node* temp = head;
        head = head->next;
        delete temp;


    }
    bool isEmpty() const {
        return head == nullptr;
    }
    void showList() {
        Node* curr = head;
        while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
};

class Stack {
public:
	LinkedList llist;
	void push(int data) {
		llist.addElement(data);
	}
	void pop() {
		if (llist.isEmpty()) {
			throw std::runtime_error("Empty List");
		}
		llist.lastdelete();
	}
	char top() {
		return llist.showlast();
	}


	bool isEmpty() const {
		return llist.isEmpty();
	}

};

class parser {
public:
	bool isOperator(char c) {
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
			return true;
		}
		return false;
	}
	bool hasHigherPrecedence(char op1, char op2) {
		int priority1 = 0, priority2 = 0;
		if (op1 == '+' || op1 == '-')
			priority1 = 1;
		else
			priority1 = 2;
		if (op2 == '+' || op2 == '-')
			priority2 = 1;
		else
			priority2 = 2;
		return(priority1 >= priority2);
	}
public:
	std::string IntoPost(std::string infix) {
		std::string post;
		Stack op;
		for (char& c : infix) {
			if (isalnum(c)) {
				post += c;

			}
			else if (c == '(') {

				op.push(c);
			}
			else if (c == ')') {
				while (!op.isEmpty() && op.top() != '(') {
					post += " ";
					post += op.top();
					op.pop();
				}

				if (!op.isEmpty() && op.top() == '(') {
					post += " ";
					op.pop();
				}
			}
			else if (isOperator(c)) {
				post += " ";
				while (!op.isEmpty() && op.top() != '(' && hasHigherPrecedence(op.top(), c)) {
					post += " ";
					post += op.top();
					post += " ";
					op.pop();
				}
				op.push(c);

			}

		}
		while (!op.isEmpty()) {
			post += " ";
			post += op.top();
			post += " ";
			op.pop();
		}
		return post;
	}


};

class pcalc {
private:
	Stack stack;

private:
	bool isOperator(char op) {
		return op == '+' || op == '-' || op == '*' || op == '/';
	}

	int operation(char op, int op1, int op2) {
		switch (op) {
		case('+'):
			return op1 + op2;
		case('-'):
			return op1 - op2;
		case('*'):
			return op1 * op2;
		case('/'):
			if (op2 == 0) {
				throw std::runtime_error("Division by 0");

			}
			return op1 / op2;
		default:
			return 0;
		}
	}
public:
	int calc(std::string s) {
		int size = s.length();

		for (int i = 0; i < size; i++) {
			if (isdigit(s[i])) {
				int num = 0;
				while (i < size && isdigit(s[i])) {
					num = num * 10 + (s[i] - '0');
					i++;
				}
				stack.push(num);

			}
			else if (s[i] == ' ') {
				continue;
			}
			else if (isOperator(s[i])) {
				int op2 = stack.top();
				stack.pop();
				int op1 = stack.top();
				stack.pop();
				try {
					int res = operation(s[i], op1, op2);
					stack.push(res);
				}
				catch (const std::runtime_error& e) {
					std::cerr << e.what() << std::endl;
					exit(0);
				}
			}
		}
		return stack.top();
	}


};

bool containsLetters(const std::string& str) {
	for (char c : str) {
		if (std::isalpha(c)) {
			return true;
		}
	}
	return false;
}

bool checkBrackets(const std::string& str) {
	Stack bracket;

	for (char c : str) {
		if (c == '(') {
			bracket.push(c);
		}
		else if (c == ')') {
			if (bracket.isEmpty()) {
				return false;
			}

			char top = bracket.top();
			bracket.pop();

			if ((c == ')' && top != '(')) {
				return false;
			}
		}
	}

	return bracket.isEmpty();
}

#endif  // MYPROJECT_H