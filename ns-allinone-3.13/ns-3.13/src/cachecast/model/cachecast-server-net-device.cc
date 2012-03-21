/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

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
{
  NS_LOG_FUNCTION_NOARGS ();
  m_ccQueue = new std::vector<PacketInfo>;
}

CacheCastServerNetDevice::~CacheCastServerNetDevice ()
{
  m_ccQueue->clear ();
  delete m_ccQueue;
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
  NS_LOG_FUNCTION (packet << dest << protocolNumber);
  bool retValue = true;

  UdpHeader udp_head;
  CacheCastTag ccTag;
  // if DCCP gets supported handle it also
  if (!packet->PeekHeader (udp_head) || !packet->PeekPacketTag (ccTag))
  {
    NS_LOG_INFO ("Packet " << packet << " is either not a UDP packets or not a CacheCast packet");
    // just use the regular PointToPointNetDevice::Send if the packet is not a
    // CacheCast packet or unsupported transport protocol is used
    return PointToPointNetDevice::Send (packet, dest, protocolNumber);
  }

  PacketInfo info (packet, dest, protocolNumber);
  m_ccQueue->push_back (info);

  if (ccTag.IsLastPacket ())
  {
    // TODO do the actual sending
    NS_LOG_INFO ("Last CacheCast packet");
    PacketInfo inf = m_ccQueue->front ();
    NS_LOG_INFO (inf.packet << " " << inf.dest << " " << inf.protocolNumber);

    PacketInfo inf2 = m_ccQueue->back ();
    NS_LOG_INFO (inf2.packet << " " << inf2.dest << " " << inf2.protocolNumber);

    // TODO get all CacheCastServerNetDevice on node and issue a FinishSend ()
//     Ptr<Node> node = GetNode ();
//     NS_LOG_INFO("Node:" << node);
// 
//     for (int i = 1; i <= node->GetNDevices (); i++)
//     {
//       Ptr<NetDevice> dev = node->GetDevice (i);
// 
//       // TODO get CacheCastServerNetDevice's
// 
//       retValue = ccDev->FinishSend () == false ? false : retValue;
//     }
// 
//     return retValue;
  }

  return true;
}

bool
CacheCastServerNetDevice::FinishSend ()
{

//   packet->RemovePacketTag

// remember to remove tag before sending packet
  return true;
}

} // namespace ns3

