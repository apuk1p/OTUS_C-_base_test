#pragma once

#include "../included/istatistics.hpp"
#include <limits>

class Min : public IStatistics {
public:
	Min() : m_min{0} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};