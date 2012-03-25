/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#ifndef CACHECAST_TAG_H
#define CACHECAST_TAG_H

#include "ns3/tag.h"

namespace ns3 {

class CacheCastTag : public Tag
{
public:
  /**
   * \brief Creates a new empty (invalid) CacheCastTag
   * 
   * Payload size and socketIndex must be set explicitly before tag is added to a packet
   * */
  CacheCastTag ();

  /** 
   * \brief Creates a new CacheCastTag and sets all necessary members
   *
   * \param socketIndex index of the socket in one Msend() iteration.
   *                    Used to report errors from CacheCastServerNetDevice to Msend()
   * \param payloadSize size of the payload the packet carries
   * \param lastPacket  notifies the CacheCastServerNetDevice that this packet is the 
   *                    last one so that all CacheCast packets can be sent
   */
  CacheCastTag (int32_t socketIndex, int32_t payloadSize, bool lastPacket = false);

  /**
   * \returns true if this packet is the last in a Msend() iteration
   */
  bool IsLastPacket ();

  /**
   * \returns the size of the payload
   */
  int32_t GetPayloadSize ();

  /**
   * \brief Set the payload size
   * \param payloadSize the new payload size
   */
  void SetPayloadSize (int32_t payloadSize);

  /**
   * \returns the socketIndex
   */
  int32_t GetSocketIndex ();

  /**
   * \brief Set the socket index
   * \param socketIndex the new socket index
   */
  void SetSocketIndex (int32_t socketIndex);

  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (TagBuffer buf) const;
  virtual void Deserialize (TagBuffer buf);
  virtual void Print (std::ostream &os) const;

private:
  int32_t m_socketIndex;
  int32_t m_payloadSize;
  bool m_lastPacket;
};

} // namespace ns3

#endif /* CACHECAST_TAG_H */
