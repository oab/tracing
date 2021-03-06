// use at least c++17 for template argument deduction
// which obsoletes the std::make_optional noise

#include<iostream>
#include<array>
#include<cassert>

#define VAR(name) name(#name)

template<typename T>
struct Var {
  std::string name;
  T value;

 Var() = default;
 Var(std::string s):name{s},value{}{}
  
  Var& operator=(const Var &v)
  {
    std::cout << "write " << name << '\n'; 
    value = v.value;
    return *this;
  }

  Var& operator=(const T v)
  {
    std::cout << "write" << ' ' << name << '\n'; 
    value = v;
    return *this;
  }
  
};

template<typename T>
void read2(const Var<T> &a, const Var<T> &b)
{
  std::cout << "read " << a.name << '\n';
  std::cout << "read " << b.name << '\n'; 
}

template<typename T>
void read1(const Var<T> a)
{
  std::cout << "read " << a.name << '\n';
}


template<typename T>
Var<T> operator+(const Var<T> a, const Var<T> b)
{
  read2(a,b);
  Var<T> temp("temp");
  temp = a.value+b.value;
  return temp;
}

template<typename T>
Var<T> operator-(const Var<T> a, const Var<T> b)
{
  read2(a,b);
  Var<T> temp("temp");
  temp = a.value-b.value;
  return temp;
}

template<typename T>
Var<T> operator*(const Var<T> a, const Var<T> b)
{
  read2(a,b);
  Var<T> temp("temp");
  temp = a.value*b.value;
  return temp;
}

template<typename T>
Var<T> operator+(const Var<T> a, const T b)
{
  read1(a);
  Var<T> temp("temp");
  temp = a.value+b;
  return temp;
}

template<typename T>
Var<T> operator+(const T a, const Var<T> b)
{
  read1(b);
  Var<T> temp("temp");
  temp = a+b.value;
  return temp;
}

template<typename T>
Var<T> operator*(const Var<T> a, const T b)
{
  read1(a);
  Var<T> temp("temp");
  temp = a.value*b;
  return temp;
}

template<typename T>
Var<T> operator*(const T a, const Var<T> b)
{
  read1(b);
  Var<T> temp("temp");
  temp = a*b.value;
  return temp;
}


template<typename T, std::size_t N> 
struct Vars {
  std::string name;
  std::array<Var<T>,N> vars;
  
  Vars(std::string s):name{s}
  {
    for(int i=0;i<N;i++) {
      vars[i].name = s+'['+std::to_string(i)+']';
    }
  }

  Var<T>& operator[](int index)
  {
    assert(index < N);
    return vars[index];
  }

};

auto mod(std::size_t inp, std::size_t modulus)
{
    auto remainder = inp % modulus;
    return remainder < 0 ? remainder + modulus : remainder;
}
 


