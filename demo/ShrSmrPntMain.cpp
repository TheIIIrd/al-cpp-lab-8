/*
Разработать также глобальную шаблонную функцию Make_MyShared, которая получает
параметры как у конструктора объекта, на который указывает указатель.
Продемонстрировать все возможности в функции main.
*/

#include "../smartpointer/SharedSmartPointer.cpp"
#include <iostream>

// Глобальная шаблоная функция Make_MyShared
template <typename T, typename... Args>
MyShared<T> Make_MyShared(Args &&...args) {
  return MyShared<T>(new T(std::forward<Args>(args)...));
}

int main() {
  // Создаем MyShared указатель
  MyShared<int> p1(new int(5));
  std::cout << *p1 << std::endl; // Выводит: 5

  // Создаем еще один указатель
  MyShared<int> p2(new int(10));
  std::cout << *p2 << std::endl; // Выводит: 10

  // Демонстрация копирования указателей
  MyShared<int> p3 = p1;
  std::cout << *p3 << std::endl; // Выводит: 5

  // Демонстрация использования оператора присваивания
  p3 = p2;
  std::cout << *p3 << std::endl; // Выводит: 10 (значение p2)

  // Демонстрация использования оператора стрелки
  struct MyStruct {
    int x;
  };
  MyShared<MyStruct> p4(new MyStruct{7});
  std::cout << p4->x << std::endl; // Выводит: 7 (значение MyStruct::x)

  // Пример использования Make_MyShared
  auto p5 = Make_MyShared<int>(20);
  std::cout << *p5 << std::endl; // Выводит: 20

  return 0;
}
