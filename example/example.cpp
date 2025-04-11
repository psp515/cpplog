//
// Created by psp515 on 02.03.2025.
//

#include <exception>
#include <iostream>
#include <ostream>

using namespace std;

int main() {
    try {
        cout << "Hello World!" << endl;

        return 0;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
