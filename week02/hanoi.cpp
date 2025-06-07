#include <iostream>

int hanoi(int n, int a=1, int b=2, int c=3) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        std::cout << "Move " << a << " to " << c << std::endl;
        return 0;
    }
    else {
        hanoi(n-1, a, c, b);
        std::cout << "Move " << a << " to " << c << std::endl;
        hanoi(n-1, b, a, c);
        return 0;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        int n = atoi(argv[1]);
        hanoi(n);
    }
}