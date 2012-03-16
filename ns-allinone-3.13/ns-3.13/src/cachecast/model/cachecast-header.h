/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_HEADER_H__
#define __CACHECAST_HEADER_H__

#include "ns3/header.h"

namespace ns3 {

/**
 * \brief Header for CacheCast packet
 */
class CacheCastHeader : public Header
{
public:
  /**
   * \brief Construct an empty CacheCastHeader
   */
  CacheCastHeader ();

  /**
   * \returns the payload ID of this packet
   */
  uint32_t GetPayloadId (void) const;

  static TypeId GetTypeId (void);
  TypeId GetInstanceTypeId (void) const;
  void Print (std::ostream &os) const;
  uint32_t GetSerializedSize (void) const;
  void Serialize (Buffer::Iterator start) const;
  uint32_t Deserialize (Buffer::Iterator start);

private:
  uint32_t m_payloadId;
  uint32_t m_payloadSize;
  uint32_t m_originalSize;
  uint32_t m_index;
};

} // namespace ns3

#endif /* __CACHECAST-HEADER_H__ */

