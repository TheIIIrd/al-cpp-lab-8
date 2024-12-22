/*
Разработать шаблон для задания «умного» указателя по аналогии шаблона
std::shared_ptr, который отличается от шаблона части 1 тем, что разрешает
копирование. Назвать его можно MyShared.
*/

// Шаблон класса MyShared (по аналогии с std::shared_ptr)
template <typename T> class MyShared {
private:
  T *ptr_;     // Указатель на данные
  int *count_; // Счетчик ссылок

  // Уменьшение счетчика и уничтожение ресурсов при необходимости
  void decrease_and_destroy() {
    if (count_ && --(*count_) == 0) {
      delete ptr_;
      delete count_;
      ptr_ = nullptr;
      count_ = nullptr;
    }
  }

public:
  // Конструктор
  MyShared(T *ptr = nullptr) : ptr_(ptr), count_(ptr ? new int(1) : nullptr) {}

  // Деструктор
  ~MyShared() { decrease_and_destroy(); }

  // Конструктор копирования
  MyShared(const MyShared &other) : ptr_(other.ptr_), count_(other.count_) {
    if (count_)
      ++(*count_);
  }

  // Оператор присваивания
  MyShared &operator=(const MyShared &other) {
    if (this != &other) {
      decrease_and_destroy();
      ptr_ = other.ptr_;
      count_ = other.count_;
      if (count_)
        ++(*count_);
    }
    return *this;
  }

  // Разыменование
  T &operator*() const { return *ptr_; }

  // Стрелочный оператор
  T *operator->() const { return ptr_; }
};
