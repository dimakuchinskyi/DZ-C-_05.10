#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Node {
private:
    T* _data = nullptr;
    int* _amount_of_data = nullptr;

    void delete_data() {
        if (_amount_of_data == nullptr) {
            if (_data != nullptr)
                delete _data;
        }
        else {
            if (_data != nullptr)
                delete[] _data;
            delete _amount_of_data;
        }
    }
public:
    Node() = default;
    Node(T data) {
        _data = new T{ data };
    }
    Node(T* data, int size) {
        _amount_of_data = new int{ size };
    }
    Node(const Node& other) {
        _data = new T{ *other._data };
        _amount_of_data = new int{ *other._amount_of_data };
    }

    void change_data(T new_value) {
        delete_data();
        _data = new T{ new_value };
    }

    void change_data(T* new_value, int size) {
        delete_data();

        _amount_of_data = new int{ size };
        _data = new T[size];

        for (int i = 0; i < size; i++) {
            _data[i] = new_value[i];
        }
    }

    T* get_data() {
        return _data;
    }

    int get_amount_of_data() {
        return *_amount_of_data;
    }

    ~Node() {
        delete_data();
    }
};

template<typename T>
class Stack {
private:
    Node<T>** _items = nullptr;
    const int _step = 10;
    int _size;
    int _fact_size = 0;

    void check_resize() {
        if (_fact_size == _size - 1) {
            resize();
        }
    }

    void resize() {
        Node<T>** new_items = new Node<T>*[_size + _step];
        for (int i = 0; i < _size; i++) {
            new_items[i] = _items[i];
        }
        delete[] _items;
        _items = new_items;
        _size += _step;
    }
public:
    Stack() {
        _size = _step;
        _items = new Node<T>*[_size];
    }

    void push(T value) {
        check_resize();
        Node<T>* new_node = new Node<T>(value);
        _items[_fact_size] = new_node;
        _fact_size++;
    }

    T pop() {
        if (_fact_size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        Node<T>* item = _items[_fact_size - 1];
        T* data = item->get_data();
        T result = *data;
        delete item;
        _fact_size--;
        return result;
    }

    T top() {
        if (_fact_size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        Node<T>* item = _items[_fact_size - 1];
        T* data = item->get_data();
        T result = *data;
        return result;
    }

    bool is_empty() {
        return _fact_size == 0;
    }

    ~Stack() {
        delete[] _items;
    }
};

bool are_brackets_matching(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

void check_brackets(const string& expression) {
    Stack<char> stack;
    for (size_t i = 0; i < expression.size(); i++) {
        char current_char = expression[i];

        if (current_char == '(' || current_char == '{' || current_char == '[') {
            stack.push(current_char);
        }
        else if (current_char == ')' || current_char == '}' || current_char == ']') {
            if (stack.is_empty()) {
                cout << "Error at position " << i << ": unexpected closing bracket '" << current_char << "'." << endl;
                return;
            }
            char open_bracket = stack.pop();
            if (!are_brackets_matching(open_bracket, current_char)) {
                cout << "Error at position " << i << ": mismatched brackets '" << open_bracket << "' and '" << current_char << "'." << endl;
                return;
            }
        }
        else if (current_char == ';') {
            break;
        }
    }

    if (!stack.is_empty()) {
        cout << "Error: there are unmatched opening brackets left." << endl;
    }
    else {
        cout << "The expression is correct." << endl;
    }
}

int main() {
    string expression = "({x-y-z} * [x + 2y] - (z + 4x));";

    check_brackets(expression);

    return 0;
}
