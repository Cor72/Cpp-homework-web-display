#include <iostream>
#include <string>
#include "httplib.h" // 引入下载的单头文件库
using namespace std;

// ================= 数据结构定义 =================
struct QNode {
    int data;
    QNode* next;
};

struct LinkQueue {
    QNode* front;
    QNode* rear;
};

// ================= 核心操作函数 =================
void InitQueue(LinkQueue* &Q) {
    Q = new LinkQueue;
    Q->front = NULL;
    Q->rear = NULL;
}

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
}

bool DeQueue(LinkQueue* Q, int &e) {
    if (Q->front == NULL) return false;
    QNode* temp = Q->front;
    e = temp->data;
    Q->front = temp->next;
    if (Q->front == NULL) Q->rear = NULL;
    delete temp;
    return true;
}

void ClearQueue(LinkQueue* Q) {
    QNode* p = Q->front;
    while (p != NULL) {
        QNode* temp = p;
        p = p->next;
        delete temp;
    }
    Q->front = NULL;
    Q->rear = NULL;
}

int FindQueue(LinkQueue* Q, int x) {
    QNode* p = Q->front;
    while (p != NULL) {
        if (p->data == x) return 1;
        p = p->next;
    }
    return 0;
}

// ================= HTTP API 服务 =================
int main() {
    httplib::Server svr;
    LinkQueue* Q = nullptr;
    InitQueue(Q); // 启动时初始化

    // 允许跨域（如果前后端分离跑在不同端口的话）
    svr.set_default_headers({{"Access-Control-Allow-Origin", "*"}});

    // 1. 初始化队列
    svr.Post("/api/init", [&](const httplib::Request&, httplib::Response& res) {
        ClearQueue(Q);
        res.set_content("初始化成功！", "text/plain");
    });

    // 2. 入队操作
    svr.Post("/api/enqueue", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("e")) {
            int e = stoi(req.get_param_value("e"));
            EnQueue(Q, e);
            res.set_content("入队成功", "text/plain");
        } else {
            res.set_content("缺少参数 e", "text/plain");
        }
    });

    // 3. 出队操作
    svr.Post("/api/dequeue", [&](const httplib::Request&, httplib::Response& res) {
        int e;
        if (DeQueue(Q, e)) {
            res.set_content(to_string(e), "text/plain");
        } else {
            res.set_content("队列为空", "text/plain");
        }
    });

    // 4. 获取队列所有元素 (前端用来展示)
    svr.Get("/api/list", [&](const httplib::Request&, httplib::Response& res) {
        string result = "";
        QNode* p = Q->front;
        while (p != NULL) {
            result += to_string(p->data);
            if (p->next != NULL) result += ",";
            p = p->next;
        }
        res.set_content(result, "text/plain");
    });

    // 5. 查找元素
    svr.Post("/api/find", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("x")) {
            int x = stoi(req.get_param_value("x"));
            res.set_content(to_string(FindQueue(Q, x)), "text/plain");
        } else {
            res.set_content("0", "text/plain");
        }
    });

    // 6. 置空队列
    svr.Post("/api/clear", [&](const httplib::Request&, httplib::Response& res) {
        ClearQueue(Q);
        res.set_content("已置空", "text/plain");
    });

    // 托管前端静态文件（交作业时用）
    svr.set_mount_point("/", "./public");

    cout << "C++ 后端服务已启动: http://localhost:8080" << endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}