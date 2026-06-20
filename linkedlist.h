#pragma once

#include <iostream> // std::cout
#include <optional> // element getter return type
#include <utility>  // std::as_const to treat *this as a const

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T m_data{};
        Node* m_nextPtr{};
    };

    static Node* createNode(const T data);

private:
    Node* m_head{};
    Node* m_tail{};
    std::size_t m_size{};

public:
    LinkedList() = default;
    LinkedList(const LinkedList& other) { copy(other); }
    ~LinkedList() { clear(); }

    void pushBack(const T data);
    void pushFront(const T data);
    void clear();
    void copy(const LinkedList<T>& other);

    std::optional<T> get(const std::size_t index) const;
    std::size_t getSize() const { return m_size; }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const LinkedList<U>& ll);

    LinkedList& operator=(const LinkedList<T>& other);
    const T& operator[](const std::size_t index) const;
    T& operator[](const std::size_t index);
};

template <typename T>
const T& LinkedList<T>::operator[](const std::size_t index) const
{
    LinkedList::Node* temp { m_head };
    std::size_t i{};

    for (; temp && i != index; ++i) {
        temp = temp->m_nextPtr;
    }

    return temp->m_data;
}

template <typename T>
T& LinkedList<T>::operator[](const std::size_t index)
{
    // std::as_const()  -> get a const version of the implicit object
    // const_cast<T&>() -> remove the const to allow element modification
    return const_cast<T&>(std::as_const(*this)[index]);
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& other)
{
    if (m_head) {
        clear();
    }

    const LinkedList::Node* otherHead {other.m_head};

    while (otherHead) {
        pushBack(otherHead->m_data);
        otherHead = otherHead->m_nextPtr;
    }
}

template <typename T>
void LinkedList<T>::clear()
{
    while (m_head) {
        LinkedList<T>::Node* temp { m_head->m_nextPtr };
        delete m_head;
        m_head = temp;
    }

    m_tail = nullptr;
    m_size = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if (this == &other) {
        return *this;
    }

    copy(other);
    return *this;
}

template <typename U>
std::ostream& operator<<(std::ostream& out, const LinkedList<U>& ll)
{
    std::cout << '[';
    auto separator { "" };

    typename LinkedList<U>::Node* temp { ll.m_head };

    while (temp != nullptr) {
        std::cout << separator << temp->m_data;
        separator = ", ";
        temp = temp->m_nextPtr;
    }

    std::cout << ']';
    return out;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::createNode(const T data)
{
    Node* node { new (std::nothrow) Node };

    if (!node) {
        return nullptr;
    }

    node->m_data = data;
    return node;
}

template <typename T>
void LinkedList<T>::pushBack(const T data)
{
    Node* node { LinkedList<T>::createNode(data) };

    if (!node) {
        std::cerr << "ERROR: Node allocation failed.\n";
        return;
    }

    if (m_head == nullptr) {
        m_head = node;
    } else {
        m_tail->m_nextPtr = node;
    }

    m_tail = node;
    ++m_size;
}

template <typename T>
void LinkedList<T>::pushFront(const T data)
{
    Node* node { LinkedList<T>::createNode(data) };

    if (!node) {
        std::cerr << "ERROR: Node allocation failed.\n";
        return;
    }

    if (m_head == nullptr) {
        m_tail = node;
    } else {
        node->m_nextPtr = m_head;
    }

    m_head = node;
    ++m_size;
}

template <typename T>
std::optional<T> LinkedList<T>::get(const std::size_t index) const
{
    if (index >= m_size) {
        return {};
    }

    return (*this)[index];
}
