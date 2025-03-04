#pragma once

template<typename T>
struct Node {
public:
    T data; // Данные узла
    int ind; // индекс элемента условного массива
    Node* next; // Указатель на следующий узел
    // Немного костыльно. Простити
    Node(T value, int index) : data(value), ind(index), next(nullptr) {}
};

template<typename T>
class ListIterator {
public:
    ListIterator(Node<T>* ptr) : m_ptr(ptr) {}

    T& operator*() const {
        return m_ptr->data;
    }

    ListIterator<T> operator++(int) {
        ListIterator<T> temp = *this;
        m_ptr = m_ptr->next;  // Переход к следующему узлу
        return temp;
    }

    ListIterator<T>& operator++() {
        m_ptr = m_ptr->next;  // Переход к следующему узлу
        return *this;
    }

    bool operator==(const ListIterator<T>& other) const {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const ListIterator<T>& other) const {
        return m_ptr != other.m_ptr;
    }

    int ind() {
        return m_ptr->ind;
    }

private:
    Node<T>* m_ptr; 
};

template<typename T>
class List {
    Node<T>* head = nullptr;
    Node<T>* ptr = nullptr;
public:
    List() : head(nullptr) {}

    List(std::initializer_list<T> lst) {
        int i = 0;
        for (auto& el : lst) {
            push_back(el, i++);
        }
    }

    List(const List& l) : head(nullptr), ptr(nullptr) {
        if (l.head != nullptr) {
            Node<T>* rp = l.head;
            head = new Node<T>{ rp->data, rp->ind };
            Node<T>* lp = head;
            ptr = head;
            while (rp->next != nullptr) {
                rp = rp->next;
                lp->next = new Node<T>{ rp->data,  rp->ind };
                lp = lp->next;
            }
        }
    }

    ~List() {
        clear();
    }

    bool operator==(const List& l) {
        auto it1 = l.begin(), it2 = begin();
        for (; it1 != nullptr && it2 != nullptr && *it1 == *it2; ++it1, ++it2) {}
        return (it1 == nullptr && it2 == nullptr);
    }

    bool operator!=(const List& l) {
        return !(*this == l);
    }

    void operator=(const List& l) {
        if (this != &l) {
            clear();
            for (auto it = l.begin(); it != l.end(); ++it) {
                push_back(*it, it.ind());
            }
        }
    }

    int ind() {
        return ptr->ind;
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    //добавляет, сортирует по ind
    void append(T value, int ind) {
        Node<T>* newNode = new Node<T>(value, ind);
        Node<T>* current = head;
        if (current == nullptr) {
            head = newNode;
            ptr = head;
        }
        else {
            while (current->next != nullptr && ind > current->next->ind) {
                current = current->next;
            }
            if (ind < head->ind) {
                newNode->next = head;
                head = newNode;

            }
            else if (current->next != nullptr && current->next->ind == ind)
                current->next->data += value; //если находим одинаковые индексы, то складываем значения
            else if (current->ind == ind)
                current->data += value; // current == head
            else {
                newNode->next = current->next;
                current->next = newNode; // "вклиниваем" newNode
            }
            if (ptr->ind < ind)
                ptr = ptr->next;
        }
    }

    // добавляет в конец
    void push_back(T value, int ind) {
        Node<T>* newNode = new Node<T>(value, ind);
        if (head == nullptr) {
            head = newNode;
            ptr = head;
        }
        else {
            newNode->next = ptr->next;
            ptr->next = newNode;
            ptr = ptr->next;
        }

    }

    // Отображение элементов списка
    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << '(' << current->ind << ") " << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // указатель на начало листа
    ListIterator<T> begin() const {
        return ListIterator<T>(head);
    }

    // указатель на nullptr
    ListIterator<T> end() const {
        return ListIterator<T>(nullptr); 
    }
};
