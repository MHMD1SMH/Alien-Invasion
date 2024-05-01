#pragma once
class Time
{
private:
	//Join Time
	int Tj;
	//first attaced time -> first time this unit got shot
	int Ta;
	//timestep this unit got destroyed and dismissed from the battle 
	int Td;
public:
	void setTj(int n) { Tj = n; }
	void setTa(int n) { Ta = n; }
	void setTd(int n) { Td = n; }

	int getTj() const { return Tj; }
	int getTa() const { return Ta; }
	int getTd() const { return Td; }

	//first Attack delay =Ta - Tj
	int getDf() { return Ta - Tj; }
	//Destruction Delay = Td - Ta
	int getDd() { return Td - Ta; }
	//Battle time = Td - Tj
	int getDb() { return Td - Tj; }
};

