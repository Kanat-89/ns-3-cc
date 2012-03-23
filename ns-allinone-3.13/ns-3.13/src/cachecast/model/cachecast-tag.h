/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#ifndef CACHECAST_TAG_H
#define CACHECAST_TAG_H

#include "ns3/tag.h"

namespace ns3 {

class CacheCastTag : public Tag
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (TagBuffer buf) const;
  virtual void Deserialize (TagBuffer buf);
  virtual void Print (std::ostream &os) const;
  CacheCastTag (int32_t payloadSize, bool lastPacket = false);
  CacheCastTag ();
  bool IsLastPacket ();
  int32_t GetPayloadSize ();
private:
  bool m_lastPacket;
  int32_t m_payloadSize;
};

} // namespace ns3

#endif /* CACHECAST_TAG_H */
