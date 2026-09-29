// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jsk_recognition_msgs:msg/PolygonArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jsk_recognition_msgs/msg/detail/polygon_array__rosidl_typesupport_introspection_c.h"
#include "jsk_recognition_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jsk_recognition_msgs/msg/detail/polygon_array__functions.h"
#include "jsk_recognition_msgs/msg/detail/polygon_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `polygons`
#include "geometry_msgs/msg/polygon_stamped.h"
// Member `polygons`
#include "geometry_msgs/msg/detail/polygon_stamped__rosidl_typesupport_introspection_c.h"
// Member `labels`
// Member `likelihood`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jsk_recognition_msgs__msg__PolygonArray__init(message_memory);
}

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_fini_function(void * message_memory)
{
  jsk_recognition_msgs__msg__PolygonArray__fini(message_memory);
}

size_t jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__size_function__PolygonArray__polygons(
  const void * untyped_member)
{
  const geometry_msgs__msg__PolygonStamped__Sequence * member =
    (const geometry_msgs__msg__PolygonStamped__Sequence *)(untyped_member);
  return member->size;
}

const void * jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__polygons(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__PolygonStamped__Sequence * member =
    (const geometry_msgs__msg__PolygonStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__polygons(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__PolygonStamped__Sequence * member =
    (geometry_msgs__msg__PolygonStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__fetch_function__PolygonArray__polygons(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__PolygonStamped * item =
    ((const geometry_msgs__msg__PolygonStamped *)
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__polygons(untyped_member, index));
  geometry_msgs__msg__PolygonStamped * value =
    (geometry_msgs__msg__PolygonStamped *)(untyped_value);
  *value = *item;
}

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__assign_function__PolygonArray__polygons(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__PolygonStamped * item =
    ((geometry_msgs__msg__PolygonStamped *)
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__polygons(untyped_member, index));
  const geometry_msgs__msg__PolygonStamped * value =
    (const geometry_msgs__msg__PolygonStamped *)(untyped_value);
  *item = *value;
}

bool jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__resize_function__PolygonArray__polygons(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__PolygonStamped__Sequence * member =
    (geometry_msgs__msg__PolygonStamped__Sequence *)(untyped_member);
  geometry_msgs__msg__PolygonStamped__Sequence__fini(member);
  return geometry_msgs__msg__PolygonStamped__Sequence__init(member, size);
}

size_t jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__size_function__PolygonArray__labels(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return member->size;
}

const void * jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__labels(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__labels(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__fetch_function__PolygonArray__labels(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__labels(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__assign_function__PolygonArray__labels(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__labels(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

bool jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__resize_function__PolygonArray__labels(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  rosidl_runtime_c__uint32__Sequence__fini(member);
  return rosidl_runtime_c__uint32__Sequence__init(member, size);
}

size_t jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__size_function__PolygonArray__likelihood(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__likelihood(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__likelihood(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__fetch_function__PolygonArray__likelihood(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__likelihood(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__assign_function__PolygonArray__likelihood(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__likelihood(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__resize_function__PolygonArray__likelihood(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs__msg__PolygonArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "polygons",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs__msg__PolygonArray, polygons),  // bytes offset in struct
    NULL,  // default value
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__size_function__PolygonArray__polygons,  // size() function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__polygons,  // get_const(index) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__polygons,  // get(index) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__fetch_function__PolygonArray__polygons,  // fetch(index, &value) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__assign_function__PolygonArray__polygons,  // assign(index, value) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__resize_function__PolygonArray__polygons  // resize(index) function pointer
  },
  {
    "labels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs__msg__PolygonArray, labels),  // bytes offset in struct
    NULL,  // default value
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__size_function__PolygonArray__labels,  // size() function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__labels,  // get_const(index) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__labels,  // get(index) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__fetch_function__PolygonArray__labels,  // fetch(index, &value) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__assign_function__PolygonArray__labels,  // assign(index, value) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__resize_function__PolygonArray__labels  // resize(index) function pointer
  },
  {
    "likelihood",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jsk_recognition_msgs__msg__PolygonArray, likelihood),  // bytes offset in struct
    NULL,  // default value
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__size_function__PolygonArray__likelihood,  // size() function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_const_function__PolygonArray__likelihood,  // get_const(index) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__get_function__PolygonArray__likelihood,  // get(index) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__fetch_function__PolygonArray__likelihood,  // fetch(index, &value) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__assign_function__PolygonArray__likelihood,  // assign(index, value) function pointer
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__resize_function__PolygonArray__likelihood  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_members = {
  "jsk_recognition_msgs__msg",  // message namespace
  "PolygonArray",  // message name
  4,  // number of fields
  sizeof(jsk_recognition_msgs__msg__PolygonArray),
  jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_member_array,  // message members
  jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_init_function,  // function to initialize message memory (memory has to be allocated)
  jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_type_support_handle = {
  0,
  &jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jsk_recognition_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jsk_recognition_msgs, msg, PolygonArray)() {
  jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PolygonStamped)();
  if (!jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_type_support_handle.typesupport_identifier) {
    jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jsk_recognition_msgs__msg__PolygonArray__rosidl_typesupport_introspection_c__PolygonArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
