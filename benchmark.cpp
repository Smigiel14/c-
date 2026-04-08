#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <list>
class TimeMeasurement
{
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	
public:
	TimeMeasurement(std::string _name) : name(_name) {
		start = std::chrono::high_resolution_clock::now();
	}
	
	~TimeMeasurement() {
		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << name << ": " << duration.count() *1000<< " msec" << std::endl;
	}
};

/* Przykład użycia: */
int main()
{
    //pierwsze
    {
        std::vector<int> v;
        TimeMeasurement t("vector");
        for (int i = 0; i < 100000; i++) {
                v.insert(v.begin(), 123456);
            }
    }

    {
        std::list<int> l;
        TimeMeasurement t("lista");
        for (int i = 0; i < 100000; i++) {
                l.insert(l.begin(), 123456);
            }
    }
    //drugie

        std::vector<int> v;
        for (int i = 0; i < 100000; i++){
            v.push_back(1);
        }
    {
        TimeMeasurement t("elementy vector");
        int sum=0;
        for (const int &it : v) {
            sum += it;
        }
    }

        std::list<int> l;
        for (int i = 0; i < 100000; i++){
            l.push_back(1);
        }

    {
        TimeMeasurement t("elementy list");
        int sum=0;
        for (const int &it : l) {
            sum += it;
        }
    }


    
	/* Wydzielamy blok kodu */
	{
		TimeMeasurement t("Krótka pętla");
		/* Tutaj wywołany zostanie automatycznie konstruktor TimeMeasurement */
		for (int i = 0; i < 1000000; i++);
		/* Tutaj wywołany zostanie automatycznie destruktor ~TimeMeasurement */
	}

	/* Wydzielamy drugi blok kodu */
	{
		TimeMeasurement t("Długa pętla");
		/* Tutaj wywołany zostanie automatycznie konstruktor TimeMeasurement */
		for (int i = 0; i < 200000000; i++);
		/* Tutaj wywołany zostanie automatycznie destruktor ~TimeMeasurement */
	}

	return 0;
}