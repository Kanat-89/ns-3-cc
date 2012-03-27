/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/log.h"
#include "ns3/simulator.h"
#include "cachecast-pid.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastPid");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastPid);

CacheCastPid::CacheCastPid ()
  : m_payloadId (-1)
{
  NS_LOG_FUNCTION_NOARGS ();

  m_preTime = Simulator::Now ().GetSeconds ();
}

TypeId
CacheCastPid::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastPid")
    .SetParent<Object> ()
    .AddConstructor<CacheCastPid> ()
  ;
  return tid;
}

TypeId
CacheCastPid::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

uint32_t
CacheCastPid::GetPayloadId () const
{
  return m_payloadId;
}


//opprett aggregated object in node CacheCastPid
uint32_t
CacheCastPid::CalculateNewPayloadId ()
{
  NS_LOG_FUNCTION_NOARGS ();

  /* Wrap around if one second has passed */
  if (Simulator::Now ().GetSeconds () - m_preTime > 1.0)
  {
    m_payloadId = 0;
    m_preTime = Simulator::Now ().GetSeconds ();
  }
  else
  {
    ++m_payloadId;
  }

  NS_LOG_DEBUG ("New payload ID=" << m_payloadId);

  return m_payloadId;
}

} // namespace ns3

