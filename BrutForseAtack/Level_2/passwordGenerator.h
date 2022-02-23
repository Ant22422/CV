#pragma once
#include "forse.h"
#include <vector>
#include <iostream>
#include <iostream>


class passwordGenerator
{
public:
	void SetPacket(int& val, std::string& startOfReport) {
		m_packet = GetGuess(val, startOfReport, m_counterGetGuess, &m_positionPass[0]);
		m_counterGetGuess++;
	}
	std::vector<std::string> GetPacket() {
		return m_packet;
	}
	int GetCounter() {
		return m_counterGetGuess;
	}
	int* GetPositionPass() {
		return &m_positionPass[0];
	}
private:
	int m_positionPass[4] = { 0 };
	std::vector<std::string> m_packet;
	int m_counterGetGuess = 0;
};

