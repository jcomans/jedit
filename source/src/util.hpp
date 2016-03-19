#ifndef _UTIL_H_
#define _UTIL_H_

template <typename T>
class PimplHolder
{
public:
  PimplHolder(): pimpl_(new T()){}
  PimplHolder(T* pimpl): pimpl_(pimpl){}

  const T* const operator->() const { return pimpl_; }
  T* const       operator->()       { return pimpl_; }

private:
  T* pimpl_;
};

#endif /* _UTIL_H_ */
