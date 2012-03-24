/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_SERVER_NET_DEVICE_H__
#define __CACHECAST_SERVER_NET_DEVICE_H__

#include "ns3/point-to-point-net-device.h"
#include "ns3/queue.h"
#include <vector>

namespace ns3 {

/**
 * /brief CacheCast NetDevice
 */
class CacheCastServerNetDevice : public PointToPointNetDevice
{
public:
  static TypeId GetTypeId (void);
  /**
   * /brief Construct an empty CacheCastServerNetDevice
   */
  CacheCastServerNetDevice ();

  ~CacheCastServerNetDevice ();

  bool Send (Ptr<Packet> packet, const Address &dest, uint16_t protocolNumber);

  /**
   * This function is called when the last CacheCast packet is received on a
   * CacheCastServerNetDevice. Then all batched packets are transmitted on the link
   * as a packet train. The function should be called on all CacheCastServerNetDevice's
   * on a node when one of them received the last packet */
  bool FinishSend();

private:
  /**
   * \brief Calculate the next available payload ID
   * Payload ID's can wrap around every Seconds
   */
  uint32_t GetNextPayloadId ();

  struct PacketInfo
  {
    Ptr<Packet> packet;
    Address dest;
    uint16_t protocolNumber;

    PacketInfo (Ptr<Packet> p, const Address &d, uint16_t prot)
    {
      packet = p;
      dest = d;
      protocolNumber = prot;
    }
  };
  /**
   * The queue which this CacheCastServerNetDevice uses to store the CacheCast packets
   * before they are sent as a batch onto the channel
   */
  std::vector<PacketInfo>* m_ccQueue;

  /**
   * The next free payload ID to use
   */
//   uint32_t m_nextPayloadId; TODO remove?

};

} // namespace ns3

#endif /* __CACHECAST_SERVER_NET_DEVICE_H__ */
