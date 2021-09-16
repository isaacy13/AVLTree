#include "binary_search_tree.h"

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
void test31();
void test32();
void test33();
void test34();
void test35();

int main() {
    // MISC TESTS
    test1();
    test2();
    test3();
    // END MISC TESTS
    // START REMOVE TESTS
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    // END REMOVE TESTS
    // START find min/max, contains tests
    test17();
    test18();
    test19();
    test20();
    // END find min/max tests
    // START INSERT TESTS
    test21();
    // END INSERT TESTS
    // START COPY CONSTRUCTOR TESTS
    test22();
    test23();
    // END COPY CONSTRUCTOR TESTS
    // START COPY ASSIGNMENT OPERATOR TESTS
    test24();
    test25();
    test26();
    test27();
    test28();
    test29();
    test30();
    // END COPY ASSIGNMENT OPERATOR TESTS
    // MISC
    test31();
    test32();
    test33();
    test34();
    test35();
    // TODO: FIX HERE AND UPDATE AVL & FIX THAT STUFF TOO
}

void test35() {
    BinarySearchTree<int> l;    
    BinarySearchTree<int> k;

    // srand(time(NULL));
    // for (int i = 0; i < 1000; i++){
    //     int ran = rand() % 1000 + 1;
    //     l.insert(ran);
    // }


    // k = l;
    // l = k;
    // k.remove(10);
    // l = k;
    // k.remove(10);
    // k = l;
    // k.print_tree();
}

void test34() {
    BinarySearchTree<int> l;
    for (int i = 5; i >= 0; i--)
        l.insert(i);
    BinarySearchTree<int> k;
    k = l;
    l = k;
    for (int i = 5; i <= 10; i++)
        l.insert(i);
    k = l;
    // okay from up
    for (int i = 5; i >= 0; i--)
        k.remove(i);
    l = k;
    for (int i = 5; i <= 10; i++)
        l.remove(i);
    k = l;
}

void test33() {
    BinarySearchTree<int> l;
    for (int i = 0; i < 5; i++)
        l.insert(i);
    BinarySearchTree<int> k;
    k = l;
    l = k;
    for (int i = 10; i > 5; i--)
        l.insert(i);
    k = l;
    // okay from up
    for (int i = 0; i < 5; i++)
        k.remove(i);
    l = k;
    for (int i = 10; i > 5; i--)
        l.remove(i);
    k = l;
    l.print_tree();
    k.print_tree();
}

void test32() {
    BinarySearchTree<int> k;
    k.remove(50);
    k.insert(50);
    k.remove(50);
    k.insert(50);

    for (int i = 50; i >= 0; i--)
        k.insert(i);

    k.print_tree();

    for (int i = 50; i >= 0; i--)
        k.remove(i);

    k.print_tree();
}

void test31() {
    BinarySearchTree<int> k;
    k.remove(50);
    k.insert(50);
    k.remove(50);
    k.insert(50);

    for (int i = 0; i < 50; i++)
        k.insert(i);

    k.print_tree();

    for (int i = 0; i <= 50; i++)
        k.remove(i);

    k.print_tree();
}

void test30() {
    BinarySearchTree<int> k;
    k.insert(10);
    k.remove(10);
    k.insert(10);
    cout << k.contains(10) << endl;
}

void test29() {
    BinarySearchTree<int> k;
    k.insert(10);
    k.remove(10);
    cout << k.contains(10) << endl;
}

void test28() {
    BinarySearchTree<int> l;
    BinarySearchTree<int> k;

    l.insert(50);
    l.insert(10);
    l.insert(100);
    k.insert(20);

    BinarySearchTree<int> v = k;

    k = l;

    l.print_tree();
    v.print_tree();

}

void test27() {
    BinarySearchTree<int> l;
    BinarySearchTree<int> k;
    l = k;
    l.insert(5);
    k = l;
    k.insert(10);
    l = k;
    k.remove(10);
    k = l;
    l.remove(5);
    l.print_tree();
    k.print_tree();
}

void test26() {
    BinarySearchTree<int> l;
    l.insert(5);
    BinarySearchTree<int> k;
    k = l;
    k.print_tree();
}

void test25() {
    BinarySearchTree<int> l;
    l.insert(5);
    BinarySearchTree<int> k;
    l = k;
    l.print_tree();
}

void test24() {
    BinarySearchTree<int> l;
    BinarySearchTree<int> k;
    l = k;
}

void test23() {
    // copying empty tree
    BinarySearchTree<int> l;
    BinarySearchTree<int> k(l);

    k.print_tree();
}

void test22() {
    BinarySearchTree<int> l;
    l.insert(5);
    l.insert(10);
    l.insert(0);
    l.insert(55);

    BinarySearchTree<int> k(l);

    k.print_tree();
}

void test21() {
    // insert already existing values
    BinarySearchTree<int> l;
    l.insert(5);
    l.insert(6);
    l.insert(4);
    l.insert(5);
    l.insert(5);
    l.insert(6);
    l.insert(4);

    l.print_tree();
}

void test20() {
    BinarySearchTree<int> l;
    l.insert(6);
    try {
        cout << l.find_min() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    try {
        cout << l.find_max() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    cout << l.contains(6) << endl;
}

void test19() {
    BinarySearchTree<int> l;
    l.insert(5);
    try {
        cout << l.find_min() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    try {
        cout << l.find_max() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    cout << l.contains(6) << endl;
}

void test18() {
    BinarySearchTree<int> l;
    try {
        cout << l.find_min() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    try {
        cout << l.find_max() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    cout << l.contains(6) << endl;
}

void test17() {
    BinarySearchTree<int> l;
    //      6              6 
    //    3   9    ->    3   8
    //   2   8              7 
    //      7              
    l.insert(6);
    l.insert(3);
    l.insert(9);
    l.insert(2);
    l.insert(8);
    l.insert(7);

    cout << l.find_min() << " " << l.find_max() << endl;
    cout << l.contains(2) << " " << l.contains(9) << endl;

    l.remove(9);
    l.remove(2);

    cout << l.contains(2) << " " << l.contains(9) << endl;
    cout << l.find_min() << " " << l.find_max() << endl;
}

void test16() {
    BinarySearchTree<int> l;
    l.insert(5);
    l.insert(10);
    l.insert(-5);
    l.remove(6);

    l.print_tree();
}

void test15() {
    BinarySearchTree<int> l;
    //  3      ->     3
    // 2 4
    l.insert(3);
    l.insert(2);
    l.insert(4);

    l.remove(4);
    l.remove(2);
    
    l.print_tree();
}

void test14() {
    BinarySearchTree<int> l;
    //  3      ->     3
    // 2 4
    l.insert(3);
    l.insert(2);
    l.insert(4);

    l.remove(2);
    l.remove(4);
    
    l.print_tree();
}

void test13() {
    // remove internal node (replacement: max of left subtree), replace with node that has children
    BinarySearchTree<int> l;
    //      6              6 
    //    3   9    ->    3   8
    //   2   8          2   7 
    //      7              
    l.insert(6);
    l.insert(3);
    l.insert(9);
    l.insert(2);
    l.insert(8);
    l.insert(7);

    l.remove(9);

    l.print_tree();
}

void test12() {
    // remove internal node (replacement: max of left subtree), replace with node that has no children
    BinarySearchTree<int> l;
    //      5              5 
    //    3   8    ->    3   6
    //   2   6          2 
    l.insert(5);
    l.insert(3);
    l.insert(8);
    l.insert(2);
    l.insert(6);

    l.remove(8);
    l.print_tree();
}

void test11() {
    // remove internal node (replacement: min of right subtree), replace with node that has children
    BinarySearchTree<int> l;
    //      5              5 
    //    3   8    ->    3   9
    //   2   6 9        2   6 10
    //        7 10           7 
    l.insert(5);
    l.insert(3);
    l.insert(8);
    l.insert(2);
    l.insert(6);
    l.insert(9);
    l.insert(7);
    l.insert(10);

    l.remove(8);
    l.print_tree();
}

void test10() {
    // remove internal node (replacement: min of right subtree), replace with node that has no children
    BinarySearchTree<int> l;
    //      5              5 
    //    3   8    ->    3   9
    //   2   6 9        2   6
    //        7              7 
    l.insert(5);
    l.insert(3);
    l.insert(8);
    l.insert(2);
    l.insert(6);
    l.insert(9);
    l.insert(7);

    l.remove(8);
    l.print_tree();
}

void test9() {
    // remove root from non-empty tree (replacement: max of left subtree), replace with node that has children
    BinarySearchTree<int> l;
    //      5              3 
    //    3       ->      2 
    //   2 
    l.insert(5);
    l.insert(3);
    l.insert(2);
    l.print_tree();

    l.remove(5);

    l.print_tree();
}

void test8() {
    // remove root from non-empty tree (replacement: max of left subtree), replace with node that has no children
    BinarySearchTree<int> l;
    //      5              3 
    //    3       ->      
    l.insert(5);
    l.insert(3);
    l.print_tree();

    l.remove(5);

    l.print_tree();
}

void test7() {
    // remove tree with only root
    BinarySearchTree<int> l;
    l.insert(5);
    l.print_tree();
    l.remove(5);
    l.print_tree();
}

void test6() {
    // remove root from non-empty tree (replacement: min of right subtree), replace with node that has child
    BinarySearchTree<int> l;
    //      5              6 
    //    3   8    ->    3   8
    //   2   6          2   7
    //        7              
    l.insert(5);
    l.insert(3);
    l.insert(8);
    l.insert(2);
    l.insert(6);
    l.insert(7);
    l.print_tree();

    l.remove(5);

    l.print_tree();
}

void test5() {
    // remove from empty tree
    BinarySearchTree<int> l;
    l.remove(5);
    l.print_tree();
}

void test4() {
    // remove root from non-empty tree (replacement: min of right subtree), replace with node that has no children
    BinarySearchTree<int> l;
    //     6                7
    //   4   8       ->   4   8 
    //  2 5 7 9          2 5   9
    l.insert(6);
    l.insert(4);
    l.insert(8);
    l.insert(2);
    l.insert(5);
    l.insert(7);
    l.insert(9);

    l.print_tree();

    l.remove(6);

    l.print_tree();
}

void test3() {
    // simple copy constructor
    BinarySearchTree<int> l;
    l.insert(6);
    l.insert(3);
    l.insert(5);
    l.insert(10);

    BinarySearchTree<int> k(l);
    l.print_tree();
    k.print_tree();
}

void test2() {
    // given test
    // make an empty tree
    BinarySearchTree<int> tree;

    // insert 5 values into the tree
    tree.insert(6);
    tree.insert(4);
    tree.insert(2);
    tree.insert(8);
    tree.insert(10);
    
    //     6
    //    4 8
    //   2   10

    // search the tree
    std::cout << "contains 4? " << std::boolalpha << tree.contains(4) << std::endl;
    std::cout << "contains 7? " << std::boolalpha << tree.contains(7) << std::endl;

    // remove the root
    tree.remove(6);

    // find the minimum element
    std::cout << "min: " << tree.find_min() << std::endl;

    // find the maximum element
    std::cout << "max: " << tree.find_max() << std::endl;

    // print the tree
    std::cout << "tree: " << std::endl;
    tree.print_tree();
}

void test1() {
    // simple insert & print
    BinarySearchTree<int> l;
    //     6
    //  3     10
    //    4    
    //      5
    l.insert(6);
    l.insert(3);
    l.insert(4);
    l.insert(10);
    l.insert(5);
    l.print_tree();
}