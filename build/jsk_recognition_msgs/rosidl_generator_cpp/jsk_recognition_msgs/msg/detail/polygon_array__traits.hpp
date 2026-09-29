// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jsk_recognition_msgs:msg/PolygonArray.idl
// generated code does not contain a copyright notice

#ifndef JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__TRAITS_HPP_
#define JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jsk_recognition_msgs/msg/detail/polygon_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'polygons'
#include "geometry_msgs/msg/detail/polygon_stamped__traits.hpp"

namespace jsk_recognition_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PolygonArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: polygons
  {
    if (msg.polygons.size() == 0) {
      out << "polygons: []";
    } else {
      out << "polygons: [";
      size_t pending_items = msg.polygons.size();
      for (auto item : msg.polygons) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: labels
  {
    if (msg.labels.size() == 0) {
      out << "labels: []";
    } else {
      out << "labels: [";
      size_t pending_items = msg.labels.size();
      for (auto item : msg.labels) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: likelihood
  {
    if (msg.likelihood.size() == 0) {
      out << "likelihood: []";
    } else {
      out << "likelihood: [";
      size_t pending_items = msg.likelihood.size();
      for (auto item : msg.likelihood) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PolygonArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: polygons
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.polygons.size() == 0) {
      out << "polygons: []\n";
    } else {
      out << "polygons:\n";
      for (auto item : msg.polygons) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: labels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.labels.size() == 0) {
      out << "labels: []\n";
    } else {
      out << "labels:\n";
      for (auto item : msg.labels) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: likelihood
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.likelihood.size() == 0) {
      out << "likelihood: []\n";
    } else {
      out << "likelihood:\n";
      for (auto item : msg.likelihood) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PolygonArray & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace jsk_recognition_msgs

namespace rosidl_generator_traits
{

[[deprecated("use jsk_recognition_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jsk_recognition_msgs::msg::PolygonArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  jsk_recognition_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jsk_recognition_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const jsk_recognition_msgs::msg::PolygonArray & msg)
{
  return jsk_recognition_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jsk_recognition_msgs::msg::PolygonArray>()
{
  return "jsk_recognition_msgs::msg::PolygonArray";
}

template<>
inline const char * name<jsk_recognition_msgs::msg::PolygonArray>()
{
  return "jsk_recognition_msgs/msg/PolygonArray";
}

template<>
struct has_fixed_size<jsk_recognition_msgs::msg::PolygonArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jsk_recognition_msgs::msg::PolygonArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jsk_recognition_msgs::msg::PolygonArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JSK_RECOGNITION_MSGS__MSG__DETAIL__POLYGON_ARRAY__TRAITS_HPP_
