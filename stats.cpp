#include "stats.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <limits>

namespace Statistics {
    Stats ComputeStatistics(const std::vector<float>& readings) {
    //Implement statistics here
    Stats stats;
    // Filter out NaN values
    std::vector<float> validReadings;
    for (float value : readings) {
        if (!std::isnan(value)) {
            validReadings.push_back(value);
        }
    }

    // Check for empty, out-of-range, or all NaN
    if (validReadings.empty()) {
        stats.average = NAN;
        stats.max = NAN;
        stats.min = NAN;
        return stats;
    }

    for (float value : validReadings) {
        if (value < 0.0f || value > 1000.0f) {
            stats.average = NAN;
            stats.max = NAN;
            stats.min = NAN;
            return stats;
        }
    }

    stats.average = std::accumulate(validReadings.begin(), validReadings.end(), 0.0f) / validReadings.size();
    stats.max = *std::max_element(validReadings.begin(), validReadings.end());
    stats.min = *std::min_element(validReadings.begin(), validReadings.end());
    return stats;
  } 
}
