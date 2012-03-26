/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/log.h"
#include "ns3/udp-header.h"
#include "ns3/simulator.h"
#include "ns3/cachecast-tag.h"
#include "cachecast-server-net-device.h"
#include "cachecast-header.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastServerNetDevice");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastServerNetDevice);

CacheCastServerNetDevice::CacheCastServerNetDevice ()
  : PointToPointNetDevice()
{
  NS_LOG_FUNCTION_NOARGS ();
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

void
CacheCastServerNetDevice::SetFailedCallback (Callback<void, uint32_t> callback)
{
  m_failedCallback = callback;
}

bool
CacheCastServerNetDevice::Send (Ptr<Packet> packet, const Address &dest, uint16_t protocolNumber)
{
  NS_LOG_FUNCTION (packet << dest << protocolNumber);
  bool retValue = true;

  UdpHeader udp_head;
  CacheCastTag ccTag;
  bool hasCcTag = packet->PeekPacketTag (ccTag);
  NS_ASSERT_MSG (hasCcTag, "All CacheCast packets must have a CacheCastTag");

  // if DCCP gets supported handle it also
  uint32_t hasUdpHrd = packet->PeekHeader (udp_head);
  NS_ASSERT_MSG(hasUdpHrd, "Only UDP packets are supported by CacheCast");

  PacketInfo info(packet, dest, protocolNumber);
  m_ccQueue.push_back (info);

  if (ccTag.IsLastPacket ())
  {
    NS_LOG_DEBUG ("Last CacheCast packet");
    Ptr<Node> node = GetNode ();
    uint32_t payloadId = GetNextPayloadId ();

    // Get all CacheCastServerNetDevice on node and issue a FinishSend ()
    for (uint32_t i = 0; i < node->GetNDevices (); i++)
    {
      Ptr<CacheCastServerNetDevice> ccDev = DynamicCast<CacheCastServerNetDevice> (node->GetDevice (i));

      if (ccDev != 0)
      {
        bool ret = ccDev->FinishSend (payloadId);
        
        if (ret == true)
          NS_LOG_DEBUG ("All CacheCast packets sent from device " << ccDev);
        else
        {
          NS_LOG_DEBUG ("Not all CacheCast packets were sent from device " << ccDev);
          retValue = false;
        }
      }
    }
  }

  return retValue;
}

bool
CacheCastServerNetDevice::FinishSend (uint32_t payloadId)
{
  NS_LOG_FUNCTION_NOARGS();
  bool retValue = true;
  uint32_t count = 0;
  std::vector<PacketInfo>::iterator it;

  for (it = m_ccQueue.begin(); it < m_ccQueue.end(); it++)
  {
    Ptr<Packet> p = it->packet;
    CacheCastTag tag;
    p->RemovePacketTag(tag);

    NS_ASSERT_MSG (tag.GetPayloadSize () >= 0, "CacheCast: Illegal payload size "
        << tag.GetPayloadSize ());
    NS_ASSERT_MSG (tag.GetSocketIndex () >= 0, "CacheCast: Illegal socket index "
        << tag.GetSocketIndex ());

    CacheCastHeader cch (payloadId, tag.GetPayloadSize (), 0);

    /* Truncate all packets besides first packet */
    if (count > 0)
    {
      p->RemoveAtEnd (tag.GetPayloadSize ());
      cch.SetPayloadSize (0);
    }
    
    // TODO enable when CSU present
//     p->AddHeader (cch);

    NS_LOG_DEBUG ("CacheCast: Sending packet " << it->packet << " " <<
        it->dest << " " << it->protocolNumber);

    bool ret = PointToPointNetDevice::Send (it->packet, it->dest, it->protocolNumber);

    /* If the packet failed to be sent onto the link, add index to failed vector */
    if (ret == false)
    {
      NS_LOG_DEBUG ("CacheCast: Packet " << it->packet << " failed to be sent on device " << this);
      m_failedCallback (tag.GetSocketIndex ());
      retValue = false;
    }

    count++;
  }

  m_ccQueue.clear ();

  return retValue;
}


//TODO sjekk om pre kan vaere static
//opprett aggregated object in node CacheCastPid
uint32_t
CacheCastServerNetDevice::GetNextPayloadId ()
{
  static uint32_t payloadId = 0;
  static double pre = Simulator::Now ().GetSeconds ();

  /* Wrap around if one second has passed */
  if (Simulator::Now ().GetSeconds () - pre > 1.0)
  {
    payloadId = 0;
    pre = Simulator::Now ().GetSeconds ();
  }

  return payloadId++;
}

} // namespace ns3

