#pragma once
class Time
{
private:
	//Join Time
	int Tj =0;
	//first attaced time -> first time this unit got shot
	int Ta = -1;
	//timestep this unit got destroyed and dismissed from the battle 
	int Td = -1;
	// time to join heal 
	int Th;
public:
	void setTj(int n) { Tj = n; }
	void setTa(int n) {
		if (Ta == -1)
			Ta = n;
	}
	void setTd(int n) {
		if (Ta == -1)
			Td = n;
	}
	void setTh(int n) {
			Th = n;
	}

	int getTj() const { return Tj; }
	int getTa() const { return Ta; }
	int getTd() const { return Td; }
	int getTh() const { return Th; }

	//first Attack delay =Ta - Tj
	int getDf() const { return Ta - Tj; }
	//Destruction Delay = Td - Ta
	int getDd() const { return Td - Ta; }
	//Battle time = Td - Tj
	int getDb() const { return Td - Tj; }
};

