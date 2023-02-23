#pragma once

#include "../included/istatistics.hpp"

class Mean : public IStatistics {
public:
	Mean() : m_mean{0.0}, numLength{0} {
	}

	void update(double next) override {
		m_mean += next;
		numLength++;
	}

	double eval() const override {
		return m_mean/numLength;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_mean;
	size_t numLength;
};