#include <core/ArgParser.hpp>
#include <physics/PhysicsWorld.hpp>
#include <iostream>
#include <core/Vector3.hpp>
#include <physics/RigidBody.hpp>
#include <core/Real.hpp>
#include <physics/colliders/SphereCollider.hpp>

using lambda::physics::RigidBody;
using lambda::core::Real;
using lambda::physics::colliders::SphereCollider;

int main(int argc, char* argv[]) {
    lambda::core::ArgParser args(argc, argv);

    bool debug = args.Has("debug");
    bool ascii = args.Has("ascii");
    double dt = args.GetDouble("dt", 1.0 / 60.0);
    int steps = std::stoi(args.Get("steps", "600"));


    // init physics world
    lambda::physics::PhysicsWorld world;
    
    // create bodies
    RigidBody ball;
    ball.SetMass(Real(1.0));
    ball.SetPosition({Real(-2.0), Real(0.0), Real(0.0)});
    ball.SetVelocity({Real(3.0), Real(0.0), Real(0.0)});

}

