#include <iostream>
using namespace std;

struct QNode {
    int data;
    QNode* next;
};

struct LinkQueue {
    QNode* front;
    QNode* rear;
};

// (1) Initialize the linked queue
void InitQueue(LinkQueue* &Q) {
    Q = new LinkQueue;
    Q->front = NULL;
    Q->rear = NULL;
    cout << "Linked queue initialized successfully!" << endl;
}

// (2) Enqueue operation
void EnQueue(LinkQueue* Q, int e) {
    QNode* newNode = new QNode;
    newNode->data = e;
    newNode->next = NULL;
    
    if (Q->rear == NULL) {
        Q->front = newNode;
        Q->rear = newNode;
    } else {
        Q->rear->next = newNode;
        Q->rear = newNode;
    }
    cout << "Element " << e << " enqueued successfully!" << endl;
}

// (3) Dequeue operation
bool DeQueue(LinkQueue* Q, int &e) {
    if (Q->front == NULL) {
        cout << "Queue is empty, cannot dequeue!" << endl;
        return false;
    }
    QNode* temp = Q->front;
    e = temp->data;
    Q->front = temp->next;
    
    if (Q->front == NULL) {
        Q->rear = NULL;
    }
    delete temp;
    cout << "Element " << e << " dequeued successfully!" << endl;
    return true;
}

// (4) Print queue elements
void PrintQueue(LinkQueue* Q) {
    if (Q->front == NULL) {
        cout << "Queue is empty!" << endl;
        return;
    }
    cout << "Queue elements (front to rear): ";
    QNode* p = Q->front;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// (5) Queue length
int QueueLength(LinkQueue* Q) {
    int count = 0;
    QNode* p = Q->front;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// (6) Clear queue
void ClearQueue(LinkQueue* Q) {
    QNode* p = Q->front;
    while (p != NULL) {
        QNode* temp = p;
        p = p->next;
        delete temp;
    }
    Q->front = NULL;
    Q->rear = NULL;
    cout << "Queue cleared!" << endl;
}

// (7) Find element x
int FindQueue(LinkQueue* Q, int x) {
    QNode* p = Q->front;
    while (p != NULL) {
        if (p->data == x) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

// ================= Main function and menu =================
void ShowMenu() {
    cout << "\n====================================" << endl;
    cout << "       Linked Queue Menu System     " << endl;
    cout << "====================================" << endl;
    cout << "  1. Initialize queue" << endl;
    cout << "  2. Enqueue" << endl;
    cout << "  3. Dequeue" << endl;
    cout << "  4. Print queue" << endl;
    cout << "  5. Queue length" << endl;
    cout << "  6. Clear queue" << endl;
    cout << "  7. Find element" << endl;
    cout << "  0. Exit" << endl;
    cout << "====================================" << endl;
    cout << "Enter your choice (0-7): ";
}

int main() {
    LinkQueue* Q = NULL;
    int choice, e, x, len, result;
    
    while (true) {
        ShowMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (Q != NULL) {
                    cout << "Queue already exists. Reinitialize? (1: Yes, 0: No): ";
                    int confirm;
                    cin >> confirm;
                    if (confirm == 1) {
                        ClearQueue(Q);
                        delete Q;
                        InitQueue(Q);
                    }
                } else {
                    InitQueue(Q);
                }
                break;
                
            case 2:
                if (Q == NULL) {
                    cout << "Please initialize the queue first! (Choose 1)" << endl;
                } else {
                    cout << "Enter element to enqueue: ";
                    cin >> e;
                    EnQueue(Q, e);
                }
                break;
                
            case 3:
                if (Q == NULL) {
                    cout << "Please initialize the queue first! (Choose 1)" << endl;
                } else {
                    DeQueue(Q, e);
                }
                break;
                
            case 4:
                if (Q == NULL) {
                    cout << "Please initialize the queue first! (Choose 1)" << endl;
                } else {
                    PrintQueue(Q);
                }
                break;
                
            case 5:
                if (Q == NULL) {
                    cout << "Please initialize the queue first! (Choose 1)" << endl;
                } else {
                    len = QueueLength(Q);
                    cout << "Current queue length: " << len << endl;
                }
                break;
                
            case 6:
                if (Q == NULL) {
                    cout << "Please initialize the queue first! (Choose 1)" << endl;
                } else {
                    ClearQueue(Q);
                }
                break;
                
            case 7:
                if (Q == NULL) {
                    cout << "Please initialize the queue first! (Choose 1)" << endl;
                } else {
                    cout << "Enter element to find: ";
                    cin >> x;
                    result = FindQueue(Q, x);
                    if (result == 1) {
                        cout << "Found! Element " << x << " is in the queue." << endl;
                    } else {
                        cout << "Not found! Element " << x << " is not in the queue." << endl;
                    }
                }
                break;
                
            case 0:
                if (Q != NULL) {
                    ClearQueue(Q);
                    delete Q;
                }
                cout << "Thank you for using the system. Exiting..." << endl;
                system("pause");
                return 0;
                
            default:
                cout << "Invalid input! Please enter a number between 0-7." << endl;
        }
    }
    return 0;
}