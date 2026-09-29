// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jsk_recognition_msgs:msg/PolygonArray.idl
// generated code does not contain a copyright notice

#ifndef JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__STRUCT_H_
#define JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'polygons'
#include "geometry_msgs/msg/detail/polygon_stamped__struct.h"
// Member 'labels'
// Member 'likelihood'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/PolygonArray in the package jsk_recognition_msgs.
/**
  * PolygonArray is a list of PolygonStamped.
  * You can use jsk_rviz_plugins to visualize PolygonArray on rviz.
 */
typedef struct jsk_recognition_msgs__msg__PolygonArray
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__PolygonStamped__Sequence polygons;
  rosidl_runtime_c__uint32__Sequence labels;
  rosidl_runtime_c__float__Sequence likelihood;
} jsk_recognition_msgs__msg__PolygonArray;

// Struct for a sequence of jsk_recognition_msgs__msg__PolygonArray.
typedef struct jsk_recognition_msgs__msg__PolygonArray__Sequence
{
  jsk_recognition_msgs__msg__PolygonArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jsk_recognition_msgs__msg__PolygonArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__STRUCT_H_
