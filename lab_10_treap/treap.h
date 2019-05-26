#ifndef _TREE_H_
#define _TREE_H_
#include <functional>
#include <iterator>
#include <iostream>
#include <cassert>

template<class T, class Compare = std::less<T>>
class BST {
private:
	class Node {
	public:
		T value;
		T& ref = value;
		int y;
		Node* left;
		Node* right;
		Node* parent;
		Node(const T& value, Node* new_parent);
	};

	Node* root;
	size_t current_size;

	void destroy(Node* cur);
	static Node* merge(Node*, Node*); 
	static std::pair<Node*, Node*> split(Node*, T key);
	static Node* get_min(Node*);
	static Node* get_max(Node*);
	static Node* next(Node* cur);
	static Node* prev(Node* cur);
	Node* find_node(const T& value) const;

public:
	template<class P>
	class TreeIterator {
	private:
		Node* ptr;
	public:
		TreeIterator(Node* new_ptr);
		TreeIterator() { ptr = nullptr; }

		P& operator*();
		bool operator!=(TreeIterator);
		bool operator==(TreeIterator);
		TreeIterator operator++();
		TreeIterator operator--();
		TreeIterator operator++(int);
		TreeIterator operator--(int);
	};

	typedef TreeIterator<T> iterator;
	typedef TreeIterator<const T> const_iterator;

	BST();
	BST(const BST&);
	BST& operator=(const BST&);
	~BST();

	template<class InputIt>
	void assign(InputIt first, InputIt last);

	iterator begin();
	const_iterator cbegin() const;
	iterator end();
	const_iterator cend() const;
	iterator back();
	const_iterator cback() const;
		
	iterator insert(const T& value);
	iterator remove(const T& value);
	iterator find(const T& value);
	const_iterator cfind(const T& value) const;
	
	bool empty() const;
	size_t size() const;

};

template<class T, class Compare>
bool BST<T, Compare>::empty() const {
	return (current_size == 0);
}

template<class T, class Compare>
size_t BST<T, Compare>::size() const {
	return current_size;
}

template<class T, class Compare>
typename BST<T, Compare>::Node* BST<T, Compare>::merge(Node* A, Node* B) {
	if (B == nullptr) {
		return A;
	}
	if (A == nullptr) {
		return B;
	}
	if (A->y > B->y) {
		A->right = merge(A->right, B);
		if (A->right) {
			A->right->parent = A;
		}
		return A;
	} else {
		B->left = merge(A, B->left);
		if (B->left) {
			B->left->parent = B;
		}
		return B;
	}
}

template<class T, class Compare>
std::pair<typename BST<T, Compare>::Node*, typename BST<T, Compare>::Node*> BST<T, Compare>::split(Node* cur, T key) {
	if (!cur) {
		return { nullptr, nullptr };
	} else {
		if (Compare()(cur->value, key)) {
			std::pair<Node*, Node*> AB = split(cur->right, key);
			Node* A = AB.first;
			Node* B = AB.second;
			cur->right = A;
			if (A) {
				A->parent = cur;
			}
			return { cur, B };
		} else {
			std::pair<Node*, Node*> AB = split(cur->left, key);
			Node* A = AB.first;
			Node* B = AB.second;
			cur->left = B;
			if (B) {
				B->parent = cur;
			}
			return { A, cur };
		}
	}
}

template<class T, class Compare>
typename BST<T, Compare>::Node* BST<T, Compare>::get_min(Node* cur) {
	if (!cur) {
		return nullptr;
	}
	while (cur->left) {
		cur = cur->left;
	}
	return cur;
}

template<class T, class Compare>
typename BST<T, Compare>::Node* BST<T, Compare>::get_max(Node* cur) {
	if (!cur) {
		return nullptr;
	}
	while (cur->right) {
		cur = cur->right;
	}
	return cur;
}

template<class T, class Compare>
BST<T, Compare>::BST() {
	root = nullptr;
	current_size = 0;
}

template<class T, class Compare>
void BST<T, Compare>::destroy(Node* cur) {
	if (!cur) {
		return;
	}
	destroy(cur->left);
	destroy(cur->right);
	delete cur;
	cur = nullptr;
}

template<class T, class Compare>
BST<T, Compare>::~BST() {
	destroy(root);
}

template<class T, class Compare>
BST<T, Compare>::BST(const BST& old_tree) : BST() {
	for (BST<T, Compare>::const_iterator it = old_tree.cbegin(); it != old_tree.cend(); it++) {
		insert(*it);
	}
}

template<class T, class Compare>
BST<T, Compare>& BST<T, Compare>::operator=(const BST& old_tree) {
	destroy(root);
	root = nullptr;
	current_size = 0;
	for (BST<T, Compare>::const_iterator it = old_tree.cbegin(); it != old_tree.cend(); it++) {
		insert(*it);
	}
	return *this;
}

template<class T, class Compare>
BST<T, Compare>::Node::Node(const T& value, Node* new_parent) {
	ref = value;
	left = nullptr;
	right = nullptr;
	parent = new_parent;
	y = rand();
}

template<class T, class Compare>
template<class P>
BST<T, Compare>::TreeIterator<P>::TreeIterator(Node* new_ptr) {
	ptr = new_ptr;
}

template<class T, class Compare> 
template<class InputIt>
void BST<T, Compare>::assign(InputIt first, InputIt last) {
	for (InputIt it = first; it != last; it++) {
		insert(*it);
	}
}

template<class T, class Compare>
template<class P>
P& BST<T, Compare>::TreeIterator<P>::operator*() {
	assert(ptr);
	return ptr->ref;
}

template<class T, class Compare>
typename BST<T, Compare>::iterator BST<T, Compare>::insert(const T& value) {
	if (find(value) != end()) {
		return iterator(root);
	}
	current_size++;
	std::pair<Node*, Node*> AB = split(root, value);
	Node* A = AB.first;
	Node* B = AB.second;
	if (A) {
		A->parent = nullptr;
	}
	if (B) {
		B->parent = nullptr;
	}
	A = merge(A, new Node(value, nullptr));
	root = merge(A, B);
	if (root) {
		root->parent = nullptr;
	}
	return iterator(root);
}

template<class T, class Compare>
typename BST<T, Compare>::iterator BST<T, Compare>::remove(const T& value) {
	if (find(value) == end()) {
		return iterator(root);
	}
	current_size--;
	std::pair<Node*, Node*> AB = split(root, value);
	Node* A = AB.first;
	Node* B = AB.second;
	if (A) {
		A->parent = nullptr;
	}
	if (B) {
		B->parent = nullptr;
	}
	Node* min_right = get_min(B);
	if (min_right->parent) {
		min_right->parent->left = min_right->right;
		if (min_right->right) {
			min_right->right->parent = min_right->parent;
		}
	} else {
		if (min_right->right) {
			min_right->right->parent = nullptr;
		}
		B = min_right->right;
	}
	delete min_right;
	min_right = nullptr;
	root = merge(A, B); 
	if (root) {
		root->parent = nullptr;
	}
	return iterator(root);
}

template<class T, class Compare>
typename BST<T, Compare>::Node* BST<T, Compare>::find_node(const T& value) const {
	Node* cur = root;
	while (cur) {
		if (Compare()(cur->value, value) == Compare()(value, cur->value)) {
			return cur;
		}
		if (Compare()(value, cur->value)) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	return nullptr;
}

template<class T, class Compare>
typename BST<T, Compare>::iterator BST<T, Compare>::find(const T& value) {
	return iterator(find_node(value));
}

template<class T, class Compare>
typename BST<T, Compare>::const_iterator BST<T, Compare>::cfind(const T& value) const {
	return const_iterator(find_node(value));
}

template<class T, class Compare>
typename BST<T, Compare>::iterator BST<T, Compare>::begin() {
	return iterator(get_min(root));
}

template<class T, class Compare>
typename BST<T, Compare>::iterator BST<T, Compare>::back() {
	return iterator(get_max(root));
}

template<class T, class Compare>
typename BST<T, Compare>::iterator BST<T, Compare>::end() {
	return iterator(nullptr);
}

template<class T, class Compare>
typename BST<T, Compare>::const_iterator BST<T, Compare>::cbegin() const {
	return const_iterator(get_min(root));
}

template<class T, class Compare>
typename BST<T, Compare>::const_iterator BST<T, Compare>::cback() const {
	return const_iterator(get_max(root));
}

template<class T, class Compare>
typename BST<T, Compare>::const_iterator BST<T, Compare>::cend() const {
	return const_iterator(nullptr);
}

template<class T, class Compare>
typename BST<T, Compare>::Node* BST<T, Compare>::next(Node* cur) {
	if (!cur) {
		return nullptr;
	}
	if (cur->right) {
		cur = get_min(cur->right);
	}
	else {
		while (cur->parent && cur->parent->right == cur) {
			cur = cur->parent;
		}
		cur = cur->parent;
	}
	return cur;
}

template<class T, class Compare>
typename BST<T, Compare>::Node* BST<T, Compare>::prev(Node* cur) {
	if (!cur) {
		return nullptr;
	}
	if (cur->left) {
		cur = get_max(cur->left);
	}
	else {
		while (cur->parent && cur->parent->left == cur) {
			cur = cur->parent;
		}
		cur = cur->parent;
	}
	return cur;
}

template<class T, class Compare>
template<class P>
BST<T, Compare>::TreeIterator<P> BST<T, Compare>::TreeIterator<P>::operator++() {
	ptr = next(ptr);
	return TreeIterator<P>(ptr);
}

template<class T, class Compare>
template<class P>
BST<T, Compare>::TreeIterator<P> BST<T, Compare>::TreeIterator<P>::operator--() {
	ptr = prev(ptr);
	return TreeIterator<P>(ptr);
}

template<class T, class Compare>
template<class P>
BST<T, Compare>::TreeIterator<P> BST<T, Compare>::TreeIterator<P>::operator++(int) {
	Node* cur = ptr;
	ptr = next(ptr);
	return TreeIterator<P>(cur);
}

template<class T, class Compare>
template<class P>
BST<T, Compare>::TreeIterator<P> BST<T, Compare>::TreeIterator<P>::operator--(int) {
	Node* cur = ptr;
	ptr = prev(ptr);
	return TreeIterator<P>(cur);
}

template<class T, class Compare>
template<class P>
bool BST<T, Compare>::TreeIterator<P>::operator!=(TreeIterator other) {
	return (other.ptr != ptr);
}

template<class T, class Compare>
template<class P>
bool BST<T, Compare>::TreeIterator<P>::operator==(TreeIterator other) {
	return (other.ptr == ptr);
}

#endif 