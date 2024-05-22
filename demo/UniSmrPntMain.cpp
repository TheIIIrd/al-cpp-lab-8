/*
В функции main продемонстрировать все заданные возможности, в том числе, создать
указатель на объект своего класса, имеющего конструктор с параметрами
(например, класса MyPoint – точка на плоскости) c помощью функции Make_MyUnique,
получающей параметры как конструктора своего класса (MyPoint).
*/

// Включаем файл реализации умного указателя
#include "../smartpointer/UniqueSmartPointer.cpp"
#include <iostream>
#include <utility>

// Определяем класс MyPoint - точка на плоскости
class MyPoint {
public:
  MyPoint(int x, int y)
      : x_(x), y_(y) {} // Конструктор принимает координаты x и y
  int GetX() const { return x_; } // Геттер для x
  int GetY() const { return y_; } // Геттер для y

private:
  int x_, y_; // Приватные данные - координаты точки
};

// Функция-хелпер для создания уникального указателя с аргументами для
// конструктора
template <typename T, typename... Args>
SmartPointer<T> Make_MyUnique(Args &&...args) {
  return SmartPointer<T>(new T(std::forward<Args>(args)...));
}

int main() {
  // Создаем умный указатель на объект MyPoint и инициализируем его координатами
  // (5, 7)
  auto pointPtr = Make_MyUnique<MyPoint>(5, 7);

  // Выводим значения координат
  std::cout << "MyPoint:n ";
  std::cout << "X: " << pointPtr->GetX() << ", Y: " << pointPtr->GetY() << "n"
            << std::endl;

  // Создаем умный указатель на int
  SmartPointer<int> intptr(new int(10));
  std::cout << "int: " << *intptr << "n" << std::endl; // Выводим число

  // Перемещаем умный указатель intptr в новый умный указатель intptr2
  SmartPointer<int> intptr2 = std::move(intptr);

  // Проверяем осталось ли что-то в исходном указателе intptr
  if (intptr.get()) {
    std::cout << "intptr is not empty" << std::endl;
  } else
    std::cout << "intptr is empty" << std::endl;

  // Вывести значение инта после перемещения указателя
  std::cout << "int: " << *intptr2 << "n" << std::endl;

  return 0;
}
// Программа демонстрирует рабочий процесс умных указателей, а также применение
// шаблонов и семантики перемещения для создания типобезопасных и эффективных
// абстракций.
