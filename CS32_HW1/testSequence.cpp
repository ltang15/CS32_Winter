#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test_1();
void test_2();
//void test_3();

int main()
{
    test_1();
    //test_2();
    //test_3();
    cout << "Passed all tests" << endl;
}

void test_1()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1 && s.find(42) == 0);


}

void test_2()
{
    Sequence s;

    for (int i = 0; i < 5; i++)
    {
        s.insert(i, i * 10);
    }

    cout << "Sequence s: " << " ";
    s.dump();

    cout << "Size: " << s.size() << endl;
    s.insert(2, 13);
    cout << "Insert 13 at pos 2: " << " ";
    s.dump();
    s.insert(15);
    cout << "Insert 15: " << " ";
    s.dump();
    cout << "Erase pos 2: " << " ";
    s.erase(2);
    s.dump();
    cout << "Insert 20 at: " << s.insert(20) << endl;
    s.dump();
    cout << "Test remove 20:(number of times)" << s.remove(20) << endl;
    s.dump();
    ItemType num;

    s.get(4, num);
    cout << "Get() at pos 4: " << num << endl;

    s.set(2, 76);
    cout << "Set 76 at pos 2: " << " ";
    s.dump();

    cout << "Find 30, 30 is at pos: " << s.find(30) << endl;

    cout << "==========" << endl;
    Sequence  a;
    for (int j = 0; j < 4; j++)
    {
        a.insert(j, j * 2);
    }

    cout << "Sequence s:" << " ";
    s.dump();
    cout << "Sequence a:" << " ";
    a.dump();
    s.swap(a);

    cout << " Swap a and s:" << endl;
    cout << "s: " << " ";
    s.dump();
    cout << "a: " << " ";
    a.dump();

}

//void test_3()
//{
//    Sequence s;
//    s.insert(0, "lavash");
//    s.insert(0, "tortilla");
//    assert(s.size() == 2);
//    ItemType x = "injera";
//    assert(s.get(0, x) && x == "tortilla");
//    assert(s.get(1, x) && x == "lavash");
//}

