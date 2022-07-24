#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// 我的解法：三次遍历，时间 12 ms 19.14%，空间 11 MB 78.26%
//class Solution {
//public:
//    Node* copyRandomList(Node* head) {
//        vector<Node*> hashMap;
//        for (Node* curr = head; curr != nullptr; curr = curr->next) {
//            hashMap.emplace_back(curr);
//        }
//        Node* next = nullptr, *curr = nullptr;
//        unordered_map<Node*, Node*> hashMap2;
//        for_each(hashMap.rbegin(), hashMap.rend(), [&next, &curr, &hashMap2](Node*& lhs){
//            curr = new Node(lhs->val);
//            curr->next = next;
//            curr->random = lhs->random;
//            hashMap2.emplace(lhs, curr);
//            next = curr;
//        });
//        for (Node* node = curr; node != nullptr; node = node->next) {
//            if (node->random != nullptr) {
//                node->random = hashMap2[node->random];
//            }
//        }
//        return curr;
//    }
//};

// 我的解法：两次遍历，时间 8 ms 74.99%，空间 11 MB 73.49%
//class Solution {
//public:
//    Node* copyRandomList(Node* head) {
//        Node* prev = nullptr, *curr = nullptr;
//        unordered_map<Node*, Node*> hashMap;
//        for (Node* node = head; node != nullptr; node = node->next) {
//            curr = new Node(node->val);
//            curr->random = node->random;
//            hashMap.emplace(node, curr);
//            if (prev != nullptr) {
//                prev->next = curr;
//            }
//            prev = curr;
//        }
//        Node* newHead = hashMap[head];
//        for (Node* node = newHead; node != nullptr; node = node->next) {
//            if (node->random != nullptr) {
//                node->random = hashMap[node->random];
//            }
//        }
//        return newHead;
//    }
//};

// 官方解法一：时间 O(n) 8 ms 74.99%，空间 O(n) 11.4 MB 8.97%
// 利用回溯的方式，让每个节点的拷贝操作相互独立。对于当前节点，我们首先要进行拷贝，然后我们进行「当前节点的后继节点」和「当前节点的随机指针指向的节点」拷贝，拷贝完成后将创建的新节点的指针返回，即可完成当前节点的两指针的赋值。
// 我们用哈希表记录每一个节点对应新节点的创建情况。遍历该链表的过程中，我们检查「当前节点的后继节点」和「当前节点的随机指针指向的节点」的创建情况。如果这两个节点中的任何一个节点的新节点没有被创建，我们都立刻递归地进行创建。当我们拷贝完成，回溯到当前层时，我们即可完成当前节点的指针赋值。注意一个节点可能被多个其他节点指向，因此我们可能递归地多次尝试拷贝某个节点，为了防止重复拷贝，我们需要首先检查当前节点是否被拷贝过，如果已经拷贝过，我们可以直接从哈希表中取出拷贝后的节点的指针并返回即可。
class Solution {
private:
    unordered_map<Node*, Node*> cachedNode;
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return head;
        auto it = cachedNode.find(head);
        if (it == cachedNode.end()) {
            Node* newHead = new Node(head->val);
            cachedNode.emplace(head, newHead);
            newHead->next = copyRandomList(head->next);
            newHead->random = copyRandomList(head->random);
            return newHead;
        }
        return it->second;
    }
};

// 官方解法二：迭代+节点拆分，三次遍历，时间 O(n) 4 ms 97.77%，空间 O(1) 10.8 MB 99.35%
// 我们首先将该链表中每一个节点拆分为两个相连的节点，例如对于链表 A→B→C，我们可以将其拆分为 A → A' → B → B' → C → C'。对于任意一个原节点 S，其拷贝节点 S' 即为其后继节点。
// 这样可以直接找到每一个拷贝节点 S' 的随机指针应当指向的节点，即为其原节点 S 的随机指针指向的节点 T 的后继节点 T'。需要注意原节点的随机指针可能为空。
// 完成了拷贝节点的随机指针的赋值，我们只需要将这个链表按照原节点与拷贝节点的种类进行拆分即可，只需要遍历一次。同样需要注意最后一个拷贝节点的后继节点为空。
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return head;
        for (Node* node = head; node != nullptr; node = node->next->next){
            Node* newNode = new Node(node->val);
            newNode->next = node->next;
            node->next = newNode;
        }
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* newNode = node->next;
            newNode->random = (node->random != nullptr) ? node->random->next : nullptr;
        }
        Node* newHead = head->next;
        for (Node* node = head; node != nullptr; node = node->next) {
            Node* newNode = node->next;
            node->next = node->next->next;
            newNode->next = (newNode->next != nullptr) ? newNode->next->next : nullptr;
        }
        return newHead;
    }
};

// 官方解法三：两次遍历，无法复原输入链表
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return head;
        for (Node* node = head; node != nullptr; node = node->next->next){
            Node* newNode = new Node(node->val);
            newNode->next = node->next;
            node->next = newNode;
        }
        Node* newHead = head->next;
        for (Node* node = head; node != nullptr;) {
            Node* newNode = node->next;
            newNode->random = (node->random != nullptr) ? node->random->next : nullptr;
            node = newNode->next;
            newNode->next = (newNode->next != nullptr) ? newNode->next->next : nullptr;
        }
        return newHead;
    }
};

int main() {
    Node* node7 = new Node(7);
    Node* node13 = new Node(13);
    Node* node11 = new Node(11);
    Node* node10 = new Node(10);
    Node* node1 = new Node(1);
    node7->next = node13;
    node13->next = node11;
    node11->next = node10;
    node10->next = node1;
    node13->random = node7;
    node11->random = node1;
    node10->random = node11;
    node1->random = node7;

    Solution sol;
    Node* ret = sol.copyRandomList(node7);
}