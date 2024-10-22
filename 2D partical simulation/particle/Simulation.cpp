//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#include "Simulation.hpp"
#include "ControlPanel.hpp"
#include "MainWindow.hpp"
#include "App.hpp"
#include "Vector2d.hpp"
//#include <math.h>

#include <cmath>
#include <cstdio>
#include <cassert>

namespace
{
  constexpr double kEpsilon{ 1e-12 };
}

namespace course
{
  Simulation::Simulation()
  {
      reset();
  }

  void Simulation::reset(
    double radius, double collision, const Vector2d& velocity)
  {
      radius_ = radius;
      collision_ = collision;
      Velocity_=velocity;
      Position_={0,0};
      time_ = 0;
      energy_ = energy();
  }

  void Simulation::oneStep()
  {

   // time_ += timeStep_;
      double t = 0, tc=0; // t represent accmulated time, tc represent collision time
      double t_left = 0, t_right = 0, t_bottom = 0;// Represent the time hit the left. right, buttom respectively
      //double t_temp = 0;
      while (t<TimeStep_)
      {
          double x_incre = GetIncreX(TimeStep_-t);
          double y_incre = GetIncreY(TimeStep_-t);
          //v*t+1/2*a*t^2
          if (Position_.x()+x_incre<=-1+radius_|| 
              Position_.x() + x_incre >=1- radius_||
              Position_.y()+y_incre<=-1+ radius_) // Check whether the ball will hit the wall
          {
              if (Velocity_.x() < 0)//It may hit the left and buttom
              {
                  t_left = (-position().x()+ radius()-1)/velocity().x(); //Calculate the time hit the left side, which is distance/v
                  double a1 = (Accele_.y())/2; //Calculate a,b and c for the buttom, 1/2*Ay
                  double b1 = velocity().y(); //Vy
                  double c1 = position().y()+1-radius();//Py+1-r
                  t_bottom = GetTime(a1,b1,c1);  //Get the collision time
                  if (t_left < t_bottom) //Choose the smallest time
                  {
                      tc = t_left;
                      Position_.x()+=GetIncreX(tc); //Update position firstly
                      Position_.y()+=GetIncreY(tc);
                      Velocity_.y()+= Accele_.y() * tc;
                      Velocity_ = (left_zone.reflect(velocity())) * collision(); //Update velocity
                  }
                  else
                  {
                      tc = t_bottom;
                      Position_.x()+=GetIncreX(tc); //Update position firstly
                      Position_.y()+=GetIncreY(tc);
                      Velocity_.y()+= Accele_.y() * tc;
                      Velocity_ = (bottom_zone.reflect(velocity())) * collision() ; //Update velocity
                  }                  
                  energy_ = energy() * collision(); //Updare energy
                  t += tc;
              }
              else if (Velocity_.x()>0) //It may hit the right and the buttom
              {
                  t_right = (1-radius_- Position_.x())/Velocity_.x(); //Get the time to hit the right wall
                  double a2 = (Accele_.y()) / 2; //Calculate a,b and c for the buttom, 1/2*Ay
                  double b2 = velocity().y(); //Vy
                  double c2 = position().y() + 1 - radius();//Py+1-r
                  t_bottom = GetTime(a2, b2, c2);  //Get the collision time
                  if (t_right<t_bottom) //Get the smaller time
                  {
                      tc = t_right;
                      Position_.x()+=GetIncreX(tc); //Update position firstly
                      Position_.y()+=GetIncreY(tc);
                      Velocity_.y()+= Accele_.y() * tc;
                      Velocity_ = (right_zone.reflect(velocity())) * collision() ; //Update velocity after collision
                  }
                  else
                  {
                      tc = t_bottom;
                      Position_.x()+=GetIncreX(tc); //Update position firstly
                      Position_.y()+=GetIncreY(tc);
                      Velocity_.y()+=Accele_.y() * tc;
                      Velocity_ = (bottom_zone.reflect(velocity())) * collision() ; //Update velocity after collision
                  }               
                  energy_ = energy() * collision(); //Updare energy
                  t += tc;
              }
              else //If it hit the buttom, which is velocity.x()==0
              {
                  double a3 = (Accele_.y()) / 2; //Calculate a,b and c for the buttom, 1/2*Ay
                  double b3 = velocity().y(); //Vy
                  double c3 = position().y() + 1 - radius();//Py+1-r
                  t_bottom= GetTime(a3, b3, c3);  //Get the collision time
                  Position_.x()+=GetIncreX(t_bottom); //Update position firtly
                  Position_.y()+=GetIncreY(t_bottom);
                  Velocity_.y() = velocity().y() + Accele_.y() * t_bottom;
                  Velocity_ = (bottom_zone.reflect(velocity())) * collision(); //Update velocity
                  energy_ = energy() * collision(); //Updare energy
                  t += tc;
              }
          }
          else
          {
              Position_.x()+=GetIncreX(TimeStep_ - t); //Change the position during this period, which
              Position_.y()+=GetIncreY(TimeStep_ - t); //is TimeStep_-t
              //v=v*t+a+t
              Velocity_.x() = velocity().x() ;  //Change the velocity during this period
              Velocity_.y() = velocity().y() + Accele_.y() * (TimeStep_ - t);
              //update t         
              t = TimeStep_;
              //The energy remain unchanged in this situation
              
          }
          if (energy_<0.001)
          {
              wxGetApp().mainWindow().simulationStop();
          }
      }
      time_ += TimeStep_;
  }

  double Simulation::GetIncreX(double time)
  { //Get the increment in X-axis, based on v*t+1/2*a*t^2
      double IncreX=Velocity_.x()* time ; 
      return IncreX;
  }

  double Simulation::GetIncreY(double time)
  { //Get the increment in Y-axis
      double IncreY=Velocity_.y()* time + ((Accele_.y() * std::pow(time, 2)) / 2);
      return IncreY;
  }

  double Simulation::GetTime(double a,double b,double c)
  {
      double t1 = (-b + std::sqrt(std::pow(b, 2) - 4 * a * c)) / 2 * a;
      //std::cout << t1<<"\n"; //Ues it to test
      double t2 = (-b - std::sqrt(std::pow(b, 2) - 4 * a * c)) / 2 * a;
      //std::cout << t2 << "\n"; //Ues it to test
      if (t1 > 0 && t2 > 0) //If both t1 and t2 is larger than 0
      {
          if (t1 > t2)  //Choose the small number to return
          {
              return t2;
          }
          else
          {
              return t1;
          }
      }
      else if (t1 > 0 && t2 < 0) //Return the positive t1
      {
          return t1;
      }
      else if (t1 < 0 && t2>0) //Return the positive t2
      {
          return t2;
      }
      else //If the result is invalid
      {
          return -1;
      }
  }

  double Simulation::radius() const
  {
      return radius_;
  }

  double Simulation::collision() const
  {
    return collision_;
  }

  const Vector2d& Simulation::position() const
  {
   
    return Position_;
  }

  const Vector2d& Simulation::velocity() const
  {
    return Velocity_;
  }

  bool Simulation::running() const
  {
     //MainWindow& mainWindow{ wxGetApp().mainWindow() };
    return wxGetApp().mainWindow().isSimulationRunning();
  }

  double Simulation::time() const
  {
    return time_;
  }

  double Simulation::energy() const
  {
    //We need to calculate Ep and Ek
    double Ep = position().y() - radius() + 1;
    double Ek = (std::pow(velocity().x(), 2) + std::pow(velocity().y(), 2))/2;
    double energy__ = Ep + Ek;
    return energy__;
  }
}