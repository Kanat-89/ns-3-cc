/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/cachecast-server-helper.h"
#include "ns3/cachecast-module.h"

using namespace ns3;

int 
main (int argc, char *argv[])
{
  LogComponentEnable ("CacheCastTestApplication", LOG_LEVEL_ALL);
  LogComponentEnable ("CacheCastServerNetDevice", LOG_LEVEL_ALL);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  bool verbose = true;

  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell application to log if true", verbose);
  cmd.Parse (argc,argv);

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

//   NetDeviceContainer devices;
//   devices = pointToPoint.Install (nodes);

  /* Set up node */
  ObjectFactory devF;
  ObjectFactory qF;
  qF.SetTypeId ("ns3::DropTailQueue");
  devF.SetTypeId ("ns3::PointToPointNetDevice");
  Ptr<PointToPointNetDevice> dev = devF.Create<PointToPointNetDevice> ();
  dev->SetAddress (Mac48Address::Allocate ());
  nodes.Get (1)->AddDevice (dev);
  Ptr<Queue> q = qF.Create<Queue> ();
  dev->SetQueue(q);

  /* Set up server */
  CacheCastServerHelper ccHelper;
  Ptr<CacheCastServerNetDevice> ccDevice = ccHelper.Install (nodes.Get(0), dev);
//   ccDevice.SetAttribute ("Mtu", UintegerValue (512));

  NetDeviceContainer devices;
  devices.Add (ccDevice);
  devices.Add (dev);

  InternetStackHelper stack;
  stack.Install (nodes);
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);
  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

//   UdpEchoClientHelper echoClient (interfaces.GetAddress (0), 9);
//   echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
//   echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
//   echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

//   ApplicationContainer clientApps = echoClient.Install (nodes.Get (1));
//   clientApps.Start (Seconds (2.0));
//   clientApps.Stop (Seconds (10.0));

  Ptr<CacheCastTestApplication> app = Create<CacheCastTestApplication> ();
  Address addr (InetSocketAddress (interfaces.GetAddress (1), 9));
  app->SetAddress (addr);
  nodes.Get (0)->AddApplication (app);
  app->SetStartTime (Seconds (2.0));
  app->SetStopTime (Seconds (10.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


