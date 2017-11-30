//
// Created by Роман Климовицкий on 24.11.2017.
//

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#include <iostream>
#include <vector>
#include <cassert>
#include <gtest/gtest.h>

template <typename Type, typename DequeType>
class DequeIterator : public std::iterator<std::random_access_iterator_tag, Type> {
private:
    DequeType* deque;
    long long diff;

public:
    explicit DequeIterator(DequeType& deque, long long diff = 0) : deque(&deque), diff(diff) { }
    DequeIterator(const DequeIterator& iter) : deque(iter.deque), diff(iter.diff) { }

    DequeIterator& operator=(const DequeIterator& iter) {
        if(this == &iter) {
            return *this;
        }
        this->deque = iter.deque;
        this->diff = iter.diff;
        return *this;
    }

    DequeIterator& operator++() {
        ++diff;
        return *this;
    }

    DequeIterator operator++(int) {
        DequeIterator tmp(*this);
        ++diff;
        return tmp;
    }


    DequeIterator& operator--() {
        --diff;
        return *this;
    }

    DequeIterator operator--(int) {
        DequeIterator tmp(*this);
        --diff;
        return tmp;
    }


    friend DequeIterator operator+(const DequeIterator& iter, long long diff) {
        DequeIterator newIter(iter);
        newIter.diff += diff;
        return newIter;
    }

    friend DequeIterator operator+(long long diff, const DequeIterator& iter) { return iter + diff; }


    friend DequeIterator operator-(const DequeIterator& iter, long long diff) {
        DequeIterator newIter(iter);
        newIter.diff -= diff;
        return newIter;
    }


    DequeIterator& operator+=(long long diff) {
        this->diff += diff;
        return *this;
    }

    DequeIterator& operator-=(long long diff) {
        this->diff -= diff;
        return *this;
    }


    friend long long operator-(const DequeIterator& iter1, const DequeIterator& iter2) { return iter1.diff - iter2.diff; }

    friend bool operator==(const DequeIterator& iter1, const DequeIterator& iter2) { return (iter1.diff == iter2.diff); }
    friend bool operator!=(const DequeIterator& iter1, const DequeIterator& iter2) { return !(iter1 == iter2); }
    friend bool operator<(const DequeIterator& iter1, const DequeIterator& iter2) { return iter1.diff < iter2.diff; }
    friend bool operator<=(const DequeIterator& iter1, const DequeIterator& iter2) { return (iter1 == iter2 || iter1 < iter2); }
    friend bool operator>(const DequeIterator& iter1, const DequeIterator& iter2) { return !(iter1 <= iter2); }
    friend bool operator>=(const DequeIterator& iter1, const DequeIterator& iter2) { return !(iter1 < iter2); }


    Type& operator*() {
        return (*deque)[diff];
    }

    Type& operator[](long long i) {
        return (*deque)[diff + i];
    }

    Type* operator->() {
        return &((*deque)[diff]);
    }
};

template <typename Type>
class Deque {
private:
    std::vector<Type> rightData_;
    std::vector<Type> leftData_;

public:
    Deque() { }
    Deque(const Deque &deque) {
        for(size_t i = 0; i < deque.leftData_.size(); ++i) {
            this->leftData_.push_back(deque.leftData_[i]);
        }
        for(size_t i = 0; i < deque.rightData_.size(); ++i) {
            this->rightData_.push_back(deque.rightData_[i]);
        }
    }

    void push_back(const Type& n) { rightData_.push_back(n); }
    void pop_back() {
        if(empty()) {
            return;
        }
        if(!rightData_.empty()) {
            rightData_.pop_back();
            return;
        }
        size_t newRSize = (leftData_.size() + 1) / 2;
        size_t newLSize = leftData_.size() - newRSize;
        for(size_t i = newRSize; i > 0; --i) {
            rightData_.push_back(leftData_[i - 1]);
        }
        for(size_t i = 0; i < newLSize; ++i) {
            leftData_[i] = leftData_[i + newRSize];
        }
        while(leftData_.size() > newLSize) {
            leftData_.pop_back();
        }
        rightData_.pop_back();
    }


    void push_front(const Type& n) { leftData_.push_back(n); }
    void pop_front() {
        if(empty()) {
            return;
        }
        if(!leftData_.empty()) {
            leftData_.pop_back();
            return;
        }
        size_t newLSize = (rightData_.size() + 1) / 2;
        size_t newRSize = rightData_.size() - newLSize;
        for(size_t i = newLSize; i > 0; --i) {
            leftData_.push_back(rightData_[i - 1]);
        }
        for(size_t i = 0; i < newRSize; ++i) {
            rightData_[i] = rightData_[i + newLSize];
        }
        while(rightData_.size() > newRSize) {
            rightData_.pop_back();
        }
        leftData_.pop_back();
    }


    Type& operator[](size_t i) {
        if(i < leftData_.size()) {
            return leftData_[leftData_.size() - i - 1];
        } else {
            return rightData_[i - leftData_.size()];
        }
    }

    const Type& operator[](size_t i) const {
        if(i < leftData_.size()) {
            return leftData_[leftData_.size() - i - 1];
        } else {
            return rightData_[i - leftData_.size()];
        }
    }


    Type& back() {
        if(!rightData_.empty()) {
            return rightData_.back();
        }
        return leftData_.front();
    }

    const Type& back() const {
        if(!rightData_.empty()) {
            return rightData_.back();
        }
        return leftData_.front();
    }


    Type& front() {
        if(!leftData_.empty()) {
            return leftData_.back();
        }
        return rightData_.front();
    }

    const Type& front() const {
        if(!leftData_.empty()) {
            return leftData_.back();
        }
        return rightData_.front();
    }


    bool empty() const { return size() == 0; }

    size_t size() const { return rightData_.size() + leftData_.size(); }

    typedef DequeIterator<Type, Deque> iterator;
    typedef DequeIterator<const Type, const Deque> const_iterator;
    typedef std::reverse_iterator<DequeIterator<Type, Deque>> reverse_iterator;
    typedef std::reverse_iterator<DequeIterator<const Type, const Deque>> const_reverse_iterator;

    iterator begin() {
        iterator iter(*this);
        return iter;
    }

    const const_iterator begin() const { return const_iterator(*this); }
    const const_iterator cbegin() const { return const_iterator(*this); }


    iterator end() {
        iterator iter(*this, size());
        return iter;
    }

    const const_iterator end() const { return const_iterator(*this, size()); }
    const const_iterator cend() const { return const_iterator(*this, size()); }


    reverse_iterator rbegin() {
        reverse_iterator rbIter(end());
        return rbIter;
    }

    const const_reverse_iterator rbegin() const { return const_reverse_iterator(cend()); }
    const const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }

    reverse_iterator rend() {
        reverse_iterator reIter(begin());
        return reIter;
    }

    const const_reverse_iterator rend() const { return const_reverse_iterator(cbegin()); }
    const const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

    void clear() {
        rightData_.clear();
        leftData_.clear();
    }
};


#endif //DEQUE_DEQUE_H