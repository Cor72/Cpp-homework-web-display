事情的起因是我要写一份期末 cpp 作业，但是我不是很想用那个黑咕隆咚的终端窗口展示，于是，我想写了个简单的前端页面来漂亮地展示它
一、完成作业
问题描述
题目17  链队列及其操作
问题描述：
实现链队列的以下操作：
（1）链队列的初始化，即生成一个空链队列；
（2）链队列的入队操作，即在已知队列的队尾插入一个元素e，即修改队尾指针；
（3）链队列的出队操作，即返回队首结点的元素值并删除队首结点；
（4）链队列的输出操作，即输出链队列中所有元素的值；
（5）链队列的求队长操作，即返回链队列中结点的个数；
（6）链队列的置空操作，即删除队列中的所有结点，仅留下指针结点；
（7）链队列的查找操作，即在链队列中查找数值为x的结点，成功返回1，否则返回0。
设计一个菜单，具有上述要求的所有功能、退出系统等最基本的功能。
cpp 源码
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

二、创建 C++后端
1. 下载单头文件库：去 GitHub 下载 cpp-httplib.h，放在你的项目目录下。
2. C++ 代码改写：保留原有的数据结构操作，去掉 main 里的 while 菜单循环，改用 HTTP 服务器监听请求。为了简单，入队和查找的参数直接通过 URL 传递，不需要复杂的 JSON 解析。
（你可以使用 AI 来完成这一步）
例如我的
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
3. 把你写的 C++ 代码文件（假设叫 main.cpp）和刚才下载的 httplib.h 放在同一个文件夹里。比如你在桌面上建个文件夹叫 QueueBackend，把这两个文件丢进去。
4. 打开 QueueBackend 的终端，输入以下命令并回车：bashg++ main.cpp -o server.exe -pthread-lws2_32
5. 如果没有报错，文件夹里会生成一个 server.exe。在终端里输入以下命令运行它：./server.exe看到终端打印 C++ 后端服务已启动: http://localhost:8080 就说明成功了！
三、完成前端
首先我们需要创建一个 vue3 的前端项目
在任意文件夹打开终端，输入
npm create vue@latest
✔ Project name: … <your-project-name>
✔ Add TypeScript? … No
✔ Add JSX Support? … No
✔ Add Vue Router for Single Page Application development? … No
✔ Add Pinia for state management? … No
✔ Add Vitest for Unit testing? … No
✔ Add an End-to-End Testing Solution? … No
✔ Add ESLint for code quality? … No
✔ Add Prettier for code formatting? … No
✔ Add Vue DevTools 7 extension for debugging? (experimental) … No

Scaffolding project in ./<your-project-name>...
Done.
一路 No 就行，注意要生成一个 空 项目，不要默认代码

把你的项目代码丢给 ai，让它帮你写一个简单的 app.vue 的前端界面，然后粘贴到 app.vue 就行，比如我的：
<template>
  <div class="container">
    <div class="card">
      <h1>🚀 链队列可视化系统</h1>
      
      <!-- 队列可视化区域 -->
      <div class="queue-display">
        <div class="tag tag-front">队首</div>
        <div class="queue-box">
          <div v-if="queueData.length === 0" class="empty-tip">空队列</div>
          <transition-group name="queue-anim" tag="div" class="queue-list">
            <div v-for="(item, index) in queueData" :key="item + '-' + index" class="queue-item">
              {{ item }}
            </div>
          </transition-group>
        </div>
        <div class="tag tag-rear">队尾</div>
      </div>

      <!-- 操作日志 -->
      <div class="message-box" v-if="message">
        {{ message }}
      </div>

      <!-- 按钮控制区 -->
      <div class="actions">
        <button class="btn btn-pink" @click="handleInit">初始化</button>
        <button class="btn btn-blue" @click="handleClear">置空</button>
        
        <div class="input-group">
          <input v-model="inputVal" type="number" placeholder="输入整数..." />
          <button class="btn btn-green" @click="handleEnqueue">入队</button>
        </div>

        <div class="input-group">
          <input v-model="searchVal" type="number" placeholder="查找数值..." />
          <button class="btn btn-orange" @click="handleFind">查找</button>
        </div>

        <button class="btn btn-red" @click="handleDequeue">出队</button>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'

const API_BASE = 'http://localhost:8080/api' // 开发时直连后端
const queueData = ref([])
const inputVal = ref('')
const searchVal = ref('')
const message = ref('')

// 获取队列数据
const fetchQueue = async () => {
  const res = await fetch(`${API_BASE}/list`)
  const text = await res.text()
  queueData.value = text ? text.split(',') : []
}

const handleInit = async () => {
  await fetch(`${API_BASE}/init`, { method: 'POST' })
  message.value = '队列已初始化！'
  await fetchQueue()
}

const handleEnqueue = async () => {
  if (!inputVal.value) return
  await fetch(`${API_BASE}/enqueue?e=${inputVal.value}`, { method: 'POST' })
  message.value = `元素 ${inputVal.value} 已入队`
  inputVal.value = ''
  await fetchQueue()
}

const handleDequeue = async () => {
  const res = await fetch(`${API_BASE}/dequeue`, { method: 'POST' })
  const text = await res.text()
  if (text !== '队列为空') {
    message.value = `元素 ${text} 已出队`
  } else {
    message.value = '队列为空，无法出队！'
  }
  await fetchQueue()
}

const handleFind = async () => {
  if (!searchVal.value) return
  const res = await fetch(`${API_BASE}/find?x=${searchVal.value}`, { method: 'POST' })
  const found = await res.text()
  message.value = found === '1' 
    ? `✅ 找到了元素 ${searchVal.value}` 
    : `❌ 没找到元素 ${searchVal.value}`
}

const handleClear = async () => {
  await fetch(`${API_BASE}/clear`, { method: 'POST' })
  message.value = '队列已置空！'
  await fetchQueue()
}

onMounted(() => {
  fetchQueue()
})
</script>

<style scoped>
/* 选一个好看的二次元背景图，这里用随机图做演示 */
.container {
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  font-family: 'Segoe UI', sans-serif;
  background-image: url('https://api.dujin.org/img/acg.php'); /* 随机二次元图API */
  background-size: cover;
  background-position: center;
}

.card {
  background: rgba(255, 255, 255, 0.85);
  backdrop-filter: blur(12px);
  padding: 30px 40px;
  border-radius: 20px;
  box-shadow: 0 8px 32px rgba(31, 38, 135, 0.2);
  border: 1px solid rgba(255, 255, 255, 0.18);
  width: 700px;
  text-align: center;
}

h1 { color: #333; margin-bottom: 20px; }

/* 队列可视化 */
.queue-display {
  display: flex;
  align-items: center;
  justify-content: center;
  margin: 20px 0;
}
.tag { padding: 5px 10px; border-radius: 8px; font-size: 12px; color: white; }
.tag-front { background: #ff6b6b; margin-right: 10px; }
.tag-rear { background: #4ecdc4; margin-left: 10px; }

.queue-box {
  min-height: 60px;
  min-width: 400px;
  border: 2px dashed #aaa;
  border-radius: 10px;
  display: flex;
  align-items: center;
  padding: 0 10px;
}
.empty-tip { color: #999; width: 100%; }
.queue-list { display: flex; }

.queue-item {
  background: #a29bfe;
  color: white;
  padding: 10px 15px;
  border-radius: 8px;
  margin: 0 5px;
  font-weight: bold;
  transition: all 0.3s ease;
}

/* Vue 过渡动画 */
.queue-anim-enter-active, .queue-anim-leave-active {
  transition: all 0.4s ease;
}
.queue-anim-enter-from { opacity: 0; transform: translateX(30px); }
.queue-anim-leave-to { opacity: 0; transform: translateX(-30px); }

/* 日志信息 */
.message-box {
  background: #fff;
  padding: 10px;
  border-radius: 8px;
  margin: 15px 0;
  color: #555;
  font-weight: bold;
}

/* 按钮 */
.actions { display: flex; flex-wrap: wrap; gap: 10px; justify-content: center; align-items: center; }
.input-group { display: flex; gap: 5px; }
input {
  padding: 8px 12px;
  border: 1px solid #ccc;
  border-radius: 8px;
  outline: none;
}
.btn {
  padding: 8px 16px;
  border: none;
  border-radius: 8px;
  color: white;
  cursor: pointer;
  font-weight: bold;
  transition: transform 0.1s;
}
.btn:active { transform: scale(0.95); }
.btn-pink { background: #ff6b6b; }
.btn-blue { background: #74b9ff; }
.btn-green { background: #55efc4; color: #333; }
.btn-orange { background: #ffeaa7; color: #333; }
.btn-red { background: #fab1a0; color: #333; }
</style>
注意后端端口是 8080
现在
npm run dev
运行前端项目
再找到后端文件夹，在终端里输入
./server.exe
运行后端项目
然后你就可以看到你的 cpp 项目以前端的方式跑起来了

四、把前端和后端打包到一起（可选）
第一步：建文件夹
在你想交作业的地方（比如桌面上），新建一个文件夹，名字随便取，比如叫 链队列大作业。
在前端项目中执行 npm run build，在 dist 目录生成纯静态网页（HTML/CSS/JS）。
第二步：放文件（最终目录结构）
把你现有的东西按下面的结构放进去：
链队列大作业/ <-- 你新建的文件夹
│
├── server.exe <-- 把你编译出来的 exe 放在这里
│
└── public/ <-- 在这里新建一个名叫 public 的文件夹
 ├── index.html <-- 把你前端 dist 里面的所有文件，全部复制到 public 里面
 ├── assets/
 │ ├── index.css
 │ └── index.js
 └── ... (dist 里的其他文件)
关键点：server.exe 和 public 文件夹必须在同一个目录下，也就是像上面那样并排着。
第三步：测试运行
1. 双击运行 server.exe。
2. 打开浏览器，地址栏输入 http://localhost:8080 并回车。
3. 你的界面就会直接显示出来，而且点击按钮前后端全通！
