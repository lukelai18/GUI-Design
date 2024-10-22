//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include "Vector2d.hpp"

namespace course
{
  class Simulation
  {
  public:
    Simulation();

    double radius_;
    double collision_;
    double time_=0;
    double energy_=0;
    Vector2d Position_ {0,0}; //Represent the position
    Vector2d Velocity_{0,0}; //Represent velocity
    Vector2d Accele_ {0,-1}; //Represent acceleration
    Vector2d left_zone{1,0};
    Vector2d right_zone{-1,0};
    Vector2d bottom_zone{0,1};
    double TimeStep_=0.05;

    void reset(
      double radius = 0.1,
      double collision = 0.9,
      const Vector2d& velocity = { 0,0 }
    );

    void oneStep();

    double radius() const;

    double collision() const;

    const Vector2d& position() const;
    const Vector2d& velocity() const;

    bool running() const;

    double time() const;

    double energy() const;

    double GetTime(double a,double b,double c);
    double GetIncreX(double time);
    double GetIncreY(double time);
  };
}