#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
    char c;
    std::cout << "Type of queue (a - array, l - list): ";
    std::cin >> c;

    BasicQueue<int> *queue = NULL;
    if (c == 'a')
        queue = new ArrayQueue<int>;
    else if (c == 'l')
        queue = new ListQueue<int>;
    else {
        std::cout << "Bad type, exit" << std::endl;
        return 1;
    }

    bool basic_tested = false;
    bool full_add_tested = false;
    if(c == 'l') {
    	full_add_tested = true;
    }
    bool length_tested = false;

    char answer;
    while(true) {
    	cout << "What do you want to test? You can test: " << endl;
    	if(!basic_tested) {
    		cout << "Manipulations with basic queue (a)" << endl;
    	}
    	if(true) {
    		cout << "Deleting from the empty queue (this will immediately crash your program) (b)" << endl;
    	}
    	if(!full_add_tested) {
    		cout << "Adding to the full queue (c)" << endl;
    	}
    	if(!length_tested) {
    		cout << "Output of getLength method (d)" << endl;
    	}
    	cout << "Or exit (e)" << endl;
    	cout << "Input letter of your test. (a - e)" << endl;
    	cin >> answer;
    	if(answer == 'e') {
    		cout << "Exiting..." << endl;
    		break;
    	}
    	if(answer == 'a' && !basic_tested) {
    		cout << "Size of the empty queue is: " << queue->getLength() << endl;
    		queue->enqueue(5);
    		cout << "Size of queue after adding one element is: " << queue->getLength() << endl;
    		queue->enqueue(1);
    		cout << "Size of queue after adding two elements is: " << queue->getLength() << endl;
    		cout << "First element was: " << queue->dequeue() << " and second was: " << queue->dequeue() << endl;
    		cout << "Size of the queue after deleting all elements is: " << queue->getLength() << endl;
    		string result = " ";
    		while(result != "NO" && result != "NO") {
				cout << "Do you want to test deleting from the empty basic queue (This will crash your program)" << endl << "YES/NO?" << endl;
				cin >> result;
				if(result == "YES") {
					queue->dequeue();
				} else if(result != "NO") {
					cout << "Unknown answer" << endl;
				}
    		}
    		basic_tested = true;
    	} else if( answer == 'b') {
    		BasicQueue<int> *q;
    		if(c == 'a') {
    			q = new ArrayQueue<int>;
    		} else {
    			q = new ListQueue<int>;
    		}
    		cout << "Do you want to add some elements before deleting?" << endl;
    		string result;
    		while(true) {
    			cin >> result;
    			if(result == "YES") {
    				q->enqueue(1);
    				q->enqueue(2);
    				q->dequeue();
    				q->dequeue();
    				break;
    			} else if(result == "NO") {
    				break;
    			} else {
    				cout << "Unknown answer. Input YES or NO";
    			}
    		}
    		q->dequeue();
    	} else if(answer == 'c' && !full_add_tested) {
    		ArrayQueue<int, 4> aq;
    		for (int i = 0; i <= 3; i++) {
    			aq.enqueue(i);
    		}
    		cout << "If you see this message before error, adding to full queue works correctly" << endl;
    		aq.enqueue(4);
    		full_add_tested = true;
    	} else if(answer == 'd' && !length_tested) {
    		BasicQueue<int> *q;
    		if(c == 'l') {
    			q = new ListQueue<int>;
    		} else {
    			q = new ArrayQueue<int, 4>;
    		}

    		cout << "Size of the empty queue: " << q->getLength() << endl;
    		q->enqueue(1);
    		q->enqueue(2);
    		q->enqueue(3);
    		q->enqueue(4);
    		cout << "Size after adding four elements: " << q->getLength() << endl;
    		q->dequeue();
    		q->dequeue();
    		cout << "Size after deleting two elements: " << q->getLength() << endl;
    		if(c == 'a') {
    			q->enqueue(1);
    			q->enqueue(1);
    			cout << "Size of the cycled queue after adding two elements (in array case): " << q->getLength() << endl;
    		}
    		length_tested = true;
    		delete q;
    	} else {
    		cout << "Unknown letter" << endl;
    	}
    }
    cout << "Done" << endl;
    delete queue;
    return 0;
}
