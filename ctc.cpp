#include "khaibao.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

// ==========================================
// 1. CÀI ĐẶT CẤU TRÚC ĐIỂN HÌNH (BST)
// ==========================================
FlashcardNode* createFlashcard(std::string word, std::string meaning, std::string example) {
    FlashcardNode* newNode = new FlashcardNode();
    newNode->word = word;
    newNode->meaning = meaning;
    newNode->example = example;
    newNode->interval = 1;
    newNode->easeFactor = 250;
    newNode->reviewCount = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->next = nullptr;
    return newNode;
}

FlashcardNode* insertBST(FlashcardNode* root, FlashcardNode* newNode) {
    if (root == nullptr) return newNode;
    if (newNode->word < root->word) {
        root->left = insertBST(root->left, newNode);
    }
    else if (newNode->word > root->word) {
        root->right = insertBST(root->right, newNode);
    }
    return root;
}

FlashcardNode* searchBST(FlashcardNode* root, std::string word) {
    if (root == nullptr || root->word == word) return root;
    if (word < root->word) return searchBST(root->left, word);
    return searchBST(root->right, word);
}

FlashcardNode* minValueNode(FlashcardNode* node) {
    FlashcardNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

FlashcardNode* deleteBST(FlashcardNode* root, std::string word) {
    if (root == nullptr) return root;
    if (word < root->word) {
        root->left = deleteBST(root->left, word);
    }
    else if (word > root->word) {
        root->right = deleteBST(root->right, word);
    }
    else {
        if (root->left == nullptr) {
            FlashcardNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            FlashcardNode* temp = root->left;
            delete root;
            return temp;
        }
        FlashcardNode* temp = minValueNode(root->right);
        root->word = temp->word;
        root->meaning = temp->meaning;
        root->example = temp->example;
        root->interval = temp->interval;
        root->easeFactor = temp->easeFactor;
        root->reviewCount = temp->reviewCount;
        root->right = deleteBST(root->right, temp->word);
    }
    return root;
}

void freeBST(FlashcardNode* root) {
    if (root == nullptr) return;
    freeBST(root->left);
    freeBST(root->right);
    delete root;
}

// ==========================================
// 2. CÀI ĐẶT HÀNG ĐỢI ƯU TIÊN (PRIORITY QUEUE)
// ==========================================
void initPriorityQueue(PriorityQueue& pq, int cap) {
    pq.capacity = cap;
    pq.size = 0;
    pq.heap = new FlashcardNode * [cap];
}

void swapNodes(FlashcardNode*& a, FlashcardNode*& b) {
    FlashcardNode* temp = a;
    a = b;
    b = temp;
}

void pqHeapifyUp(PriorityQueue& pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq.heap[index]->interval < pq.heap[parent]->interval) {
        swapNodes(pq.heap[index], pq.heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void pushPriorityQueue(PriorityQueue& pq, FlashcardNode* card) {
    if (pq.size == pq.capacity) return;
    pq.heap[pq.size] = card;
    pq.size++;
    pqHeapifyUp(pq, pq.size - 1);
}

void pqHeapifyDown(PriorityQueue& pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq.size && pq.heap[left]->interval < pq.heap[smallest]->interval)
        smallest = left;
    if (right < pq.size && pq.heap[right]->interval < pq.heap[smallest]->interval)
        smallest = right;

    if (smallest != index) {
        swapNodes(pq.heap[index], pq.heap[smallest]);
        pqHeapifyDown(pq, smallest);
    }
}

FlashcardNode* popPriorityQueue(PriorityQueue& pq) {
    if (pq.size <= 0) return nullptr;
    if (pq.size == 1) {
        pq.size--;
        return pq.heap[0];
    }
    FlashcardNode* root = pq.heap[0];
    pq.heap[0] = pq.heap[pq.size - 1];
    pq.size--;
    pqHeapifyDown(pq, 0);
    return root;
}

bool isPQEmpty(const PriorityQueue& pq) {
    return pq.size == 0;
}

// ==========================================
// 3. CÀI ĐẶT HÀNG ĐỢI THƯỜNG (SESSION QUEUE)
// ==========================================
void initQueue(SessionQueue& q) {
    q.front = nullptr;
    q.rear = nullptr;
}

void enqueue(SessionQueue& q, FlashcardNode* card) {
    QueueNode* newNode = new QueueNode{ card, nullptr };
    if (q.rear == nullptr) {
        q.front = q.rear = newNode;
        return;
    }
    q.rear->next = newNode;
    q.rear = newNode;
}

FlashcardNode* dequeue(SessionQueue& q) {
    if (q.front == nullptr) return nullptr;
    QueueNode* temp = q.front;
    FlashcardNode* card = temp->card;
    q.front = q.front->next;
    if (q.front == nullptr) q.rear = nullptr;
    delete temp;
    return card;
}

bool isQueueEmpty(const SessionQueue& q) {
    return q.front == nullptr;
}

// ==========================================
// 4. CÀI ĐẶT NGĂN XẾP HOÀN TÁC (UNDO STACK)
// ==========================================
void initStack(UndoStack& s) {
    s.top = nullptr;
}

void pushStack(UndoStack& s, FlashcardNode* card, bool result) {
    StackNode* newNode = new StackNode{ card, result, s.top };
    s.top = newNode;
}

StackNode* popStack(UndoStack& s) {
    if (s.top == nullptr) return nullptr;
    StackNode* temp = s.top;
    s.top = s.top->next;
    return temp;
}

bool isStackEmpty(const UndoStack& s) {
    return s.top == nullptr;
}

// ==========================================
// 5. THUẬT TOÁN & FILE
// ==========================================
void processAnswer(FlashcardNode* card, bool isCorrect, UndoStack& s) {
    pushStack(s, card, isCorrect);

    if (!isCorrect) {
        card->reviewCount = 0;
        card->interval = 1;
        card->easeFactor = std::max(130, card->easeFactor - 20);
    }
    else {
        if (card->reviewCount == 0) card->interval = 1;
        else if (card->reviewCount == 1) card->interval = 6;
        else {
            card->interval = static_cast<int>(std::round(card->interval * (card->easeFactor / 100.0)));
        }
        card->reviewCount++;
        card->easeFactor += 15;
    }
}

void saveBSTToStream(FlashcardNode* root, std::ofstream& outFile) {
    if (root == nullptr) return;
    outFile << root->word << "|" << root->meaning << "|" << root->example << "|"
        << root->interval << "|" << root->easeFactor << "|" << root->reviewCount << "\n";
    saveBSTToStream(root->left, outFile);
    saveBSTToStream(root->right, outFile);
}

void saveToFile(const std::string& filename, FlashcardNode* root) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) return;
    saveBSTToStream(root, outFile);
    outFile.close();
}

void loadFromFile(const std::string& filename, FlashcardNode*& bstRoot, PriorityQueue& pq) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return;

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string w, m, e, interStr, efStr, rcStr;

        if (std::getline(ss, w, '|') && std::getline(ss, m, '|') && std::getline(ss, e, '|') &&
            std::getline(ss, interStr, '|') && std::getline(ss, efStr, '|') && std::getline(ss, rcStr, '|')) {

            FlashcardNode* card = createFlashcard(w, m, e);
            card->interval = std::stoi(interStr);
            card->easeFactor = std::stoi(efStr);
            card->reviewCount = std::stoi(rcStr);

            bstRoot = insertBST(bstRoot, card);
            pushPriorityQueue(pq, card);
        }
    }
    inFile.close();
}

void countAndPrintStats(FlashcardNode* root, int& total, int& hardWords) {
    if (root == nullptr) return;
    countAndPrintStats(root->left, total, hardWords);
    total++;
    if (root->interval <= 2) hardWords++;
    std::cout << " - [" << root->word << "]: " << root->meaning << " (Lặp lại sau: " << root->interval << " ngày)\n";
    countAndPrintStats(root->right, total, hardWords);
}

void displayStatistics(FlashcardNode* root) {
    int total = 0, hardWords = 0;
    std::cout << "\n=== DANH SÁCH TỪ VỰNG TỪ ĐIỂN (A-Z) ===\n";
    countAndPrintStats(root, total, hardWords);
    std::cout << "-------------------------------------\n";
    std::cout << ">> Tổng số từ đang quản lý: " << total << "\n";
    std::cout << ">> Số lượng từ thuộc nhóm 'khó ghi nhớ' (Interval <= 2): " << hardWords << "\n";
}

void displayMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "              ĐỀ TÀI SỐ 5\n";
    std::cout << "=========================================\n";
    std::cout << "     FLASHCARD HỌC NGOẠI NGỮ (CLI)\n";
    std::cout << "=========================================\n";
    std::cout << "CHÀO MỪNG BẠN ĐẾN VỚI ỨNG DỤNG FLASHCARD\n";
    std::cout << "1. Thêm Flashcard mới\n";
    std::cout << "2. Tra cứu từ điển (BST search)\n";
    std::cout << "3. Bắt đầu phiên học (Queue + Heap)\n";
    std::cout << "4. Xem toàn bộ từ điển\n";
    std::cout << "5. Xóa 1 Flashcard\n";
    std::cout << "6. Lưu dữ liệu & Thoát ứng dụng\n";
    std::cout << "Vui lòng nhập lựa chọn của bạn (1-6): ";
}