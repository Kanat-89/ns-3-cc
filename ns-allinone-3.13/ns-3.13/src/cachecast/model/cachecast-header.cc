/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/log.h"
#include "cachecast-header.h"

// NS_LOG_COMPONENT_DEFINE ("CacheCastHeader");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastHeader);

CacheCastHeader::CacheCastHeader ()
  : m_payloadId (0),
    m_payloadSize (0),
//     m_originalSize (0),
    m_index (0)
{
}

CacheCastHeader::CacheCastHeader (uint32_t payloadId, uint32_t payloadSize,
//     uint32_t originalSize,
    uint32_t index)
  : m_payloadId (payloadId),
    m_payloadSize (payloadSize),
//     m_originalSize (originalSize),
    m_index (index)
{
}

uint32_t
CacheCastHeader::GetPayloadId (void) const
{
  return m_payloadId;
}

uint32_t
CacheCastHeader::GetPayloadSize (void) const
{
  return m_payloadSize;
}

// uint32_t
// CacheCastHeader::GetOriginalSize (void) const
// {
//   return m_originalSize;
// }

uint32_t
CacheCastHeader::GetIndex (void) const
{
  return m_index;
}

void
CacheCastHeader::SetPayloadId (uint32_t payloadId)
{
  m_payloadId = payloadId;
}

void
CacheCastHeader::SetPayloadSize (uint32_t payloadSize)
{
  m_payloadSize = payloadSize;
}

// void
// CacheCastHeader::SetOriginalSize (uint32_t originalSize)
// {
//   m_originalSize = originalSize;
// }

void
CacheCastHeader::SetIndex (uint32_t index)
{
  m_index = index;
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
  os << "payload ID=" << m_payloadId << " "
     << "payload size=" << m_payloadSize << " "
//      << "original size " << m_originalSize
     << "index=" << m_index
  ;
}

uint32_t
CacheCastHeader::GetSerializedSize (void) const
{
  return sizeof (uint32_t) * 3;
}

void
CacheCastHeader::Serialize (Buffer::Iterator start) const
{
  Buffer::Iterator i = start;

  i.WriteHtonU32 (m_payloadId);
  i.WriteHtonU32 (m_payloadSize);
  i.WriteHtonU32 (m_index);
}

uint32_t
CacheCastHeader::Deserialize (Buffer::Iterator start)
{
  Buffer::Iterator i = start;

  m_payloadId = i.ReadNtohU32 ();
  m_payloadSize = i.ReadNtohU32 ();
  m_index = i.ReadNtohU32 ();
  return GetSerializedSize ();
}

} // namespace ns3

