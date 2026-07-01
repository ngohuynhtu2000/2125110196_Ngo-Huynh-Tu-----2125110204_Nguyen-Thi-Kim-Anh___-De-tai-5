#ifndef KHAIBAO_H
#define KHAIBAO_H

#include <string>
#include <iostream>

// ==========================================
// 1. CẤU TRÚC DỮ LIỆU NỀN TẢNG (CORE DATA)
// ==========================================
struct FlashcardNode {
    std::string word;
    std::string meaning;
    std::string example;
    int interval;
    int easeFactor;
    int reviewCount;

    FlashcardNode* left;
    FlashcardNode* right;
    FlashcardNode* next;
};

// ==========================================
// 2. CẤU TRÚC HÀNG ĐỢI ƯU TIÊN (PRIORITY QUEUE)
// ==========================================
struct PriorityQueue {
    FlashcardNode** heap;
    int capacity;
    int size;
};

// ==========================================
// 3. CẤU TRÚC HÀNG ĐỢI THƯỜNG (QUEUE)
// ==========================================
struct QueueNode {
    FlashcardNode* card;
    QueueNode* next;
};

struct SessionQueue {
    QueueNode* front;
    QueueNode* rear;
};

// ==========================================
// 4. CẤU TRÚC NGĂN XẾP (STACK)
// ==========================================
struct StackNode {
    FlashcardNode* card;
    bool userResult;
    StackNode* next;
};

struct UndoStack {
    StackNode* top;
};

// ==========================================
// 5. DANH SÁCH CÁC HÀM PROTOTYPE (INTERFACES)
// ==========================================

void pqHeapifyUp(PriorityQueue& pq, int index);
void pqHeapifyDown(PriorityQueue& pq, int index);

// --- Nhóm hàm Quản lý Từ điển (BST) ---
FlashcardNode* createFlashcard(std::string word, std::string meaning, std::string example);
FlashcardNode* insertBST(FlashcardNode* root, FlashcardNode* newNode);
FlashcardNode* searchBST(FlashcardNode* root, std::string word);
FlashcardNode* deleteBST(FlashcardNode* root, std::string word);
void freeBST(FlashcardNode* root);

// --- Nhóm hàm Hàng đợi ưu tiên (Priority Queue) ---
void initPriorityQueue(PriorityQueue& pq, int cap);
void pushPriorityQueue(PriorityQueue& pq, FlashcardNode* card);
FlashcardNode* popPriorityQueue(PriorityQueue& pq);
bool isPQEmpty(const PriorityQueue& pq);

// --- Nhóm hàm Phiên học (Queue) ---
void initQueue(SessionQueue& q);
void enqueue(SessionQueue& q, FlashcardNode* card);
FlashcardNode* dequeue(SessionQueue& q);
bool isQueueEmpty(const SessionQueue& q);

// --- Nhóm hàm Hoàn tác (Stack) ---
void initStack(UndoStack& s);
void pushStack(UndoStack& s, FlashcardNode* card, bool result);
StackNode* popStack(UndoStack& s);
bool isStackEmpty(const UndoStack& s);

// --- Nhóm hàm Tính năng Hệ thống & File ---
void loadFromFile(const std::string& filename, FlashcardNode*& bstRoot, PriorityQueue& pq);
void saveToFile(const std::string& filename, FlashcardNode* root);
void processAnswer(FlashcardNode* card, bool isCorrect, UndoStack& s);
void displayMenu();
void displayStatistics(FlashcardNode* root);

#endif // KHAIBAO_H
