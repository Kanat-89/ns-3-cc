#include "ns3/log.h"
#include "ns3/udp-header.h"
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

//   UdpHeader udp_head;
//   CacheCastTag ccTag;
//   if (!packet->PeekHeader (udp_head) || packet->PeekPacketTag (ccTag))
//     std::cout << "UDP\n";


// remember to remove tag before sending packet

  return PointToPointNetDevice::Send (packet, dest, protocolNumber);
}

} // namespace ns3

