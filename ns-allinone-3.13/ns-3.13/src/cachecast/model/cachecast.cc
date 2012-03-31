/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast.h"
#include "ns3/log.h"
#include "cachecast-tag.h"
#include "ns3/node.h"
#include "cachecast-server-net-device.h"

NS_LOG_COMPONENT_DEFINE ("CacheCast");

namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED (CacheCast);


CacheCast::Iterator 
CacheCast::Begin (void) const
{
  return m_sockets.begin ();
}

CacheCast::Iterator 
CacheCast::End (void) const
{
  return m_sockets.end ();
}

CacheCast::Iterator 
CacheCast::BeginFailedSockets (void) const
{
  return m_failed.begin ();
}

CacheCast::Iterator 
CacheCast::EndFailedSockets (void) const
{
  return m_failed.end ();
}

void 
CacheCast::AddSocket (Ptr<Socket> socket)
{
    m_sockets.push_back (socket);
}

void
CacheCast::RemoveSocket(Ptr<Socket> socket){
    std::vector<Ptr<Socket> >::iterator vItr = m_sockets.begin();
    while ( vItr != m_sockets.end() )
    {
    if ( (*vItr) == socket )
    {
        vItr = m_sockets.erase( vItr ); // Will return next valid iterator
        break;
    }
    else
        vItr++;
    }    
}

bool 
CacheCast::Msend(Ptr<Packet> packet)
{
    Ptr<Packet> pack; 
    Ptr<Node> node;
    std::vector<Ptr <Socket> >::iterator socket;
    
    uint32_t socket_index = 0;

    bool lastpacket;
    bool succesful = true;
     
    for(socket = m_sockets.begin(); socket != m_sockets.end(); ++socket)
    {        
        // if DCCP gets supported handle it also
        NS_ASSERT_MSG ((*socket)->GetSocketType () == Socket::NS3_SOCK_DGRAM, "This socket is not an UDP socket");
        
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
           SetFailedSocket (socket_index); 
        }
        socket_index++; 
    }
    
    return succesful; 
}

void
CacheCast::Merge(CacheCast cc)
{
    std::vector<Ptr<Socket> >::iterator vItr = cc.m_sockets.begin();
    while ( vItr != cc.m_sockets.end() )
    {
        AddSocket((*vItr));
        vItr++;
    } 
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
