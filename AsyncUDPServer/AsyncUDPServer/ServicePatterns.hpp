#ifndef SERVICEPATTERNS
#define SERVICEPATTERNS

#include <iostream>
#include <string>
#include <fstream>
#include "exoSolver.hpp"
#include "exoActuator.hpp"

using namespace std;

namespace pattern
{

	class ServicePatterns : public exoSolver
	{
	public:
		//double Angle[10];

		std::string Name;

		//------------------------------------------------------------------------------
		ServicePatterns()
		{
			SolverStartTime = 0;
			isRun = false;
		}
		//------------------------------------------------------------------------------
		void OpenPatterns(std::string file_)
		{
			std::ifstream file(file_);
			std::string line;

			int count_point = 0;

			while (std::getline(file, line))
			{
				if (line == "//Time:")
				{
					std::getline(file, line);
					ArrayData[count_point][0] = std::stoi(line);
				}
				if (line == "//Angles:")
				{
					for (int j = 1; j < 11; j++)
					{
						std::getline(file, line);
						ArrayData[count_point][j] = std::stoi(line);
					}
					count_point++;
				}
			}

		}
		//---------------------------------------------------------------
		double GetLine(double y1, double y2, double t1, double t2, double t)
		{
			double k = (y1 - y2) / (t1 - t2);
			double c = y1 - (k * t1);
			return k * t + c;
		}
		//---------------------------------------------------------------
		void StartPattern()
		{
			isRun = true;
		}
		//---------------------------------------------------------------
		void StopPattern()
		{
			isRun = false;
			SolverStartTime = 0;
		}
		//---------------------------------------------------------------
		void GetCurrentAngles(exoActuator actuators[], const int size, uint32_t ttime)
		{
			if (isRun)
			{
				if (SolverStartTime == 0) SolverStartTime = ttime;

				uint32_t SolverTime = ttime - SolverStartTime;

				for (int i = 0; i < 23; i++)
				{
					if (SolverTime >= ArrayData[22][0]) StopPattern();

					if ((SolverTime >= ArrayData[i][0]) && (SolverTime <= ArrayData[i + 1][0]))
					{
						for (int j = 0; j < size; j++)
						{
							actuators[j].SetTargetPosition(GetLine(ArrayData[i][j + 1], ArrayData[i + 1][j + 1], ArrayData[i][0], ArrayData[i + 1][0], SolverTime));
						}
						break;
					}
				}

			}			

		}
		//-------------------------------------------------------------------
		~ServicePatterns()
		{

		}

	private:
		int ArrayData[23][11];

		uint32_t SolverStartTime;
		bool isRun;

		

	};


}

/////////////////////////////////////////////////////////////////////////////////////////////
#endif
