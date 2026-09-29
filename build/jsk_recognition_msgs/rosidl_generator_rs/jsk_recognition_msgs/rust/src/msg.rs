#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to jsk_recognition_msgs__msg__PolygonArray
/// PolygonArray is a list of PolygonStamped.
/// You can use jsk_rviz_plugins to visualize PolygonArray on rviz.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PolygonArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub polygons: Vec<geometry_msgs::msg::PolygonStamped>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub labels: Vec<u32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub likelihood: Vec<f32>,

}



impl Default for PolygonArray {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PolygonArray::default())
  }
}

impl rosidl_runtime_rs::Message for PolygonArray {
  type RmwMsg = super::msg::rmw::PolygonArray;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        polygons: msg.polygons
          .into_iter()
          .map(|elem| geometry_msgs::msg::PolygonStamped::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        labels: msg.labels.into(),
        likelihood: msg.likelihood.into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        polygons: msg.polygons
          .iter()
          .map(|elem| geometry_msgs::msg::PolygonStamped::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        labels: msg.labels.as_slice().into(),
        likelihood: msg.likelihood.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      polygons: msg.polygons
          .into_iter()
          .map(geometry_msgs::msg::PolygonStamped::from_rmw_message)
          .collect(),
      labels: msg.labels
          .into_iter()
          .collect(),
      likelihood: msg.likelihood
          .into_iter()
          .collect(),
    }
  }
}


