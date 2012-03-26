/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast.h"
#include "ns3/log.h"
#include "cachecast-tag.h"
#include "ns3/node.h"
#include "cachecast-server-net-device.h"

NS_LOG_COMPONENT_DEFINE ("CacheCast");

namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED (CacheCast);

void 
CacheCast::AddSocket (Ptr<Socket> socket)
{
    m_sockets.push_back (socket);
}

bool 
CacheCast::Msend(Ptr<Packet> packet)
{
    //sjekke om socket er udp?
    Ptr<Packet> pack; 
    Ptr<Node> node;
    std::vector<Ptr <Socket> >::iterator socket;
    
    uint32_t socket_index = 0;

    bool lastpacket;
    bool succesful = true;
    
    
    for(socket = m_sockets.begin(); socket != m_sockets.end(); ++socket)
    {
        
        NS_ASSERT_MSG ((*socket)->GetSocketType () == Socket::NS3_SOCK_DGRAM, "Beskjed til meg");
        
        node = (*socket)->GetNode ();
        for (uint32_t i = 0; i < (node->GetNDevices ()); i++)
        {
            Ptr<CacheCastServerNetDevice> ccDev = DynamicCast<CacheCastServerNetDevice> (node->GetDevice (i));
            if (ccDev != 0)
            {
                ccDev->SetFailedCallback (MakeCallback (&CacheCast::SetFailedSocket, this));
            }
        } 

        lastpacket = (socket_index == m_sockets.size ()-1); 
        pack = Copy<Packet> (packet); 
        CacheCastTag tag (socket_index, pack->GetSize (), lastpacket);
        pack->AddPacketTag (tag);        
          
        if((*socket)->Send(pack) < 0)
        {
           succesful = false;
           //m_failed[i] = true; 
        }
        socket_index++; 
    }
    
    
    return succesful; 
}

void
CacheCast::SetFailedSocket (uint32_t i){
     m_failed.push_back (m_sockets[i]);
}

TypeId
CacheCast::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCast")
    .SetParent<Object> ()
    .AddConstructor<CacheCast> ()
  ;
  return tid;
}

}//end namespace ns3
