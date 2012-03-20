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
  return sizeof (uint32_t);
}

void 
CacheCastTag::Serialize (TagBuffer buf) const
{
  buf.WriteU32 (m_id);
}

void 
CacheCastTag::Deserialize (TagBuffer buf)
{
  m_id = buf.ReadU32 ();
}

void 
CacheCastTag::Print (std::ostream &os) const
{
  os << "CacheCastTag: ID=" << m_id;
}

CacheCastTag::CacheCastTag ()
  : Tag (),
    m_id (0)
{
}

CacheCastTag::CacheCastTag (uint32_t id)
  : Tag (),
    m_id (id)
{
}


} // namespace ns3

