#pragma once

#include "domain/Client.hpp"
#include "domain/ScenarioConstraints.hpp"
#include "domain/TrafficLightNode.hpp"
#include "domain/VehicleMission.hpp"
#include "domain/VehicleStateReport.hpp"

#include <algorithm>
#include <cstddef>
#include <vector>

namespace vws
{

    class WorldState
    {
    public:
        void add_client(const Client &client)
        {
            clients_.push_back(client);
        }

        std::size_t client_count() const
        {
            return clients_.size();
        }

        const std::vector<Client> &clients() const
        {
            return clients_;
        }

        void add_mission(const VehicleMission &mission)
        {
            missions_.push_back(mission);
        }

        std::size_t mission_count() const
        {
            return missions_.size();
        }

        const std::vector<VehicleMission> &missions() const
        {
            return missions_;
        }

        void upsert_vehicle_state(const VehicleStateReport &report)
        {
            const auto it = std::find_if(
                vehicle_states_.begin(),
                vehicle_states_.end(),
                [&](const VehicleStateReport &state)
                {
                    return state.vehicle_id == report.vehicle_id;
                });

            if (it != vehicle_states_.end())
            {
                *it = report;
                return;
            }

            vehicle_states_.push_back(report);
        }

        std::size_t vehicle_state_count() const
        {
            return vehicle_states_.size();
        }

        const std::vector<VehicleStateReport> &vehicle_states() const
        {
            return vehicle_states_;
        }

        void add_traffic_light(const TrafficLightNode &node)
        {
            traffic_lights_.push_back(node);
        }

        std::size_t traffic_light_count() const
        {
            return traffic_lights_.size();
        }

        const std::vector<TrafficLightNode> &traffic_lights() const
        {
            return traffic_lights_;
        }

        std::vector<TrafficLightNode> &traffic_lights_mutable()
        {
            return traffic_lights_;
        }

        void set_constraints(const ScenarioConstraints &constraints)
        {
            constraints_ = constraints;
            has_constraints_ = true;
        }

        bool has_constraints() const
        {
            return has_constraints_;
        }

        const ScenarioConstraints &constraints() const
        {
            return constraints_;
        }

    private:
        std::vector<Client> clients_;
        std::vector<VehicleMission> missions_;
        std::vector<VehicleStateReport> vehicle_states_;
        std::vector<TrafficLightNode> traffic_lights_;
        ScenarioConstraints constraints_;
        bool has_constraints_ = false;
    };

} // namespace vws
