# Cpp Week 5 notes

## 1. Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;
class CStudent
{
    private:
        string name;
        string id;
        char gender;
        int age;
    public:
        void PrintInfo();
        void SetInfo( const string &name_, const string &id_, int age_, char gender_);
        string GetName(){return name;}
};

class CUndergraduateStudent:public CStudent
{
    private:
        string department;
    public:
        void QualifiedForBaoyan()
        {
            cout<<"qualified for baoyan"<<endl;
        }
        void PrintInfo()
        {
            CStudent::PrintInfo();
            cout<<"Department:"<<department<<endl;
        }
        void SetInfo( const string &name_, const string &id_, int age_, char gender_, const string &department_)
        {
            CStudent::SetInfo(name_, id_, age_, gender_);
            department = department_;
        }
};

void CStudent::PrintInfo()
{
    cout << "Name:" << name << endl;
    cout << "ID"  << id << endl;
    cout << "Age" << age << endl;
    cout << "Gender" << gender << endl;
}

void CStudent::SetInfo( const string &name_, const string &id_, int age_, char gender_)
{
    name = name_;
    id = id_;
    age = age_;
    gender = gender_;
}

int main()
{
    CUndergraduateStudent s2;
    s2.SetInfo("LittleMing","11223456",19,'M',"Computer Science");
    cout<<s2.GetName()<<"";
    s2.QualifiedForBaoyan();
    s2.PrintInfo();
    return 0;
}
```

## 2. 复合关系

## 3.1 Parents and child class have member with same name

```cpp
class base
{
        int j;
    public:
        int i;
        void func();
};

class derived:public base
{
    public:
        int i;
        void access();
        void function;
};

void derived::access()
{
    //j =5;// error
    i = 5;
    base::i = 5;
    func();
    base::func();
};

derived obj;
obj.i=1;
obj.base::i =1;
```

## 3.2 Protect Key

```cpp
class Father
{
    private: int nPrivate;
    public: int nPublic;
    protexted: int nProtexted;
};

class Son:public Father
{
    void AccessFather()
    {
        nPublic = 1;
        //nPrivate =1;//error
        nProtexted =1;
        Son f;
        //f.nProtexted =1;//error
    }
};

int main()
{
    Father f;
    Son s;
    f.nPublic =1;
    s.nPublic =1;
    //f.nProtected =1; // error
    //f.nPrivate =1; //error
    //s.nProtected =1; //error
    //s.nPrivate =1; // error
    return 0;
}
```

## 4. The constructor function of child class

```cpp
class Bug
{
    private:
        int nLegs;
        int nColor;
    public:
        int nType;
        Bug(int legs, int color);
        void PrintBug(){};
};
class FlyBug:public Bug
{
        int nWings;
    public:
        FlyBug(int legs, int color, int wings);
};

Bug:Bug(int legs, int color)
{
    nLegs = legs;
    nColor = color;
}

FlyBug::FlyBug(int legs, int color, int wings):Bug(legs,color)
{
    nWings =wings;
}

int main()
{
    FlyBug fb(2,3,4);
    fb.PrintBug();
    fb.nType =1;
    fb.nLegs =2;
    return 0;
}
```

```cpp
class Base
{
    public:
        int n;
        Base(int i):n(i)
        {
            cout<<"Base"<< n << "constructed" << endl;
        }
        ~Base()
        {
            cout<<"Base"<< n << "destructed"<< endl;
        }
};

class Derived:public Base
{
    public:
        Derived(int i):Base(i)
        {
            cout << "Derived constructed" <<endl;
        }
        ~Derived()
        {
            cout<<"Derived destructed"<<endl;
        }
};

int main()
{
    Derived Obj(3);
    return 0;
}
```

```cpp
class Skill
{
    public:
        Skill(int n){}
};

class FlyBug:public Bug
{
        int nWings;
        Skill sk1, sk2;
    public:
        FlyBug(int legs, int color, int wings);
};

FlyBug::FlyBug(int legs, int color, int wings):Bug(legs,color),sk1(5),sk2(color)
{
    nWings = wings;
}
```

## 5. Pulbic Key word and Inheritance

```cpp
class base{};
class derived:public base{ };
base b;
derived d;
// method 1
b=d;
// method 2
base &br =d;
// method 3
base *pb = & d;
```

```cpp
#include<iostream>
using namespace std;
class Base
{
    public:
        int n;
        Base(int i):n(i)
        {
            cout << "Base" << n <<"constructed"<< endl;
        }
        ~Base()
        {
            cout<<"Base"<< n << "destructed" << endl;
        }
};

class Derived:public Base
{
    public:
        Derived(int i):Base(i)
        {
            cout << "Derived constructed"<<endl;
        }
        ~Derived()
        {
            cout << "Derived destructed"<<endl;
        }
};

class MoreDerived:public Derived
{
    public:
        MoreDerived()Derived(4)
        {
            cout <<"More Derived constructed"<<endl;
        }
        ~MoreDerived()
        {
            cout<< "More Derived destructed" <<endl;
        }
};

int main()
{
    MoreDerived Obj;
    return 0;
}
```
