#pragma once

#include <cstring>
#include <iostream>
#include <vector>

class String {
 public:
  String();
  String(size_t size, char character);
  String(const char* string);
  String(const String& s);
  String& operator=(const String& s);
  ~String();
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  char& operator[](size_t index);
  const char& operator[](size_t index) const;
  char& Front();
  [[nodiscard]] const char& Front() const;
  char& Back();
  [[nodiscard]] const char& Back() const;
  [[nodiscard]] bool Empty() const;
  [[nodiscard]] size_t Size() const;
  [[nodiscard]] size_t Capacity() const;
  [[nodiscard]] const char* Data() const;
  bool operator<(const String& str) const;
  bool operator>(const String& str) const;
  bool operator<=(const String& str) const;
  bool operator>=(const String& str) const;
  String& operator+=(const String& str);
  String& operator*=(int n);
  std::vector<String> Split(const String& delim = " ");
  [[nodiscard]] String Join(const std::vector<String>& strings) const;

 private:
  char* string_;
  size_t size_;
  size_t capacity_;
};
bool operator==(const String& str1, const String& str2);
bool operator!=(const String& str1, const String& str2);
String operator+(const String& str1, const String& str2);
String operator*(const String& str1, int n);
std::ostream& operator<<(std::ostream& out, const String& str);
std::istream& operator>>(std::istream& in, String& str);
