#include "stl_containers/vector11_practice.h"

#include <memory>
#include <string.h>

namespace vector11 {
VerboseClass::VerboseClass() {
  std::cout << "CTOR by default" << std::endl;
  this->data = -1;
}
VerboseClass::VerboseClass(int data) {
  this->data = data;
  std::cout << "CTOR with data. data = " << this->data << std::endl;
}
VerboseClass::~VerboseClass() {
  std::cout << "DTOR by default. data = " << this->data << std::endl;
}
VerboseClass::VerboseClass(const VerboseClass &rhs) {
  this->data = rhs.data;
  std::cout << "CTOR of copy. data = " << this->data << std::endl;
}
VerboseClass::VerboseClass(VerboseClass &&rhs) {
  this->data = std::move(rhs.data);
  std::cout << "CTOR of movement. data = " << this->data << std::endl;
}

VerboseClass &VerboseClass::operator=(const VerboseClass &rhs) {
  this->data = rhs.data;
  std::cout << "assignment operator. data = " << this->data << std::endl;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const VerboseClass &obj) {
  os << obj.data;
  return os;
}

void construction_review() {
  {
    std::vector<int> A;
    print(A, "A");
  }
  {
    std::vector<int> B(5);
    print(B, "B");
  }
  {
    std::vector<int> C{5};
    print(C, "C");
  }
  {
    std::vector<int> D(5, 6);
    print(D, "D");
    std::vector<int> E(D);
    print(E, "E");
    std::vector<int> F(std::move(D));
    print(F, "F");
    std::cout << "vector D after it's moved to vector F" << std::endl;
    print(D, "D");
  }

  {
    std::vector<VerboseClass> G(3, 4);
    print(G, "G");
    {
      std::vector<VerboseClass> G1{3, 4};
      print(G1, "G1");
    }
    {
      std::vector<VerboseClass> G2{5};
      print(G2, "G2");
    }
    {
      std::vector<VerboseClass> G3(5);
      print(G3, "G3");
    }

    std::vector<VerboseClass> H(std::move(G));
    print(H, "H");
    std::cout << "vector G after it's moved to vector H" << std::endl;
    print(G, "G");
    std::vector<VerboseClass> I(H);
    print(I, "I");
    std::cout << "vector H after it's copied to vector I" << std::endl;
    print(H, "H");
  }
}

void assignment_review() {
  {
    std::vector<int> A(3, 4);
    std::vector<int> B{3, 4};
    print(A, "A");
    print(B, "B");
    A = B;
    print(A, "A");
    A.assign(4, 3);
    print(A, "A");
  }
  {
    std::cout << "on assignments destructions of extra elements happens after "
                 "assignment itself"
              << std::endl;
    std::vector<VerboseClass> A(3, 4);
    print(A, "A");
    std::vector<VerboseClass> B{1, 2};
    print(B, "B");
    std::vector<VerboseClass> C{8, 7, 6, 5};
    print(C, "C");

    print(A, "A");
    std::cout << "call A = B;" << std::endl;
    A = B; // 2 assignments + 1 dtor
    print(A, "A");
    std::cout << "call A = C;" << std::endl;
    A = C; // 4 copy ctors + 2 dtors
    print(A, "A");
    std::cout << "call A.assign(3, -1);" << std::endl;
    A.assign(3, -1); // 3 assignments + 1 dtor
    print(A, "A");
    std::cout << "call A.assign(4, -2);" << std::endl;
    A.assign(4, -2); // 3 assignments + 1 copy ctor
    print(A, "A");
  }
}

void access_review() {
  std::vector<VerboseClass> A{8, 7, 6, 5};
  print(A, "A");

  std::cout << A.at(2) << std::endl;
  try {
    std::cout << A.at(5) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  std::cout << A[2] << std::endl;

  // We mustn't use operator [] if we aren't sure that it's argument less than
  // size of vector. It causes undefined behavior.
  // std::cout << A[105] << std::endl;

  auto front = A.front();
  std::cout << front << std::endl;

  auto back = A.back();
  std::cout << back << std::endl;

  auto raw_data = A.data();

  std::cout << raw_data[0] << std::endl;
  std::cout << raw_data[1] << std::endl;
  std::cout << raw_data[2] << std::endl;
  std::cout << raw_data[3] << std::endl;
}

void capacity_review() {

  std::vector<VerboseClass> A{8, 7, 6, 5};
  print(A, "A");

  std::cout << "size of A " << A.size() << std::endl;
  std::cout << "capacity of A " << A.capacity() << std::endl;
  std::cout << "max_size of A " << A.max_size() << std::endl;
  std::cout << "-call A.assign(3, -1);" << std::endl;
  A.assign(3, -1);
  std::cout << "size of A " << A.size() << std::endl;
  std::cout << "capacity of A " << A.capacity() << std::endl;
  std::cout << "-call A.assign(5, -2);" << std::endl;
  A.assign(5, -2);
  std::cout << "size of A " << A.size() << std::endl;
  std::cout << "capacity of A " << A.capacity() << std::endl;
  std::cout << "-call A.reserve(9);" << std::endl;
  A.reserve(9); // here the memory will be reallocated probably. And copy ctors
                // and dtors of old elemets will be called
  print(A, "A");
  std::cout << "size of A " << A.size() << std::endl;
  std::cout << "capacity of A " << A.capacity() << std::endl;
  std::cout << "-call A.shrink_to_fit();" << std::endl;
  A.shrink_to_fit(); // here the memory will be reallocated probably. And copy
                     // ctors and dtors of old elemets will be called
  print(A, "A");
  std::cout << "size of A " << A.size() << std::endl;
  std::cout << "capacity of A " << A.capacity() << std::endl;
  if (A.empty()) {
    std::cout << "A is empty" << std::endl;
  } else {
    std::cout << "A is NOT empty" << std::endl;
  }
  std::cout << "-call A.assign(0,0);" << std::endl;
  A.assign(0, 0);
  if (A.empty()) {
    std::cout << "A is empty" << std::endl;
  } else {
    std::cout << "A is NOT empty" << std::endl;
  }
}

void iterators_review() {
  {
    std::vector<int> B{3, 4, 5, 8};
    auto begin_it = B.begin();
    auto cbegin_it = B.cbegin();
    auto end_it = B.end();
    auto cend_it = B.cend();

    // 'end' and 'cend' are iterators that are pointed to the next after last
    // element so we cant get their values.

    for (; begin_it != cend_it; ++begin_it) // it's ok
    {
      std::cout << "begin_it val " << *begin_it << std::endl;
      *begin_it = 11;
      std::cout << "begin_it val " << *begin_it << std::endl;
    }

    for (; cbegin_it != end_it; ++cbegin_it) // it's ok too
    {
      std::cout << "cbegin_it val " << *cbegin_it << std::endl;
      //*cbegin_it = 11; // error: assignment of read-only location
    }

    std::cout << "--end_it val " << *(--end_it) << std::endl;
    std::cout << "--cend_it val " << *(--cend_it) << std::endl;
  }
  {
    std::vector<int> B{3, 4, 5, 8};
    auto rbegin_it = B.rbegin();
    auto crbegin_it = B.crbegin();
    auto rend_it = B.rend();
    auto crend_it = B.crend();

    // 'rend' and 'crend' are iterators that are pointed to the element before
    // first element so we cant get their values.

    // for reverse iterating it's correct to use incrementing of reverse
    // iterator. this operator moves iterator in the reverse forward direct form
    // regular ending to regular beginning
    for (; rbegin_it != crend_it; ++rbegin_it) // it's ok
    {
      std::cout << "rbegin_it val " << *rbegin_it << std::endl;
      *rbegin_it = 11;
      std::cout << "rbegin_it val " << *rbegin_it << std::endl;
    }

    for (; crbegin_it != rend_it; ++crbegin_it) // it's ok too
    {
      std::cout << "crbegin_it val " << *crbegin_it << std::endl;
      //*cbegin_it = 11; // error: assignment of read-only location
    }

    std::cout << "--rend_it val " << *(--rend_it) << std::endl;
    std::cout << "--crend_it val " << *(--crend_it) << std::endl;
  }
}

void modifiers_review_part1() {
  {
    std::vector<int> A;

    A.insert(A.begin(), 9);
    A.insert(A.cbegin(), 10);
    auto inserted_it = A.insert(A.begin() + 2, 11);
    print(A, "A");

    std::cout << "inserted_it val " << *inserted_it << std::endl;

    A.insert(A.begin(), 5, 12);
    print(A, "A");

    std::vector<int> B{3, 4, 5, 8};
    // inserting to A.end() position add elements to the back (after last
    // element). inserting to A.end()-1 position insert elements between
    // pre-last and last elements.
    A.insert(A.end() - 1, B.begin(), B.end());
    print(A, "A");
    A.insert(A.begin(), {0, 1, 2});
    print(A, "A");
  }
  {
    std::vector<VerboseClass> A;
    A.reserve(16);
    const VerboseClass B{59};
    VerboseClass C{59};
    std::cout << "push_back ()" << std::endl;
    A.push_back(10);
    std::cout << "push_back const(B)" << std::endl;
    A.push_back(B);
    std::cout << "push_back (C)" << std::endl;
    A.push_back(C);
    std::cout << "push_back {}" << std::endl;
    A.push_back({10});
    std::cout << "emplace_back " << std::endl;
    A.emplace_back(10);
    std::cout << "emplace_back const(B)" << std::endl;
    A.emplace_back(B);
    std::cout << "emplace_back (C)" << std::endl;
    A.emplace_back(C);
  }
}

void modifiers_review_part2() {
  {
    std::vector<int> A{8, 7, 6, 5};
    print(A, "A");

    A.clear();
    print(A, "A");
  }
  {
    std::vector<int> A{8, 7, 6, 5, 4, 3, 2, 1};
    print(A, "A");

    A.erase(A.erase(A.begin() + 2) + 2);
    print(A, "A");

    // A.erase(A.rbegin() + 3); //error
    // A.erase(A.end()); // segfault;
    {
      auto retval = A.erase(A.end() - 1);
      if (retval == A.end()) {
        std::cout << "A.erase returned A.end()" << std::endl;
      }
      print(A, "A");
    }

    {
      auto retval = A.erase(A.end() - 1, A.end());
      if (retval == A.end()) {
        std::cout << "A.erase returned A.end()" << std::endl;
      }
      print(A, "A");
    }

    {
      auto retval =
          A.erase(A.begin() + 3, A.begin() + 3); // returned  it to last
      std::cout << "A.erase returned it to " << *retval << std::endl;
      print(A, "A");
    }

    {
      // this will copy elements from `A.begin() + 1` to `A.begin() + 2` and
      // placed them after `A.begin() + 2`
      auto retval = A.erase(A.begin() + 3, A.begin() + 1);
      std::cout << "A.erase returned it to " << *retval << std::endl;
      print(A, "A");
    }

    A.erase(A.begin() + 1, A.end() - 2);
    print(A, "A");

    A.pop_back();
    print(A, "A");

    A.resize(10);
    print(A, "A");

    A.resize(2);
    print(A, "A");

    A.resize(5, -2);
    print(A, "A");
  }
  {
    std::vector<VerboseClass> A{4, 3, 2, 1};
    std::vector<VerboseClass> B{1, 2, 3, 4};

    print(A, "A");
    print(B, "B");

    A.swap(B);

    print(A, "A");
    print(B, "B");
  }
}

std::string bool_to_str(bool val) {
  if (val)
    return "true";
  else
    return "false";
}

void non_member_funcs_review() {

#define CONSTRUCT_AND_MAKE_ALL_COMPARISONS(A_INIT, B_INIT)                     \
  {                                                                            \
    std::vector<int> A A_INIT;                                                 \
    std::vector<int> B B_INIT;                                                 \
    std::cout << "A " #A_INIT " != B " #B_INIT " is " << bool_to_str(A != B)   \
              << std::endl;                                                    \
    std::cout << "A " #A_INIT " == B " #B_INIT " is " << bool_to_str(A == B)   \
              << std::endl;                                                    \
    std::cout << "A " #A_INIT " < B " #B_INIT " is " << bool_to_str(A < B)     \
              << std::endl;                                                    \
    std::cout << "A " #A_INIT " <= B " #B_INIT " is " << bool_to_str(A <= B)   \
              << std::endl;                                                    \
    std::cout << "A " #A_INIT " > B " #B_INIT " is " << bool_to_str(A > B)     \
              << std::endl;                                                    \
    std::cout << "A " #A_INIT " >= B " #B_INIT " is " << bool_to_str(A >= B)   \
              << std::endl;                                                    \
    std::cout << std::endl;                                                    \
  }

  CONSTRUCT_AND_MAKE_ALL_COMPARISONS(({1, 1, 1, 1}), (4, 1));
  CONSTRUCT_AND_MAKE_ALL_COMPARISONS(({1, 1, 2, 1}), (4, 1));
  CONSTRUCT_AND_MAKE_ALL_COMPARISONS(({1, 1, 1, 1}), (3, 1));

#undef CONSTRUCT_AND_COMPARE
  {
    std::vector<VerboseClass> A{4, 3, 2, 1, 0};
    std::vector<VerboseClass> B{1, 2, 3, 4};

    print(A, "A");
    print(B, "B");

    std::swap(A, B);

    print(A, "A");
    print(B, "B");
  }
} // namespace vector11
void bool_specialization_review() {}
} // namespace vector11