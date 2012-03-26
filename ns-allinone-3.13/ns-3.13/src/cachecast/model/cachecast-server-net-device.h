/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_SERVER_NET_DEVICE_H__
#define __CACHECAST_SERVER_NET_DEVICE_H__

#include "ns3/point-to-point-net-device.h"
#include "ns3/queue.h"
#include "ns3/callback.h"
#include <vector>

namespace ns3 {

/**
 * /brief CacheCast NetDevice
 */
class CacheCastServerNetDevice : public PointToPointNetDevice
{
public:
  /**
   * Iterator to loop over failed sockets
   * Used Begin() and End() to use the iterator
   *
   * Usage:
   * CacheCastServerNetDevice::Iterator it;
   * for (it = ccDev.Begin(); it < ccDev.End(); it++) {
   *   // uint32_t socketIndex = *it; 
   * }
   */
//   typedef std::vector<uint32_t>::const_iterator Iterator;

  /**
   * /brief Construct an empty CacheCastServerNetDevice
   */
  CacheCastServerNetDevice ();

  static TypeId GetTypeId (void);

  /**
   * \brief Overridden function Send() in PointToPointNetDevice
   */
  bool Send (Ptr<Packet> packet, const Address &dest, uint16_t protocolNumber);

  /**
   * \brief This function is called when the last CacheCast packet is received on a
   * CacheCastServerNetDevice. Then all batched packets are transmitted on the link
   * as a packet train. The function should be called on all CacheCastServerNetDevices
   * on a node when one of them received the last packet 
   *
   * \param payloadId the payload ID to use for these packet's payload
   */
  bool FinishSend(uint32_t payloadId); //TODO check if it can be private (friend)

  /**
   * \brief Get an iterator which refers to the first failed socket index
   */
//   Iterator Begin (void) const;

  /**
   * \brief Get an iterator which indicates past-the-last failed socket index
   */
//   Iterator End (void) const;

  void SetFailedCallback (Callback<void, uint32_t> callback);

private:
  /**
   * \brief Calculate the next available payload ID
   * Payload ID's can wrap around every Seconds
   */
  uint32_t GetNextPayloadId ();

  /**
   * \brief used to store the parameters for the Send() function call in the 
   * CacheCast queue in order to call Send() in FinishSend()
   */
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
  std::vector<PacketInfo> m_ccQueue;

  /**
   * The index of sockets which failed to send on this CacheCastServerNetDevice
   */
//   std::vector<uint32_t> m_failed;

  Callback<void, uint32_t> m_failedCallback;

};

} // namespace ns3

#endif /* __CACHECAST_SERVER_NET_DEVICE_H__ */
