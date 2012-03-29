/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/cachecast-server-helper.h"
#include "ns3/cachecast-module.h"

using namespace ns3;

//              TOPOLOGY
//        
//         (client)  (client)
//            n1        n2
//   10.1.1.2  \        /  10.1.2.2
//              \      /
//               \    /
//       10.1.1.1 \  / 10.1.2.1
//                 n0
//              (server)


int 
main (int argc, char *argv[])
{
  LogComponentEnable ("CacheCastTestApplication", LOG_LEVEL_ALL);
  LogComponentEnable ("CacheCastServerNetDevice", LOG_LEVEL_ALL);
  LogComponentEnable ("CacheCastPid", LOG_LEVEL_ALL);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

//   bool verbose = true;
// 
//   CommandLine cmd;
//   cmd.AddValue ("verbose", "Tell application to log if true", verbose);
//   cmd.Parse (argc,argv);


// Ptr<Packet> packet = Create<Packet> (1000);
// UdpHeader uh;
// CacheCastHeader cch (111, 222, true);
// PppHeader ppp;
// 
// packet->AddHeader (uh);
// packet->AddHeader (cch);
// packet->AddHeader (ppp);
// 
// packet->RemoveHeader (ppp);
// CacheCastHeader cch2;
// packet->RemoveHeader (cch2);
// cch2.Print(std::cerr);
// 
// return 0;

  NodeContainer nodes;
  nodes.Create (3);

  /* Set up channel n0 <-> n1 */
  CacheCastServerHelper ccHelper;
//   pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  ccHelper.SetDeviceAttribute ("DataRate", StringValue ("10Kbps"));
  ccHelper.SetChannelAttribute ("Delay", StringValue ("100ms"));

  NetDeviceContainer devices1 = ccHelper.Install (nodes.Get(0), nodes.Get(1));
//   ccDevice.SetAttribute ("Mtu", UintegerValue (512));

  /* Set up channel n0 <-> n2 */
  ccHelper.SetDeviceAttribute ("DataRate", StringValue ("10Kbps"));
  ccHelper.SetChannelAttribute ("Delay", StringValue ("100ms"));

  NetDeviceContainer devices2 = ccHelper.Install (nodes.Get(0), nodes.Get(2));

  /* Setup network stack and addresses */
  InternetStackHelper stack;
  stack.Install (nodes);
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces1 = address.Assign (devices1);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces2 = address.Assign (devices2);

  UdpEchoServerHelper echoServer1 (9);
  ApplicationContainer serverApps1 = echoServer1.Install (nodes.Get (1));
  serverApps1.Start (Seconds (1.0));
  serverApps1.Stop (Seconds (10.0));

  UdpEchoServerHelper echoServer2 (9);
  ApplicationContainer serverApps2 = echoServer2.Install (nodes.Get (2));
  serverApps2.Start (Seconds (1.0));
  serverApps2.Stop (Seconds (10.0));


  Ptr<CacheCastTestApplication> app = Create<CacheCastTestApplication> ();
  Address addr1 (InetSocketAddress (interfaces1.GetAddress (1), 9));
  Address addr2 (InetSocketAddress (interfaces2.GetAddress (1), 9));
  app->AddAddress (addr1);
  app->AddAddress (addr2);
  app->AddAddress (addr2);
  app->AddAddress (addr1);
  app->AddAddress (addr1);
  nodes.Get (0)->AddApplication (app);
  app->SetStartTime (Seconds (2.0));
  app->SetStopTime (Seconds (10.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


