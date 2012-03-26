/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_HEADER_H__
#define __CACHECAST_HEADER_H__

#include "ns3/header.h"

namespace ns3 {

/**
 * \brief Header for CacheCast packet, aka. CacheCast header
 */
class CacheCastHeader : public Header
{
public:
  /**
   * \brief Construct an empty CacheCastHeader
   */
  CacheCastHeader ();

  /**
   * \brief Construct a CacheCastHeader with fields set
   */
  CacheCastHeader (uint32_t payloadId, uint32_t payloadSize,
//       uint32_t originalSize, 
      uint32_t index);

  /**
   * \returns the payload ID of this packet
   */
  uint32_t GetPayloadId (void) const;

  /**
   * \returns the payload size of this packet
   */
  uint32_t GetPayloadSize (void) const;

  /**
   * \returns the original size of this packet
   */
//   uint32_t GetOriginalSize (void) const;

  /**
   * \returns the table/cache-slot index of this packet
   */
  uint32_t GetIndex (void) const;

  /**
   * \brief Set the payload ID of this packet
   */
  void SetPayloadId (uint32_t payloadId);

  /**
   * \brief Set the payload size of this packet
   */
  void SetPayloadSize (uint32_t payloadSize);

  /**
   * \brief Set the original size of this packet
   */
//   void SetOriginalSize (uint32_t originalSize);

  /**
   * \brief Set the table/cache-slot index of this packet
   */
  void SetIndex (uint32_t index);

  static TypeId GetTypeId (void);
  TypeId GetInstanceTypeId (void) const;
  void Print (std::ostream &os) const;
  uint32_t GetSerializedSize (void) const;
  void Serialize (Buffer::Iterator start) const;
  uint32_t Deserialize (Buffer::Iterator start);

private:
  /**
   * The payload ID of the packet
   */
  uint32_t m_payloadId;

  /**
   * The size of the payload in the packet.
   */
  uint32_t m_payloadSize;

//   uint32_t m_originalSize; //TODO remove?

  /**
   * The index into the CMU table and the CSU cache slot
   */
  uint32_t m_index;
};

} // namespace ns3

#endif /* __CACHECAST-HEADER_H__ */

