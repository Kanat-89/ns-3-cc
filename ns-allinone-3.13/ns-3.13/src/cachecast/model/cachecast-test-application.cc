/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/cachecast-module.h"
#include "ns3/packet.h"
#include "ns3/address.h"

using namespace ns3;

NS_OBJECT_ENSURE_REGISTERED (CacheCastTestApplication);

TypeId
CacheCastTestApplication::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastTestApplication")
    .SetParent<Application> ()
    .AddConstructor<CacheCastTestApplication> ()
  ;

  return tid;
}

CacheCastTestApplication::CacheCastTestApplication ()
{
}

void
CacheCastTestApplication::SetAddress (Address address)
{
  m_address = address;
}

void
CacheCastTestApplication::StartApplication (void)
{
  m_sock = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  m_sock->Bind();
  m_sock->Connect (m_address);

  Ptr<Packet> packet = Create<Packet> (512);
  CacheCastTag tag;
  packet->AddPacketTag (tag);
  
  m_sock->Send (packet);
}

void
CacheCastTestApplication::StopApplication (void)
{
  m_sock->Close();
}
