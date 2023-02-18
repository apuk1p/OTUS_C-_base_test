#pragma once

#include "../included/istatistics.hpp"
#include <vector>

class Pct90 : public IStatistics {
public:
	Pct90() = default;

	void update(double next) override;

	double eval() const override;

	//~StdClass() override {};

	const char * name() const override {
		return "Pct90";
	}
	void calc();
 
private:
	std::vector<double> vect;
	double m_pct90{0};
};