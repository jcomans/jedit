#ifndef _UTIL_H_
#define _UTIL_H_

#include <memory>

template <typename T>
class PimplHolder
{
public:
  PimplHolder(): pimpl_(new T()){}
  PimplHolder(T* pimpl): pimpl_(pimpl){}
  ~PimplHolder() { }

  const T* const operator->() const { return pimpl_.get(); }
  T* const       operator->()       { return pimpl_.get(); }

private:
  std::unique_ptr<T> pimpl_;
};

#endif /* _UTIL_H_ */
