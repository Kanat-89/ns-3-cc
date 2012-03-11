/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/log.h"
#include "cachecast-header.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastHeader");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastHeader);

CacheCastHeader::CacheCastHeader ()
  : m_payloadId (0),
    m_payloadSize (0),
    m_originalSize (0)
{
}

uint32_t
CacheCastHeader::GetPayloadId (void) const
{
  return m_payloadId;
}

TypeId
CacheCastHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastHeader")
    .SetParent<Header> ()
    .AddConstructor<CacheCastHeader> ();

  return tid;
}

TypeId
CacheCastHeader::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

void
CacheCastHeader::Print (std::ostream &os) const
{
  os << "payload ID " << m_payloadId << " "
     << "payload size " << m_payloadSize << " "
     << "original size " << m_originalSize
  ;
}

uint32_t
CacheCastHeader::GetSerializedSize (void) const
{
  // TODO figure out serialized size
  return 0;
}

void
CacheCastHeader::Serialize (Buffer::Iterator start) const
{
  // TODO
}

uint32_t
CacheCastHeader::Deserialize (Buffer::Iterator start)
{
  //TODO
  return 0;
}

} // namespace ns3

