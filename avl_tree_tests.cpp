#include "avl_tree.h"

#include <iostream>
#include <cstddef>
#include <stdexcept>

using std::size_t;
using std::cout;
using std::endl;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
void test12();
void test13();
void test14();
void test15();
void test16();
void test17();
void test18();
void test19();
void test20();
void test21();
void test22();
void test23();
void test24();
void test25();
void test26();
void test27();
void test28();
void test29();
void test30();

int main() {
    // START MISC CASES
    test1();
    test2();
    test3();
    test4();
    test5();
    // END MISC CASES
    // START COPY CONSTRUCTOR CASES
    test6();
    test7();
    test8();
    // END COPY CONSTRUCTOR CASES
    // START COPY ASSIGNMENT OPERATOR CASES
    test9();
    test10();
    test11();
    test12();
    // END COPY ASSIGNMENT OPERATOR CASES
    // CONTAINS CASES
    test13();
    test14();
    test15();
    test16();
    test22();
    test23();
    test24();
    // END CONTAINS CASES
    // FIND MIN/MAX CASES
    test17();
    test18();
    // END FIND MIN/MAX CASES
    // INSERT/REMOVE/PRINT
    test19();
    test20();
    test21();
    // END INSERT/REMOVE/PRINT
}

void test24() {
    // short L, R, LR, RL
    // long L, R, LR, RL

    AVLTree<int> l;   
}

void test23() {
    AVLTree<int> l;
    for (int i = 0; i < 1000; i++)
        l.insert(i);
    AVLTree<int> k;
    k = l;
    l = k;
    for (int i = 2000; i > 1000; i--)
        l.insert(i);
    k = l;
    for (int i = 0; i < 1000; i++)
        k.remove(i);
    l = k;
    for (int i = 2000; i > 1000; i--)
        l.remove(i);
    k = l;
    l.print_tree();
    k.print_tree();
}

void test22() {
    AVLTree<int> k;
    k = k;

    k.print_tree();
    k.insert(1);
    
    k = k;

    k.print_tree();
}

void test21() {
    AVLTree<int> k;
    k.insert(50);
    k.insert(25);
    k.remove(50);

    k.print_tree();

    AVLTree<int> l;
    l.insert(50);
    l.insert(75);
    l.remove(50);

    l.print_tree();
}

void test20() {
    AVLTree<int> k;
    k.remove(50);
    k.insert(50);
    k.remove(50);
    k.insert(50);

    for (int i = 5; i >= 0; i--) {
        k.insert(i);
    }

    k.print_tree();

    for (int i = 5; i >= 0; i--){
        cout << "i: " << i << endl;
        cout << "==========" << endl;
        k.remove(i);
        k.print_tree();
        cout << "==========" << endl;
    }
    k.remove(50);
    k.print_tree();

    AVLTree<int> v;
    v.insert(10);
    v.remove(10);
}

void test19() {
    AVLTree<int> k;
    k.remove(50);
    k.insert(50);
    k.remove(50);
    k.insert(50);

    for (int i = 0; i <= 10; i++) {
        k.insert(i);
    }

    k.print_tree();

    for (int i = 0; i <= 10; i++){
        cout << "i: " << i << endl;
        cout << "========" << endl;
        k.remove(i);
        k.print_tree();
        cout << "========" << endl;
    }
    k.remove(50);
    k.print_tree();
}

void test18() {
    AVLTree<int> k;
    try {
        cout << k.find_max() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    try {
        cout << k.find_min() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }
}

void test17() {
    AVLTree<int> k;
    k.insert(50);
    k.insert(30);
    k.insert(70);
    k.insert(100);
    k.insert(-500);
    k.insert(5000);
    cout << k.find_max() << " " << k.find_min() << endl;
}

void test16() {
    AVLTree<int> k;
    k.insert(10);
    k.remove(10);
    k.insert(10);
    cout << k.contains(10) << endl;
}

void test15 () {
    AVLTree<int> k;
    k.insert(10);
    k.remove(10);
    cout << k.contains(10) << endl;
}

void test14() {
    AVLTree<int> k;
    k.insert(10);
    cout << k.contains(-10) << " " << k.contains(10) << endl;
}

void test13() {
    AVLTree<int> l;
    cout << l.contains(5) << endl;
}

void test12() {
    AVLTree<int> l;
    //   10             12               12               12                15
    //     15   ->    10  15      ->   10  15       ->      15      ->    12  20
    //    12         5      20               20               20
    l.insert(10);
    l.insert(15);
    l.insert(12);
    l.insert(20);
    l.insert(5);

    AVLTree<int> k;
    k = l;
    l = k;
    k = l;
    l = k;
    l.print_tree();
}

void test11() {
    AVLTree<int> l;
    //   10             12               12               12                15
    //     15   ->    10  15      ->   10  15       ->      15      ->    12  20
    //    12         5      20               20               20
    l.insert(10);
    l.insert(15);
    l.insert(12);
    l.insert(20);
    l.insert(5);

    AVLTree<int> k;
    l = k;
    l.print_tree();
}

void test10() {
    AVLTree<int> l;
    //   10             12               12               12                15
    //     15   ->    10  15      ->   10  15       ->      15      ->    12  20
    //    12         5      20               20               20
    l.insert(10);
    l.insert(15);
    l.insert(12);
    l.insert(20);
    l.insert(5);

    AVLTree<int> k;
    k = l;
    k.print_tree();
}

void test9() {
    AVLTree<int> l;
    //   10             12  
    //     15   ->    10  15
    //    12         5      20
    l.insert(10);
    l.insert(15);
    l.insert(12);
    l.insert(20);
    l.insert(5);

    AVLTree<int> k;
    k.insert(10);
    k = l;
    k.print_tree();
}

void test8() {
    AVLTree<int> l;
    l.insert(5);
    AVLTree<int> k(l);

    l.insert(10);

    l.print_tree();
    k.print_tree();
}

void test7() {
    AVLTree<int> l;
    AVLTree<int> k(l);

    l.print_tree();
    k.print_tree();
}

void test6() {
    AVLTree<int> l;
    //   10             12               12               12                15
    //     15   ->    10  15      ->   10  15       ->      15      ->    12  20
    //    12         5      20               20               20
    l.insert(10);
    l.insert(15);
    l.insert(12);
    l.insert(20);
    l.insert(5);

    AVLTree<int> k(l);
    k.remove(10);
    k.remove(5);

    l.print_tree();
    cout << endl;
    k.print_tree();
}

void test5() {
    AVLTree<int> l;
    //   10             12               12               12                15
    //     15   ->    10  15      ->   10  15       ->      15      ->    12  20
    //    12         5      20               20               20
    l.insert(10);
    l.insert(15);
    l.insert(12);
    l.insert(20);
    l.insert(5);

    l.print_tree();
    cout << endl;
    l.remove(5);
    l.print_tree();
    cout << endl;
    l.remove(10);
    l.print_tree();
}

void test4() {
    // right-left rotation
    AVLTree<int> l;
    //      7                        9
    //        10          ->        7 10
    //       9
    l.insert(7);
    l.insert(10);
    l.insert(9);

    l.print_tree();
}

void test3() {
    // left-right rotation
    AVLTree<int> l;
    //     10                        7
    //   5            ->          5     10
    //     7
    l.insert(10);
    l.insert(5);
    l.insert(7);

    l.print_tree();
}

void test2() {
    // right rotation
    AVLTree<int> l;
    //    6                        6
    //   5  10          ->       4   10
    //  4                       3 5
    // 3        
    l.insert(6);
    l.insert(5);
    l.insert(10);
    l.insert(4);
    l.insert(3);

    l.print_tree();
}

void test1() {
    // left rotation
    AVLTree<int> l;
    //    6                        6
    //   5  10          ->       5   50
    //       50                    10  60
    //         60

    l.insert(6);
    l.insert(5);
    l.insert(10);
    l.insert(50);
    l.insert(60);

    l.print_tree();
}