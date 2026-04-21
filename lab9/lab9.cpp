#include <iostream>
#include <list>
#include <array>
#include <deque>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

// 1, function pointer
bool isOdd(int n) {
    return n % 2 != 0;
}

// 3, functor
class TaxApplier {
    double tax;
public:
    TaxApplier(double t) : tax(t) {}

    void operator()(double& price) {
        price += price * tax;
    }
};

// 4, functor
class WithinRange {
    int min, max;
public:
    WithinRange(int min, int max) : min(min), max(max) {}

    bool operator()(int x) {
        return x >= min && x <= max;
    }
};

int main() {

    // 1
    std::list<int> lst;
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < 20; i++)
        lst.push_back(dist(gen));

    std::cout << "List:\n";
    for (int x : lst) std::cout << x << " ";

    lst.remove_if(isOdd);

    std::cout << "\nAfter remove odd:\n";
    for (int x : lst) std::cout << x << " ";

    // 2
    std::array<std::string, 5> names = { "Anna", "Oleksandr", "Ira", "Max", "Katya" };

    std::sort(names.begin(), names.end(),
        [](const std::string& a, const std::string& b) {
            return a.length() < b.length();
        });

    std::cout << "\n\nSorted names:\n";
    for (auto& n : names) std::cout << n << " ";

    // 3
    std::deque<double> prices = { 100, 200, 300 };

    std::for_each(prices.begin(), prices.end(), TaxApplier(0.2));

    std::cout << "\n\nPrices with tax:\n";
    for (auto p : prices) std::cout << p << " ";

    // 4
    std::set<int> s = { 1, 5, 10, 15, 20, 25 };

    int count = std::count_if(s.begin(), s.end(), WithinRange(10, 20));

    std::cout << "\n\nCount in range [10,20]: " << count;

    // 5
    std::map<std::string, int> warehouse = {
        {"Laptop", 150},
        {"Mouse", 50},
        {"Phone", 200}
    };

    std::cout << "\n\nItems > 100:\n";
    std::for_each(warehouse.begin(), warehouse.end(),
        [](const std::pair<std::string, int>& p) {
            if (p.second > 100)
                std::cout << p.first << ": " << p.second << std::endl;
        });

    // 6
    std::vector<int> nums = { -5, 3, -2, 7 };

    std::replace_if(nums.begin(), nums.end(),
        [](int x) { return x < 0; }, 0);

    std::cout << "\nVector after replace:\n";
    for (int x : nums) std::cout << x << " ";

    // 7
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    int sum = 0;
    std::for_each(v.begin(), v.end(),
        [&sum](int x) { sum += x; });

    double avg = (double)sum / v.size();

    std::cout << "\n\nSum: " << sum << ", Avg: " << avg;

    // 8
    std::string text = "Hello World";

    int vowels = std::count_if(text.begin(), text.end(),
        [](char c) {
            c = tolower(c);
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        });

    std::cout << "\n\nVowels: " << vowels << std::endl;

    return 0;
}