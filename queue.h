#pragma once


template<typename T>
class BasicQueue
{
public:

    // Add element to the end
    virtual void enqueue(const T &val) = 0;

    // Return first element
    virtual T dequeue() = 0;

    // Get total count of elements
    virtual unsigned getLength() const = 0;

protected:
    unsigned size;
};

template<typename T>
class ListQueue: public BasicQueue<T>
{

public:

    ListQueue() {
    	this->size = 0;
    	head = NULL;
    }

    ~ListQueue() {
    	while(head != NULL) {
    		Node<T> *b = head->next;
    		delete head;
    		head = b;
    	}
    }

    template<typename A>
    class Node {
    public:
    	Node() {
    		next = NULL;
    		data = 0;
    	}

    	Node<A> *next;

    	A data;
    };

    void enqueue(const T &val) override {
    	if(head == NULL) {
    		head = new Node<T>;
    		head->next = NULL;
    		head->data = val;
    	} else {
    		Node<T>* last = head;
    		while(last->next != NULL) {
    			last = last->next;
    		}
    		Node<T> *New = new Node<T>;
    		New->data = val;
    		New->next = NULL;
    		last->next = New;
    	}
    	this->size++;
    }

    T dequeue() override {
    	if(head == NULL) {
    		std::cout << "ERROR! YOU'RE DELETING FROM THE EMPTY QUEUE!" << std::endl;
    		exit(1);
    	}
    	Node<T> b = *head;
    	delete head;
    	head = b.next;
    	this->size--;
    	return b.data;
    }


    unsigned getLength() const override {
    	return this->size;
    }

    /*
     * Fully implement class:
     * - declarations here
     * - definitions in queue.cpp
     * Could have infinite size
     */
private:
    Node<T>* head;
};

template<typename T, unsigned N = 64>
class ArrayQueue: public BasicQueue<T>
{
public:
    ArrayQueue() {
    	this->size = 0;
    	current = 0;
    }

    void enqueue(const T &val) override {
    	if(this->size < N) {
    		arr[current] = val;
    		current = (current + 1) % N;
        	this->size++;
    	} else {
    		std::cout << "ERROR! YOU'RE ADDING TO FULL QUEUE!" << std::endl;
    	}
    }

    T dequeue() override {
    	if(this->size != 0) {
    		T b;
    		if(current >= this->size) {
        		b = arr[current - this->size];
    		} else {
    			b = arr[N - (this->size - current)];
    		}
    		this->size--;
    		return b;

    	} else {
    		std::cout << "ERROR! YOU'RE DELETING FROM THE EMPTY QUEUE!" << std::endl;
    		exit(1);
    	}
    }

    unsigned getLength() const override {
    	return this->size;
    }

    /*
     * Fully implement class:
     * - declarations here
     * - definitions in queue.cpp
     * Only finite size implementation is required
     */
private:
    T arr[N];
    unsigned current; //number of the element after the last element in the queue
};
