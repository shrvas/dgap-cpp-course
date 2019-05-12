
#include <iostream>
#include <stdexcept>

using namespace std;

// Object to log construction/destruction
struct debug
{
    debug(const char *_name): name(_name)
    {
        cout << "debug constructor " << name << endl;
    }
    ~debug()
    {
        cout << "debug destructor " << name << endl;
    }

    const char *name;
};


void reliable_func() noexcept
{
    // should never throw!
    
    cout << "Reliable func: OK" << endl;
#if 0
    cout << "little error" << endl;
    throw(string("reliable_func failed :("));
#endif
}

void fail_func()
{
#if 1
    throw(string("fail_func always fails"));
#else
    throw(runtime_error("fail_func"));
#endif
}

void TestAll()
{
    debug d1("TestAll");
    debug *pd = new debug("TestAll allocated on heap"); // This will not be deleted

    try {
        fail_func();
    }
    catch(string s) {
        cout << "exc pre-catch: " << s << endl;
        throw;  // Send this exception further to next catch
    }
}


int main()
{
    debug d1("main");

    try {
        debug d2("try block");
        TestAll();
        TestAll();
    }
    catch(const char* c) {
        cout << "exc char catched: " << c << endl;
    }
    catch(exception &e) {
        cout << "exc e catched: " << e.what() << endl;
    }
    catch(...) {
        cout << "exc catched: unknown type" << endl;
    }

    return 0;
}
