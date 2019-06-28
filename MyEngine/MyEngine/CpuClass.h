#pragma once
#pragma comment(lib, "pdh.lib")
#include <pdh.h>
class CpuClass
{
public:
	CpuClass();
	CpuClass(const CpuClass& orther);
	virtual ~CpuClass();

	void Initialize();
	void Shutdown();
	void Frame();
	int GetCpuPercentage();

private:
	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;
};

