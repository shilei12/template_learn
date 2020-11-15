#include <iostream>
using namespace std;

class NoCopyable {
public:
    NoCopyable() {}
    ~NoCopyable() {}
private:
    NoCopyable(const NoCopyable&);
    NoCopyable(NoCopyable&&);
    NoCopyable &operator =(const NoCopyable&);
    NoCopyable &operator =(NoCopyable&&);
};

class Test : private NoCopyable {
public:
    Test() {}
    ~Test() {}
    static Test &GetInstance()
    {
        static Test instance;
        return instance;
    }
    void func1(const string& str, const string& str1) {
        cout << str << ' ' << str1 << endl;
    }
    void func2(const string& str) {
        cout << str << endl;
    }
    void func3(int& m) {
        cout << m << endl;
    }

    // 通过函数模板调用三个成员函数
    template <typename F, typename... Args>
    void CallService(F f, Args&&... agrs)
    {
        (this->*f)(std::forward<Args>(agrs)...); // (this->*f) 这样可以不用定义static函数
    }
};

int main()
{
    string str = "hello";
    string str1 = "world";
    int m = 190;
    Test::GetInstance().CallService(&Test::func1, str, str1);
    Test::GetInstance().CallService(&Test::func2, str);
    Test::GetInstance().CallService(&Test::func3, m);
    return 0;
}