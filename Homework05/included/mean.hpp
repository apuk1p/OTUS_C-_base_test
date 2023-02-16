#pragma once

#include "../included/istatistics.hpp"

class Mean : public IStatistics {
public:
	Mean() : m_mean{0.0}, strLength{0} {
	}

	void update(double next) override {
		m_mean += next;
		strLength++;
	}

	double eval() const override {
		return m_mean/strLength;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_mean;
	int strLength;
};