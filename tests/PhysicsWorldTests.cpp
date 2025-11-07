#include <gtest/gtest.h>

#include <core/Constants.hpp>
#include <lambda/physics/PhysicsWorld.hpp>
#include <lambda/physics/RigidBody.hpp>

#include <array>
#include <cmath>
#include <memory>

namespace {

using lambda::core::Constants::G;
using lambda::core::Real;
using lambda::physics::PhysicsWorld;
using lambda::physics::RigidBody;
using lambda::physics::RigidBodyStatus;

std::array<Real, 9> IdentityTensor() {
    return {
        Real{1.0}, Real{0.0}, Real{0.0},
        Real{0.0}, Real{1.0}, Real{0.0},
        Real{0.0}, Real{0.0}, Real{1.0}
    };
}

bool ConfigureDynamicBody(RigidBody& body, Real mass) {
    const auto massStatus = body.SetMass(mass);
    const auto inertiaStatus = body.SetInertiaTensor(IdentityTensor());
    return massStatus == RigidBodyStatus::OK && inertiaStatus == RigidBodyStatus::OK;
}

std::array<double, 3> ExtractColumn(const std::array<Real, 9>& matrix, int column) {
    return {
        matrix[0 + column].Value(),
        matrix[3 + column].Value(),
        matrix[6 + column].Value()
    };
}

} // namespace

TEST(PhysicsWorldTests, FreeFallMatchesAnalyticalSolution) {
    PhysicsWorld world;
    auto body = std::make_unique<RigidBody>();
    ASSERT_TRUE(ConfigureDynamicBody(*body, Real{1.0}));
    ASSERT_TRUE(world.AddRigidBody(body.get()));

    const Real dt{0.01};
    constexpr int steps = 200;
    for (int i = 0; i < steps; ++i) {
        world.Simulate(dt);
    }

    const auto position = body->GetPosition();
    const auto velocity = body->GetVelocity();
    const double totalTime = steps * dt.Value();
    const double expectedY = -0.5 * G.Value() * totalTime * totalTime;
    const double expectedVy = -G.Value() * totalTime;

    EXPECT_NEAR(position[1].Value(), expectedY, 1e-2);
    EXPECT_NEAR(velocity[1].Value(), expectedVy, 1e-2);
}

TEST(PhysicsWorldTests, OrientationRemainsOrthonormalUnderRotation) {
    PhysicsWorld world;
    auto body = std::make_unique<RigidBody>();
    ASSERT_TRUE(ConfigureDynamicBody(*body, Real{2.0}));
    ASSERT_TRUE(world.AddRigidBody(body.get()));

    const std::array<Real, 3> initialAngularVelocity{
        Real{0.0}, Real{5.0}, Real{0.5}
    };
    ASSERT_EQ(body->SetAngularVelocity(initialAngularVelocity), RigidBodyStatus::OK);

    const Real dt{0.005};
    constexpr int steps = 400;
    for (int i = 0; i < steps; ++i) {
        world.Simulate(dt);
    }

    const auto orientation = body->GetOrientationMatrix();
    const auto col0 = ExtractColumn(orientation, 0);
    const auto col1 = ExtractColumn(orientation, 1);
    const auto col2 = ExtractColumn(orientation, 2);

    const auto length = [](const std::array<double, 3>& c) {
        return std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    };
    const auto dot = [](const std::array<double, 3>& a, const std::array<double, 3>& b) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    };

    EXPECT_NEAR(length(col0), 1.0, 5e-3);
    EXPECT_NEAR(length(col1), 1.0, 5e-3);
    EXPECT_NEAR(length(col2), 1.0, 5e-3);
    EXPECT_NEAR(dot(col0, col1), 0.0, 5e-3);
    EXPECT_NEAR(dot(col0, col2), 0.0, 5e-3);
    EXPECT_NEAR(dot(col1, col2), 0.0, 5e-3);
}

TEST(PhysicsWorldTests, TotalMechanicalEnergyRemainsStableInFreeFall) {
    PhysicsWorld world;
    auto body = std::make_unique<RigidBody>();
    ASSERT_TRUE(ConfigureDynamicBody(*body, Real{1.0}));
    ASSERT_TRUE(world.AddRigidBody(body.get()));

    const Real dt{0.01};
    constexpr int steps = 200;
    for (int i = 0; i < steps; ++i) {
        world.Simulate(dt);
    }

    const auto position = body->GetPosition();
    const auto velocity = body->GetVelocity();
    const double mass = body->GetMass().Value();
    const double vy = velocity[1].Value();
    const double kinetic = 0.5 * mass * (vy * vy);
    const double potential = mass * G.Value() * position[1].Value();

    EXPECT_NEAR(kinetic + potential, 0.0, 1e-2);
}

TEST(PhysicsWorldTests, DeterministicSteppingProducesIdenticalResults) {
    PhysicsWorld worldA;
    PhysicsWorld worldB;

    auto bodyA = std::make_unique<RigidBody>();
    auto bodyB = std::make_unique<RigidBody>();

    ASSERT_TRUE(ConfigureDynamicBody(*bodyA, Real{3.0}));
    ASSERT_TRUE(ConfigureDynamicBody(*bodyB, Real{3.0}));

    ASSERT_TRUE(worldA.AddRigidBody(bodyA.get()));
    ASSERT_TRUE(worldB.AddRigidBody(bodyB.get()));

    const Real dt{0.008};
    constexpr int steps = 512;
    for (int i = 0; i < steps; ++i) {
        worldA.Simulate(dt);
        worldB.Simulate(dt);
    }

    const auto posA = bodyA->GetPosition();
    const auto posB = bodyB->GetPosition();
    const auto velA = bodyA->GetVelocity();
    const auto velB = bodyB->GetVelocity();

    EXPECT_DOUBLE_EQ(posA[1].Value(), posB[1].Value());
    EXPECT_DOUBLE_EQ(velA[1].Value(), velB[1].Value());
}
