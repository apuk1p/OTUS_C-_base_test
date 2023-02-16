#pragma once

#include "../included/istatistics.hpp"
#include <vector>

class StdClass : public IStatistics {
public:
	StdClass() = default;

	void update(double next) override;

	double eval() const override;

	void calc();

	const char * name() const override {
		return "StdClass";
	}

private:
	std::vector<double> vect{0};
	double m_std{0};
	double mean_{0};
};