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
.container {
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  font-family: 'Segoe UI', sans-serif;
  background-image: url('/HIRKnjZaMAAYB76.jpg'); /* 随机二次元图API */
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