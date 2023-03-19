#include <list>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

template <typename X>
void forward_go(X &tmp)
{
    typename X ::const_iterator it = tmp.begin();
    cout << "+\n";
    for (int i : tmp)
        cout << *(it++) << endl;
};

template <typename X>
void backwards_go(X &tmp)
{
    typename X ::const_reverse_iterator it = tmp.rbegin();
    cout << "-\n";
    for (int i : tmp)
        cout << *(it++) << endl;
};
int main()
{
    const vector<int> vector_a = {10, 13, 15};
    list<int> list_b;


    forward_go<const vector<int>>(vector_a);
    backwards_go<const vector<int>>(vector_a);
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        list_b.push_back(a);
    }


    forward_go<list<int>>(list_b);
    backwards_go<list<int>>(list_b);
}