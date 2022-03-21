#include "String.hpp"

String::String() {
  string_ = nullptr;
  capacity_ = 0;
  size_ = 0;
}

String::String(size_t size, char character) {
  string_ = new char[size];
  size_ = size;
  capacity_ = size_;
  memset(string_, character, size);
}

String::String(const char* string) {
  size_ = strlen(string);
  capacity_ = size_ + 1;
  string_ = new char[capacity_];
  memcpy(string_, string, capacity_);
}

String::String(const String& s) : size_(s.size_), capacity_(s.capacity_) {
  string_ = new char[capacity_];
  memcpy(string_, s.string_, size_);
}
String& String::operator=(const String& s) {
  if (&s == this) {
    return *this;
  }
  delete[] string_;
  size_ = s.size_;
  capacity_ = s.capacity_;
  string_ = new char[size_];
  memcpy(string_, s.string_, size_);
  return *this;
}

String::~String() { delete[] string_; }

void String::Clear() {
  size_ = 0;
  capacity_ = 0;
  delete[] string_;
  string_ = nullptr;
}

void String::Resize(size_t new_size) {
  if (new_size > capacity_) {
    if (capacity_ == 0) {
      ++capacity_;
    }
    while (new_size > capacity_) {
      capacity_ *= 2;
    }
    char* new_string = new char[capacity_];
    memcpy(new_string, string_, size_);
    delete[] string_;
    string_ = new_string;
  }
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  if (new_size > capacity_) {
    if (capacity_ == 0) {
      ++capacity_;
    }
    while (new_size > capacity_) {
      capacity_ *= 2;
    }
    char* new_string = new char[capacity_];
    memcpy(new_string, string_, size_);
    memset(new_string + size_, character, new_size - size_);
    delete[] string_;
    string_ = new_string;
  }
  size_ = new_size;
}
void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    char* new_string = new char[new_cap];
    memcpy(new_string, string_, size_);
    delete[] string_;
    string_ = new_string;
    capacity_ = new_cap;
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
  }
}

void String::PushBack(char character) {
  if (size_ == capacity_) {
    if (size_ == 0) {
      Reserve(2);
    } else {
      Reserve(size_ * 2);
    }
  }
  string_[size_++] = character;
}

void String::PopBack() {
  if (size_ > 0) {
    --size_;
  }
}
void String::Swap(String& other) {
  char* tmp_str = string_;
  string_ = other.string_;
  other.string_ = tmp_str;

  size_t tmp = size_;
  size_ = other.size_;
  other.size_ = tmp;

  tmp = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = tmp;
}
const char& String::operator[](const size_t kIndex) const {
  return string_[kIndex];
}

char& String::operator[](const size_t kIndex) { return string_[kIndex]; }

char& String::Front() { return string_[0]; }
const char& String::Front() const { return string_[0]; }
char& String::Back() { return string_[size_ - 1]; }
const char& String::Back() const { return string_[size_ - 1]; }
bool String::Empty() const { return (size_ == 0); }
size_t String::Size() const { return size_; }
size_t String::Capacity() const { return capacity_; }
const char* String::Data() const { return string_; }
bool String::operator<(const String& str) const {
  if (str.string_ == string_) {
    return false;
  }
  size_t min_size = size_;
  if (str.size_ < size_) {
    min_size = str.size_;
  }
  for (int i = 0; i < min_size; i++) {
    if (string_[i] > str.string_[i]) {
      return false;
    }
  }
  return size_ <= str.size_;
}

bool String::operator>(const String& str) const {
  if (str.string_ == string_) {
    return false;
  }
  size_t min_size = size_;
  if (str.size_ < size_) {
    min_size = str.size_;
  }
  for (int i = 0; i < min_size; i++) {
    if (string_[i] < str.string_[i]) {
      return false;
    }
  }
  return size_ >= str.size_;
}

bool String::operator<=(const String& str) const {
  if (str.string_ == string_) {
    return true;
  }
  size_t min_size = size_;
  if (str.size_ < size_) {
    min_size = str.size_;
  }
  for (int i = 0; i < min_size; i++) {
    if (string_[i] > str.string_[i]) {
      return false;
    }
  }
  return size_ <= str.size_;
}

bool String::operator>=(const String& str) const {
  if (str.string_ == string_) {
    return true;
  }
  size_t min_size = size_;
  if (str.size_ < size_) {
    min_size = str.size_;
  }
  for (int i = 0; i < min_size; i++) {
    if (string_[i] < str.string_[i]) {
      return false;
    }
  }
  return size_ >= str.size_;
}

bool operator==(const String& str1, const String& str2) {
  return ((str1 > str2) || (str2 < str1));
}

bool operator!=(const String& str1, const String& str2) {
  return !((str1 > str2) || (str2 < str1));
}

String& String::operator+=(const String& str) {
  size_t old_size = size_;
  if (str.size_ + size_ > capacity_) {
    Resize(size_ + str.size_);
  }
  size_ = old_size + str.size_;
  memcpy(string_ + old_size, str.string_, str.size_);
  return *this;
}
String operator+(const String& str1, const String& str2) {
  String ans = str1;
  return ans += str2;
}
String& String::operator*=(int n) {
  if (n == 0) {
    Clear();
    return *this;
  }
  String old_str = *this;
  size_t old_size = size_;
  for (size_t i = 0; i < n; i++) {
    for (int j = 0; j < old_size; j++) {
      PushBack(old_str.string_[j]);
    }
  }
  return *this;
}

String operator*(const String& str1, int n) {
  String ans = str1;
  return ans *= n;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    out << str[i];
  }
  return out;
}
std::istream& operator>>(std::istream& in, String& str) {
  str.Clear();
  char c = 1;
  while (in.get(c) && c != '\n') {
    str.PushBack(c);
  }
  return in;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> vec;
  String part;
  bool flag = true;
  for (size_t i = 0; i < size_; ++i) {
    if (string_[i] == delim[0]) {
      for (size_t j = 0; j < delim.size_; j++) {
        if (i + j >= size_ || string_[i + j] != delim[j]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        vec.push_back(part);
        part.Clear();
        i += delim.size_ - 1;
      } else {
        String tmp(1, string_[i]);
        part += tmp;
        flag = true;
      }
    } else {
      String tmp(1, string_[i]);
      part += tmp;
      flag = true;
    }
  }
  vec.push_back(part);
  return vec;
}

String String::Join(const std::vector<String>& str) const {
  String result;
  for (int i = 0; i < str.size(); ++i) {
    result += str[i];
    if (i < str.size() - 1) {
      result += *this;
    }
  }
  return result;
}
