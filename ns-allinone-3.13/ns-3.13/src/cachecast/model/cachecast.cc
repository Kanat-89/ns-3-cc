/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast.h"

NS_LOG_COMPONENT_DEFINE ("CacheCast");


namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED (CacheCast);

/* ... */
void 
AddSocket (Ptr<Socket> socket)
{
  m_sockets.push_back (socket);
}

bool 
Msend(Ptr <Packet> packet)
{

}

}//end namespace ns3

