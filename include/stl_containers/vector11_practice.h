#pragma once

#include <vector>

#include <iostream> // for cout
#include <string>   // for to_string

namespace vector11 {

template <class T, class Alloc>
void print(const std::vector<T, Alloc> &data, const std::string &caption) {
  std::cout << "vector " << caption << " size " << data.size() << " capacity "
            << data.capacity() << std::endl;
  for (const auto &item : data) {
    std::cout << "\"" << item << "\"; ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

class VerboseClass {
public:
  VerboseClass();
  VerboseClass(int data);
  ~VerboseClass();
  VerboseClass(const VerboseClass &rhs);
  VerboseClass(VerboseClass &&rhs);

  VerboseClass &operator=(const VerboseClass &rhs);

  int data{};
};
std::ostream &operator<<(std::ostream &os, const VerboseClass &obj);
void construction_review();
void assignment_review();
void access_review();
void capacity_review();
void iterators_review();
void modifiers_review();
void modifiers_review_part1();
void modifiers_review_part2();
void non_member_funcs_review();

void bool_specialization_review();
} // namespace vector11