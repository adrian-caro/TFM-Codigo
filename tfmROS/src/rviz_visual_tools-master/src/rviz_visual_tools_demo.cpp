
// ROS
#include <ros/ros.h>
#include <string>
// For visualizing things in rviz
#include <rviz_visual_tools/rviz_visual_tools.h>

// C++
#include <string>
#include <vector>
#include "rviz_visual_tools/headers/Node.h"
#include "rviz_visual_tools/headers/Tunnel.h"
#include "rviz_visual_tools/headers/Graph.h"
#include "rviz_visual_tools/headers/Segment.h"
#include "rviz_visual_tools/headers/Dijkstra.h"
#include "rviz_visual_tools/headers/Exploration.h"
#include "rviz_visual_tools/headers/OOI.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <random>
#include <math.h>
using namespace std;


//Distances in meters (m).

#define MinNodeHeight 1.5
#define MaxNodeHeight 4

#define MinNodewidth 1.5
#define MaxNodewidth 3

#define MinNodedepth 1
#define MaxNodedepth 4

#define MinHeight 0.5
#define MaxHeight 1.5

#define Minwidth 0.5
#define Maxwidth 1.5

#define MinHorizontalOrientation 0
#define MaxHorizontalOrientation 360

#define MinVerticalOrientation 0
#define MaxVerticalOrientation 360

#define MinNumberoftunnels 2
#define MaxNumberoftunnels 4

#define Mintunnelsegments 1
#define Maxtunnelsegments 4

#define Minsegmentlength 1
#define Maxsegmentlength 8

#define Minsegmentwidth 0.5
#define Maxsegmentwidth 1.5

#define Minsegmentheight 0.5
#define Maxsegmentheight 1.5

//Slope in %
#define Minsegmentlope 0
#define Maxsegmentlope 15

#define RandomlocationdistX 10 //Distance between nodes
#define RandomlocationdistY 10
#define RandomlocationdistZ 2

#define OOIgenerationRatio 0.3 //If the random number is lower than OOIgenerationRatio, then a OOI is generated

#define OOIdetectionRatio 0.9
#define unknownodeRatio 0.1

namespace rvt = rviz_visual_tools;

namespace rviz_visual_tools
{
class RvizVisualToolsDemo
{
private:
  // A shared node handle
  ros::NodeHandle nh_;

  // For visualizing things in rviz
  rvt::RvizVisualToolsPtr visual_tools_;

  std::string name_;

public:
  /**
   * \brief Constructor
   */
  RvizVisualToolsDemo() : name_("rviz_demo")
  {
    visual_tools_.reset(new rvt::RvizVisualTools("world", "/rviz_visual_tools"));
    visual_tools_->loadMarkerPub();  // create publisher before waiting

    ROS_INFO("Sleeping 5 seconds before running demo");
    ros::Duration(5.0).sleep();

    // Clear messages
    visual_tools_->deleteAllMarkers();
    visual_tools_->enableBatchPublishing();
  }



  void plotroute(Node *nodos,vector<int> solutionpath)
  {
    Eigen::Isometry3d pose = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d poseto = Eigen::Isometry3d::Identity();
    int i=0;
    ROS_INFO_STREAM_NAMED("test","Publishing Route");
    vector<float> coordenadas;

    coordenadas=nodos[solutionpath.at(0)].getcoordinates();
    pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    coordenadas=nodos[solutionpath.at(1)].getcoordinates();
    poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::GREY , rviz_visual_tools::XXXLARGE);


    while (i<solutionpath.size()-1)
    {
      coordenadas=nodos[solutionpath.at(i)].getcoordinates();
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      coordenadas=nodos[solutionpath.at(i+1)].getcoordinates();
      poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::GREY , rviz_visual_tools::XXXLARGE);
      i++;
    }

    coordenadas=nodos[solutionpath.at(0)].getcoordinates();
    pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    coordenadas=nodos[solutionpath.at(1)].getcoordinates();
    poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::GREY , rviz_visual_tools::XXXLARGE);

    visual_tools_->trigger();
  }

  /** \brief Compare every size range */
  void ploteo(int numnodes,Node *nodos,vector<Enlace> const& enlaces,int numberoftunnels,Tunnel *tuneles,int startnode, int endnode)
  {
    //ROS_INFO_STREAM_NAMED(name_, "Testing sizes of marker scale");


    Eigen::Isometry3d pose = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d poseto = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d posename = Eigen::Isometry3d::Identity();
    poseto.translation() = Eigen::Vector3d( 0, 0, 0 );
    vector<float> coordenadas;
    ROS_INFO_STREAM_NAMED("test","Publishing Nodes");
    for (int i=0;i<numnodes;i++)
    {
      //Create pose

      coordenadas=nodos[i].getcoordinates();

      //pose = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) ); // translate x,y,z
      // Publish arrow vector of pose

      if (i==startnode)
      {
        visual_tools_->publishSphere(pose, rviz_visual_tools::GREEN, rviz_visual_tools::XXXXLARGE);
      }
      else if (i==endnode)
      {
        visual_tools_->publishSphere(pose, rviz_visual_tools::RED, rviz_visual_tools::XXXXLARGE);
      }
      else {
        visual_tools_->publishSphere(pose, rviz_visual_tools::BLUE, rviz_visual_tools::XXXXLARGE);
      }
      posename.translation() = Eigen::Vector3d(coordenadas.at(0), coordenadas.at(1), coordenadas.at(2)+0.5);
      visual_tools_->publishText(posename, "Node " + nodos[i].gettype(), WHITE, rviz_visual_tools::XXXXLARGE, false);


      poseto=pose;
    }
    vector<int> endings;
    for (int i=0;i<numberoftunnels;i++)
    {
      endings=tuneles[i].getendings();

      coordenadas=nodos[endings.at(0)].getcoordinates();
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      coordenadas=nodos[endings.at(1)].getcoordinates();
      poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::BLACK , rviz_visual_tools::XXLARGE);
    }
    visual_tools_->trigger();
  }

  void explorationplot(int numnodes,Node *nodos,vector<Enlace> const& enlaces,int numberoftunnels,Tunnel *tuneles,int startnode, int endnode,vector<int> solutionpath,int tunnelornode,int actualtunnelornode)
  {
    //ROS_INFO_STREAM_NAMED(name_, "Testing sizes of marker scale");
    visual_tools_->deleteAllMarkers();

    Eigen::Isometry3d pose = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d poseto = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d posename = Eigen::Isometry3d::Identity();
    poseto.translation() = Eigen::Vector3d( 0, 0, 0 );
    vector<float> coordenadas;
    for (int i=0;i<numnodes;i++)
    {
      //Create pose

      coordenadas=nodos[i].getcoordinates();

      //pose = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) ); // translate x,y,z
      // Publish arrow vector of pose
      if(i!=actualtunnelornode){
        if (i==startnode)
        {
          visual_tools_->publishSphere(pose, rviz_visual_tools::GREEN, rviz_visual_tools::XXXXLARGE);
        }
        else if (i==endnode)
        {
          visual_tools_->publishSphere(pose, rviz_visual_tools::RED, rviz_visual_tools::XXXXLARGE);
        }
        else {
          visual_tools_->publishSphere(pose, rviz_visual_tools::BLUE, rviz_visual_tools::XXXXLARGE);
        }
      }
      posename.translation() = Eigen::Vector3d(coordenadas.at(0), coordenadas.at(1), coordenadas.at(2)+0.5);
      visual_tools_->publishText(posename, "Node " + nodos[i].gettype(), WHITE, rviz_visual_tools::XXXXLARGE, false);


      poseto=pose;
    }
    vector<int> endings;
    for (int i=0;i<numberoftunnels;i++)
    {
      endings=tuneles[i].getendings();

      coordenadas=nodos[endings.at(0)].getcoordinates();
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      coordenadas=nodos[endings.at(1)].getcoordinates();
      poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::BLACK , rviz_visual_tools::XLARGE);
    }

    int i=0;

    coordenadas=nodos[solutionpath.at(0)].getcoordinates();
    pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    coordenadas=nodos[solutionpath.at(1)].getcoordinates();
    poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::GREY , rviz_visual_tools::XXLARGE);


    while (i<solutionpath.size()-1)
    {
      coordenadas=nodos[solutionpath.at(i)].getcoordinates();
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      coordenadas=nodos[solutionpath.at(i+1)].getcoordinates();
      poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::GREY , rviz_visual_tools::XXLARGE);
      i++;
    }

    coordenadas=nodos[solutionpath.at(0)].getcoordinates();
    pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    coordenadas=nodos[solutionpath.at(1)].getcoordinates();
    poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
    //std::cout << coordenadas.at(0) << coordenadas.at(1) << coordenadas.at(2)<< std::endl;
    visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::GREY , rviz_visual_tools::XXLARGE);





    if(tunnelornode==0)//Tunnel
    {
      endings=tuneles[actualtunnelornode].getendings();

      coordenadas=nodos[endings.at(0)].getcoordinates();
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      coordenadas=nodos[endings.at(1)].getcoordinates();
      poseto.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) );
      visual_tools_->publishCylinder(pose.translation(), poseto.translation(),rviz_visual_tools::ORANGE , rviz_visual_tools::XXXLARGE);
    }
    else//Node
    {
      coordenadas=nodos[actualtunnelornode].getcoordinates();

      //pose = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
      pose.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2) ); // translate x,y,z
      // Publish arrow vector of pose


      visual_tools_->publishSphere(pose, rviz_visual_tools::ORANGE, rviz_visual_tools::XXXXLARGE);
    }



    visual_tools_->trigger();





  }


  void replanning(int nodenumber,Node *nodos)
  {
    //ROS_INFO_STREAM_NAMED(name_, "Testing sizes of marker scale");


    Eigen::Isometry3d replan = Eigen::Isometry3d::Identity();
    vector<float> coordenadas;


      coordenadas=nodos[nodenumber].getcoordinates();


      replan.translation() = Eigen::Vector3d( coordenadas.at(0), coordenadas.at(1), coordenadas.at(2)+0.5 ); // translate x,y,z



      replan.translation() = Eigen::Vector3d(coordenadas.at(0), coordenadas.at(1), coordenadas.at(2)+1);
      visual_tools_->publishText(replan, "Robot lost. REPLANNING ", PINK, rviz_visual_tools::XXXXLARGE, false);

    visual_tools_->trigger();
  }



};  // end class

}  // namespace rviz_visual_tools




int main(int argc, char** argv)
{

  //roscore
  //roslaunch rviz_visual_tools demo_rviz.launch


  ros::init(argc, argv, "visual_tools_demo");
  ROS_INFO_STREAM("Visual Tools Demo");

  // Allow the action server to recieve and send ros messages
  ros::AsyncSpinner spinner(1);
  spinner.start();





  double x_location = 0;
  //demo.testRows(x_location);
  //demo.testSize(x_location, rviz_visual_tools::MEDIUM);
  //demo.testSize(x_location, rviz_visual_tools::LARGE);


  char inputmode;

  cout << "Choose a graph input mode: " << std::endl;
  cout << "1. Load graph from file (.txt)." << std::endl;
  cout << "2. Random graph." << std::endl;
  cout << "--------------------" << std::endl;
  cout << "Mode:";

  vector<Pair> OOIlist;
  int OOI_ID=0;
  float unknownodeR;


  do{
    std::cin >> inputmode;

    switch(inputmode)
    {
    case '1':

      break;
    case '2':

      break;
    default:
      std::cout<<"Invalid choice" << std::endl;

    }
  }while(inputmode!='1' &&  inputmode!='2');



  if (inputmode=='2')
  {
    cout<< std::endl;
    std::cout<<"Generating a random graph" << std::endl;
    //Grafo grafito;
    int Numnodos;
    int explorationactualnode;

    cout << "Introduce the number of nodes of the desired graph: ";

    cin >> Numnodos;
    Node nodos[Numnodos+1];
    string name="N",result;

    random_device rd;
    mt19937 mt(rd());

    OOI OOIs[Numnodos];
    Tunnel tuneles[Numnodos*4];
    vector<Segment> segments(Numnodos*5);
    uniform_real_distribution<double> randomx(-RandomlocationdistX, RandomlocationdistX);
    uniform_real_distribution<double> randomy(-RandomlocationdistY, RandomlocationdistY);
    uniform_real_distribution<double> randomz(-RandomlocationdistZ, RandomlocationdistZ);

    uniform_real_distribution<double> nodeh(MinNodeHeight, MaxNodeHeight);
    uniform_real_distribution<double> nodew(MinNodewidth, MaxNodewidth);
    uniform_real_distribution<double> noded(MinNodedepth, MaxNodedepth);
    float x,y,z,OOIratio;
    vector<float> previousnodeposition;

    uniform_real_distribution<double> OOIgeneration(0,1);

    for (int i=0;i<Numnodos;i++)
    {
      result = name + std::to_string(i);

      OOIratio= OOIgeneration(mt);

      if (OOIratio<OOIgenerationRatio) //If the random number is lower than OOIgenerationRatio, then a OOI is generated
      {
        //Create an OOI

        OOIs[OOI_ID].setID(OOI_ID);
        OOIlist.push_back(make_pair(OOI_ID,i));
        nodos[i].addOOI(&OOIs[OOI_ID]);
        //OOIs[OOI_ID].
        OOI_ID++;
      }

      unknownodeR=OOIgeneration(mt);

      if (unknownodeR<=unknownodeRatio && i!=0)
      {
        //Create unknown node
        nodos[i].settype("Unknown");
        //nodos[i].setnodenumber(9999);

      }
      else
      {
        nodos[i].settype(result);
        nodos[i].setnodenumber(i);
      }

      if (i==0)
      {
        x= randomx(mt);
        y= randomy(mt);
        z= randomz(mt);
      }
      else
      {
        previousnodeposition=nodos[i-1].getcoordinates();
        x= randomx(mt)+previousnodeposition.at(0);
        y= randomy(mt)+previousnodeposition.at(1);
        z= randomz(mt)+previousnodeposition.at(2);
      }

      nodos[i].setcoordinates(x,y,z);
      nodos[i].setheight(nodeh(mt));
      nodos[i].setwidth(nodew(mt));
      nodos[i].setdepth(noded(mt));
    }
    float var7,var3,var4,var5,var6;

    //Node 0 Entrance
    vector<float> coordi;
    coordi=nodos[4].getcoordinates();


    //connected node
    var7=1;
    //height
    uniform_real_distribution<double> dist11(MinHeight, MaxHeight);
    var3= dist11(mt);
    //width
    uniform_real_distribution<double> dist12(Minwidth, Maxwidth);
    var4= dist12(mt);
    //HorizontalOrientation
    uniform_real_distribution<double> dist13(MinHorizontalOrientation, MaxHorizontalOrientation);
    var5= dist13(mt);
    //VerticalOrientation
    uniform_real_distribution<double> dist14(MinVerticalOrientation, MaxVerticalOrientation);
    var6= dist14(mt);

    nodos[0].setexitprop(var7,var3,var4,var5,var6);
    nodos[0].setnumberofexits(1);
    nodos[1].setexitprop(0,var3,var4,var5,var6);
    nodos[1].setnumberofexits(1);



    int numberofexits;
    float tempor;
    int connectingnode,tempnumexits;
    uniform_real_distribution<double> dist(-5, 5);
    uniform_real_distribution<double> tunnn(MinNumberoftunnels, MaxNumberoftunnels);
    uniform_real_distribution<double> tunnseg(Mintunnelsegments, Maxtunnelsegments);

    uniform_real_distribution<double> dist20(Minsegmentlength, Maxsegmentlength);
    uniform_real_distribution<double> dist21(Minsegmentwidth, Maxsegmentwidth);
    uniform_real_distribution<double> dist22(Minsegmentheight, Maxsegmentheight);
    uniform_real_distribution<double> dist23(Minsegmentlope, Maxsegmentlope);


    vector<Enlace> enlaces;

    std::string tunnelname;
    int tunnelnumber=0, segmentnumber;
    int nuseg,segcounter=0;
    float longitud;
    int numberoftunnels=0;

    tempor = tunnseg(mt);
    nuseg=round(tempor);
    tunnelname=std::to_string(tunnelnumber);
    tuneles[numberoftunnels].setname(tunnelname);
    tuneles[numberoftunnels].setstartnode(0);
    tuneles[numberoftunnels].setfinalnode(1);
    tuneles[numberoftunnels].setnumberofsegments(nuseg);



    //creates as many segments as the tunnel has=
    for (int j=0;j<nuseg;j++)
    {

      segments[segcounter].setlength(dist20(mt));
      segments[segcounter].setwidth(dist21(mt));
      segments[segcounter].setheight(dist22(mt));
      segments[segcounter].setslope(dist23(mt));
      tuneles[numberoftunnels].addsegment(&segments[segcounter]);
      segcounter++;
    }

    longitud=tuneles[numberoftunnels].getlength();
    //tuneles[numberoftunnels].printtunnel();

    //creates links in the node adjacency list
    enlaces.push_back({0,1,longitud});

    numberoftunnels++;
    tunnelnumber++;
    segmentnumber++;




    for (int j=1;j<Numnodos;j++)
    {
      tempor = tunnn(mt);
      //numberofexits=round(tempor);
      numberofexits=3;
      segmentnumber=0;
      int repetido=0;

      if (nodos[j].gettype()=="Unknown")
      {
        numberofexits=1;
      }

      for (int i=nodos[j].getnumberofexits();i<numberofexits;i++)
      {

        repetido=0;
        tempor = dist(mt);
        connectingnode=round(tempor)+j;

        for (int k=0; k<enlaces.size();k++)
        {
          if (enlaces[k].nodofuente==connectingnode && enlaces[k].nododestino==j)
          {
            repetido=1;
          }
          if (enlaces[k].nododestino==connectingnode && enlaces[k].nodofuente==j)
          {
            repetido=1;
          }
        }

        while (nodos[connectingnode].getnumberofexits()>=MaxNumberoftunnels ||nodos[connectingnode].gettype()=="Unknown" || connectingnode==j || connectingnode<=0 || connectingnode>Numnodos-1 || repetido==1)
        {
          repetido=0;
          tempor = dist(mt);
          connectingnode=round(tempor)+j;

          for (int k=0; k<enlaces.size();k++)
          {
            if (enlaces[k].nodofuente==connectingnode && enlaces[k].nododestino==j)
            {
              repetido=1;
            }
            if (enlaces[k].nododestino==connectingnode && enlaces[k].nodofuente==j)
            {
              repetido=1;
            }
          }
        }
        //connected node
        var7 = connectingnode;
        //height
        var3 = dist11(mt);
        //width
        var4 = dist12(mt);
        //HorizontalOrientation
        var5 = dist13(mt);
        //VerticalOrientation
        var6 = dist14(mt);

        nodos[j].setexitprop(var7,var3,var4,var5,var6);
        tempnumexits=nodos[j].getnumberofexits();
        nodos[j].setnumberofexits(tempnumexits+1);

        nodos[connectingnode].setexitprop(j,var3,var4,var5,var6);
        tempnumexits=nodos[connectingnode].getnumberofexits();
        nodos[connectingnode].setnumberofexits(tempnumexits+1);

        tunnelname=std::to_string(tunnelnumber);
        tuneles[numberoftunnels].setname(tunnelname);
        tuneles[numberoftunnels].setstartnode(j);
        tuneles[numberoftunnels].setfinalnode(connectingnode);
        vector<float> coordenadas1, coordenadas2;
        coordenadas1=nodos[j].getcoordinates();
        coordenadas2=nodos[connectingnode].getcoordinates();
        tuneles[numberoftunnels].setlenght(sqrt(   pow((coordenadas1.at(0)-coordenadas2.at(0)),2)+pow((coordenadas1.at(1)-coordenadas2.at(1)),2)+ pow((coordenadas1.at(2)-coordenadas2.at(2)),2)       ));

        tempor = tunnseg(mt);
        nuseg=round(tempor);

        OOIratio= OOIgeneration(mt);
        if (OOIratio<OOIgenerationRatio) //If the random number is lower than OOIgenerationRatio, then a OOI is generated
        {
          //Create an OOI

          OOIs[OOI_ID].setID(OOI_ID+Numnodos*2);
          OOIlist.push_back(make_pair(OOI_ID+Numnodos*2,numberoftunnels));
          tuneles[numberoftunnels].addOOI(&OOIs[OOI_ID]);
          //OOIs[OOI_ID].
          OOI_ID++;
        }

        tuneles[numberoftunnels].setnumberofsegments(nuseg);


        //creates as many segments as the tunnel has
        for (int j=0;j<nuseg;j++)
        {

          segments[segcounter].setlength(dist20(mt));
          segments[segcounter].setwidth(dist21(mt));
          segments[segcounter].setheight(dist22(mt));
          segments[segcounter].setslope(dist23(mt));
          tuneles[numberoftunnels].addsegment(&segments[segcounter]);
          segcounter++;
        }


        longitud=tuneles[numberoftunnels].getlength();


        //creates links in the node adjacency list
        enlaces.push_back({j,connectingnode,longitud});

        numberoftunnels++;
        tunnelnumber++;
        segmentnumber++;
      }


    }
    std::cout  << std::endl;
    std::cout << "------Nodes input------" << std::endl;
    std::cout  << std::endl;
    for (int i=0; i<Numnodos;i++)
    {
      nodos[i].printnode();
    }

    std::cout  << std::endl;
    std::cout << "------Tunnels input------" << std::endl;
    std::cout  << std::endl;


    for (int i=0; i<numberoftunnels;i++)
    {
      tuneles[i].printtunnel();
    }

    std::cout << std::endl;
    std::cout << "------Node adjacency list------" << std::endl;
    std::cout << std::endl;
    std::cout << "Node --> (LinkedNode,Distance)" << std::endl;
    std::cout << std::endl;

    //Constructs the graph
    Grafo grafo(enlaces, Numnodos,nodos);

    //Print adjacency list representation of the graph
    grafo.printGraph(grafo, Numnodos);
    std::cout << std::endl;


    std::cout << "Do you want to perform a path search between two nodes? (Y/N)." << std::endl;
    char response;

    int search=2;
    int startnode = 0, goalnode = 0;
    do{
      std::cin>>response;
      switch(response)
      {
      case 'Y':
        search=1;

        break;
      case 'y':
        search=1;

        break;
      case 'N':
        search=0;
        goalnode=0;
        startnode=0;

        break;
      case 'n':   search=0;
        goalnode=0;
        startnode=0;


        break;
      default: std::cout<<"Invalid choice" << std::endl;
        break;
      }
    }while(search!=0 && search!=1);


    vector<int> solutionpath;
    if (search==1)
    {
      int searchmode = 0;
      std::cout << "Select start mode." << std::endl;
      std::cout << "1. Lost start mode" << std::endl;
      std::cout << "2. Known start node" << std::endl;
      cout << "--------------------" << std::endl;
      cout << "Mode:";

      int lostnode = 0;



      char answer;
      do{
        std::cin>>answer;
        switch(answer)
        {
        case '1':
          searchmode=1;
          std::cout << "Set start lost node:" << std::endl;
          std::cin >> lostnode;
          std::cout << "Set goal node:" << std::endl;
          std::cin >> goalnode;
          break;
        case '2':
          searchmode=2;
          std::cout << "Set start node:" << std::endl;
          std::cin >> startnode;
          std::cout << "Set goal node:" << std::endl;
          std::cin >> goalnode;

          break;
        default: std::cout<<"Invalid choice" << std::endl;
          break;
        }
      }while(answer!='1' && answer!='2');


      Exploration exploration1;

      if (searchmode==1)
      {
        startnode=exploration1.lost(nodos,Numnodos,lostnode);
      }



      //Performs the path search betweeen to given nodes (defined at the very first lines of the main().

      Dijkstra search;
      solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());
      int a,b;

      std::cout << std::endl;
      //std::cout << "Solution tunnel and segments sequence:" << std::endl;
      std::cout << std::endl;

      vector<Segment*> segmentpath,segmentemp;
      for(int i=0; i<solutionpath.size()-1;i++){
        a=solutionpath.at(i);
        b=solutionpath.at(i+1);

        //search tunnel between nodes
        vector<int> temp;

        for(int j=0;j<numberoftunnels;j++)
        {
          temp=tuneles[j].getendings();


          if(temp.at(0)==a && temp.at(1)==b)
          {
            segmentemp=tuneles[j].getsegments();
            //tuneles[j].printtunnel();
            for (int i=0; i<tuneles[j].getnumberofsegments(); i++)
            {
              segmentpath.push_back(segmentemp.at(i));
            }
          }


          if(temp.at(0)==b && temp.at(1)==a)
          {
            //tuneles[j].reverseprinttunnel();
            segmentemp=tuneles[j].getsegments();
            for (int i=tuneles[j].getnumberofsegments()-1; i>-1; i--)
            {
              segmentpath.push_back(segmentemp.at(i));
            }
          }

        }

      }


      std::cout << std::endl;


      explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numberoftunnels,OOIlist,Numnodos,enlaces);

      while (explorationactualnode!=solutionpath[solutionpath.size()-1])
      {
        solutionpath.clear();
        startnode=explorationactualnode;
        solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());


        explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numberoftunnels,OOIlist,Numnodos,enlaces);
      }




    }
    else if(search==0)
    {
      rviz_visual_tools::RvizVisualToolsDemo demo;
      demo.ploteo(Numnodos,nodos,enlaces,numberoftunnels,tuneles,startnode,goalnode);
    }


    ROS_INFO_STREAM("Shutting down.");






  }
  else if (inputmode=='1')
  {


    //----------------------------------------------------------------------------r------------------------------------------------------------------------------------------------------------











































    ifstream inputdata;
    srand(time(NULL));
    //definitions
    //int startnode, goalnode;
    inputdata.open("/home/adri/Datos/Git/TFM-Codigo/tfmROS/src/rviz_visual_tools-master/src/data.txt");
    int explorationactualnode;

    //Checks the openned file
    if (!inputdata)
    {
      cout << "Error: Can't open the file.\n";
      exit(1);
    }


    //Jumps header data
    string junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;

    string name;
    int var1,var2, var7;
    float var3, var5, var6, var4,x,y,z;

    std::cout << "------Nodes input------" << std::endl;
    std::cout << std::endl;


    Node nodos[100];
    int i=0, Numnodos; // N=Number of nodes in the graph

    while (inputdata >> name >> var1 >> var2 >> var3 >> var4 >> var5 >> x >> y >> z)
    {
      //Check for the end of node definition
      if (name=="NoMoreNodesFLAG")
      {
        break;
      };
      //std::cout << name << var1 << var2 << var3 << var4 << var5 << x << y << z << std::endl;
      //Configures the node
      nodos[i].settype(name);
      nodos[i].setnodenumber(var1);
      nodos[i].setnumberofexits(var2);
      nodos[i].setheight(var3);
      nodos[i].setwidth(var4);
      nodos[i].setdepth(var5);
      nodos[i].setcoordinates(x,y,z);
      std::cout << std::endl;

      for (int j=0;j<var2;j++)
      {
        inputdata >> var7 >> var3 >> var4 >> var5 >> var6;
        //std::cout << var7 << var3 << var4 << var5 << var6 << std::endl;

        nodos[i].setexitprop(var7,var3,var4,var5,var6);
      }
      std::cout << std::endl;
      nodos[i].printnode();

      i++;
    }


    //Jumps header data
    Numnodos=i;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;


    Tunnel tuneles[100];
    vector<Segment> segments(30);



    std::cout << std::endl;
    std::cout << "------Tunnels input------" << std::endl;
    std::cout << std::endl;



    vector<Enlace> enlaces;
    i=0;
    std::string tunnel;
    int start, final, nuseg,segcounter=0;


    float len, wid, hei, slo,longitud;
    while (inputdata >> tunnel >> start >> final >> nuseg)
    {
      if (tunnel=="NoMoreTunnelsFlag")
      {
        break;
      };
      //std::cout << tunnel << start << final << nuseg << std::endl;
      tuneles[i].setname(tunnel);
      tuneles[i].setstartnode(start);
      tuneles[i].setfinalnode(final);
      tuneles[i].setnumberofsegments(nuseg);

      //creates as many segments as the tunnel has
      for (int j=0;j<nuseg;j++)
      {
        inputdata>> len >> wid >> hei >> slo;
        segments[segcounter].setlength(len);
        segments[segcounter].setwidth(wid);
        segments[segcounter].setheight(hei);
        segments[segcounter].setslope(slo);
        tuneles[i].addsegment(&segments[segcounter]);
        segcounter++;
      }

      longitud=tuneles[i].getlength();
      tuneles[i].printtunnel();

      //creates links in the node adjacency list
      enlaces.push_back({start,final,longitud});
      i++;
    }

    int numtuneles=i;
    int contadorOOI=0;
    OOI OOIs[Numnodos*3];

    int ooiposition;
    int tunnelornode;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;

    while (inputdata >> OOI_ID >> ooiposition >> tunnelornode)
    {

      std::cout << OOI_ID << ooiposition << tunnelornode << std::endl;
      OOIs[contadorOOI].setID(OOI_ID);
      OOIlist.push_back(make_pair(OOI_ID,ooiposition));
      if (tunnelornode==0){
        nodos[ooiposition].addOOI(&OOIs[contadorOOI]);
      }
      else{
        tuneles[ooiposition].addOOI(&OOIs[contadorOOI]);
      }
      contadorOOI++;

    }






    std::cout << std::endl;
    std::cout << "------Node adjacency list------" << std::endl;
    std::cout << std::endl;
    std::cout << "Node --> (LinkedNode,Distance)" << std::endl;
    std::cout << std::endl;




    //Constructs the graph
    Grafo grafo(enlaces, Numnodos,nodos);

    //Print adjacency list representation of the graph
    grafo.printGraph(grafo, Numnodos);
    std::cout << std::endl;


    std::cout << "Do you want to perform a path search between two nodes? (Y/N)." << std::endl;
    char response;

    int search=2;
    int startnode = 0, goalnode = 0;
    do{
      std::cin>>response;
      switch(response)
      {
      case 'Y':
        search=1;

        break;
      case 'y':
        search=1;

        break;
      case 'N':
        search=0;
        goalnode=0;
        startnode=0;

        break;
      case 'n':   search=0;
        goalnode=0;
        startnode=0;


        break;
      default: std::cout<<"Invalid choice" << std::endl;
        break;
      }
    }while(search!=0 && search!=1);


    vector<int> solutionpath;
    if (search==1)
    {
      int searchmode = 0;
      std::cout << "Select start mode." << std::endl;
      std::cout << "1. Lost start mode" << std::endl;
      std::cout << "2. Known start node" << std::endl;
      cout << "--------------------" << std::endl;
      cout << "Mode:";

      int lostnode = 0;



      char answer;
      do{
        std::cin>>answer;
        switch(answer)
        {
        case '1':
          searchmode=1;
          std::cout << "Set start lost node:" << std::endl;
          std::cin >> lostnode;
          std::cout << "Set goal node:" << std::endl;
          std::cin >> goalnode;
          break;
        case '2':
          searchmode=2;
          std::cout << "Set start node:" << std::endl;
          std::cin >> startnode;
          std::cout << "Set goal node:" << std::endl;
          std::cin >> goalnode;

          break;
        default: std::cout<<"Invalid choice" << std::endl;
          break;
        }
      }while(answer!='1' && answer!='2');


      Exploration exploration1;

      if (searchmode==1)
      {
        startnode=exploration1.lost(nodos,Numnodos,lostnode);
      }



      //Performs the path search betweeen to given nodes (defined at the very first lines of the main().

      Dijkstra search;
      solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());
      int a,b;

      std::cout << std::endl;
      //std::cout << "Solution tunnel and segments sequence:" << std::endl;
      std::cout << std::endl;

      vector<Segment*> segmentpath,segmentemp;
      for(int i=0; i<solutionpath.size()-1;i++){
        a=solutionpath.at(i);
        b=solutionpath.at(i+1);

        //search tunnel between nodes
        vector<int> temp;

        for(int j=0;j<numtuneles;j++)
        {
          temp=tuneles[j].getendings();


          if(temp.at(0)==a && temp.at(1)==b)
          {
            segmentemp=tuneles[j].getsegments();
            //tuneles[j].printtunnel();
            for (int i=0; i<tuneles[j].getnumberofsegments(); i++)
            {
              segmentpath.push_back(segmentemp.at(i));
            }
          }


          if(temp.at(0)==b && temp.at(1)==a)
          {
            //tuneles[j].reverseprinttunnel();
            segmentemp=tuneles[j].getsegments();
            for (int i=tuneles[j].getnumberofsegments()-1; i>-1; i--)
            {
              segmentpath.push_back(segmentemp.at(i));
            }
          }

        }

      }


      std::cout << std::endl;


      explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numtuneles,OOIlist,Numnodos,enlaces);

      while (explorationactualnode!=solutionpath[solutionpath.size()-1])
      {
        solutionpath.clear();
        startnode=explorationactualnode;
        solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());


        explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numtuneles,OOIlist,Numnodos,enlaces);
      }




    }
    else if(search==0)
    {
      rviz_visual_tools::RvizVisualToolsDemo demo;
      demo.ploteo(Numnodos,nodos,enlaces,numtuneles,tuneles,startnode,goalnode);
    }


    ROS_INFO_STREAM("Shutting down.");























//    //Constructs the graph
//    Grafo grafo(enlaces, Numnodos,nodos);

//    //Print adjacency list representation of the graph
//    grafo.printGraph(grafo, Numnodos);
//    std::cout << std::endl;

//    std::cout << "Do you want to perform a path search between two nodes? (Y/N)." << std::endl;
//    char response;

//    int search=2;

//    do{
//      std::cin>>response;
//      switch(response)
//      {
//      case 'Y':
//        search=1;
//        std::cout << "Set start node:" << std::endl;
//        std::cin >> startnode;
//        std::cout << "Set goal node:" << std::endl;
//        std::cin >> goalnode;
//        break;
//      case 'y':
//        search=1;
//        std::cout << "Set start node:" << std::endl;
//        std::cin >> startnode;
//        std::cout << "Set goal node:" << std::endl;
//        std::cin >> goalnode;
//        break;
//      case 'N':   search=0;
//        goalnode=0;
//        startnode=0;
//        break;
//      case 'n':   search=0;
//        goalnode=0;
//        startnode=0;
//        break;
//      default: std::cout<<"Invalid choice" << std::endl;
//        break;
//      }
//    }while(search!=0 && search!=1);


//    vector<int> solutionpath;
//    if (search==1)
//    {
//      //Performs the path search betweeen to given nodes (defined at the very first lines of the main().

//      Dijkstra search;
//      solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());
//      int a,b;

//      std::cout << std::endl;
//      //std::cout << "Solution tunnel and segments sequence:" << std::endl;
//      std::cout << std::endl;

//      vector<Segment*> segmentpath,segmentemp;
//      for(int i=0; i<solutionpath.size()-1;i++){
//        a=solutionpath.at(i);
//        b=solutionpath.at(i+1);

//        //search tunnel between nodes
//        vector<int> temp;

//        for(int j=0;j<numtuneles;j++)
//        {
//          temp=tuneles[j].getendings();


//          if(temp.at(0)==a && temp.at(1)==b)
//          {
//            segmentemp=tuneles[j].getsegments();
//            //tuneles[j].printtunnel();
//            for (int i=0; i<tuneles[j].getnumberofsegments(); i++)
//            {
//              segmentpath.push_back(segmentemp.at(i));
//            }
//          }


//          if(temp.at(0)==b && temp.at(1)==a)
//          {
//            //tuneles[j].reverseprinttunnel();
//            segmentemp=tuneles[j].getsegments();
//            for (int i=tuneles[j].getnumberofsegments()-1; i>-1; i--)
//            {
//              segmentpath.push_back(segmentemp.at(i));
//            }
//          }

//        }

//      }

//      //ADD REVERSE PRINT TUNNEL SECTION

//    }


//    std::cout << std::endl;\
//    Exploration exploration1;

//    exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numtuneles,OOIlist,Numnodos,enlaces);


//    int asd=exploration1.lost(nodos,Numnodos,5);
  }




  return 0;
}
