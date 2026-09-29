// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jsk_recognition_msgs:msg/PolygonArray.idl
// generated code does not contain a copyright notice
#include "jsk_recognition_msgs/msg/detail/polygon_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `polygons`
#include "geometry_msgs/msg/detail/polygon_stamped__functions.h"
// Member `labels`
// Member `likelihood`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
jsk_recognition_msgs__msg__PolygonArray__init(jsk_recognition_msgs__msg__PolygonArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    jsk_recognition_msgs__msg__PolygonArray__fini(msg);
    return false;
  }
  // polygons
  if (!geometry_msgs__msg__PolygonStamped__Sequence__init(&msg->polygons, 0)) {
    jsk_recognition_msgs__msg__PolygonArray__fini(msg);
    return false;
  }
  // labels
  if (!rosidl_runtime_c__uint32__Sequence__init(&msg->labels, 0)) {
    jsk_recognition_msgs__msg__PolygonArray__fini(msg);
    return false;
  }
  // likelihood
  if (!rosidl_runtime_c__float__Sequence__init(&msg->likelihood, 0)) {
    jsk_recognition_msgs__msg__PolygonArray__fini(msg);
    return false;
  }
  return true;
}

void
jsk_recognition_msgs__msg__PolygonArray__fini(jsk_recognition_msgs__msg__PolygonArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // polygons
  geometry_msgs__msg__PolygonStamped__Sequence__fini(&msg->polygons);
  // labels
  rosidl_runtime_c__uint32__Sequence__fini(&msg->labels);
  // likelihood
  rosidl_runtime_c__float__Sequence__fini(&msg->likelihood);
}

bool
jsk_recognition_msgs__msg__PolygonArray__are_equal(const jsk_recognition_msgs__msg__PolygonArray * lhs, const jsk_recognition_msgs__msg__PolygonArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // polygons
  if (!geometry_msgs__msg__PolygonStamped__Sequence__are_equal(
      &(lhs->polygons), &(rhs->polygons)))
  {
    return false;
  }
  // labels
  if (!rosidl_runtime_c__uint32__Sequence__are_equal(
      &(lhs->labels), &(rhs->labels)))
  {
    return false;
  }
  // likelihood
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->likelihood), &(rhs->likelihood)))
  {
    return false;
  }
  return true;
}

bool
jsk_recognition_msgs__msg__PolygonArray__copy(
  const jsk_recognition_msgs__msg__PolygonArray * input,
  jsk_recognition_msgs__msg__PolygonArray * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // polygons
  if (!geometry_msgs__msg__PolygonStamped__Sequence__copy(
      &(input->polygons), &(output->polygons)))
  {
    return false;
  }
  // labels
  if (!rosidl_runtime_c__uint32__Sequence__copy(
      &(input->labels), &(output->labels)))
  {
    return false;
  }
  // likelihood
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->likelihood), &(output->likelihood)))
  {
    return false;
  }
  return true;
}

jsk_recognition_msgs__msg__PolygonArray *
jsk_recognition_msgs__msg__PolygonArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jsk_recognition_msgs__msg__PolygonArray * msg = (jsk_recognition_msgs__msg__PolygonArray *)allocator.allocate(sizeof(jsk_recognition_msgs__msg__PolygonArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jsk_recognition_msgs__msg__PolygonArray));
  bool success = jsk_recognition_msgs__msg__PolygonArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jsk_recognition_msgs__msg__PolygonArray__destroy(jsk_recognition_msgs__msg__PolygonArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jsk_recognition_msgs__msg__PolygonArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jsk_recognition_msgs__msg__PolygonArray__Sequence__init(jsk_recognition_msgs__msg__PolygonArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jsk_recognition_msgs__msg__PolygonArray * data = NULL;

  if (size) {
    data = (jsk_recognition_msgs__msg__PolygonArray *)allocator.zero_allocate(size, sizeof(jsk_recognition_msgs__msg__PolygonArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jsk_recognition_msgs__msg__PolygonArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jsk_recognition_msgs__msg__PolygonArray__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
jsk_recognition_msgs__msg__PolygonArray__Sequence__fini(jsk_recognition_msgs__msg__PolygonArray__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      jsk_recognition_msgs__msg__PolygonArray__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

jsk_recognition_msgs__msg__PolygonArray__Sequence *
jsk_recognition_msgs__msg__PolygonArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jsk_recognition_msgs__msg__PolygonArray__Sequence * array = (jsk_recognition_msgs__msg__PolygonArray__Sequence *)allocator.allocate(sizeof(jsk_recognition_msgs__msg__PolygonArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jsk_recognition_msgs__msg__PolygonArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jsk_recognition_msgs__msg__PolygonArray__Sequence__destroy(jsk_recognition_msgs__msg__PolygonArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jsk_recognition_msgs__msg__PolygonArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jsk_recognition_msgs__msg__PolygonArray__Sequence__are_equal(const jsk_recognition_msgs__msg__PolygonArray__Sequence * lhs, const jsk_recognition_msgs__msg__PolygonArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jsk_recognition_msgs__msg__PolygonArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jsk_recognition_msgs__msg__PolygonArray__Sequence__copy(
  const jsk_recognition_msgs__msg__PolygonArray__Sequence * input,
  jsk_recognition_msgs__msg__PolygonArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jsk_recognition_msgs__msg__PolygonArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jsk_recognition_msgs__msg__PolygonArray * data =
      (jsk_recognition_msgs__msg__PolygonArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jsk_recognition_msgs__msg__PolygonArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jsk_recognition_msgs__msg__PolygonArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jsk_recognition_msgs__msg__PolygonArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
