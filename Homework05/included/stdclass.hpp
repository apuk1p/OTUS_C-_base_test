#pragma once

#include "../included/istatistics.hpp"
#include <vector>

class StdClass : public IStatistics {
public:
	StdClass() = default;

	void update(double next) override;

	double eval() const override;

	~StdClass() override {};

	const char * name() const override {
		return "StdClass";
	}
	void calc();
 
private:
	std::vector<double> vect;
	double m_std{0};
	double sum_{0};
	double mean_{0};
};