#ifndef INCLUDE_BACKENDS_TENSOR_H_
#define INCLUDE_BACKENDS_TENSOR_H_

#include "backends/shape.h"

#include "utils/common.h"

namespace blitz {

template<typename DType = float>
class Tensor {
 public:
  explicit Tensor(const Shape& shape) :
    shape_(shape), row_major_(true) {}

  explicit Tensor(DType* data, const Shape& shape) :
    data_(data), shape_(shape), row_major_(true) {}

  virtual ~Tensor() {}

  // getter
  const Shape& shape() const {
    return shape_;
  }

  BLITZ_DATA_LAYOUT data_layout() const {
    return shape_.data_layout();
  }

  // low-level consistent api
  const Shape* shape_ptr() const {
    return &shape_;
  }

  size_t size() const {
    return shape_.size();
  }

  bool row_major() const {
    return row_major_;
  }

  const DType* data() const {
    return data_;
  }

  DType* data() {
    return data_;
  }

  // operator
  // one dimension data
  DType& operator[](size_t index) const {
    return data_[index];
  }

  DType& operator[](size_t index) {
    return data_[index];
  }

  // setter
  void set_row_major() {
    this->row_major_ = true;
  }

  void set_column_major() {
    this->row_major_ = false;
  }

  void set_shape(const Shape& shape) {
    this->shape_ = shape;
  }

  virtual void Fill(const DType value) = 0;
  virtual DType* Slice(const size_t index) = 0;
  virtual const DType* Slice(const size_t index) const = 0;
  virtual void OutputCSV(ofstream* ofs) const = 0;

 protected:
  virtual void Allocate() = 0;

  DType* data_;
  Shape shape_;
  bool row_major_;

  DISABLE_COPY_AND_ASSIGN(Tensor);
};

#define INSTANTIATE_TENSOR(tensor) \
  char BlitzInstantiationTensorGuard##tensor; \
  template class tensor<float>; \
  template class tensor<double>; \
  template class tensor<int>; \
  template class tensor<size_t>; \
  template class tensor<short> \

}  // namespace blitz

#endif  // INCLUDE_BACKENDS_TENSOR_H_
