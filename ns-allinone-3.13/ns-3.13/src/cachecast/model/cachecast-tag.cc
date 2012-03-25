/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast-tag.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastTag);

CacheCastTag::CacheCastTag (int32_t socketIndex, int32_t payloadSize, bool lastPacket)
  : Tag (),
    m_socketIndex (socketIndex),
    m_payloadSize (payloadSize),
    m_lastPacket (lastPacket)
{
}

CacheCastTag::CacheCastTag ()
  : Tag (),
    m_socketIndex (-1),
    m_payloadSize (-1),
    m_lastPacket (false)
{
}

bool
CacheCastTag::IsLastPacket ()
{
  return m_lastPacket;
}

int32_t
CacheCastTag::GetPayloadSize ()
{
  return m_payloadSize;
}

void
CacheCastTag::SetPayloadSize (int32_t payloadSize)
{
  m_payloadSize = payloadSize;
}

int32_t
CacheCastTag::GetSocketIndex ()
{
  return m_socketIndex;
}

void
CacheCastTag::SetSocketIndex (int32_t socketIndex)
{
  m_socketIndex = socketIndex;
}

TypeId 
CacheCastTag::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastTag")
    .SetParent<Tag> ()
    .AddConstructor<CacheCastTag> ()
  ;
  return tid;
}

TypeId 
CacheCastTag::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

uint32_t 
CacheCastTag::GetSerializedSize (void) const
{
  return sizeof (uint8_t) + sizeof (int32_t) * 2;
}

void 
CacheCastTag::Serialize (TagBuffer buf) const
{
  buf.WriteU32 (m_socketIndex);
  buf.WriteU32 (m_payloadSize);
  buf.WriteU8 (m_lastPacket ? 1 : 0);
}

void 
CacheCastTag::Deserialize (TagBuffer buf)
{
  m_socketIndex = (int32_t) buf.ReadU32 ();
  m_payloadSize = (int32_t) buf.ReadU32 ();
  m_lastPacket = buf.ReadU8 () ? true : false;
}

void 
CacheCastTag::Print (std::ostream &os) const
{
  os << "CacheCastTag: LastPacket=" << m_lastPacket << " "
     << "Socket index=" << m_socketIndex << " "
     << "Payload size=" << m_payloadSize;
}

} // namespace ns3

