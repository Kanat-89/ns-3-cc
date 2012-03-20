#include "ns3/log.h"
#include "ns3/udp-header.h"
#include "ns3/cachecast-tag.h"
#include "cachecast-server-net-device.h"
//#include "cachecast-header.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastServerNetDevice");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastServerNetDevice);

CacheCastServerNetDevice::CacheCastServerNetDevice ()
  : PointToPointNetDevice(),
    m_nextPayloadId (0)
//     m_payloadSize (0),
//     m_originalSize (0)
{

}

TypeId
CacheCastServerNetDevice::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastServerNetDevice")
    .SetParent<PointToPointNetDevice> ()
    .AddConstructor<CacheCastServerNetDevice> ()
  ;
  return tid;
}

bool
CacheCastServerNetDevice::Send (Ptr<Packet> packet, const Address &dest, uint16_t protocolNumber)
{
  std::cout << "CacheCastServerNetDevice testing testing" << std::endl;

  UdpHeader udp_head;
  CacheCastTag ccTag;
  // if DCCP gets supported handle it also
  if (!packet->PeekHeader (udp_head) || !packet->PeekPacketTag (ccTag)) {
    std::cout << "No CacheCast packet or UDP\n";
    // just use the regular PointToPointNetDevice::Send if the packet is not a
    // CacheCast packet or unsupported transport protocol is used
    return PointToPointNetDevice::Send (packet, dest, protocolNumber);
  }

  std::cout << "CacheCast packet\n";

  

  if (ccTag.IsLastPacket ()) {
    // TODO do the actual sending
    
    return true;
  }

//   packet->RemovePacketTag

// remember to remove tag before sending packet

  return true;
}

} // namespace ns3

