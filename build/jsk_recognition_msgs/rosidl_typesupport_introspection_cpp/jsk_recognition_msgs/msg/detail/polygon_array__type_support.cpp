// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from jsk_recognition_msgs:msg/PolygonArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "jsk_recognition_msgs/msg/detail/polygon_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace jsk_recognition_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void PolygonArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) jsk_recognition_msgs::msg::PolygonArray(_init);
}

void PolygonArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<jsk_recognition_msgs::msg::PolygonArray *>(message_memory);
  typed_message->~PolygonArray();
}

size_t size_function__PolygonArray__polygons(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::PolygonStamped> *>(untyped_member);
  return member->size();
}

const void * get_const_function__PolygonArray__polygons(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::PolygonStamped> *>(untyped_member);
  return &member[index];
}

void * get_function__PolygonArray__polygons(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::PolygonStamped> *>(untyped_member);
  return &member[index];
}

void fetch_function__PolygonArray__polygons(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const geometry_msgs::msg::PolygonStamped *>(
    get_const_function__PolygonArray__polygons(untyped_member, index));
  auto & value = *reinterpret_cast<geometry_msgs::msg::PolygonStamped *>(untyped_value);
  value = item;
}

void assign_function__PolygonArray__polygons(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<geometry_msgs::msg::PolygonStamped *>(
    get_function__PolygonArray__polygons(untyped_member, index));
  const auto & value = *reinterpret_cast<const geometry_msgs::msg::PolygonStamped *>(untyped_value);
  item = value;
}

void resize_function__PolygonArray__polygons(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::PolygonStamped> *>(untyped_member);
  member->resize(size);
}

size_t size_function__PolygonArray__labels(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__PolygonArray__labels(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__PolygonArray__labels(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__PolygonArray__labels(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint32_t *>(
    get_const_function__PolygonArray__labels(untyped_member, index));
  auto & value = *reinterpret_cast<uint32_t *>(untyped_value);
  value = item;
}

void assign_function__PolygonArray__labels(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint32_t *>(
    get_function__PolygonArray__labels(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint32_t *>(untyped_value);
  item = value;
}

void resize_function__PolygonArray__labels(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__PolygonArray__likelihood(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__PolygonArray__likelihood(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__PolygonArray__likelihood(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__PolygonArray__likelihood(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__PolygonArray__likelihood(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__PolygonArray__likelihood(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__PolygonArray__likelihood(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__PolygonArray__likelihood(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PolygonArray_message_member_array[4] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs::msg::PolygonArray, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "polygons",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::PolygonStamped>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs::msg::PolygonArray, polygons),  // bytes offset in struct
    nullptr,  // default value
    size_function__PolygonArray__polygons,  // size() function pointer
    get_const_function__PolygonArray__polygons,  // get_const(index) function pointer
    get_function__PolygonArray__polygons,  // get(index) function pointer
    fetch_function__PolygonArray__polygons,  // fetch(index, &value) function pointer
    assign_function__PolygonArray__polygons,  // assign(index, value) function pointer
    resize_function__PolygonArray__polygons  // resize(index) function pointer
  },
  {
    "labels",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs::msg::PolygonArray, labels),  // bytes offset in struct
    nullptr,  // default value
    size_function__PolygonArray__labels,  // size() function pointer
    get_const_function__PolygonArray__labels,  // get_const(index) function pointer
    get_function__PolygonArray__labels,  // get(index) function pointer
    fetch_function__PolygonArray__labels,  // fetch(index, &value) function pointer
    assign_function__PolygonArray__labels,  // assign(index, value) function pointer
    resize_function__PolygonArray__labels  // resize(index) function pointer
  },
  {
    "likelihood",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs::msg::PolygonArray, likelihood),  // bytes offset in struct
    nullptr,  // default value
    size_function__PolygonArray__likelihood,  // size() function pointer
    get_const_function__PolygonArray__likelihood,  // get_const(index) function pointer
    get_function__PolygonArray__likelihood,  // get(index) function pointer
    fetch_function__PolygonArray__likelihood,  // fetch(index, &value) function pointer
    assign_function__PolygonArray__likelihood,  // assign(index, value) function pointer
    resize_function__PolygonArray__likelihood  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PolygonArray_message_members = {
  "jsk_recognition_msgs::msg",  // message namespace
  "PolygonArray",  // message name
  4,  // number of fields
  sizeof(jsk_recognition_msgs::msg::PolygonArray),
  PolygonArray_message_member_array,  // message members
  PolygonArray_init_function,  // function to initialize message memory (memory has to be allocated)
  PolygonArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PolygonArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PolygonArray_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace jsk_recognition_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<jsk_recognition_msgs::msg::PolygonArray>()
{
  return &::jsk_recognition_msgs::msg::rosidl_typesupport_introspection_cpp::PolygonArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, jsk_recognition_msgs, msg, PolygonArray)() {
  return &::jsk_recognition_msgs::msg::rosidl_typesupport_introspection_cpp::PolygonArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
