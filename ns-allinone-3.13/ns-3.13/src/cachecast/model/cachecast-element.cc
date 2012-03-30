/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/log.h"
// #include "ns3/simulator.h"
#include "cachecast-element.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastElement");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastElement);

TypeId
CacheCastElement::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastElement")
    .SetParent<Object> ()
  ;
  return tid;
}

TypeId
CacheCastElement::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

} // namespace ns3

