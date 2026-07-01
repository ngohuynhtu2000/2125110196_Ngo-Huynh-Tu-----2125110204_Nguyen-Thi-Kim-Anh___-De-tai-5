#include "khaibao.h"
#include <iostream>
#include <string>
#include <Windows.h> // Thư viện bắt buộc để cấu hình hiển thị tiếng Việt

const std::string DATA_FILE = "flashcard_data.txt";

// Hàm hỗ trợ duyệt cây để xây dựng lại Heap phục vụ hàm xóa
void rebuildPQHelper(FlashcardNode* node, PriorityQueue& newPq) {
    if (node == nullptr) return;
    newPq.heap[newPq.size++] = node;
    rebuildPQHelper(node->left, newPq);
    rebuildPQHelper(node->right, newPq);
}

int main() {
    // Kích hoạt bảng mã UTF-8 cho Console Windows hiển thị chuẩn tiếng Việt có dấu
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    FlashcardNode* bstRoot = nullptr;
    PriorityQueue pq;
    initPriorityQueue(pq, 1000);

    loadFromFile(DATA_FILE, bstRoot, pq);

    int choice;
    while (true) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cout << "⚠️ Lỗi: Vui lòng chỉ nhập số ký tự điều hướng menu!\n";
            std::cin.clear();
            std::string ignoreLine;
            std::getline(std::cin, ignoreLine);
            continue;
        }
        std::cin.ignore();

        if (choice == 6) {
            saveToFile(DATA_FILE, bstRoot);
            std::cout << "💾 Đã đồng bộ dữ liệu vào file thành công. Tạm biệt!\n";
            break;
        }

        switch (choice) {
        case 1: {
            std::string word, meaning, example;
            std::cout << "👉 Nhập từ mới: "; std::getline(std::cin, word);
            std::cout << "👉 Nhập định nghĩa: "; std::getline(std::cin, meaning);
            std::cout << "👉 Nhập ví dụ minh họa: "; std::getline(std::cin, example);

            if (searchBST(bstRoot, word) != nullptr) {
                std::cout << "❌ Từ này đã tồn tại trong hệ thống!\n";
            }
            else {
                FlashcardNode* newCard = createFlashcard(word, meaning, example);
                bstRoot = insertBST(bstRoot, newCard);
                pushPriorityQueue(pq, newCard);
                std::cout << "✔️ Đã thêm flashcard thành công!\n";
            }
            break;
        }
        case 2: {
            std::string searchWord;
            std::cout << "🔎 Nhập từ cần tra cứu: "; std::getline(std::cin, searchWord);
            FlashcardNode* result = searchBST(bstRoot, searchWord);
            if (result == nullptr) {
                std::cout << "❌ Không tìm thấy từ '" << searchWord << "' trong từ điển.\n";
            }
            else {
                std::cout << "\n[KẾT QUẢ TÌM KIẾM]:\n";
                std::cout << " * Từ: " << result->word << "\n";
                std::cout << " * Nghĩa: " << result->meaning << "\n";
                std::cout << " * Ví dụ: " << result->example << "\n";
                std::cout << " * Lịch ôn tập (Interval): " << result->interval << " ngày\n";
            }
            break;
        }
        case 3: {
            if (isPQEmpty(pq)) {
                std::cout << "📭 Không có từ vựng nào khả dụng để học. Hãy thêm từ trước!\n";
                break;
            }

            SessionQueue sessionQ;
            initQueue(sessionQ);
            UndoStack undoS;
            initStack(undoS);

            int wordsInSession = 0;
            FlashcardNode* tempArr[5];
            while (!isPQEmpty(pq) && wordsInSession < 5) {
                FlashcardNode* currentCard = popPriorityQueue(pq);
                enqueue(sessionQ, currentCard);
                tempArr[wordsInSession] = currentCard;
                wordsInSession++;
            }

            std::cout << "\n🎬 BẮT ĐẦU PHIÊN HỌC TẬP (" << wordsInSession << " từ ưu tiên cao nhất)\n";
            while (!isQueueEmpty(sessionQ)) {
                FlashcardNode* card = dequeue(sessionQ);
                std::cout << "\n-----------------------------------------\n";
                std::cout << "Từ cần nhớ: 👉 " << card->word << " 👈\n";
                std::cout << "Bấm Enter để xem nghĩa...";
                std::cin.get();

                std::cout << "-> Nghĩa: " << card->meaning << "\n";
                std::cout << "-> Ví dụ: " << card->example << "\n\n";
                std::cout << "Bạn có nhớ từ này không? (1: Nhớ / 0: Quên / 2: Undo lượt vừa rồi): ";

                int ans;
                std::cin >> ans;
                std::cin.ignore();

                if (ans == 2) {
                    if (isStackEmpty(undoS)) {
                        std::cout << "↩️ Không có thao tác trước đó để Undo!\n";
                        enqueue(sessionQ, card);
                    }
                    else {
                        StackNode* lastAction = popStack(undoS);
                        std::cout << "↩️ Đã hoàn tác trạng thái từ: " << lastAction->card->word << "\n";
                        if (lastAction->userResult) {
                            lastAction->card->reviewCount--;
                        }
                        else {
                            lastAction->card->interval = 2;
                        }
                        enqueue(sessionQ, lastAction->card);
                        enqueue(sessionQ, card);
                        delete lastAction;
                    }
                }
                else {
                    bool correct = (ans == 1);
                    processAnswer(card, correct, undoS);
                    if (!correct) {
                        enqueue(sessionQ, card);
                        std::cout << "📌 Từ này sẽ xuất hiện lại ở cuối phiên học hôm nay.\n";
                    }
                }
            }

            for (int i = 0; i < wordsInSession; i++) {
                pushPriorityQueue(pq, tempArr[i]);
            }
            std::cout << "\n🎉 Chúc mừng bạn đã hoàn thành phiên học hôm nay!\n";
            break;
        }
        case 4: {
            displayStatistics(bstRoot);
            break;
        }
        case 5: {
            std::string delWord;
            std::cout << "❌ Nhập từ muốn xóa hoàn toàn: "; std::getline(std::cin, delWord);
            if (searchBST(bstRoot, delWord) == nullptr) {
                std::cout << "❌ Từ không tồn tại để xóa!\n";
            }
            else {
                bstRoot = deleteBST(bstRoot, delWord);

                PriorityQueue newPq;
                initPriorityQueue(newPq, 1000);

                rebuildPQHelper(bstRoot, newPq);

                for (int i = (newPq.size / 2) - 1; i >= 0; i--) {
                    pqHeapifyDown(newPq, i);
                }
                delete[] pq.heap;
                pq = newPq;
                std::cout << "✔️ Đã xóa từ '" << delWord << "' ra khỏi hệ thống từ điển và hàng đợi.\n";
            }
            break;
        }
        default:
            std::cout << "⚠️ Lựa chọn không hợp lệ. Vui lòng chọn từ 1 đến 6.\n";
        }
    }

    freeBST(bstRoot);
    delete[] pq.heap;
    return 0;
}