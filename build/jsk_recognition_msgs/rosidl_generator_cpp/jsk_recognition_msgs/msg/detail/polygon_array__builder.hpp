// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jsk_recognition_msgs:msg/PolygonArray.idl
// generated code does not contain a copyright notice

#ifndef JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__BUILDER_HPP_
#define JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jsk_recognition_msgs/msg/detail/polygon_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jsk_recognition_msgs
{

namespace msg
{

namespace builder
{

class Init_PolygonArray_likelihood
{
public:
  explicit Init_PolygonArray_likelihood(::jsk_recognition_msgs::msg::PolygonArray & msg)
  : msg_(msg)
  {}
  ::jsk_recognition_msgs::msg::PolygonArray likelihood(::jsk_recognition_msgs::msg::PolygonArray::_likelihood_type arg)
  {
    msg_.likelihood = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jsk_recognition_msgs::msg::PolygonArray msg_;
};

class Init_PolygonArray_labels
{
public:
  explicit Init_PolygonArray_labels(::jsk_recognition_msgs::msg::PolygonArray & msg)
  : msg_(msg)
  {}
  Init_PolygonArray_likelihood labels(::jsk_recognition_msgs::msg::PolygonArray::_labels_type arg)
  {
    msg_.labels = std::move(arg);
    return Init_PolygonArray_likelihood(msg_);
  }

private:
  ::jsk_recognition_msgs::msg::PolygonArray msg_;
};

class Init_PolygonArray_polygons
{
public:
  explicit Init_PolygonArray_polygons(::jsk_recognition_msgs::msg::PolygonArray & msg)
  : msg_(msg)
  {}
  Init_PolygonArray_labels polygons(::jsk_recognition_msgs::msg::PolygonArray::_polygons_type arg)
  {
    msg_.polygons = std::move(arg);
    return Init_PolygonArray_labels(msg_);
  }

private:
  ::jsk_recognition_msgs::msg::PolygonArray msg_;
};

class Init_PolygonArray_header
{
public:
  Init_PolygonArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PolygonArray_polygons header(::jsk_recognition_msgs::msg::PolygonArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PolygonArray_polygons(msg_);
  }

private:
  ::jsk_recognition_msgs::msg::PolygonArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jsk_recognition_msgs::msg::PolygonArray>()
{
  return jsk_recognition_msgs::msg::builder::Init_PolygonArray_header();
}

}  // namespace jsk_recognition_msgs

#endif  // JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__BUILDER_HPP_
