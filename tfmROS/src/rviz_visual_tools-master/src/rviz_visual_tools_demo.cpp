/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2017, PickNik Consulting
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Univ of CO, Boulder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Dave Coleman
   Desc:   Demo implementation of rviz_visual_tools
           To use, add a Rviz Marker Display subscribed to topic /rviz_visual_tools
*/

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

  void publishLabelHelper(const Eigen::Isometry3d& pose, const std::string& label)
  {
    Eigen::Isometry3d pose_copy = pose;
    pose_copy.translation().x() -= 0.2;
    visual_tools_->publishText(pose_copy, label, rvt::WHITE, rvt::XXLARGE, false);
  }

  void testRows(double& x_location)
  {
    // Create pose
    Eigen::Isometry3d pose1 = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d pose2 = Eigen::Isometry3d::Identity();

    pose1.translation().x() = x_location;

    double space_between_rows = 0.2;
    double y = 0;
    double step;

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying range of colors red->green");
//    step = 0.02;
//    for (double i = 0; i <= 1.0; i += 0.02)
//    {
//      geometry_msgs::Vector3 scale = visual_tools_->getScale(MEDIUM);
//      std_msgs::ColorRGBA color = visual_tools_->getColorScale(i);
//      visual_tools_->publishSphere(visual_tools_->convertPose(pose1), color, scale, "Sphere");
//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Sphere Color Range");
//      }
//      pose1.translation().x() += step;
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Coordinate Axis");
//    pose1.translation().x() = 0;
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    step = 0.025;
//    for (double i = 0; i <= 1.0; i += step)
//    {
//      visual_tools_->publishAxis(pose1);
//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Coordinate Axis");
//      }

//      pose1.translation().x() += step;
//      pose1 = pose1 * Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitX()) *
//              Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitY()) *
//              Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitZ());
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
    //    ROS_INFO_STREAM_NAMED(name_, "Displaying Arrows");
    //    pose1 = Eigen::Isometry3d::Identity();
    //    y += space_between_rows;
    //    pose1.translation().y() = y;
    //    step = 0.025;
    //    for (double i = 0; i <= 1.0; i += step)
    //    {
    //      visual_tools_->publishArrow(pose1, rvt::RAND);
    //      if (i == 0.0)
    //      {
    //        publishLabelHelper(pose1, "Arrows");
    //      }

    //      pose1.translation().x() += step;
    //      pose1 = pose1 * Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitZ());
    //    }
    //    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Rectangular Cuboid");
//    double cuboid_max_size = 0.075;
//    double cuboid_min_size = 0.01;
//    pose1 = Eigen::Isometry3d::Identity();
//    pose2 = Eigen::Isometry3d::Identity();
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    pose2.translation().y() = y;
//    step = 0.1;
//    for (double i = 0; i <= 1.0; i += step)
//    {
//      pose2 = pose1;
//      pose2.translation().x() += i * cuboid_max_size + cuboid_min_size;
//      pose2.translation().y() += i * cuboid_max_size + cuboid_min_size;
//      pose2.translation().z() += i * cuboid_max_size + cuboid_min_size;
//      visual_tools_->publishCuboid(pose1.translation(), pose2.translation(), rvt::RAND);

//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Cuboid");
//      }

//      pose1.translation().x() += step;
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Lines");
//    double line_max_size = 0.075;
//    double line_min_size = 0.01;
//    pose1 = Eigen::Isometry3d::Identity();
//    pose2 = Eigen::Isometry3d::Identity();
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    pose2.translation().y() = y;
//    step = 0.1;
//    for (double i = 0; i <= 1.0; i += step)
//    {
//      pose2 = pose1;
//      pose2.translation().x() += i * line_max_size + line_min_size;
//      pose2.translation().y() += i * line_max_size + line_min_size;
//      pose2.translation().z() += i * line_max_size + line_min_size;
//      visual_tools_->publishLine(pose1.translation(), pose2.translation(), rvt::RAND);

//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Line");
//      }

//      pose1.translation().x() += step;
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
    ROS_INFO_STREAM_NAMED(name_, "Displaying Cylinder");
    pose1 = Eigen::Isometry3d::Identity();
    y += space_between_rows;
    pose1.translation().y() = y;
    step = 0.025;
    for (double i = 0; i <= 1.0; i += step)
    {
      visual_tools_->publishCylinder(pose1, rvt::RAND);
      if (i == 0.0)
      {
        publishLabelHelper(pose1, "Cylinder");
      }

      pose1.translation().x() += step;
      pose1 = pose1 * Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitZ());
    }
    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Axis Cone");
//    pose1 = Eigen::Isometry3d::Identity();
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    step = 0.025;
//    double angle_step = 0.1;
//    double angle = 1;

//    for (double i = 0; i <= 1.0; i += step)
//    {
//      visual_tools_->publishCone(pose1, M_PI / angle, rvt::RAND, 0.05);
//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Cone");
//      }

//      pose1.translation().x() += step;
//      pose1 = pose1 * Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitZ());
//      angle += angle_step;
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Wireframe Cuboid");
//    pose1 = Eigen::Isometry3d::Identity();
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    step = 0.1;
//    // TODO(davetcoleman): use generateRandomCuboid()
//    Eigen::Vector3d min_point, max_point;
//    min_point << -0.05, -0.05, -0.05;
//    max_point << 0.05, 0.05, 0.05;
//    for (double i = 0; i <= 1.0; i += step)
//    {
//      visual_tools_->publishWireframeCuboid(pose1, min_point, max_point, rvt::RAND);
//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Wireframe Cuboid");
//      }

//      pose1.translation().x() += step;
//      pose1 = pose1 * Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitZ());
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Sized Wireframe Cuboid");
//    pose1 = Eigen::Isometry3d::Identity();
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    step = 0.1;
//    double depth = 0.05, width = 0.05, height = 0.05;
//    for (double i = 0; i <= 1.0; i += step)
//    {
//      visual_tools_->publishWireframeCuboid(pose1, depth, width, height, rvt::RAND);
//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Wireframe Cuboid");
//      }

//      pose1.translation().x() += step;
//      pose1 = pose1 * Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitZ());
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Planes");
//    pose1 = Eigen::Isometry3d::Identity();
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    step = 0.2;
//    double max_plane_size = 0.075;
//    double min_plane_size = 0.01;
//    for (double i = 0; i <= 1.0; i += step)
//    {
//      visual_tools_->publishXYPlane(pose1, rvt::RED, i * max_plane_size + min_plane_size);
//      visual_tools_->publishXZPlane(pose1, rvt::GREEN, i * max_plane_size + min_plane_size);
//      visual_tools_->publishYZPlane(pose1, rvt::BLUE, i * max_plane_size + min_plane_size);
//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Planes");
//      }

//      pose1.translation().x() += step;
//    }
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
    ROS_INFO_STREAM_NAMED(name_, "Displaying Graph");
    pose1 = Eigen::Isometry3d::Identity();
    y += space_between_rows;
    pose1.translation().y() = y;
    step = 0.1;
    graph_msgs::GeometryGraph graph;
    for (double i = 0; i <= 1.0; i += step)
    {
      graph.nodes.push_back(visual_tools_->convertPose(pose1).position);
      graph_msgs::Edges edges;
      if (i > 0)
      {
        edges.node_ids.push_back(0);
      }
      graph.edges.push_back(edges);

      if (i == 0.0)
      {
        publishLabelHelper(pose1, "Graph");
      }

      pose1.translation().x() += step;
      pose1.translation().z() += visual_tools_->dRand(-0.1, 0.1);
    }
    visual_tools_->publishGraph(graph, rvt::ORANGE, 0.005);
    visual_tools_->trigger();

    // --------------------------------------------------------------------
    // TODO(davetcoleman): publishMesh

    // --------------------------------------------------------------------
    // TODO(davetcoleman): publishPolygon

    // --------------------------------------------------------------------
    ROS_INFO_STREAM_NAMED(name_, "Displaying Labeled Coordinate Axis");
    pose1.translation().x() = 0;
    y += space_between_rows;
    pose1.translation().y() = y;
    pose1.translation().z() = 0;
    step = 0.2;
    for (double i = 0; i <= 1.0; i += step)
    {
      visual_tools_->publishAxisLabeled(pose1, "label of axis");
      if (i == 0.0)
      {
        publishLabelHelper(pose1, "Labeled Axis");
      }

      pose1.translation().x() += step;
      pose1 = pose1 * Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitX()) *
              Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitY()) *
              Eigen::AngleAxisd(step * 2 * M_PI, Eigen::Vector3d::UnitZ());
    }
    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying Multi-Color Path");
//    pose1 = Eigen::Isometry3d::Identity();
//    pose2 = Eigen::Isometry3d::Identity();
//    y += space_between_rows;
//    pose1.translation().y() = y;
//    step = 0.1;

//    EigenSTL::vector_Vector3d path;
//    std::vector<rviz_visual_tools::colors> colors;
//    unsigned index(0);
//    for (double i = 0; i < 1.0; i += step)
//    {
//      pose1.translation().y() = y;
//      if (++index % 2 == 0)
//      {
//        pose1.translation().y() += step / 2.0;
//        colors.push_back(rviz_visual_tools::WHITE);
//      }
//      else
//      {
//        pose1.translation().y() -= step / 2.0;
//        colors.push_back(rviz_visual_tools::BLUE);
//      }
//      path.emplace_back(pose1.translation());
//      pose1.translation().x() += step;

//      if (i == 0.0)
//      {
//        publishLabelHelper(pose1, "Path");
//      }
//    }
//    visual_tools_->publishPath(path, colors);
//    visual_tools_->trigger();

    // --------------------------------------------------------------------
//    ROS_INFO_STREAM_NAMED(name_, "Displaying ABCD Plane");
//    double x_width = 0.15;
//    double y_width = 0.05;

//    Eigen::Vector3d n;
//    double a, b, c = 0, d;
//    y += space_between_rows;
//    double x_plane = 0, y_plane = y;

//    pose1 = Eigen::Isometry3d::Identity();
//    pose1.translation().x() = x_plane;
//    pose1.translation().y() = y_plane;
//    publishLabelHelper(pose1, "ABCD Plane");

//    for (std::size_t i = 0; i < 10; ++i)
//    {
//      x_plane = i * step;
//      a = x_plane;
//      b = y_plane;
//      // D takes this value to satisfy Ax+By+D=0
//      d = -(x_plane * x_plane + y_plane * y_plane);
//      visual_tools_->publishABCDPlane(a, b, c, d, rvt::MAGENTA, x_width, y_width);
//      x_location += step;
//    }

//    // Set x location for next visualization function
//    x_location += 1.25;

//    visual_tools_->trigger();
  }

  /** \brief Compare sizes of markers using all MEDIUM-scale markers */
  void testSize(double& x_location, scales scale)
  {
    // Create pose
    Eigen::Isometry3d pose1 = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d pose2 = Eigen::Isometry3d::Identity();

    // Reusable vector of 2 colors
    std::vector<colors> colors;
    colors.push_back(RED);
    colors.push_back(GREEN);

    // Reusable points vector
    EigenSTL::vector_Vector3d points1;
    EigenSTL::vector_Vector3d points2;

    double step = 0.25;  // space between each row

    // Show test label
    pose1.translation().x() = x_location - 0.1;
    visual_tools_->publishText(pose1, "Testing consistency of " + visual_tools_->scaleToString(scale) + " marker scale",
                               WHITE, XLARGE, false);

    pose1.translation().x() = x_location;

    // TODO(dave): publishCone() - no scale version available
    // TODO(dave): publishXYPlane() - no scale version available
    // TODO(dave): publishXZPlane() - no scale version available
    // TODO(dave): publishYZPlane() - no scale version available

    // Sphere
    visual_tools_->publishSphere(pose1, BLUE, scale);
    pose1.translation().y() += step;

    // Spheres
    points1.clear();
    points1.emplace_back(pose1.translation());
    pose1.translation().x() += step;
    points1.emplace_back(pose1.translation());
    visual_tools_->publishSpheres(points1, BLUE, scale);
    pose1.translation().x() = x_location;  // reset
    pose1.translation().y() += step;

    // Spheres with colors
    points1.clear();
    points1.emplace_back(pose1.translation());
    pose1.translation().x() += step;
    points1.emplace_back(pose1.translation());
    visual_tools_->publishSpheres(points1, colors, scale);
    pose1.translation().x() = x_location;  // reset
    pose1.translation().y() += step;

//    // YArrow
//    visual_tools_->publishYArrow(pose1, BLUE, scale);
//    pose1.translation().y() += step;

//    // ZArrow
//    visual_tools_->publishZArrow(pose1, GREEN, scale);
//    pose1.translation().y() += step;

//    // XArrow
//    visual_tools_->publishXArrow(pose1, RED, scale);
//    pose1.translation().y() += step;

    // Arrow (x arrow)
    visual_tools_->publishArrow(pose1, RED, scale);
    pose1.translation().y() += step;

    // Line
    pose2 = pose1;
    pose2.translation().x() += step / 2.0;
    visual_tools_->publishLine(pose1, pose2, PURPLE, scale);
    pose1.translation().y() += step;

    // Lines
    points1.clear();
    points2.clear();
    pose2 = pose1;
    pose2.translation().x() += step / 2.0;
    points1.emplace_back(pose1.translation());
    points2.emplace_back(pose2.translation());
    pose1.translation().x() += step / 2.0;

    pose2 = pose1;
    pose2.translation().x() += step / 2.0;
    // points1.push_back(pose1.translation());
    // points2.push_back(pose2.translation());
    colors.clear();  // temp
    colors.push_back(ORANGE);
    visual_tools_->publishLines(points1, points2, colors, scale);
    pose1.translation().x() = x_location;  // reset
    pose1.translation().y() += step;

    // TODO(dave): publishPath
    // TODO(dave): publishPolygon
    // TODO(dave): publishWireframeCuboid
    // TODO(dave): publishWireframeRectangle

    // Axis Labeled
    visual_tools_->publishAxisLabeled(pose1, "Axis", scale);
    pose1.translation().y() += step;

    // Axis
    visual_tools_->publishAxis(pose1, scale);
    pose1.translation().y() += step;

    // TODO(dave): publishAxis

    // Cylinder
    pose2 = pose1;
    pose2.translation().x() += step / 2.0;
    visual_tools_->publishCylinder(pose1.translation(), pose2.translation(), BLUE, scale);
    pose1.translation().y() += step;

    // TODO(dave): publishMesh

    // TODO(dave): publishGraph

    // Text
    visual_tools_->publishText(pose1, "NODOOOOOOOOOOOOOOOOOOOOO", WHITE, scale, false);
    pose1.translation().y() += step;

    // Display test
    visual_tools_->trigger();

    // Set x location for next visualization function
    x_location += 0.5;
  }

  /** \brief Compare every size range */
  void ploteo(int numnodes,Node *nodos,vector<Enlace> const& enlaces,int numberoftunnels,Tunnel *tuneles)
  {
    ROS_INFO_STREAM_NAMED(name_, "Testing sizes of marker scale");

//    // Create pose
//    Eigen::Isometry3d pose1 = Eigen::Isometry3d::Identity();
//    Eigen::Isometry3d pose2 = Eigen::Isometry3d::Identity();

//    // Show test label
//    pose1.translation().x() = x_location - 0.1;
//    visual_tools_->publishText(pose1, "Testing sizes of marker scale", WHITE, XLARGE, false);

//    pose1.translation().x() = x_location;
//    pose2.translation().x() = x_location;

    // Sphere
//    for (scales scale = XXXLARGE; scale <= XXXXLARGE; /*inline*/)
//    {
//      if (scale == MEDIUM)
//      {
//        visual_tools_->publishSphere(pose1, GREEN, scale);
//      }
//      else
//      {
//        visual_tools_->publishSphere(pose1, GREY, scale);
//      }
//      visual_tools_->publishText(pose2, "Nodo " + visual_tools_->scaleToString(scale), WHITE, scale, false);

//      scale = static_cast<scales>(static_cast<int>(scale) + 1);
//      pose1.translation().y() += visual_tools_->getScale(scale).x + 0.1;

//      // Text location
//      pose2.translation().y() = pose1.translation().y();
//      pose2.translation().x() = x_location + visual_tools_->getScale(scale).x * 1.3;
//    }

    // Display test
    //visual_tools_->trigger();

    // Set x location for next visualization function
    //x_location += 0.5;


//    // Create pose

//    Eigen::Isometry3d pose = Eigen::Isometry3d::Identity();
//    //pose = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
//    pose.translation() = Eigen::Vector3d( 1, 1, 1 ); // translate x,y,z

//    // Publish arrow vector of pose
//    ROS_INFO_STREAM_NAMED("test","Publishing Arrow");
//    visual_tools_->publishSphere(pose, rviz_visual_tools::RED, rviz_visual_tools::XXXXLARGE);
//    visual_tools_->publishText(pose, "Nodo 1", WHITE, XLARGE, false);

//    // Don't forget to trigger the publisher!



//    pose = Eigen::Isometry3d::Identity();
//    //pose = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitY()); // rotate along X axis by 45 degrees
//    pose.translation() = Eigen::Vector3d( 2, 2, 2 ); // translate x,y,z
//    visual_tools_->publishText(pose, "Nodo 2", WHITE, XLARGE, false);
//    visual_tools_->publishSphere(pose, rviz_visual_tools::RED, rviz_visual_tools::XXXXLARGE);
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
          ROS_INFO_STREAM_NAMED("test","Publishing Arrow");
          visual_tools_->publishSphere(pose, rviz_visual_tools::RED, rviz_visual_tools::XXXXLARGE);
          posename.translation() = Eigen::Vector3d(coordenadas.at(0), coordenadas.at(1), coordenadas.at(2)+0.5);
          visual_tools_->publishText(posename, "Nodo " + std::to_string(nodos[i].getnodenumber()), WHITE, rviz_visual_tools::XXXXLARGE, false);


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
      visual_tools_->publishCylinder(pose.translation(), poseto.translation(), BLUE, rviz_visual_tools::XXXLARGE);
    }
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

  rviz_visual_tools::RvizVisualToolsDemo demo;

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

          if (unknownodeR<=unknownodeRatio)
          {
              //Create unknown node
              nodos[i].settype(result);
              nodos[i].setnodenumber(9999);

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
      int start, final, nuseg,segcounter=0;
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

          if (nodos[j].getnodenumber()==9999)
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

              while (nodos[connectingnode].getnumberofexits()>=MaxNumberoftunnels ||nodos[connectingnode].getnodenumber()==9999 || connectingnode==j || connectingnode<=0 || connectingnode>Numnodos-1 || repetido==1)
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
      int startnode, goalnode;
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
          case 'N':   search=0;
              break;
          case 'n':   search=0;
              break;
          default: std::cout<<"Invalid choice" << std::endl;
              break;
          }
      }while(search!=0 && search!=1);


      vector<int> solutionpath;
      if (search==1)
      {
          int searchmode;
          std::cout << "Select start mode." << std::endl;
          std::cout << "1. Lost start mode" << std::endl;
          std::cout << "2. Known start node" << std::endl;
          cout << "--------------------" << std::endl;
          cout << "Mode:";

          int lostnode;



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


          std::cout << std::endl;\


          explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numberoftunnels,OOIlist);

          while (explorationactualnode!=solutionpath[solutionpath.size()-1])
          {
              solutionpath.clear();
              startnode=explorationactualnode;
              solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());


              explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numberoftunnels,OOIlist);
          }




      }
      demo.ploteo(Numnodos,nodos,enlaces,numberoftunnels,tuneles);

      ROS_INFO_STREAM("Shutting down.");






  }
  else if (inputmode=='1')
  {


      //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------








      ifstream inputdata;
      srand(time(NULL));
      //definitions
      int startnode, goalnode;
      inputdata.open("/home/adri/Git/TFM-Codigo/data.txt");


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

          //Configures the node
          nodos[i].settype(name);
          nodos[i].setnodenumber(var1);
          nodos[i].setnumberofexits(var2);
          nodos[i].setheight(var3);
          nodos[i].setwidth(var4);
          nodos[i].setdepth(var5);
          nodos[i].setcoordinates(x,y,z);


          for (int j=0;j<var2;j++)
          {
              inputdata >> var7 >> var3 >> var4 >> var5 >> var6;

              nodos[i].setexitprop(var7,var3,var4,var5,var6);
          }

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

      do{
          std::cin>>response;
          switch(response)
          {
          case 'Y':
              search=1;
              std::cout << "Set start node:" << std::endl;
              std::cin >> startnode;
              std::cout << "Set goal node:" << std::endl;
              std::cin >> goalnode;
              break;
          case 'y':
              search=1;
              std::cout << "Set start node:" << std::endl;
              std::cin >> startnode;
              std::cout << "Set goal node:" << std::endl;
              std::cin >> goalnode;
              break;
          case 'N':   search=0;
              break;
          case 'n':   search=0;
              break;
          default: std::cout<<"Invalid choice" << std::endl;
              break;
          }
      }while(search!=0 && search!=1);


      vector<int> solutionpath;
      if (search==1)
      {
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

              //ADD REVERSE PRINT TUNNEL SECTION

      }


      std::cout << std::endl;\
      Exploration exploration1;

      exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numtuneles,OOIlist);


      int asd=exploration1.lost(nodos,Numnodos,5);
  }




  return 0;
}
