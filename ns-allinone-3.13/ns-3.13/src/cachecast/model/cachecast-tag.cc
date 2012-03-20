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
  return sizeof (uint8_t);
}

void 
CacheCastTag::Serialize (TagBuffer buf) const
{
  buf.WriteU8 (m_lastPacket ? 1 : 0);
}

void 
CacheCastTag::Deserialize (TagBuffer buf)
{
  m_lastPacket = buf.ReadU8 () ? true : false;
}

void 
CacheCastTag::Print (std::ostream &os) const
{
  os << "CacheCastTag: LastPacket=" << m_lastPacket;
}

CacheCastTag::CacheCastTag ()
  : Tag (),
    m_lastPacket (false)
{
}

CacheCastTag::CacheCastTag (bool lastPacket)
  : Tag (),
    m_lastPacket (lastPacket)
{
}

bool
CacheCastTag::IsLastPacket ()
{
  return m_lastPacket;
}

} // namespace ns3

