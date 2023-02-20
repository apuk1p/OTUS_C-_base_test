#pragma once

#include "../included/istatistics.hpp"
#include "../included/mean.hpp"
#include <vector>

class StdClass : public IStatistics {
public:
	StdClass() = default;

	void update(double next) override;

	double eval() const override;

	const char * name() const override {
		return "StdClass";
	}
 
private:
	std::vector<double> vect;
	Mean mean;
};