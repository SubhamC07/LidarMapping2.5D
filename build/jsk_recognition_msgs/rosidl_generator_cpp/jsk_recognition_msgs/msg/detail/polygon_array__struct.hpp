// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jsk_recognition_msgs:msg/PolygonArray.idl
// generated code does not contain a copyright notice

#ifndef JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__STRUCT_HPP_
#define JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'polygons'
#include "geometry_msgs/msg/detail/polygon_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__jsk_recognition_msgs__msg__PolygonArray __attribute__((deprecated))
#else
# define DEPRECATED__jsk_recognition_msgs__msg__PolygonArray __declspec(deprecated)
#endif

namespace jsk_recognition_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PolygonArray_
{
  using Type = PolygonArray_<ContainerAllocator>;

  explicit PolygonArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit PolygonArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _polygons_type =
    std::vector<geometry_msgs::msg::PolygonStamped_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::PolygonStamped_<ContainerAllocator>>>;
  _polygons_type polygons;
  using _labels_type =
    std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>>;
  _labels_type labels;
  using _likelihood_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _likelihood_type likelihood;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__polygons(
    const std::vector<geometry_msgs::msg::PolygonStamped_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::PolygonStamped_<ContainerAllocator>>> & _arg)
  {
    this->polygons = _arg;
    return *this;
  }
  Type & set__labels(
    const std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>> & _arg)
  {
    this->labels = _arg;
    return *this;
  }
  Type & set__likelihood(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->likelihood = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jsk_recognition_msgs__msg__PolygonArray
    std::shared_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jsk_recognition_msgs__msg__PolygonArray
    std::shared_ptr<jsk_recognition_msgs::msg::PolygonArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PolygonArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->polygons != other.polygons) {
      return false;
    }
    if (this->labels != other.labels) {
      return false;
    }
    if (this->likelihood != other.likelihood) {
      return false;
    }
    return true;
  }
  bool operator!=(const PolygonArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PolygonArray_

// alias to use template instance with default allocator
using PolygonArray =
  jsk_recognition_msgs::msg::PolygonArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jsk_recognition_msgs

#endif  // JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__STRUCT_HPP_
