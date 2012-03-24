/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast-tag.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastTag);

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
  return sizeof (uint8_t) + sizeof (int32_t);
}

void 
CacheCastTag::Serialize (TagBuffer buf) const
{
  buf.WriteU8 (m_lastPacket ? 1 : 0);
  buf.WriteU32 (m_payloadSize);
}

void 
CacheCastTag::Deserialize (TagBuffer buf)
{
  m_lastPacket = buf.ReadU8 () ? true : false;
  m_payloadSize = (int32_t) buf.ReadU32 ();
}

void 
CacheCastTag::Print (std::ostream &os) const
{
  os << "CacheCastTag: LastPacket=" << m_lastPacket;
}

CacheCastTag::CacheCastTag (int32_t payloadSize, bool lastPacket)
  : Tag (),
    m_lastPacket (lastPacket),
    m_payloadSize (payloadSize)
{
}

CacheCastTag::CacheCastTag ()
  : Tag (),
    m_lastPacket (false),
    m_payloadSize (-1)
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

} // namespace ns3

