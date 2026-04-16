#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <string>

// 1. merge array 
template <typename T, size_t N, size_t M>
std::array<T, N + M> mergeArrays(const std::array<T, N>& a,
    const std::array<T, M>& b) {
    std::array<T, N + M> result;

    auto itA = a.begin();
    auto itB = b.begin();
    auto itR = result.begin();

    while (itA != a.end() && itB != b.end()) {
        if (*itA < *itB) {
            *itR = *itA;
            ++itA;
        }
        else {
            *itR = *itB;
            ++itB;
        }
        ++itR;
    }

    while (itA != a.end()) {
        *itR = *itA;
        ++itA; ++itR;
    }

    while (itB != b.end()) {
        *itR = *itB;
        ++itB; ++itR;
    }

    return result;
}

//  2. split vector 
template <typename T>
void splitVector(const std::vector<T>& v,
    std::vector<T>& even,
    std::vector<T>& odd) {

    for (auto it = v.begin(); it != v.end(); ++it) {
        if ((*it) % 2 == 0) {
            even.push_back(*it);
        }
        else {
            odd.push_back(*it);
        }
    }
}

// 3. palindrome deque
template <typename T>
bool isPalindrome(const std::deque<T>& d) {
    auto left = d.begin();
    auto right = d.end() - 1;

    while (left < right) {
        if (*left != *right) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}

// print
template <typename Container>
void print(const Container& c) {
    for (auto it = c.begin(); it != c.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// custom class
class Test {
public:
    int value;

    Test(int v = 0) : value(v) {}

    bool operator<(const Test& other) const {
        return value < other.value;
    }

    bool operator==(const Test& other) const {
        return value == other.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Test& t) {
        os << t.value;
        return os;
    }
};

//main
int main() {

    //1. merge array
    std::array<int, 3> a1 = { 1, 3, 5 };
    std::array<int, 3> a2 = { 2, 4, 6 };

    auto merged = mergeArrays(a1, a2);

    std::cout << "Merged array:\n";
    print(merged);

    // custom type
    std::array<Test, 2> t1 = { Test(1), Test(5) };
    std::array<Test, 2> t2 = { Test(2), Test(3) };

    auto mergedTest = mergeArrays(t1, t2);

    std::cout << "\nMerged custom:\n";
    print(mergedTest);

    // 2. split vector
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };

    std::vector<int> even, odd;
    splitVector(v, even, odd);

    std::cout << "\nEven:\n";
    print(even);

    std::cout << "Odd:\n";
    print(odd);

    // 3. palindrome
    std::deque<int> d = { 1, 2, 3, 2, 1 };

    std::cout << "\nIs palindrome: ";
    if (isPalindrome(d))
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

    std::deque<std::string> d2 = { "a", "b", "b", "a" };

    std::cout << "String palindrome: ";
    std::cout << (isPalindrome(d2) ? "YES\n" : "NO\n");

    return 0;
}