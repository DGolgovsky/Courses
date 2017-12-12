int foo();
int& foo1();
const int foo2();
const int& foo3();
const int&& foo4();

int main()
{
  auto ri = foo(); // int
  auto ri1 = foo1(); // int
  auto ri2 = foo2(); // int
  auto ri3 = foo3(); // int

  auto& ri4 = foo(); // Не скомпилируется
  auto& ri5 = foo1(); // int&
  auto& ri6 = foo2(); // Не скомпилируется
  auto& ri7 = foo3(); // const int&

  auto&& ri8 = foo(); // int&&
  auto&& ri9 = foo1(); // int&
  auto&& ri10 = foo2(); // const int&&
  auto&& ri11 = foo3(); // const int&

  int k = 5;
  decltype(k)&& rk = k; // Не скомпилируется
  decltype(foo())&& ri12 = foo(); // int&&
  decltype(foo1())&& ri13 = foo1(); // int&
  
  int i = 3;
  decltype(i) ri14; // int
  decltype((i)) ri15; // int&

  auto ri16 = foo4(); //  int
  decltype(auto) ri17 = foo4(); //  const int&&
}
