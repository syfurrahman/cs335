// --> SYFUR RAHMAN
// A class to represent a sequence of 2D points.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <utility>

namespace teaching_project {

// A class that represents a sequence of 2D points.
template<typename Object>
class Points2D {
 public:
  // Zero-parameter constructor.
  Points2D() : sequence_(nullptr), size_(0) {}

  // Copy constructor.
  Points2D(const Points2D &rhs) : sequence_(new std::array<Object, 2>[rhs.size_]), size_(rhs.size_) {
    for (size_t i = 0; i < size_; ++i) {
      sequence_[i] = rhs.sequence_[i];
    }
  }

  // Copy assignment operator.
  Points2D& operator=(const Points2D &rhs) {
    if (this != &rhs) {
      Points2D copy = rhs;
      std::swap(*this, copy);
    }
    return *this;
  }

  // Move constructor.
  Points2D(Points2D &&rhs) noexcept : sequence_(rhs.sequence_), size_(rhs.size_) {
    rhs.sequence_ = nullptr;
    rhs.size_ = 0;
  }

  // Move assignment operator.
  Points2D& operator=(Points2D &&rhs) noexcept {
    if (this != &rhs) {
      std::swap(sequence_, rhs.sequence_);
      std::swap(size_, rhs.size_);
    }
    return *this;
  }

  // Destructor.
  ~Points2D() {
    delete[] sequence_;
  }

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) {
    size_ = 1;
    sequence_ = new std::array<Object, 2>[1];
    sequence_[0] = item;
  }

  // Access the size of the sequence.
  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const {
    if (location >= size_) {
      std::cerr << "ERROR" << std::endl;
      abort();
    }
    return sequence_[location];
  }

  // @c1: A sequence.
  // @c2: A second sequence.
  // @return their sum. If the sequences are not of the same size, append the
  // result with the remaining part of the larger sequence.
  friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
    Points2D result;
    result.size_ = std::max(c1.size_, c2.size_);
    result.sequence_ = new std::array<Object, 2>[result.size_];

    for (size_t i = 0; i < result.size_; ++i) {
      if (i < c1.size_ && i < c2.size_) {
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      } else if (i < c1.size_) {
        result.sequence_[i] = c1.sequence_[i];
      } else {
        result.sequence_[i] = c2.sequence_[i];
      }
    }

    return result;
  }

  // Overloading the << operator.
  friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
    for (size_t i = 0; i < some_points.size_; ++i) {
      out << "(" << some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ") ";
    }
    out << std::endl;
    return out;
  }

  // Overloading the >> operator.
  // Read a chain from an input stream (e.g., standard input).
  friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
    int size_of_sequence;
    in >> size_of_sequence;

    if (!in) {
      std::cerr << "ERROR" << std::endl;
      return in;
    }

    some_points.size_ = size_of_sequence;
    delete[] some_points.sequence_;
    some_points.sequence_ = new std::array<Object, 2>[some_points.size_];

    for (size_t i = 0; i < some_points.size_; ++i) {
      in >> some_points.sequence_[i][0] >> some_points.sequence_[i][1];
      if (!in) {
        std::cerr << "ERROR" << std::endl;
        delete[] some_points.sequence_;
        some_points.size_ = 0;
        some_points.sequence_ = nullptr;
        break;
      }
    }

    return in;
  }

 private:
  // Sequence of points.
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;
};

}  // namespace teaching_project

#endif // CSCI_335_HOMEWORK1_POINTS2D_H_
