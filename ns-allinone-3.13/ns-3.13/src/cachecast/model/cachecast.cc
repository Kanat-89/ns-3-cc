/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast.h"
#include "ns3/log.h"

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
    std::vector<Ptr <Socket> >::iterator socket;
    bool failed;
    for(socket = m_sockets.begin(); socket != m_sockets.end(); ++socket)
    {
        if((*socket)->Send(packet) < 0){
           failed = true; 
        }  
    }
    return failed; 
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
